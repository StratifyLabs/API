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
  static void cond_deleter(pthread_cond_t * cond);
  static constexpr pthread_cond_t null_condition = {};
  using CondSystemResource = api::SystemResource<pthread_cond_t, decltype(&cond_deleter)>;

  Mutex *m_mutex = nullptr;
  CondSystemResource m_cond = CondSystemResource(null_condition);
  API_AB(Cond, asserted, false);

  static pthread_cond_t initialize_cond(const pthread_condattr_t * attr);
};

} // namespace thread

#endif // COND_HPP
