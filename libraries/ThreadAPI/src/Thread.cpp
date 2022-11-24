// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#include "thread/Thread.hpp"
#include "chrono.hpp"
#include "thread/Cond.hpp"
#include "thread/Mutex.hpp"

#include <cstdio>
using namespace thread;

#if defined __link
#define THREAD_ATTRIBUTES_DEFAULT_STACK_SIZE (512 * 1024)
#else
#define THREAD_ATTRIBUTES_DEFAULT_STACK_SIZE (4096)
#endif

namespace {
struct StartupFunction {
  void *argument = nullptr;
  Thread::function_t function = nullptr;
  Thread::Function thread_function;
};

struct StartUp {
  StartupFunction function;
  Mutex mutex;
  Cond cond = Cond{mutex};
  void *signature = nullptr;
};

void *handle_thread(void *args) {
  auto *startup_pointer = reinterpret_cast<StartUp *>(args);

  auto startup_function = startup_pointer->function;
  startup_pointer->signature = api::Error::get_thread_signature();
  startup_pointer->cond.set_asserted().broadcast();

  void *result = startup_function.function
                   ? startup_function.function(startup_function.argument)
                   : startup_function.thread_function();

  return result;
}

} // namespace

Thread::Attributes::Attributes() {
  API_RETURN_IF_ERROR();
  API_SYSTEM_CALL("", pthread_attr_init(&m_pthread_attr));
  set_inherit_sched(IsInherit::yes);
  set_stack_size(THREAD_ATTRIBUTES_DEFAULT_STACK_SIZE);
  set_detach_state(DetachState::detached);
  set_sched_policy(Sched::Policy::other);
#if !__win32
  const auto minimum_priority = Sched::get_priority_min(Sched::Policy::other);
  set_sched_priority(minimum_priority);
#endif
}

Thread::Attributes::~Attributes() { pthread_attr_destroy(&m_pthread_attr); }

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
    pthread_attr_getinheritsched(&m_pthread_attr, &inherit_sched));
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
#if defined __win32
  // I am not sure if windows implements this
#else
  struct sched_param param = {};
  param.sched_priority = priority;
  API_SYSTEM_CALL("", pthread_attr_setschedparam(&m_pthread_attr, &param));
  set_inherit_sched(IsInherit::no);
#endif
  return *this;
}

Thread::Attributes &Thread::Attributes::set_sched_policy(Sched::Policy value) {
  API_RETURN_VALUE_IF_ERROR(*this);
#if defined __win32
#else
  API_SYSTEM_CALL(
    "",
    pthread_attr_setschedpolicy(&m_pthread_attr, static_cast<int>(value)));
  set_inherit_sched(IsInherit::no);
#endif
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

Thread::Thread(Function &&function) {
  construct(
    Attributes(),
    Construct().set_thread_function(std::forward<Function>(function)));
}

Thread::Thread(const Attributes &attributes, Function &&function) {
  construct(
    attributes,
    Construct().set_thread_function(std::forward<Function>(function)));
}

void Thread::construct(const Attributes &attributes, const Construct &options) {
  API_RETURN_IF_ERROR();
  API_ASSERT(options.function || options.thread_function);

  // this can't be a member of Thread because if thread gets
  // moved the address will be wrong
  // this is deleted in the new thread OR below if creation fails

  auto startup = StartUp{.function{
    .argument = options.argument,
    .function = options.function,
    .thread_function = options.thread_function}};

  // First create the thread
  auto id = pthread_t{};
  int result = API_SYSTEM_CALL(
    "pthread_create",
    pthread_create(&id, &attributes.m_pthread_attr, handle_thread, &startup));
  if (result < 0) {
    context->state = State::error;
  } else {
    startup.cond.wait_until_asserted();
    context->id = id;
    context->signature = startup.signature;
    context->state = attributes.get_detach_state() == DetachState::joinable
                       ? State::joinable
                       : State::detached;
  }
}

void Thread::deleter(Thread::Context *context) {
  api::ErrorScope error_scope;
  if (context->state == State::joinable) {
    API_SYSTEM_CALL("", pthread_cancel(context->id));
    API_RESET_ERROR();
    void *tmp_ptr;
    API_SYSTEM_CALL("", pthread_join(context->id, &tmp_ptr));
  }
  api::ExecutionContext::free_context(context->signature);
}

Thread &Thread::set_sched_parameters(Sched::Policy policy, int priority) {
  API_RETURN_VALUE_IF_ERROR(*this);
  struct sched_param param = {};
  param.sched_priority = priority;
  API_SYSTEM_CALL(
    "",
    pthread_setschedparam(id(), static_cast<int>(policy), &param));
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
  int result
    = API_SYSTEM_CALL("", pthread_getschedparam(id(), &policy, &param));
  priority = param.sched_priority;
  return result;
}

bool Thread::is_valid() const {
  return (context->state == State::joinable)
         || (context->state == State::detached);
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
  API_SYSTEM_CALL(
    "",
    pthread_setcanceltype(static_cast<int>(cancel_type), &old));
  return CancelType(old);
}

Thread::CancelState Thread::set_cancel_state(CancelState cancel_state) {
  API_RETURN_VALUE_IF_ERROR(CancelState::disable);
  int old = 0;
  API_SYSTEM_CALL(
    "",
    pthread_setcancelstate(static_cast<int>(cancel_state), &old));
  return CancelState(old);
}

Thread &Thread::join(void **value) & {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_ASSERT(is_joinable());

  void *tmp_ptr;
  void **ptr = value == nullptr ? &tmp_ptr : value;

  const int local_result = API_SYSTEM_CALL("", pthread_join(id(), ptr));
  if (local_result == 0) {
    context->state = State::completed;
  }
  return *this;
}

const char *Thread::to_cstring(Thread::CancelState value) {
  switch (value) {
  case CancelState::disable:
    return "disable";
  case CancelState::enable:
    return "enable";
  }
  return "unknown";
}

const char *Thread::to_cstring(Thread::CancelType value) {
  switch (value) {
  case CancelType::deferred:
    return "deferred";
  case CancelType::asynchronous:
    return "asynchronous";
  }
  return "unknown";
}

const Thread &Thread::kill(int signal_number) const {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL("", pthread_kill(id(), signal_number));
  return *this;
}
