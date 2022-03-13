#ifndef COND_HPP
#define COND_HPP

#include <pthread.h>

#include <api/api.hpp>

#include "Mutex.hpp"
#include "chrono/ClockTime.hpp"

namespace thread {

class Cond : public api::ExecutionContext {
public:
  using ProcessShared = Mutex::ProcessShared;

  class Attributes : public api::ExecutionContext {
  public:
    Attributes();

    Attributes(const Attributes &) = delete;
    Attributes &operator=(const Attributes &) = delete;
    ~Attributes();
    Attributes(Attributes &&a) noexcept;
    Attributes &operator=(Attributes &&a) noexcept;

    Attributes &set_pshared(ProcessShared pshared);
    Attributes &set_pshared(bool value = true) {
      return set_pshared(
        value ? ProcessShared::shared : ProcessShared::private_);
    }
    API_NO_DISCARD bool get_is_pshared() const;
    API_NO_DISCARD ProcessShared get_pshared() const;

  private:
    friend class Cond;
    pthread_condattr_t m_attributes{};
  };

  explicit Cond(Mutex &mutex);
  Cond(Mutex &mutex, const Attributes &attr);
  Cond(const Cond &Cond) = delete;
  Cond &operator=(const Cond &) = delete;
  Cond(Cond &&a) noexcept : m_mutex(a.m_mutex) { std::swap(m_cond, a.m_cond); }
  Cond &operator=(Cond &&a) noexcept {
    std::swap(m_cond, a.m_cond);
    std::swap(m_mutex, a.m_mutex);
    return *this;
  }
  ~Cond();

  Cond &lock();
  Cond &unlock();
  Cond &wait();
  Cond &wait_timed(const chrono::ClockTime &timeout);
  Cond &signal();
  Cond &broadcast();

  Cond &
  wait_until_asserted(const chrono::ClockTime &timeout = chrono::ClockTime());

  Mutex &mutex() { return *m_mutex; }

  API_NO_DISCARD const Mutex &mutex() const { return *m_mutex; }

private:
  Mutex *m_mutex = nullptr;
  pthread_cond_t m_cond = {};
  API_AB(Cond, asserted, false);
};

} // namespace thread

#endif // COND_HPP
