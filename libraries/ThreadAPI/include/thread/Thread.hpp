// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef THREADAPI_THREAD_THREAD_HPP
#define THREADAPI_THREAD_THREAD_HPP

#include <pthread.h>
#include <csignal>

#include "Sched.hpp"
#include "chrono/ClockTime.hpp"

namespace thread {

class Thread : public api::ExecutionContext {
public:
  enum class DetachState {
    joinable = PTHREAD_CREATE_JOINABLE,
    detached  = PTHREAD_CREATE_DETACHED
  };
  using Policy = Sched::Policy;

  enum class IsInherit {
    no = PTHREAD_EXPLICIT_SCHED,
    yes = PTHREAD_INHERIT_SCHED
  };
  enum class ContentionScope {
    system = PTHREAD_SCOPE_SYSTEM,
    process = PTHREAD_SCOPE_PROCESS
  };
  using Scope = ContentionScope;

  typedef void *(*function_t)(void *);

  class Attributes : public api::ExecutionContext {
  public:
    Attributes();
    ~Attributes();

    Attributes &set_stack_size(size_t value);
    API_NO_DISCARD int get_stack_size() const;


    Attributes &set_detach_state(DetachState value);
    Attributes& set_joinable(){
      return set_detach_state(DetachState::joinable);
    }

    Attributes& set_detached(){
      return set_detach_state(DetachState::detached);
    }

    API_NO_DISCARD DetachState get_detach_state() const;

    Attributes &set_inherit_sched(IsInherit value);
    API_NO_DISCARD IsInherit get_inherit_sched() const;

    Attributes &set_scope(ContentionScope value);
    API_NO_DISCARD ContentionScope get_scope() const;

    Attributes &set_sched_policy(Sched::Policy value);
    Attributes &set_sched_priority(int priority);
    API_NO_DISCARD Sched::Policy get_sched_policy() const;
    API_NO_DISCARD int get_sched_priority() const;

  private:
    friend class Thread;
    pthread_attr_t m_pthread_attr{};
  };

  class Construct {
    API_ACCESS_FUNDAMENTAL(Construct, function_t, function, nullptr);
    API_ACCESS_FUNDAMENTAL(Construct, void *, argument, nullptr);
  };

  Thread() = default;

  // don't allow making copies
  Thread(const Thread &thread) = delete;
  Thread &operator=(const Thread &thread) = delete;

  // allow moving threads
  Thread &operator=(Thread &&a)  noexcept {
    swap(std::move(a));
    return *this;
  }
  Thread(Thread &&a)  noexcept { swap(std::move(a)); }
  Thread &&move() { return std::move(*this); }

  explicit Thread(const Construct &options);
  Thread(const Attributes &attributes, const Construct &options);
  Thread(const Attributes &attributes, void * argument, function_t thread_function){
    construct(attributes, Construct().set_argument(argument).set_function(thread_function));
  }
  Thread(void * argument, function_t thread_function){
    construct(Attributes(), Construct().set_argument(argument).set_function(thread_function));
  }
  ~Thread();

  /*! \details Gets the ID of the thread. */
  API_NO_DISCARD pthread_t id() const { return m_id; }

  /*! \details Returns true if the thread has a valid id.
   *
   * If create() has not been called, this will return false.
   * If there was an error creating the thread, this will
   * also return false;
   *
   */
  API_NO_DISCARD bool is_valid() const;

  enum class CancelType {
    deferred = PTHREAD_CANCEL_DEFERRED,
    asynchronous = PTHREAD_CANCEL_ASYNCHRONOUS
  };

  static CancelType set_cancel_type(CancelType cancel_type);
  enum class CancelState {
    enable = PTHREAD_CANCEL_ENABLE,
    disable = PTHREAD_CANCEL_DISABLE
  };

  Thread &set_sched_parameters(Sched::Policy policy, int priority);
  API_NO_DISCARD Sched::Policy get_sched_policy() const;
  API_NO_DISCARD int get_sched_priority() const;

  static CancelState set_cancel_state(CancelState cancel_state);

  const Thread &cancel() const;
  Thread &cancel() { return API_CONST_CAST_SELF(Thread, cancel); }

  API_NO_DISCARD bool is_running() const;
  API_NO_DISCARD static pthread_t self() { return pthread_self(); }

  const Thread &kill(int signal_number) const {
    API_RETURN_VALUE_IF_ERROR(*this);
    API_SYSTEM_CALL("", pthread_kill(id(), signal_number));
    return *this;
  }

  Thread &join(void **value = nullptr);

  API_NO_DISCARD bool is_joinable() const { return m_state == State::joinable; }

private:
  enum class State { null = 0, completed, error, joinable, detached };

  volatile State m_state = State::null;

  pthread_t m_id = {};

  void swap(Thread &&a) {
    std::swap(m_id, a.m_id);
    std::swap(m_state, a.m_state);
  }

  void construct(const Attributes & attributes, const Construct & options);

  static void *handle_thread(void *args);

  int get_sched_parameters(int &policy, int &priority) const;
};

} // namespace thread

#endif /* THREADAPI_THREAD_THREAD_HPP */
