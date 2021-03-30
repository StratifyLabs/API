// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef THREADAPI_THREAD_MUTEX_HPP_
#define THREADAPI_THREAD_MUTEX_HPP_

#include <pthread.h>

#include "api/api.hpp"
#include "var/Array.hpp"

#include "chrono/ClockTime.hpp"

#if defined __android
#define PTHREAD_PRIO_PROTECT PTHREAD_PRIO_NONE
#endif

namespace thread {

class Cond;

class Mutex : public api::ExecutionContext {
public:
  enum class Type {
    normal = PTHREAD_MUTEX_NORMAL,
    recursive = PTHREAD_MUTEX_RECURSIVE
  };

  enum class Protocol {
    priority_none = PTHREAD_PRIO_NONE,
    priority_inherit = PTHREAD_PRIO_INHERIT,
    priority_protect = PTHREAD_PRIO_PROTECT,
  };

  enum class ProcessShared {
    shared = PTHREAD_PROCESS_SHARED,
    private_ = PTHREAD_PROCESS_PRIVATE
  };

  class Attributes : public api::ExecutionContext {
  public:
    Attributes();
    explicit Attributes(const pthread_mutexattr_t &mutexattr)
        : m_item(mutexattr) {}

    ~Attributes();

    API_NO_DISCARD bool is_valid() const {
#if defined __link
      return m_is_valid;
#else
      return m_item.is_initialized != 0;
#endif
    }

    Attributes &set_priority_ceiling(int ceiling);
    Attributes &set_protocol(Protocol value);
    Attributes &set_process_shared(ProcessShared process_shared);
    Attributes &set_type(Type value);
    API_NO_DISCARD int get_priority_ceiling() const;
    API_NO_DISCARD Protocol get_protocol() const;
    API_NO_DISCARD Type get_type() const;
    API_NO_DISCARD ProcessShared get_process_shared() const;

  private:
    friend class Mutex;
    void invalidate() {
#if defined __link
      m_is_valid = false;
#else
      m_item.is_initialized = 0;
#endif
    }

    void validate() {
#if defined __link
      m_is_valid = true;
#else
#endif
    }
    pthread_mutexattr_t m_item;
#if defined __link
    bool m_is_valid;
#endif
  };

  Mutex();
  explicit Mutex(const Attributes &attr);
  ~Mutex();

  Mutex &lock();

#if !defined __link
  Mutex &lock_timed(const chrono::ClockTime &clock_time);
#endif

  API_NO_DISCARD bool try_lock();
  Mutex &unlock();

  class Guard {
  public:
    explicit Guard(Mutex *mutex) : m_mutex(mutex) {
      if (mutex) {
        mutex->lock();
      }
    }
    explicit Guard(Mutex &mutex) : m_mutex(&mutex) { mutex.lock(); }

    Guard(Mutex &mutex, void *context, void (*execute)(void *context))
        : m_mutex(&mutex) {
      mutex.lock();
      execute(context);
    }

    ~Guard() {
      if (m_mutex) {
        m_mutex->unlock();
      }
    }

  private:
    Mutex *m_mutex;
  };

  using Scope = Guard;

private:
  friend class Cond;
  pthread_mutex_t m_mutex;
  Mutex &set_attributes(const Attributes &attr);
};


} // namespace thread

#endif /* THREADAPI_THREAD_MUTEX_HPP_ */
