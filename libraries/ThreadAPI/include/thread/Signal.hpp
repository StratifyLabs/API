// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef THREADAPI_THREAD_SIGNAL_HPP_
#define THREADAPI_THREAD_SIGNAL_HPP_

#include <signal.h>

#include "api/api.hpp"
#include "Sched.hpp"
#include "Thread.hpp"

#if defined __link
typedef void (*signal_function_callback_t)(int);
#if defined __win32
typedef void (*signal_action_callback_t)(int, void *, void *);
#define SIGNAL_SIGINFO_FLAG 0
#else
typedef void (*signal_action_callback_t)(int, siginfo_t *, void *);
typedef signal_function_callback_t _sig_func_ptr;
#define SIGNAL_SIGINFO_FLAG SA_SIGINFO
#endif
#endif

#if defined __StratifyOS__
typedef void (*signal_function_callback_t)(int);
typedef void (*signal_action_callback_t)(int, siginfo_t *, void *);
#define SIGNAL_SIGINFO_FLAG (1 << SA_SIGINFO)
#endif

#if defined __win32
#define THREAD_API_POSIX_KILL raise
typedef u32 sigset_t;
struct sigaction {
  signal_function_callback_t sa_handler;
  signal_action_callback_t sa_sigaction;
  u32 sa_flags;
  u32 sa_mask;
};
union sigval {
  int sival_int;
  void *sival_ptr;
};
#else
#define THREAD_API_POSIX_KILL kill
#endif

namespace thread {

class SignalFlags : public api::ExecutionContext{
public:
  enum class Number {
    null = 0,
    abort = SIGABRT,
    fpe = SIGFPE,
    interrupt = SIGINT,
    illegal = SIGILL,
    segmentation = SIGSEGV,
    terminate = SIGTERM,
#if !defined __win32
    alarm = SIGALRM,
    bus = SIGBUS,
    child = SIGCHLD,
    continue_ = SIGCONT,
    handup = SIGHUP,
    kill = SIGKILL,
    pipe = SIGPIPE,
    quit = SIGQUIT,
    stop = SIGSTOP,
    terminal_stop = SIGTSTP,
    terminal_input = SIGTTIN,
    terminal_output = SIGTTOU,
    user1 = SIGUSR1,
    user2 = SIGUSR2,
    profiling_timer = SIGPROF,
    system = SIGSYS,
    trap = SIGTRAP,
    high_bandwidth = SIGURG,
    virtual_alarm = SIGVTALRM,
    cpu_time_limit = SIGXCPU,
    file_size_limit = SIGXFSZ,
#endif
#if !defined __link
    poll = SIGPOLL,
    realtime_min = SIGRTMIN,
    realtime = SIGRTMIN + 1,
    realtime_max = SIGRTMAX
#endif
  };
};

class SignalHandler : public SignalFlags {
public:
  class Construct {
    API_AF(Construct, signal_function_callback_t, signal_function, nullptr);
    API_AF(Construct, signal_action_callback_t, signal_action, nullptr);
    API_AF(Construct, u32, flags, 0);
    API_AF(Construct, sigset_t, mask, {0});
  };

  explicit SignalHandler(const Construct &options) {
    if (options.signal_function()) {
#if defined __win32
      m_sig_action.sa_handler = options.signal_function();
#else
      m_sig_action.sa_handler = (_sig_func_ptr)options.signal_function();
#endif
      m_sig_action.sa_flags = 0;
      m_sig_action.sa_mask = {};
    } else {
      m_sig_action.sa_sigaction = options.signal_action();
      m_sig_action.sa_flags = options.flags() | SIGNAL_SIGINFO_FLAG;
      m_sig_action.sa_mask = options.mask();
    }
  }

  explicit SignalHandler(signal_function_callback_t function){
    m_sig_action.sa_handler = (_sig_func_ptr)function;
  }

  explicit SignalHandler(signal_action_callback_t action){
    m_sig_action.sa_sigaction = action;
    m_sig_action.sa_flags = SIGNAL_SIGINFO_FLAG;
  }

  API_NO_DISCARD const struct sigaction *sigaction() const {
    return &m_sig_action;
  }

  static SignalHandler default_(){
    return SignalHandler(SignalHandler::Construct().set_signal_function((signal_function_callback_t)SIG_DFL));
  }

  static SignalHandler ignore(){
    return SignalHandler(SignalHandler::Construct().set_signal_function((signal_function_callback_t)SIG_IGN));
  }

private:
  struct sigaction m_sig_action = {};
};

class Signal : public SignalFlags {
public:

#if !defined __link
  class Event {
  public:
    enum class Notify {
        none = SIGEV_NONE,
        signal = SIGEV_SIGNAL,
        thread = SIGEV_THREAD
    };

    Event & set_notify(Notify value){
      m_event.sigev_notify = int(value);
      return *this;
    }

    Event & set_number(Number value){
      m_event.sigev_signo = int(value);
      return *this;
    }

    Event & set_value(int value){
      m_event.sigev_value.sival_int = value;
      return *this;
    }

    Event & set_value(void * value){
      m_event.sigev_value.sival_ptr = value;
      return *this;
    }

    Event & set_notify_function(void (*value)(sigval)){
      m_event.sigev_notify_function = value;
      return *this;
    }

    Event & set_notify_attributes(pthread_attr_t * value){
      m_event.sigev_notify_attributes = value;
      return *this;
    }

  private:
    friend class Timer;
    struct sigevent m_event = {};
  };

  class Set {
  public:
    Set &add(Number signo) {
      sigaddset(&m_sigset, static_cast<int>(signo));
      return *this;
    }

    Set &del(Number signo) {
      sigdelset(&m_sigset, static_cast<int>(signo));
      return *this;
    }

    Set &fill() {
      sigfillset(&m_sigset);
      return *this;
    }

    Set &clear() {
      sigemptyset(&m_sigset);
      return *this;
    }

    API_NO_DISCARD bool is_member(Number signo) const {
      return sigismember(&m_sigset, static_cast<int>(signo));
    }

  private:
    friend class Signal;
    sigset_t m_sigset = {0};
  };
#endif

  explicit Signal(Number signo, int signal_value = 0) {
    m_signo = static_cast<int>(signo);
    m_sigvalue.sival_int = signal_value;
  }

  Signal(Number signo, void *signal_pointer) {
    m_signo = static_cast<int>(signo);
    m_sigvalue.sival_ptr = signal_pointer;
  }

  const Signal &send(pid_t pid) const;
  Signal &send(pid_t pid) { return API_CONST_CAST_SELF(Signal, send, pid); }

  const Signal &queue(pid_t pid) const;
  Signal &queue(pid_t pid) { return API_CONST_CAST_SELF(Signal, queue, pid); }

  const Signal &send(const Thread &t) const;
  Signal &send(const Thread &t) { return API_CONST_CAST_SELF(Signal, send, t); }

  Signal &set_handler(const SignalHandler &handler);
  Signal &reset_handler();

#if !defined __link
  static Signal wait(const Set &set);
#endif

  Number number() const { return Number(m_signo); }
  API_NO_DISCARD int signo() const { return m_signo; }
  API_NO_DISCARD int sigvalue() const { return m_sigvalue.sival_int; }
  API_NO_DISCARD void *sigptr() const { return m_sigvalue.sival_ptr; }

  class HandlerScope {
  public:
    HandlerScope(Signal & signal, const SignalHandler & handler) : m_signo(signal.number()){
      signal.set_handler(handler);
    }
    ~HandlerScope(){
      Signal(m_signo).set_handler(SignalHandler::default_());
    }
  private:
    Number m_signo;
  };

private:
  int m_signo;
  union sigval m_sigvalue;
};

} // namespace thread

#endif /* THREADAPI_THREAD_SIGNAL_HPP_ */
