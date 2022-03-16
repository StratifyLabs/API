// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef THREADAPI_THREAD_SEM_HPP_
#define THREADAPI_THREAD_SEM_HPP_


#include <fcntl.h>
#include <semaphore.h>

#include "chrono/ClockTime.hpp"
#include "fs/FileInfo.hpp"
#include "fs/Path.hpp"

namespace thread {

class SemaphoreObject : public api::ExecutionContext {
public:

  API_NO_DISCARD int get_value() const;

  SemaphoreObject &post();
  SemaphoreObject &wait_timed(const chrono::ClockTime &clock_time);
  SemaphoreObject &timedwait(const chrono::ClockTime &clock_time) {
    return wait_timed(clock_time);
  }

  SemaphoreObject &try_wait();
  SemaphoreObject &wait();

protected:
  SemaphoreObject() = default;

private:
  friend class UnnamedSemaphore;
  friend class Semaphore;

  sem_t * m_handle = SEM_FAILED;
};

template <class Derived> class SemAccess : public SemaphoreObject {
public:
  Derived &post() { return static_cast<Derived &>(SemaphoreObject::post()); }

  Derived &wait_timed(const chrono::ClockTime &clock_time) {
    return static_cast<Derived &>(SemaphoreObject::wait_timed(clock_time));
  }

  Derived &timedwait(const chrono::ClockTime &clock_time) {
    return static_cast<Derived &>(SemaphoreObject::timedwait(clock_time));
  }

  Derived &try_wait() {
    return static_cast<Derived &>(SemaphoreObject::try_wait());
  }

  Derived &wait() { return static_cast<Derived &>(SemaphoreObject::wait()); }
};

class UnnamedSemaphore : public SemAccess<UnnamedSemaphore> {
public:
  enum class ProcessShared { no, yes };

  UnnamedSemaphore(ProcessShared process_shared, unsigned int value);

private:
  static void sem_deleter(sem_t * sem);
  using UnnamedSemaphoreSystemResource = api::SystemResource<sem_t, decltype(&sem_deleter)>;
  UnnamedSemaphoreSystemResource m_sem = UnnamedSemaphoreSystemResource(null_sem);

  static sem_t initialize_semaphore(ProcessShared process_shared, unsigned int value);
  static constexpr sem_t null_sem = {};
};

class Semaphore : public SemAccess<Semaphore> {
public:
  enum class IsExclusive { no, yes };

  //get access to an existing named semaphore
  explicit Semaphore(var::StringView name);

  //create a named semaphore
  Semaphore(
    int value,
    IsExclusive is_exclusive,
    var::StringView name,
    fs::Permissions perms = fs::Permissions(0666));


  const Semaphore &unlink() const;
  Semaphore &unlink() { return API_CONST_CAST_SELF(Semaphore, unlink); }
  static void unlink(var::StringView name);

private:
  var::KeyString m_name;

  static void sem_deleter(sem_t * sem);

  using SemUniquePointer = std::unique_ptr<sem_t, decltype(&sem_deleter)>;
  SemUniquePointer m_unique_pointer = SemUniquePointer(SEM_FAILED, &sem_deleter);

  sem_t *
  open(int value, var::StringView name, int o_flags, fs::Permissions perms);
};

} // namespace thread

#endif /* THREADAPI_THREAD_SEM_HPP_ */
