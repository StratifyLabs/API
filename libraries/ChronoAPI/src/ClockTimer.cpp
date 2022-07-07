// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#include "printer/Printer.hpp"

#include "chrono/ClockTime.hpp"
#include "chrono/ClockTimer.hpp"

using namespace chrono;

ClockTimer::ClockTimer() { reset(); }

ClockTimer::ClockTimer(IsRunning is_running) {
  reset();
  if (is_running == IsRunning::yes) {
    start();
  }
}

ClockTimer &ClockTimer::reset() {
  m_start.reset();
  m_stop.reset();
  // when stop.seconds() value is 0, the timer is in reset mode
  // when stop.seconds() value is -1, the timer is currently running
  return *this;
}

ClockTimer &ClockTimer::restart() {
  m_start = ClockTime::get_system_time();
  m_stop.set_seconds(-1).set_nanoseconds(0);
  return *this;
}

ClockTimer &ClockTimer::start() {
  if (!is_running()) {
    restart();
  }
  return *this;
}

ClockTimer &ClockTimer::resume() {
  ClockTime new_start;
  ClockTime now;

  if (m_stop.seconds() < 0) {
    return *this; // timer is not stopped
  }

  // if timer has been stopped, then resume counting
  if (m_start.seconds() + m_start.nanoseconds()) { // start is non-zero
    new_start = m_stop - m_start;
    now = ClockTime::get_system_time();
    m_start = now - new_start;
    m_stop.set_seconds(-1).set_nanoseconds(0);
  } else {
    // if timer is not running then start it
    restart();
  }
  return *this;
}

ClockTime ClockTimer::clock_time() const {
  ClockTime now;
  if (m_stop.seconds() < 0) {
    now = ClockTime::get_system_time();
  } else {
    now = m_stop;
  }
  // difference between now and start_
  now -= m_start;
  return now;
}

Microseconds ClockTimer::calc_value() const {
  return Microseconds(clock_time());
}

ClockTimer &ClockTimer::stop() {
  if (is_running()) {
    m_stop = ClockTime::get_system_time();
  }
  return *this;
}

PerformanceScope::PerformanceScope(
  const var::StringView name,
  const ClockTimer &timer,
  printer::Printer &printer)
  : m_system_resource({&timer, &printer}, &deleter) {
  printer.open_object("start ->" | name);
  m_system_resource.pointer_to_value()->start = timer.microseconds();
}

void PerformanceScope::deleter(PerformanceScope::Context *context) {
  const auto stop = context->timer->microseconds();
  context->printer->key("stop", var::NumberString(stop - context->start))
    .close_object();
}
