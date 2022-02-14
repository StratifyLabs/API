// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#if defined __StratifyOS__
#include <sos/dev/rtc.h>
#include <sys/time.h>
#include <unistd.h>
#endif

#include "var/StackString.hpp"

#include "printer/Printer.hpp"

#include "chrono/DateTime.hpp"

#if defined __win32
#include <iomanip>
#include <sstream>
#include <time.h>

static char *strptime(const char *s, const char *f, struct tm *tm) {
  // Isn't the C++ standard lib nice? std::get_time is defined such that its
  // format parameters are the exact same as strptime. Of course, we have to
  // create a string stream first, and imbue it with the current C locale, and
  // we also have to make sure we return the right things if it fails, or
  // if it succeeds, but this is still far simpler an implementation than any
  // of the versions in any of the C standard libraries.
  std::istringstream input(s);
  input.imbue(std::locale(setlocale(LC_ALL, nullptr)));
  input >> std::get_time(tm, f);
  if (input.fail()) {
    return nullptr;
  }
  return (char *)(s + input.tellg());
}

#endif

printer::Printer &
printer::operator<<(printer::Printer &printer, const chrono::DateTime &a) {
  return printer.key("ctime", var::NumberString(a.ctime()));
}

printer::Printer &
printer::operator<<(printer::Printer &printer, const chrono::Date &a) {
  return printer.key("year", var::NumberString(a.year()))
    .key("month", chrono::Date::to_cstring(a.month()))
    .key("day", var::NumberString(a.day()))
    .key("weekday", var::NumberString(a.weekday()))
    .key("hour", var::NumberString(a.hour()))
    .key("minute", var::NumberString(a.minute()))
    .key("second", var::NumberString(a.second()));
}

using namespace chrono;

const char *Date::to_cstring(Month value) {
  switch (value) {
  case Month::null:
    return "null";
  case Month::january:
    return "january";
  case Month::february:
    return "february";
  case Month::march:
    return "march";
  case Month::april:
    return "april";
  case Month::may:
    return "may";
  case Month::june:
    return "june";
  case Month::july:
    return "july";
  case Month::august:
    return "august";
  case Month::september:
    return "september";
  case Month::october:
    return "october";
  case Month::november:
    return "november";
  case Month::december:
    return "december";
  }
  return "unknown";
}

/*! \brief Construct using current time */

DateTime::DateTime(const Construct &options) {
  struct tm tm {};
  if (
    strptime(
      var::StackString64(options.time()).cstring(),
      var::StackString64(options.format()).cstring(),
      &tm)
    != nullptr) {
    m_ctime = mktime(&tm);
  } else {
    m_ctime = 0;
  }
}

DateTime &DateTime::operator+=(const DateTime &a) {
  m_ctime += a.ctime();
  return *this;
}

DateTime &DateTime::operator-=(const DateTime &a) {
  m_ctime -= a.ctime();
  return *this;
}

DateTime DateTime::get_system_time() {
  time_t t = ::time(nullptr);
  if (t < 962668800) {
    t = 962668800;
  }
  return DateTime(t);
}

DateTime &DateTime::set_system_time() {
  API_RETURN_VALUE_IF_ERROR(*this);
#if !defined __link
  struct timeval tp {};
  struct timezone tz {};
  tp.tv_sec = m_ctime;
  settimeofday(&tp, &tz);
#endif
  return *this;
}

u32 DateTime::second() const { return m_ctime % 60; }

u32 DateTime::minute() const { return (m_ctime % 3600) / 60; }

u32 DateTime::hour() const { return m_ctime / 3600 % 24; }
var::NumberString DateTime::to_string() const {
  const auto date = Date(*this);
  return var::NumberString().format(
    "%04u-%02u-%02u %02d:%02d:%02d",
    date.year(),
    date.month(),
    date.day(),
    date.hour(),
    date.minute(),
    date.second());
}

Date::Date(const DateTime &date_time, const Construct &options) {
  const time_t ctime = date_time.ctime() + options.is_daylight_savings() * 3600
                       + options.time_zone() * 3600;
#if defined __win32
  struct tm *ptr;
  ptr = gmtime(&ctime);
  m_tm = *ptr;
#else
  // adjust for local time if provided

  gmtime_r(&ctime, &m_tm);
#endif
}

var::GeneralString Date::to_string(var::StringView format) const {
  API_RETURN_VALUE_IF_ERROR(var::GeneralString());
  char buffer[64] = {};
  size_t result
    = strftime(buffer, 63, var::StackString64(format).cstring(), &m_tm);
  if (result == 0) {
    API_SYSTEM_CALL("format time", -1);
    return {};
  }
  return {buffer};
}
