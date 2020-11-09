/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
// Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc

#include <signal.h>

#include "thread/Signal.hpp"
using namespace thread;

Signal &Signal::set_handler(const SignalHandler &handler) {
#if defined __win32
  signal_function_callback_t ptr = handler.sigaction()->sa_handler;
  ::signal(m_signo, ptr);
#else
  if (handler.sigaction()->sa_flags & SIGNAL_SIGINFO_FLAG) {
    API_SYSTEM_CALL(
      "",
      ::sigaction(m_signo, handler.sigaction(), 0));

  } else {
    _sig_func_ptr ptr = (_sig_func_ptr)handler.sigaction()->sa_handler;
    ::signal(m_signo, ptr);
  }
#endif
  return *this;
}

Signal &Signal::reset_handler() {
  API_RETURN_VALUE_IF_ERROR(*this);
  auto result = ::signal(m_signo, SIG_DFL);
  if (result == SIG_ERR) {
    API_RETURN_VALUE_ASSIGN_ERROR(*this, "", errno);
  }
  return *this;
}

const Signal &Signal::send_pid(pid_t pid) const {
#if !defined __macosx
  if (m_sigvalue.sival_int != 0) {
    return queue(pid);
  }
#endif

  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL(
    "",
    ::THREAD_API_POSIX_KILL(
#if !defined __win32
      pid,
#endif
      m_signo));
  return *this;
}

const Signal &Signal::send_thread(pthread_t t) const {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL("", ::pthread_kill(t, m_signo));
  return *this;
}

const Signal &Signal::queue(pid_t pid) const {
#if defined __macosx
  return send_pid(pid);
#else
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL("", sigqueue(pid, m_signo, m_sigvalue));
#endif
  return *this;
}
