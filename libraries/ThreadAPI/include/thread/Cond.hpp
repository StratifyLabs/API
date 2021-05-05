#ifndef COND_HPP
#define COND_HPP

#include <pthread.h>

#include <api/api.hpp>

#include "Mutex.hpp"
#include "chrono/ClockTime.hpp"

namespace thread {

class Cond : public api::ExecutionContext {
public:
  class Attributes : public api::ExecutionContext {
  public:
    Attributes() {
      API_RETURN_IF_ERROR();
      API_SYSTEM_CALL("", pthread_condattr_init(&m_attributes));
    }

    ~Attributes() { pthread_condattr_destroy(&m_attributes); }

    Attributes &set_pshared(bool value = true) {
      pthread_condattr_setpshared(&m_attributes, value);
      return *this;
    }

  private:
    friend class Cond;
    pthread_condattr_t m_attributes;
  };

  Cond(Mutex &mutex);
  Cond(Mutex &mutex, const Attributes &attr);
  Cond(const Cond & Cond) = delete;
  Cond& operator=(const Cond&mutex) = delete;
  Cond(Cond && a) : m_mutex(a.m_mutex){
    std::swap(m_cond, a.m_cond);
  }
  Cond& operator=(Cond&&a){
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

private:
  Mutex &m_mutex;
  pthread_cond_t m_cond;
};

} // namespace thread

#endif // COND_HPP
