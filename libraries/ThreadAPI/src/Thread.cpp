// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#include "thread/Thread.hpp"
#include "chrono.hpp"
#include "thread/Mutex.hpp"
#include "thread/Cond.hpp"

#include <cstdio>
#include <errno.h>
using namespace thread;

Thread::Attributes::Attributes() {
#if defined __win32
  return;
#endif
  API_RETURN_IF_ERROR();
  API_SYSTEM_CALL("", pthread_attr_init(&m_pthread_attr));
  set_inherit_sched(IsInherit::yes);
  set_stack_size(4096);
  set_detach_state(DetachState::detached);
  set_sched_policy(Sched::Policy::other);
  set_sched_priority(Sched::get_priority_min(Sched::Policy::other));
}

Thread::Attributes::~Attributes() { pthread_attr_destroy(&m_pthread_attr); }

Thread::Attributes &Thread::Attributes::set_stack_size(size_t value) {
#if defined __win32
  return *this;
#endif
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
#if defined __win32
  return *this;
#endif
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL("", pthread_attr_setdetachstate(&m_pthread_attr,
                                                  static_cast<int>(value)));
  return *this;
}

Thread::DetachState Thread::Attributes::get_detach_state() const {
  API_RETURN_VALUE_IF_ERROR(DetachState::detached);
  int detach_state = 0;
  API_SYSTEM_CALL("",
                  pthread_attr_getdetachstate(&m_pthread_attr, &detach_state));
  return static_cast<DetachState>(detach_state);
}

Thread::Attributes &Thread::Attributes::set_inherit_sched(IsInherit value) {
#if defined __win32
  return *this;
#endif
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL("", pthread_attr_setinheritsched(&m_pthread_attr,
                                                   static_cast<int>(value)));
  return *this;
}
Thread::IsInherit Thread::Attributes::get_inherit_sched() const {
  API_RETURN_VALUE_IF_ERROR(IsInherit::yes);
  int inherit_sched = 0;
  API_SYSTEM_CALL("",
                  pthread_attr_getinheritsched(&m_pthread_attr, &inherit_sched));
  return static_cast<IsInherit>(inherit_sched);
}

Thread::Attributes &Thread::Attributes::set_scope(ContentionScope value) {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL(
      "", pthread_attr_setscope(&m_pthread_attr, static_cast<int>(value)));
  return *this;
}

Thread::ContentionScope Thread::Attributes::get_scope() const {
  API_RETURN_VALUE_IF_ERROR(ContentionScope::process);
  int value = 0;
  API_SYSTEM_CALL("", pthread_attr_getdetachstate(&m_pthread_attr, &value));
  return static_cast<ContentionScope>(value);
}

Thread::Attributes &Thread::Attributes::set_sched_priority(int priority) {
#if defined __win32
  return *this;
#endif
  API_RETURN_VALUE_IF_ERROR(*this);
  struct sched_param param = {};
  param.sched_priority = priority;
  API_SYSTEM_CALL("", pthread_attr_setschedparam(&m_pthread_attr, &param));
  set_inherit_sched(IsInherit::no);
  return *this;
}

Thread::Attributes &Thread::Attributes::set_sched_policy(Sched::Policy value) {
#if defined __win32
  return *this;
#endif
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL("", pthread_attr_setschedpolicy(&m_pthread_attr,
                                                  static_cast<int>(value)));
  set_inherit_sched(IsInherit::no);
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
  struct sched_param param = {};
  API_SYSTEM_CALL("", pthread_attr_getschedparam(&m_pthread_attr, &param));
  return param.sched_priority;
}

Thread::Thread(const Attributes &attributes, const Construct &options) {
  API_RETURN_IF_ERROR();
  construct(attributes, options);
}

Thread::Thread(const Construct &options) {
  API_RETURN_IF_ERROR();
  construct(Attributes(), options);
}

struct StartUp {
  volatile Thread::function_t function = nullptr;
  void *argument = nullptr;
};

void Thread::construct(const Attributes &attributes, const Construct & options){
  API_ASSERT(options.function() != nullptr);

  auto * startup = new StartUp{ .function = options.function(), .argument = options.argument() };

  // First create the thread
  int result =
    API_SYSTEM_CALL("", pthread_create(&m_id, &attributes.m_pthread_attr,
                                       handle_thread, startup));

  if (result < 0) {
    m_state = State::error;
    delete startup;
  } else {
    m_state = attributes.get_detach_state() == DetachState::joinable
                ? State::joinable
                : State::detached;
  }

}

void *Thread::handle_thread(void *args) {
  auto *startup = reinterpret_cast<StartUp *>(args);

  function_t function = startup->function;
  void *argument = startup->argument;
  void *result = function(argument);
  delete startup;
  free_context();
  return result;
}


Thread::~Thread() {
  api::ErrorGuard error_guard;
  if (is_joinable()) {
    API_RESET_ERROR();
    cancel();
    API_RESET_ERROR();
    join();
  }
}

Thread &Thread::set_sched_parameters(Sched::Policy policy, int priority) {
  API_RETURN_VALUE_IF_ERROR(*this);
  struct sched_param param = {};
  param.sched_priority = priority;
  API_SYSTEM_CALL(
      "", pthread_setschedparam(id(), static_cast<int>(policy), &param));
  return *this;
}

Sched::Policy Thread::get_sched_policy() const {
  int policy = 0;
  int priority = 0;
  get_sched_parameters(policy, priority);
  return Sched::Policy(policy);
}

int Thread::get_sched_priority() const {
  int policy = 0;
  int priority = 0;
  get_sched_parameters(policy, priority);
  return priority;
}

int Thread::get_sched_parameters(int &policy, int &priority) const {
  API_RETURN_VALUE_IF_ERROR(-1);
  API_ASSERT(is_valid());
  struct sched_param param = {};
  int result =
      API_SYSTEM_CALL("", pthread_getschedparam(id(), &policy, &param));
  priority = param.sched_priority;
  return result;
}

bool Thread::is_valid() const {
  return (m_state == State::joinable) || (m_state == State::detached);
}

const Thread &Thread::cancel() const {
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


Thread::CancelType Thread::set_cancel_type(CancelType cancel_type) {
  API_RETURN_VALUE_IF_ERROR(CancelType::deferred);
  int old = int(CancelType::deferred);
  API_SYSTEM_CALL("",
                  pthread_setcanceltype(static_cast<int>(cancel_type), &old));
  return CancelType(old);
}

Thread::CancelState Thread::set_cancel_state(CancelState cancel_state){
  API_RETURN_VALUE_IF_ERROR(CancelState::disable);
  int old = 0;
  API_SYSTEM_CALL("",
                  pthread_setcancelstate(static_cast<int>(cancel_state), &old));
  return CancelState(old);
}

Thread &Thread::join(void **value) {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_ASSERT(is_joinable());

  void *tmp_ptr;
  void **ptr = value == nullptr ? &tmp_ptr : value;

  const int local_result = API_SYSTEM_CALL("", pthread_join(id(), ptr));
  if (local_result == 0) {
    m_state = State::completed;
  }
  return *this;
}
