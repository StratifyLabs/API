// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef THREADAPI_THREAD_THREAD_HPP
#define THREADAPI_THREAD_THREAD_HPP

#include <pthread.h>
#include <signal.h>

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

  class Attributes {
  public:
    Attributes();
    ~Attributes();

    Attributes &set_stack_size(size_t value);
    int get_stack_size() const;

    Attributes &set_detach_state(DetachState value);
    DetachState get_detach_state() const;

    Attributes &set_inherit_sched(IsInherit value);
    IsInherit get_inherit_sched() const;

    Attributes &set_scope(ContentionScope value);
    ContentionScope get_scope() const;

    Attributes &set_sched_policy(Sched::Policy value);
    Attributes &set_sched_priority(int priority);
    Sched::Policy get_sched_policy() const;
    int get_sched_priority() const;

  private:
    friend class Thread;
    pthread_attr_t m_pthread_attr;
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
  Thread &operator=(Thread &&a) {
    swap(std::move(a));
    return *this;
  }
  Thread(Thread &&a) { swap(std::move(a)); }
  Thread &&move() { return std::move(*this); }

  Thread(const Construct &options);
  Thread(const Attributes &attributes, const Construct &options);
  ~Thread();

  /*! \details Gets the ID of the thread. */
  pthread_t id() const { return m_id; }

  /*! \details Returns true if the thread has a valid id.
   *
   * If create() has not been called, this will return false.
   * If there was an error creating the thread, this will
   * also return false;
   *
   */
  volatile bool is_valid() const;

  enum class CancelType {
    deferred = PTHREAD_CANCEL_DEFERRED,
    asynchronous = PTHREAD_CANCEL_ASYNCHRONOUS
  };

  Thread &set_cancel_type(CancelType cancel_type);
  enum class CancelState {
    enable = PTHREAD_CANCEL_ENABLE,
    disable = PTHREAD_CANCEL_DISABLE
  };

  Thread &set_sched_parameters(Sched::Policy policy, int priority);
  Sched::Policy get_sched_policy() const;
  int get_sched_priority() const;

  const Thread &set_cancel_state(CancelState cancel_state) const;
  Thread &set_cancel_state(CancelState cancel_state) {
    return API_CONST_CAST_SELF(Thread, set_cancel_state, cancel_state);
  }

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
  API_NO_DISCARD const api::Error *execution_context_error() const {
    return m_execution_context_error;
  }

private:
  enum class State { null = 0, completed, error, joinable, detached };

  volatile function_t m_function = nullptr;
  void *m_argument = nullptr;
  const api::Error *m_execution_context_error = nullptr;
  volatile State m_state = State::null;

  pthread_t m_id =
#if defined __link
      {0};
#else
      0;
#endif

  void swap(Thread &&a) {
    std::swap(m_id, a.m_id);
    std::swap(m_state, a.m_state);
  }

  static void *handle_thread(void *args);

  int get_sched_parameters(int &policy, int &priority) const;
};

} // namespace thread

#endif /* THREADAPI_THREAD_THREAD_HPP */
