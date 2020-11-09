/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.

#include "printer/Printer.hpp"

#include "chrono/MicroTime.hpp"
#include "chrono/ClockTime.hpp"

printer::Printer &
printer::operator<<(printer::Printer &printer, const chrono::ClockTime &a) {
  printer.key("seconds", var::NumberString(a.seconds()).string_view());
  printer.key("nanoseconds", var::NumberString(a.nanoseconds()).string_view());
  return printer;
}

using namespace chrono;

#if defined __macosx
#include <sys/time.h>
static int clock_gettime(int clk_id, struct timespec *t) {
  MCU_UNUSED_ARGUMENT(clk_id);
  struct timeval now;
  int rv = gettimeofday(&now, NULL);
  if (rv)
    return rv;
  t->tv_sec = now.tv_sec;
  t->tv_nsec = now.tv_usec * 1000;
  return 0;
}
#endif

using namespace chrono;

ClockTime ClockTime::get_system_time(ClockId clock_id) {
  API_RETURN_VALUE_IF_ERROR(ClockTime());
  ClockTime clock_time;
  const int result = API_SYSTEM_CALL(
    "",
    clock_gettime(static_cast<clockid_t>(clock_id), clock_time));
  return clock_time;
}

ClockTime ClockTime::get_system_resolution(ClockId clock_id) {
  API_RETURN_VALUE_IF_ERROR(ClockTime());
#if defined __macosx
  ClockTime resolution = ClockTime().set_nanoseconds(1000);
#else
  ClockTime resolution;
  const int result = API_SYSTEM_CALL(
    "",
    clock_getres(static_cast<clockid_t>(clock_id), resolution));
#endif
  return resolution;
}

ClockTime ClockTime::get_age() const { return get_system_time() - *this; }

ClockTime::ClockTime(const MicroTime &micro_time) {
  m_value.tv_sec = micro_time.seconds();
  u32 microseconds = micro_time.microseconds() - m_value.tv_sec * 1000000;
  m_value.tv_nsec = microseconds * 1000;
}

bool ClockTime::operator>(const ClockTime &a) const {
  if (m_value.tv_sec > a.m_value.tv_sec) {
    return true;
  } else if (m_value.tv_sec == a.m_value.tv_sec) {
    return m_value.tv_nsec > a.m_value.tv_nsec;
  }
  return false;
}

bool ClockTime::operator<(const ClockTime &a) const {
  if (m_value.tv_sec < a.m_value.tv_sec) {
    return true;
  } else if (m_value.tv_sec == a.m_value.tv_sec) {
    return m_value.tv_nsec < a.m_value.tv_nsec;
  }
  return false;
}

bool ClockTime::operator>=(const ClockTime &a) const {
  if (m_value.tv_sec >= a.m_value.tv_sec) {
    return true;
  } else if (m_value.tv_sec == a.m_value.tv_sec) {
    return m_value.tv_nsec >= a.m_value.tv_nsec;
  }
  return false;
}

bool ClockTime::operator<=(const ClockTime &a) const {
  if (m_value.tv_sec <= a.m_value.tv_sec) {
    return true;
  } else if (m_value.tv_sec == a.m_value.tv_sec) {
    return m_value.tv_nsec <= a.m_value.tv_nsec;
  }
  return false;
}

bool ClockTime::operator==(const ClockTime &a) const {
  if (
    (m_value.tv_sec == a.m_value.tv_sec)
    && (m_value.tv_nsec == a.m_value.tv_nsec)) {
    return true;
  }
  return false;
}

bool ClockTime::operator!=(const ClockTime &a) const {
  if (
    (m_value.tv_sec != a.m_value.tv_sec)
    || (m_value.tv_nsec != a.m_value.tv_nsec)) {
    return true;
  }
  return false;
}

void ClockTime::assign(u32 seconds, u32 nanoseconds) {
  m_value.tv_sec = seconds;
  m_value.tv_nsec = nanoseconds;
  if (m_value.tv_nsec > 1000000000) {
    m_value.tv_sec++;
    m_value.tv_nsec -= 1000000000;
  }

  if (m_value.tv_nsec < 0) {
    m_value.tv_sec--;
    m_value.tv_nsec += 1000000000;
  }
}

ClockTime ClockTime::add(const ClockTime &a, const ClockTime &b) {
  ClockTime c;
  c.m_value.tv_sec = a.m_value.tv_sec + b.m_value.tv_sec;
  c.m_value.tv_nsec = a.m_value.tv_nsec + b.m_value.tv_nsec;
  if (c.m_value.tv_nsec > 1000000000) {
    c.m_value.tv_nsec -= 1000000000;
    c.m_value.tv_sec++;
  }
  return c;
}

ClockTime ClockTime::subtract(const ClockTime &a, const ClockTime &b) {
  ClockTime c;
  c.m_value.tv_sec = a.m_value.tv_sec - b.m_value.tv_sec;
  c.m_value.tv_nsec = a.m_value.tv_nsec - b.m_value.tv_nsec;
  if (c.m_value.tv_nsec < 0) {
    c.m_value.tv_nsec += 1000000000;
    c.m_value.tv_sec--;
  }
  return c;
}
