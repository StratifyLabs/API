// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef CHRONO_API_CHRONO_TIME_HPP_
#define CHRONO_API_CHRONO_TIME_HPP_

#include <ctime>

#include "var/String.hpp"
#include "MicroTime.hpp"

namespace chrono {

class DateTime {
public:
  DateTime();

  explicit DateTime(time_t t) : m_ctime(t) {}

  class Construct {
    API_AC(Construct, var::StringView, time);
    API_AC(Construct, var::StringView, format);

  public:
    Construct() : m_format("%Y-%m-%d %H:%M:%S") {}
  };

  DateTime(const Construct &options);

  DateTime(MicroTime t) : m_ctime(t.seconds()) {}

  bool is_valid() { return m_ctime != 0; }

  DateTime operator+(const DateTime &a) const {
    DateTime result;
    result.m_ctime = m_ctime + a.m_ctime;
    return result;
  }

  DateTime operator-(const DateTime &a) const {
    DateTime result;
    result.m_ctime = m_ctime - a.m_ctime;
    return result;
  }

  bool operator==(const DateTime &a) const { return m_ctime == a.m_ctime; }
  bool operator!=(const DateTime &a) const { return m_ctime != a.m_ctime; }
  bool operator>(const DateTime &a) const { return m_ctime > a.m_ctime; }
  bool operator<(const DateTime &a) const { return m_ctime < a.m_ctime; }
  bool operator>=(const DateTime &a) const { return m_ctime >= a.m_ctime; }
  bool operator<=(const DateTime &a) const { return m_ctime <= a.m_ctime; }

  DateTime age() const { return DateTime::get_system_time() - *this; }

  DateTime &operator+=(const DateTime &a);

  DateTime &operator-=(const DateTime &a);
  static DateTime get_system_time();
  DateTime &set_time(time_t tm) {
    m_ctime = tm;
    return *this;
  }

  time_t ctime() const { return m_ctime; }

  u32 second() const;
  u32 minute() const;
  u32 hour() const;

private:
  time_t m_ctime;
};

class Date {
public:
  class Construct {
    API_AB(Construct, daylight_savings, false);
    API_AF(Construct, int, time_zone, 0);

  public:
    Construct() : m_is_daylight_savings(false), m_time_zone(0) {}
  };

  explicit Date(
    const DateTime &date_time,
    const Construct &options = Construct());

  var::String to_string(var::StringView format = "%Y-%m-%d %H:%M:%S") const;

  int second() const { return m_tm.tm_sec; }
  int minute() const { return m_tm.tm_min; }
  int hour() const { return m_tm.tm_hour; }

  int day() const { return m_tm.tm_mday; }
  int weekday() const { return m_tm.tm_wday; }
  int yearday() const { return m_tm.tm_yday; }
  int month() const { return m_tm.tm_mon + 1; }
  int year() const { return m_tm.tm_year + 1900; }

  const struct tm &get_tm() const { return m_tm; }

private:
  struct tm m_tm;
};

} // namespace chrono

inline chrono::DateTime operator"" _weeks(unsigned long long int value) {
  return chrono::DateTime(value * 7 * 24 * 3600UL);
}

inline chrono::DateTime operator"" _days(unsigned long long int value) {
  return chrono::DateTime(value * 24 * 3600UL);
}

inline chrono::DateTime operator"" _hours(unsigned long long int value) {
  return chrono::DateTime(value * 3600UL);
}

inline chrono::DateTime operator"" _minutes(unsigned long long int value) {
  return chrono::DateTime(value * 60UL);
}

namespace printer {
class Printer;
Printer &operator<<(Printer &printer, const chrono::DateTime &a);
} // namespace printer

#endif /* CHRONO_API_CHRONO_TIME_HPP_ */
