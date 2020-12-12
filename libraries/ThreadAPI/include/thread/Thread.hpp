/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.

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

  Thread(const Construct &options, const Attributes &attributes = Attributes());
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
  bool is_valid() const;

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

  Thread &set_cancel_state(CancelState cancel_state);

  Thread &cancel();

  bool is_running() const;

  /*! \details Returns the thread ID of the calling thread. */
  static pthread_t self() { return pthread_self(); }

  const Thread &kill(int signal_number) const {
    API_RETURN_VALUE_IF_ERROR(*this);
    API_SYSTEM_CALL("", pthread_kill(id(), signal_number));
    return *this;
  }

  Thread &join(void **value = nullptr);

  bool is_joinable() const { return is_valid(); }

  const api::Error *execution_context_error() const {
    return m_execution_context_error;
  }

private:
  enum thread_flags {
    id_completed = static_cast<u32>(-3),
    id_error /*! ID is an error */ = static_cast<u32>(-2),
    id_ready = 1
  };

  static void *handle_thread(void *args);
  volatile function_t m_function;
  void *m_argument;
  const api::Error *m_execution_context_error = nullptr;

#if defined __link
  u32 m_private_context;
  pthread_t m_id = {0};
#define THREADAPI_STATUS_ID m_private_context
#else
  pthread_t m_id = 0;
#define THREADAPI_STATUS_ID m_id
#endif

  void swap(Thread &&a) {
    std::swap(m_id, a.m_id);
#if defined __link
    std::swap(m_private_context, a.m_private_context);
#endif
  }

  int get_sched_parameters(int &policy, int &priority) const;

  void set_id_error() { THREADAPI_STATUS_ID = id_error; }
  void set_id_completed() { THREADAPI_STATUS_ID = id_completed; }
  void set_id_ready() {
#if defined __link
    THREADAPI_STATUS_ID = id_ready;
#endif
  }

  bool is_id_ready() const { return THREADAPI_STATUS_ID > 0; }
  bool is_id_error() const { return THREADAPI_STATUS_ID == id_error; }
  bool is_id_completed() const { return THREADAPI_STATUS_ID == id_completed; }
};

} // namespace thread

#endif /* THREADAPI_THREAD_THREAD_HPP */
