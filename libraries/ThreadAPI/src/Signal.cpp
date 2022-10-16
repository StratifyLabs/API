// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

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
      ::sigaction(m_signo, handler.sigaction(), nullptr));

  } else {
    auto ptr = (_sig_func_ptr)handler.sigaction()->sa_handler;
    ::signal(m_signo, ptr);
  }
#endif
  return *this;
}

Signal &Signal::reset_handler() {
  API_RETURN_VALUE_IF_ERROR(*this);
  auto result = ::signal(m_signo, SIG_DFL);
  if (result == SIG_ERR) {
    API_RETURN_VALUE_ASSIGN_ERROR(*this, "signal result is SIG_ERR", errno);
  }
  return *this;
}

const Signal &Signal::send(pid_t pid) const {
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

const Signal &Signal::send(const Thread &t) const {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL("", ::pthread_kill(t.id(), m_signo));
  return *this;
}

#if !defined __link
Signal Signal::wait(const Set &set) {
  API_RETURN_VALUE_IF_ERROR(Signal(Number::null));
  int signal_number = 0;
  sigset_t sigset = set.m_sigset;
  int result = sigwait(&sigset, &signal_number);
  if (result > 0) {
    errno = result;
    handle_system_call_result(__LINE__, "", -1);
  }
  return Signal(Number(signal_number));
}
#endif

const Signal &Signal::queue(pid_t pid) const {
#if defined __macosx || defined __win32
  return send(pid);
#else
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL("", sigqueue(pid, m_signo, m_sigvalue));
#endif
  return *this;
}
Signal::Signal(SignalFlags::Number signo, int signal_value)
  : m_signo{int(signo)}, m_sigvalue{signal_value} {}
Signal::Signal(SignalFlags::Number signo, void *signal_pointer)
  : m_signo{int(signo)}, m_sigvalue{.sival_ptr = signal_pointer} {}
