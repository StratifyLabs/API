/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.

#ifndef THREADAPI_THREAD_SEM_HPP_
#define THREADAPI_THREAD_SEM_HPP_


#include <fcntl.h>
#include <semaphore.h>

#include "chrono/ClockTime.hpp"
#include "fs/FileInfo.hpp"
#include "fs/Path.hpp"

namespace thread {

/*! \brief Semaphore Class
 * \details This class is a wrapper for POSIX style semphores.
 *
 * Here is an example using named semaphores.
 *
 * \code
 *
 * #include <sapi/sys.hpp>
 *
 * Sem sem;
 * sem.create("my_semaphore", 10);
 * sem.wait(); //decrement the semaphore value, block if semaphore can't be
 * decremented sem.post(); //increment semaphore value sem.close(); //close
 * reference to semaphore sem.unlink(); //delete semaphore if all references are
 * closed \endcode
 *
 */
class SemaphoreObject : public api::ExecutionContext {
public:
  int get_value() const;

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
  ~UnnamedSemaphore();

private:
  sem_t m_sem;
};

class Semaphore : public SemAccess<Semaphore> {
public:
  enum class IsExclusive { no, yes };

  Semaphore(const Semaphore &value) = delete;
  Semaphore &operator=(const Semaphore &value) = delete;
  Semaphore(Semaphore &&value) = default;
  Semaphore &operator=(Semaphore &&value) = default;

  Semaphore(var::StringView name);

  Semaphore(
    int value,
    IsExclusive is_exclusive,
    var::StringView name,
    fs::Permissions perms = fs::Permissions(0666));

  ~Semaphore();

  /*! \details Deletes a named semaphore.
   *
   * @param name The name of the semaphore
   *
   */
  const Semaphore &unlink() const;
  static void unlink(var::StringView name);

private:
  var::NameString m_name;

  void
  open(int value, var::StringView name, int o_flags, fs::Permissions perms);
  void close();
};

} // namespace thread

#endif /* THREADAPI_THREAD_SEM_HPP_ */
