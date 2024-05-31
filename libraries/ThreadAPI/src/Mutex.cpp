// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#include "thread/Mutex.hpp"
#include "chrono/ClockTime.hpp"

using namespace thread;

Mutex::Attributes::Attributes() {
  const auto is_invalid = pthread_mutexattr_init(&m_resource.pointer_to_value()->mutexattr) < 0;
  m_resource.pointer_to_value()->set_valid(!is_invalid);
}

void Mutex::Attributes::deleter(Resource *resource) {
  if (resource->is_valid()) {
    pthread_mutexattr_destroy(&resource->mutexattr);
  }
}

Mutex::Attributes &Mutex::Attributes::set_priority_ceiling(int value) {
#if !defined __android
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL(
    "",
    pthread_mutexattr_setprioceiling(
      &m_resource.pointer_to_value()->mutexattr,
      value));
#endif
  return *this;
}

Mutex::Attributes &Mutex::Attributes::set_protocol(Protocol value) {
#if !defined __android
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL(
    "",
    pthread_mutexattr_setprotocol(
      &m_resource.pointer_to_value()->mutexattr,
      static_cast<int>(value)));
#endif
  return *this;
}

Mutex::Attributes &Mutex::Attributes::set_process_shared(ProcessShared value) {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL(
    "",
    pthread_mutexattr_setpshared(
      &m_resource.pointer_to_value()->mutexattr,
      static_cast<int>(value)));
  return *this;
}

Mutex::Attributes &Mutex::Attributes::set_type(Type value) {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL(
    "",
    pthread_mutexattr_settype(
      &m_resource.pointer_to_value()->mutexattr,
      static_cast<int>(value)));
  return *this;
}

int Mutex::Attributes::get_priority_ceiling() const {
  int ret = 0;
#if !defined __android
  API_RETURN_VALUE_IF_ERROR(-1);
  API_SYSTEM_CALL(
    "",
    pthread_mutexattr_getprioceiling(
      &m_resource.pointer_to_value()->mutexattr,
      &ret));
#endif
  return ret;
}

Mutex::Protocol Mutex::Attributes::get_protocol() const {
  int ret = 0;
#if !defined __android
  API_RETURN_VALUE_IF_ERROR(Protocol::priority_none);
  API_SYSTEM_CALL(
    "",
    pthread_mutexattr_getprotocol(
      &m_resource.pointer_to_value()->mutexattr,
      &ret));
#endif
  return static_cast<Protocol>(ret);
}

Mutex::Type Mutex::Attributes::get_type() const {
  int ret;
  API_RETURN_VALUE_IF_ERROR(Type::normal);
  API_SYSTEM_CALL(
    "",
    pthread_mutexattr_gettype(&m_resource.pointer_to_value()->mutexattr, &ret));
  return static_cast<Type>(ret);
}

Mutex::ProcessShared Mutex::Attributes::get_process_shared() const {
  int ret = 0;
  API_RETURN_VALUE_IF_ERROR(ProcessShared::private_);
  API_SYSTEM_CALL(
    "",
    pthread_mutexattr_getpshared(
      &m_resource.pointer_to_value()->mutexattr,
      &ret));
  return static_cast<ProcessShared>(ret);
}

Mutex::Mutex() : m_mutex(initialize_mutex(nullptr), &deleter) {}

Mutex::Mutex(const Mutex::Attributes &attr)
  : m_mutex(
    initialize_mutex(&attr.m_resource.pointer_to_value()->mutexattr),
    &deleter) {}

Mutex &Mutex::set_attributes(const Attributes &attr) {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL(
    "",
    pthread_mutex_init(
      m_mutex.pointer_to_value(),
      &(attr.m_resource.pointer_to_value()->mutexattr)));
  return *this;
}

Mutex &Mutex::lock() {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL("", pthread_mutex_lock(m_mutex.pointer_to_value()));
  return *this;
}

#if !defined __link
Mutex &Mutex::lock_timed(const chrono::ClockTime &clock_time) {
  API_RETURN_VALUE_IF_ERROR(*this);
  const auto calc_time = chrono::ClockTime::get_system_time() + clock_time;
  API_SYSTEM_CALL(
    "",
    pthread_mutex_timedlock(m_mutex.pointer_to_value(), calc_time));
  return *this;
}
#endif

bool Mutex::try_lock() {
  API_RETURN_VALUE_IF_ERROR(false);
  if (pthread_mutex_trylock(m_mutex.pointer_to_value()) == 0) {
    return true;
  }
  API_RESET_ERROR();
  return false;
}

Mutex &Mutex::unlock() {
  // unlock even if there is an error in the context
  api::ErrorScope error_scope;
  pthread_mutex_unlock(m_mutex.pointer_to_value());
  return *this;
}

Mutex &Mutex::unlock_with_error_check() {
  API_SYSTEM_CALL("", pthread_mutex_unlock(m_mutex.pointer_to_value()));
  return *this;
}

void Mutex::deleter(pthread_mutex_t *mutex) {
  API_RETURN_IF_ERROR();
  pthread_mutex_destroy(mutex);
}

pthread_mutex_t Mutex::initialize_mutex(const pthread_mutexattr_t *attr) {
  API_RETURN_VALUE_IF_ERROR({});
  pthread_mutex_t result;
  API_SYSTEM_CALL("mutex init", pthread_mutex_init(&result, attr));
  return result;
}
bool Mutex::Attributes::Resource::is_valid() const {
#if defined __link
  return is_link_valid;
#else
  return mutexattr.is_initialized != 0;

#endif
}
void Mutex::Attributes::Resource::set_valid(bool value) {
#if defined __link
  is_link_valid = value;
#else
  if (!value) {
          mutexattr.is_initialized = 0;
        }
#endif
}
