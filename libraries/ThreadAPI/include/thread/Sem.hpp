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

  SemaphoreObject(const SemaphoreObject & a) = delete;
  SemaphoreObject& operator=(const SemaphoreObject & a) = delete;

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

  SemaphoreObject(SemaphoreObject && a) noexcept {
    std::swap(m_handle, a.m_handle);
  }
  SemaphoreObject& operator=(SemaphoreObject && a) noexcept {
    std::swap(m_handle, a.m_handle);
    return *this;
  }

private:
  friend class UnnamedSemaphore;
  friend class Semaphore;
  sem_t *m_handle = reinterpret_cast<sem_t *>(SEM_FAILED);
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
  UnnamedSemaphore(const UnnamedSemaphore & a) = delete;
  UnnamedSemaphore& operator=(const UnnamedSemaphore & a) = delete;
  UnnamedSemaphore(UnnamedSemaphore && a) noexcept {
    std::swap(m_sem, a.m_sem);
  }
  UnnamedSemaphore& operator=(UnnamedSemaphore && a) noexcept {
    std::swap(m_sem, a.m_sem);
    return *this;
  }
  ~UnnamedSemaphore();

private:
  sem_t m_sem{};
};

class Semaphore : public SemAccess<Semaphore> {
public:
  enum class IsExclusive { no, yes };

  Semaphore(const Semaphore &value) = delete;
  Semaphore &operator=(const Semaphore &value) = delete;
  Semaphore(Semaphore &&value) noexcept {
    m_name = value.m_name;
  }
  Semaphore &operator=(Semaphore &&value) noexcept {
    m_name = value.m_name;
    return *this;
  }

  //get access to an existing named semaphore
  explicit Semaphore(var::StringView name);

  //create a named semaphore
  Semaphore(
    int value,
    IsExclusive is_exclusive,
    var::StringView name,
    fs::Permissions perms = fs::Permissions(0666));

  ~Semaphore();

  const Semaphore &unlink() const;
  Semaphore &unlink() { return API_CONST_CAST_SELF(Semaphore, unlink); }
  static void unlink(var::StringView name);

private:
  var::KeyString m_name;

  void
  open(int value, var::StringView name, int o_flags, fs::Permissions perms);
};

} // namespace thread

#endif /* THREADAPI_THREAD_SEM_HPP_ */
