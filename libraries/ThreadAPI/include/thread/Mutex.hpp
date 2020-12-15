/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
/* Copyright 2016 tgil All Rights Reserved */

#ifndef THREADAPI_THREAD_MUTEX_HPP_
#define THREADAPI_THREAD_MUTEX_HPP_

#include "api/api.hpp"
#include "var/Array.hpp"

#include "chrono/ClockTime.hpp"

#include <sdk/types.h>
#include <pthread.h>

#if defined __android
#define PTHREAD_PRIO_PROTECT PTHREAD_PRIO_NONE
#endif

namespace thread {

/*! \brief Mutex Class
 * \details This class holds a Mutex used with
 * multi-threaded applications.
 *
 */
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
    ~Guard() {
      if (m_mutex) {
        m_mutex->unlock();
      }
    }

  private:
    Mutex *m_mutex;
  };

private:
  pthread_mutex_t m_mutex;
  Mutex &set_attributes(const Attributes &attr);
};

class SyncPoint {
public:
  SyncPoint(const chrono::MicroTime period = 10_milliseconds)
      : m_period(period) {}
  void wait_here() {
    Mutex::Guard mg0(m_mutex_pair.at(0));
    wait_until_locked(m_mutex_pair.at(1));
  }

  void wait_there() {
    wait_until_locked(m_mutex_pair.at(0));
    Mutex::Guard mg1(m_mutex_pair.at(1));
    { Mutex::Guard mg0(m_mutex_pair.at(0)); }
  }

private:
  var::Array<Mutex, 2> m_mutex_pair;
  chrono::MicroTime m_period = 10_milliseconds;

  void wait_until_locked(Mutex &mutex) {
    while (mutex.try_lock() == true) {
      mutex.unlock();
      chrono::wait(m_period);
    }
  }

  void wait_for_synchronization(Mutex &mine, Mutex &theirs) {
    mine.lock();
    while (theirs.try_lock() == true) {
      theirs.unlock();
      chrono::wait(m_period);
    }
    mine.unlock();
  }
};

} // namespace thread

#endif /* THREADAPI_THREAD_MUTEX_HPP_ */
