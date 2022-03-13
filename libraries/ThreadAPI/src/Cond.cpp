#include <chrono.hpp>

#include "thread/Cond.hpp"

using namespace thread;

Cond::Attributes::Attributes() {
  API_RETURN_IF_ERROR();
  API_SYSTEM_CALL("", pthread_condattr_init(&m_attributes));
}

Cond::Attributes::~Attributes() { pthread_condattr_destroy(&m_attributes); }

Cond::Attributes::Attributes(Cond::Attributes &&a) noexcept {
  std::swap(m_attributes, a.m_attributes);
}

Cond::Attributes &Cond::Attributes::operator=(Cond::Attributes &&a) noexcept {
  std::swap(m_attributes, a.m_attributes);
  return *this;
}

Cond::Attributes &Cond::Attributes::set_pshared(Cond::ProcessShared pshared) {
  API_SYSTEM_CALL("",
                  pthread_condattr_setpshared(&m_attributes, int(pshared)));
  return *this;
}

bool Cond::Attributes::get_is_pshared() const {
  int pshared = 0;
  pthread_condattr_getpshared(&m_attributes, &pshared);
  return pshared == int(ProcessShared::shared);
}

Cond::ProcessShared Cond::Attributes::get_pshared() const {
  int pshared = 0;
  pthread_condattr_getpshared(&m_attributes, &pshared);
  return ProcessShared(pshared);
}

Cond::Cond(Mutex &mutex) : m_mutex(&mutex) {
  API_RETURN_IF_ERROR();
  Attributes attr;
  API_SYSTEM_CALL("", pthread_cond_init(&m_cond, &attr.m_attributes));
}

Cond::Cond(Mutex &mutex, const Attributes &attr) : m_mutex(&mutex) {
  API_RETURN_IF_ERROR();
  API_SYSTEM_CALL("", pthread_cond_init(&m_cond, &attr.m_attributes));
}

Cond::~Cond() { pthread_cond_destroy(&m_cond); }

Cond &Cond::lock() {
  m_mutex->lock();
  return *this;
}

Cond &Cond::unlock() {
  m_mutex->unlock();
  return *this;
}

Cond & Cond::wait_until_asserted(const chrono::ClockTime &timeout){
  bool is_ready;
  do {
    Mutex::Scope ms(mutex());
    is_ready = is_asserted();
    if(!is_ready){
      if( timeout != chrono::ClockTime() ){
        wait_timed(timeout);
      } else {
        wait();
      }
    }
  } while(!is_ready);
  return *this;
}

Cond &Cond::wait() {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL("", pthread_cond_wait(&m_cond, &m_mutex->m_mutex));
  return *this;
}

Cond &Cond::wait_timed(const chrono::ClockTime &timeout) {
  const auto abs_timeout = ClockTime::get_system_time() + timeout;
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL("", pthread_cond_timedwait(&m_cond, &m_mutex->m_mutex,
                                             abs_timeout.timespec()));
  return *this;
}

Cond &Cond::signal() {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL("", pthread_cond_signal(&m_cond));
  return *this;
}

Cond &Cond::broadcast() {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL("", pthread_cond_broadcast(&m_cond));
  return *this;
}
