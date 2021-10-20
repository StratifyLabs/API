// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef CHRONO_API_CHRONO_TIMER_HPP_
#define CHRONO_API_CHRONO_TIMER_HPP_

#include "ClockTime.hpp"
#include "MicroTime.hpp"

namespace printer {
class Printer;
}

namespace chrono {

class ClockTimer : public api::ExecutionContext {
public:

  enum class IsRunning {
    no, yes
  };

  ClockTimer();
  ClockTimer(IsRunning is_running);

  // start if not started
  ClockTimer &start();
  // restart from zero even if already started
  ClockTimer &restart();
  // continue after stop()
  ClockTimer &resume();
  // stop for now
  ClockTimer &stop();
  // stop and reset the state to initial values
  ClockTimer &reset();

  bool is_running() const { return !is_stopped(); }
  bool is_started() const {
    return (m_start.nanoseconds() + m_start.seconds()) != 0;
  }
  bool is_stopped() const {
    return (m_stop.seconds() != -1) || (m_stop.seconds() == 0);
  }

  bool is_reset() const { return m_stop.seconds() == 0; }

  u32 milliseconds() const { return calc_value().milliseconds(); }
  u32 microseconds() const { return calc_value().microseconds(); }
  u32 seconds() const { return calc_value().seconds(); }

  ClockTime clock_time() const;
  MicroTime micro_time() const { return calc_value(); }

private:
  ClockTime m_start;
  ClockTime m_stop;

  MicroTime calc_value() const;
};

inline bool operator==(const ClockTimer &lhs, const MicroTime &rhs) {
  return lhs.micro_time() == rhs;
}

inline bool operator!=(const ClockTimer &lhs, const MicroTime &rhs) {
  return lhs.micro_time() != rhs;
}

inline bool operator>(const ClockTimer &lhs, const MicroTime &rhs) {
  return lhs.micro_time() > rhs;
}

inline bool operator<(const ClockTimer &lhs, const MicroTime &rhs) {
  return lhs.micro_time() < rhs;
}

inline bool operator<=(const ClockTimer &lhs, const MicroTime &rhs) {
  return lhs.micro_time() <= rhs;
}

inline bool operator>=(const ClockTimer &lhs, const MicroTime &rhs) {
  return lhs.micro_time() >= rhs;
}

inline bool operator==(const MicroTime &lhs, const ClockTimer &rhs) {
  return lhs == rhs.micro_time();
}

inline bool operator!=(const MicroTime &lhs, const ClockTimer &rhs) {
  return lhs != rhs.micro_time();
}

inline bool operator>(const MicroTime &lhs, const ClockTimer &rhs) {
  return lhs > rhs.micro_time();
}

inline bool operator<(const MicroTime &lhs, const ClockTimer &rhs) {
  return lhs < rhs.micro_time();
}

inline bool operator<=(const MicroTime &lhs, const ClockTimer &rhs) {
  return lhs <= rhs.micro_time();
}

inline bool operator>=(const MicroTime &lhs, const ClockTimer &rhs) {
  return lhs >= rhs.micro_time();
}

class PerformanceScope {
public:
  PerformanceScope(const var::StringView name, const ClockTimer &timer, printer::Printer &printer);
  ~PerformanceScope();

private:
  const ClockTimer * m_timer = nullptr;
  printer::Printer * m_printer = nullptr;
  u32 m_start = 0;
};

using PerformanceContext = PerformanceScope;

} // namespace chrono

#endif // CHRONO_API_CHRONO_TIMER_HPP_
