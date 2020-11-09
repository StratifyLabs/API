/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
// Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc

#include "thread/Thread.hpp"
#include "chrono.hpp"

#include <cstdio>
#include <errno.h>
using namespace thread;

Thread::Attributes::Attributes() {
  API_RETURN_IF_ERROR();
  API_SYSTEM_CALL("", pthread_attr_init(&m_pthread_attr));
  set_inherit_sched(IsInherit::yes);
  set_stack_size(4096);
  set_detach_state(DetachState::detached);
  set_sched_policy(Sched::Policy::other);
  set_sched_priority(Sched::get_priority_min(Sched::Policy::other));
}

Thread::Attributes::~Attributes() {
  API_RETURN_IF_ERROR();
  API_SYSTEM_CALL("", pthread_attr_destroy(&m_pthread_attr));
}

Thread::Attributes &Thread::Attributes::set_stack_size(size_t value) {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL("", pthread_attr_setstacksize(&m_pthread_attr, value));
  return *this;
}

int Thread::Attributes::get_stack_size() const {
  API_RETURN_VALUE_IF_ERROR(-1);
  size_t stack_size = 0;
  API_SYSTEM_CALL("", pthread_attr_getstacksize(&m_pthread_attr, &stack_size));
  return stack_size;
}

Thread::Attributes &Thread::Attributes::set_detach_state(DetachState value) {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL(
    "",
    pthread_attr_setdetachstate(&m_pthread_attr, static_cast<int>(value)));
  return *this;
}

Thread::DetachState Thread::Attributes::get_detach_state() const {
  API_RETURN_VALUE_IF_ERROR(DetachState::detached);
  int detach_state = 0;
  API_SYSTEM_CALL(
    "",
    pthread_attr_getdetachstate(&m_pthread_attr, &detach_state));
  return static_cast<DetachState>(detach_state);
}

Thread::Attributes &Thread::Attributes::set_inherit_sched(IsInherit value) {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL(
    "",
    pthread_attr_setinheritsched(&m_pthread_attr, static_cast<int>(value)));
  return *this;
}
Thread::IsInherit Thread::Attributes::get_inherit_sched() const {
  API_RETURN_VALUE_IF_ERROR(IsInherit::yes);
  int inherit_sched = 0;
  API_SYSTEM_CALL(
    "",
    pthread_attr_getdetachstate(&m_pthread_attr, &inherit_sched));
  return static_cast<IsInherit>(inherit_sched);
}

Thread::Attributes &Thread::Attributes::set_scope(ContentionScope value) {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL(
    "",
    pthread_attr_setscope(&m_pthread_attr, static_cast<int>(value)));
  return *this;
}

Thread::ContentionScope Thread::Attributes::get_scope() const {
  API_RETURN_VALUE_IF_ERROR(ContentionScope::process);
  int value = 0;
  API_SYSTEM_CALL("", pthread_attr_getdetachstate(&m_pthread_attr, &value));
  return static_cast<ContentionScope>(value);
}

Thread::Attributes &Thread::Attributes::set_sched_priority(int priority) {
  API_RETURN_VALUE_IF_ERROR(*this);
  struct sched_param param = {0};
  param.sched_priority = priority;
  API_SYSTEM_CALL("", pthread_attr_setschedparam(&m_pthread_attr, &param));
  return *this;
}

Thread::Attributes &Thread::Attributes::set_sched_policy(Sched::Policy value) {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL(
    "",
    pthread_attr_setschedpolicy(&m_pthread_attr, static_cast<int>(value)));
  return *this;
}

Sched::Policy Thread::Attributes::get_sched_policy() const {
  API_RETURN_VALUE_IF_ERROR(Sched::Policy::round_robin);
  int value = 0;
  API_SYSTEM_CALL("", pthread_attr_getschedpolicy(&m_pthread_attr, &value));
  return static_cast<Policy>(value);
}

int Thread::Attributes::get_sched_priority() const {
  API_RETURN_VALUE_IF_ERROR(-1);
  struct sched_param param = {0};
  API_SYSTEM_CALL("", pthread_attr_getschedparam(&m_pthread_attr, &param));
  return param.sched_priority;
}

void *Thread::handle_thread(void *args) {
  Thread *self = reinterpret_cast<Thread *>(args);
  self->m_execution_context_error = &error();
  function_t function = self->m_function;
  void *argument = self->m_argument;
  self->m_function = nullptr;
  void *result = function(argument);
  free_context();
  return result;
}

Thread::Thread(const Construct &options, const Attributes &attributes) {
  API_RETURN_IF_ERROR();
  API_ASSERT(options.function() != nullptr);

  DetachState detach_state = attributes.get_detach_state();

  m_function = options.function();
  m_argument = options.argument();

  // First create the thread
  int result = API_SYSTEM_CALL(
    "",
    pthread_create(&m_id, &attributes.m_pthread_attr, handle_thread, this));

  if (result < 0) {
    set_id_error();
  } else {
    if (detach_state == DetachState::detached) {
      set_id_completed();
    } else {
      set_id_ready();
    }
  }
}

Thread::~Thread() {
  if (is_joinable()) {
    cancel();
    join();
  } else {
    // for detached threads, the function must be allowed to start before
    // destroying the object
    while (m_function != nullptr) {
      Sched().yield();
    }
  }
}

Thread &Thread::set_sched_parameters(Sched::Policy policy, int priority) {
  API_RETURN_VALUE_IF_ERROR(*this);
  struct sched_param param = {0};
  param.sched_priority = priority;
  API_SYSTEM_CALL(
    "",
    pthread_setschedparam(id(), static_cast<int>(policy), &param));
  return *this;
}

Sched::Policy Thread::get_sched_policy() const {
  int policy;
  int priority;
  get_sched_parameters(policy, priority);
  return static_cast<Sched::Policy>(policy);
}

int Thread::get_sched_priority() const {
  int policy;
  int priority;
  get_sched_parameters(policy, priority);
  return priority;
}

int Thread::get_sched_parameters(int &policy, int &priority) const {
  API_RETURN_VALUE_IF_ERROR(-1);
  API_ASSERT(is_valid());
  struct sched_param param = {0};
  int result
    = API_SYSTEM_CALL("", pthread_getschedparam(id(), &policy, &param));
  priority = param.sched_priority;
  return result;
}

bool Thread::is_valid() const { return is_id_ready(); }

Thread &Thread::cancel() {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL("", pthread_cancel(id()));
  return *this;
}

bool Thread::is_running() const {
  API_RETURN_VALUE_IF_ERROR(false);
  int result = API_SYSTEM_CALL("", pthread_kill(id(), 0));
  if (result == 0) {
    return true;
  }
  API_RESET_ERROR();
  return false;
}

Thread &Thread::set_cancel_type(CancelType cancel_type) {
  API_RETURN_VALUE_IF_ERROR(*this);
  int old = 0;
  API_SYSTEM_CALL(
    "",
    pthread_setcanceltype(static_cast<int>(cancel_type), &old));
  return *this;
}

Thread &Thread::set_cancel_state(CancelState cancel_state) {
  API_RETURN_VALUE_IF_ERROR(*this);
  int old = 0;
  API_SYSTEM_CALL(
    "",
    pthread_setcancelstate(static_cast<int>(cancel_state), &old));
  return *this;
}

Thread &Thread::join(void **value) {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_ASSERT(is_joinable());

  void *tmp_ptr;
  void **ptr = value == nullptr ? &tmp_ptr : value;

  const int local_result = API_SYSTEM_CALL("", pthread_join(id(), ptr));
  if (local_result == 0) {
    set_id_completed();
  }
  return *this;
}
