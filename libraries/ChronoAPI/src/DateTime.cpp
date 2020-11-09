/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
// Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc

#if defined __StratifyOS__
#include <fcntl.h>
#include <sos/dev/rtc.h>
#include <unistd.h>
#endif

#include "var/StackString.hpp"

#include "printer/Printer.hpp"

#include "chrono/ClockTimer.hpp"
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
  printer.key("ctime", var::NumberString(a.ctime()).string_view());
  return printer;
}

using namespace chrono;

/*! \brief Construct using current time */
DateTime::DateTime() { m_ctime = 0; }

DateTime::DateTime(const Construct &options) {
  struct tm tm = {0};
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
  time_t t = ::time(0);
  if (t < 962668800) {
    t = 962668800;
  }
  return DateTime(t);
}

u32 DateTime::second() const { return m_ctime % 60; }

u32 DateTime::minute() const { return (m_ctime % 3600) / 60; }

u32 DateTime::hour() const { return m_ctime / 3600 % 24; }

Date::Date(const DateTime &date_time, const Construct &options) {
  time_t ctime = date_time.ctime() + options.is_daylight_savings() * 3600
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

var::String Date::get_string(var::StringView format) const {
  API_RETURN_VALUE_IF_ERROR(var::String());
  char buffer[64] = {0};
  size_t result
    = strftime(buffer, 63, var::StackString64(format).cstring(), &m_tm);
  if (result == 0) {
    API_SYSTEM_CALL("format time", -1);
    return var::String();
  }
  return std::move(var::String(buffer));
}
