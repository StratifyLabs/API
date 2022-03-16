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
  API_SYSTEM_CALL("", pthread_condattr_setpshared(&m_attributes, int(pshared)));
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

Cond::Cond(Mutex &mutex)
  : m_cond(initialize_cond(nullptr), &cond_deleter), m_mutex(&mutex) {}

Cond::Cond(Mutex &mutex, const Attributes &attr)
  : m_cond(initialize_cond(&attr.m_attributes), &cond_deleter),
    m_mutex(&mutex) {}

Cond &Cond::lock() {
  m_mutex->lock();
  return *this;
}

Cond &Cond::unlock() {
  m_mutex->unlock();
  return *this;
}

Cond &Cond::wait_until_asserted(const chrono::ClockTime &timeout) {
  bool is_ready;
  do {
    Mutex::Scope ms(mutex());
    is_ready = is_asserted();
    if (!is_ready) {
      if (timeout != chrono::ClockTime()) {
        wait_timed(timeout);
      } else {
        wait();
      }
    }
  } while (!is_ready);
  return *this;
}

Cond &Cond::wait() {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL(
    "",
    pthread_cond_wait(m_cond.pointer_to_value(), m_mutex->m_mutex.pointer_to_value()));
  return *this;
}

Cond &Cond::wait_timed(const chrono::ClockTime &timeout) {
  const auto abs_timeout = ClockTime::get_system_time() + timeout;
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL(
    "",
    pthread_cond_timedwait(
      m_cond.pointer_to_value(),
      m_mutex->m_mutex.pointer_to_value(),
      abs_timeout.timespec()));
  return *this;
}

Cond &Cond::signal() {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL("", pthread_cond_signal(m_cond.pointer_to_value()));
  return *this;
}

Cond &Cond::broadcast() {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL("", pthread_cond_broadcast(m_cond.pointer_to_value()));
  return *this;
}

void Cond::cond_deleter(pthread_cond_t *cond) { pthread_cond_destroy(cond); }

pthread_cond_t Cond::initialize_cond(const pthread_condattr_t *attr) {
  API_RETURN_VALUE_IF_ERROR({});
  pthread_cond_t result;
  Attributes attributes;
  const auto effective_attributes
    = attr == nullptr ? &attributes.m_attributes : attr;
  API_SYSTEM_CALL(
    "cond init",
    pthread_cond_init(&result, effective_attributes));
  return result;
}
