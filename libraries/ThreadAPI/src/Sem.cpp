// Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for
// rights.


#include "thread/Sem.hpp"

using namespace thread;

int SemaphoreObject::get_value() const {
#if defined __macosx
  API_RETURN_VALUE_ASSIGN_ERROR(
    -1,
    "macosx doesn't supported unnamed semaphores",
    ENOTSUP);
#else
  API_RETURN_VALUE_IF_ERROR(-1);
  int value = 0;
  int ret;
  API_SYSTEM_CALL("", sem_getvalue(m_handle, &value));
  return value;
#endif
}

SemaphoreObject &SemaphoreObject::post() {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL("", sem_post(m_handle));
  return *this;
}

SemaphoreObject &SemaphoreObject::wait() {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL("", sem_wait(m_handle));
  return *this;
}

SemaphoreObject &SemaphoreObject::wait_timed(const chrono::ClockTime &timeout) {
#if defined __macosx
  MCU_UNUSED_ARGUMENT(timeout);
  API_RETURN_VALUE_ASSIGN_ERROR(
    *this,
    "macosx doesn't supported timed_wait semaphores",
    ENOTSUP);
#else
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL("", sem_timedwait(m_handle, timeout.timespec()));
#endif
  return *this;
}

SemaphoreObject &SemaphoreObject::try_wait() {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL("", sem_trywait(m_handle));
  return *this;
}

const Semaphore &Semaphore::unlink() const {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL("", sem_unlink(m_name.cstring()));
  return *this;
}

void Semaphore::unlink(var::StringView name) {
  API_RETURN_IF_ERROR();
  const var::NameString name_string(name);
  API_SYSTEM_CALL(name_string.cstring(), sem_unlink(name_string.cstring()));
}

UnnamedSemaphore::UnnamedSemaphore(
  ProcessShared process_shared,
  unsigned int value) {
#if defined __macosx
  API_RETURN_ASSIGN_ERROR(
    "macosx doesn't supported unnamed semaphores",
    ENOTSUP);
#else
  API_RETURN_IF_ERROR();
  m_handle = &m_sem;
  API_SYSTEM_CALL(
    "",
    sem_init(&m_sem, static_cast<int>(process_shared), value));
#endif
}

UnnamedSemaphore::~UnnamedSemaphore() {
#if !defined __macosx
  API_RETURN_IF_ERROR();
  API_SYSTEM_CALL("", sem_destroy(m_handle));
#endif
}

Semaphore::Semaphore(var::StringView name) {
  open(-1, name, 0, fs::Permissions(0666));
}

Semaphore::Semaphore(
  int value,
  IsExclusive is_exclusive,
  var::StringView name,
  fs::Permissions perms) {
  API_RETURN_IF_ERROR();

  int o_flags = O_CREAT;

  if (is_exclusive == IsExclusive::yes) {
    o_flags |= O_EXCL;
  }

  open(value, name, o_flags, perms);
}

Semaphore::~Semaphore() {
  API_RETURN_IF_ERROR();
  if (m_handle != SEM_FAILED) {
    API_SYSTEM_CALL("", sem_close(m_handle));
  }
}

void Semaphore::open(
  int value,
  var::StringView name,
  int o_flags,
  fs::Permissions perms) {
  API_RETURN_IF_ERROR();
  const var::NameString name_string(name);
  if (value > 0) {
    m_handle
      = sem_open(name_string.cstring(), o_flags, perms.permissions(), value);
  } else {
    m_handle = sem_open(name_string.cstring(), o_flags);
  }
  if (m_handle == SEM_FAILED) {
    API_RETURN_ASSIGN_ERROR(name_string.cstring(), errno);
  } else {
    m_name = name_string;
  }
}
