// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

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
  const auto calc_time = chrono::ClockTime::get_system_time() + timeout;

  API_SYSTEM_CALL("", sem_timedwait(m_handle, calc_time.timespec()));
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
  const var::KeyString name_string(name);
  API_SYSTEM_CALL(name_string.cstring(), sem_unlink(name_string.cstring()));
}

UnnamedSemaphore::UnnamedSemaphore(
  API_MAYBE_UNUSED ProcessShared process_shared,
  API_MAYBE_UNUSED unsigned int value) : m_sem(initialize_semaphore(process_shared, value), &sem_deleter){
  m_handle = m_sem.pointer_to_value();
}

sem_t UnnamedSemaphore::initialize_semaphore(
  API_MAYBE_UNUSED UnnamedSemaphore::ProcessShared process_shared,
  API_MAYBE_UNUSED unsigned int value) {
#if defined __macosx
  API_RETURN_VALUE_ASSIGN_ERROR(null_sem,
    "macosx doesn't supported unnamed semaphores",
    ENOTSUP);
#else
  sem_t result{};
  API_RETURN_VALUE_IF_ERROR(result);
  API_SYSTEM_CALL(
    "",
    sem_init(&result, static_cast<int>(process_shared), value));
  return result;
#endif
}

void UnnamedSemaphore::sem_deleter(sem_t *sem) {
#if !defined __macosx
  {
    API_RETURN_IF_ERROR();
    API_SYSTEM_CALL("", sem_destroy(sem));
  }
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

  m_unique_pointer.reset(open(value, name, o_flags, perms));
  m_handle = m_unique_pointer.get();
}

#if 0
Semaphore::~Semaphore() {
  API_RETURN_IF_ERROR();
  if (m_handle != SEM_FAILED) {
    API_SYSTEM_CALL("", sem_close(m_handle));
  }
}
#endif

sem_t * Semaphore::open(
  int value,
  var::StringView name,
  int o_flags,
  fs::Permissions perms) {
  API_RETURN_VALUE_IF_ERROR(nullptr);
  sem_t * result = sem_pointer(SEM_FAILED);
  const var::KeyString name_string(name);
  if (value > 0) {
    result
      = sem_open(name_string.cstring(), o_flags, perms.permissions(), value);
  } else {
    result = sem_open(
      name_string.cstring(),
      o_flags
#if defined __win32
      ,
      perms.permissions(),
      0
#endif
    );
  }
  if (result == SEM_FAILED) {
    API_RETURN_VALUE_ASSIGN_ERROR(nullptr, name_string.cstring(), errno);
  } else {
    m_name = name_string;
  }
  return result;
}

void Semaphore::sem_deleter(sem_t *sem) {
  if( sem && (sem != SEM_FAILED) ){
    sem_close(sem);
  }
}
