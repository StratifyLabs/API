// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef CHRONO_API_CHRONO_TIMER_HPP_
#define CHRONO_API_CHRONO_TIMER_HPP_

#include "ClockTime.hpp"
#include "MicroTime.hpp"

namespace printer {
class Printer;
}

namespace chrono {

/*! \details
 *
 * This class creates a software timer based on `ClockTime`.
 *
 * It keeps track of when a timer is started and stopped. The
 * timer can have the following states:
 *
 * - reset: after construction or `reset()`
 * - running: after `start()` or `restart()`
 * - stopped: after `stop()` but before `reset()`
 *
 * The functions to manage the state include:
 *
 * - `reset()`: stop and put the timer in a reset state
 * - `start()`: start the timer if it isn't already running
 * - `stop()`: stop the timer
 * - `resume()`: resume after stopping
 * - `restart()`: start the timer at zero even if it is already running
 *
 * ClockTimer's can be directly compared to chrono::MicroTime values:
 *
 * ```cpp
 * #include <chrono.hpp>
 *
 * ClockTimer timer;
 *
 * timer.start();
 * while( timer < 5_seconds ){
 *   wait(10_milliseconds);
 * }
 * ```
 *
 *
 */
class ClockTimer : public api::ExecutionContext {
public:
  enum class IsRunning { no, yes };

  ClockTimer();
  explicit ClockTimer(IsRunning is_running);

  //! \details start if not started
  ClockTimer &start();
  //! \details restart from zero even if already started
  ClockTimer &restart();
  //! \details continue after stop()
  ClockTimer &resume();
  //! \details stop for now
  ClockTimer &stop();
  //! \details stop and reset the state to initial values
  ClockTimer &reset();

  API_NO_DISCARD bool is_running() const { return !is_stopped(); }
  API_NO_DISCARD bool is_started() const {
    return (m_start.nanoseconds() + m_start.seconds()) != 0;
  }
  API_NO_DISCARD bool is_stopped() const {
    return (m_stop.seconds() != -1) || (m_stop.seconds() == 0);
  }

  API_NO_DISCARD bool is_reset() const { return m_stop.seconds() == 0; }

  API_NO_DISCARD u32 milliseconds() const {
    return calc_value().milliseconds();
  }
  API_NO_DISCARD u32 microseconds() const {
    return calc_value().microseconds();
  }
  API_NO_DISCARD u32 seconds() const { return calc_value().seconds(); }

  API_NO_DISCARD ClockTime clock_time() const;
  API_NO_DISCARD MicroTime micro_time() const { return calc_value(); }

private:
  ClockTime m_start;
  ClockTime m_stop;

  API_NO_DISCARD MicroTime calc_value() const;
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


/*! \details
 *
 * This class can be used with a printer::Printer
 * and a chrono::ClockTimer to show the performance
 * of any scope.
 *
 * ```cpp
 * #include <fs.hpp>
 * #include <chrono.hpp>
 * #include <printer.hpp>
 *
 *
 * Printer printer;
 * ClockTimer timer(ClockTimer::IsRunning::yes);
 * {
 *   PerformanceScope ps("readFile", timer, printer);
 *   DataFile data_file(File("read_this_file.txt"));
 * }
 * ```
 *
 * The output will look something like this (the stop value is in
 * microseconds):
 *
 * ```
 * - start -> readFile
 *   stop: 50234
 * ```
 *
 */
class PerformanceScope {
  struct Context {
    const ClockTimer * timer;
    printer::Printer * printer;
    u32 start;
  };

  static void deleter(Context * context);
  using SystemResource = api::SystemResource<Context, decltype(&deleter)>;
  SystemResource m_system_resource;

public:
  PerformanceScope(
    var::StringView name,
    const ClockTimer &timer,
    printer::Printer &printer);
};

using PerformanceContext = PerformanceScope;

} // namespace chrono

#endif // CHRONO_API_CHRONO_TIMER_HPP_
