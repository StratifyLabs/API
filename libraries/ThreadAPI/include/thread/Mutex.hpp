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
      : m_resource({mutexattr}) {}

    API_NO_DISCARD bool is_valid() const {
      return m_resource.value().is_valid();
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

    struct Resource {
      pthread_mutexattr_t mutexattr;
#if defined __link
      bool is_link_valid;
#endif

      void set_valid(bool value = true);
      bool is_valid() const;
    };

    static void deleter(Resource *resource);
    using SystemResource = api::SystemResource<Resource, decltype(&deleter)>;
    static constexpr Resource null_resource{};

    SystemResource m_resource = SystemResource(null_resource);
  };

  Mutex();
  explicit Mutex(const Attributes &attr);
  Mutex &lock();

#if !defined __link
  Mutex &lock_timed(const chrono::ClockTime &clock_time);
#endif

  API_NO_DISCARD bool try_lock();
  Mutex &unlock();

  Mutex &unlock_with_error_check();

  class Scope {
    static void deleter(Mutex *mutex) { mutex->unlock(); }
    api::UniquePointer<Mutex, decltype(&deleter)> m_mutex;

  public:
    explicit Scope(Mutex *mutex) : m_mutex(mutex, &deleter) {
      API_ASSERT(mutex);
      mutex->lock();
    }
    explicit Scope(Mutex &mutex) : m_mutex(&mutex, &deleter) { mutex.lock(); }

    Scope(Mutex &mutex, api::Function<void()> function)
      : m_mutex(&mutex, &deleter) {
      mutex.lock();
      function();
    }
  };

  using Guard = Scope;

private:
  friend class Cond;
  static void deleter(pthread_mutex_t *mutex);
  using MutexSystemResource
    = api::SystemResource<pthread_mutex_t, decltype(&deleter)>;
  MutexSystemResource m_mutex = MutexSystemResource(null_mutex);

  static pthread_mutex_t initialize_mutex(const pthread_mutexattr_t *attr);
  static constexpr pthread_mutex_t null_mutex = {};

  Mutex &set_attributes(const Attributes &attr);
};

} // namespace thread

#endif /* THREADAPI_THREAD_MUTEX_HPP_ */
