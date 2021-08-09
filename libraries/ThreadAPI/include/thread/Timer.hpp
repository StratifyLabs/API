// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef THREADAPI_THREAD_TIMER_HPP
#define THREADAPI_THREAD_TIMER_HPP

#if !defined __link

#include <signal.h>

#include "Signal.hpp"
#include "chrono/ClockTime.hpp"

namespace thread {

class Timer : public api::ExecutionContext {
public:
  using ClockId = chrono::ClockTime::ClockId;
  Timer(Signal::Event &signal_event, ClockId clock_id = ClockId::realtime);
  ~Timer();

  Timer(const Timer &a) = delete;
  Timer &operator=(const Timer &a) = delete;

  Timer(Timer &&a) { std::swap(m_timer, a.m_timer); }

  Timer &operator=(Timer &&a) {
    std::swap(m_timer, a.m_timer);
    return *this;
  }

  bool is_valid() const { return m_timer != timer_t(-1); }

  enum class Flags { null = 0, absolute_time = TIMER_ABSTIME };

  class SetTime {
    API_AC(SetTime, chrono::ClockTime, interval);
    API_AC(SetTime, chrono::ClockTime, value);
    API_AF(SetTime, Flags, flags, Flags::null);
  };

  Timer &set_time(const SetTime &options);

  class Info {
    API_RAC(Info, chrono::ClockTime, interval);
    API_RAC(Info, chrono::ClockTime, value);
    friend class Timer;
  };

  Info get_info() const;

  class Alarm {
  public:
    enum class Type { seconds, useconds };

  private:
    API_AC(Alarm, chrono::ClockTime, value);
    API_AC(Alarm, chrono::ClockTime, interval);
    API_AF(Alarm, Type, type, Type::seconds);
  };

  static chrono::ClockTime alarm(const Alarm &options);
  static void cancel_alarm() { alarm(Alarm()); }

private:
  timer_t m_timer = timer_t(-1);
};

} // namespace thread

#endif

#endif // THREADAPI_THREAD_TIMER_HPP
