// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef CHRONO_API_CHRONO_TIME_HPP_
#define CHRONO_API_CHRONO_TIME_HPP_

#include <ctime>

#include "var/String.hpp"
#include "MicroTime.hpp"

namespace chrono {

class DateTime {
public:
  DateTime() = default;
  explicit DateTime(time_t t) : m_ctime(t) {}

  class Construct {
    API_AC(Construct, var::StringView, time);
    API_AF(Construct, var::StringView, format, "%Y-%m-%d %H:%M:%S");
  };

  explicit DateTime(const Construct &options);
  explicit DateTime(MicroTime t) : m_ctime(t.seconds()) {}

  API_NO_DISCARD bool is_valid() const { return m_ctime != 0; }

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

  API_NO_DISCARD var::NumberString to_string() const;
  API_NO_DISCARD DateTime age() const { return DateTime::get_system_time() - *this; }

  DateTime &operator+=(const DateTime &a);

  DateTime &operator-=(const DateTime &a);
  static DateTime get_system_time();
  DateTime& set_system_time();

  DateTime &set_time(time_t tm) {
    m_ctime = tm;
    return *this;
  }

  API_NO_DISCARD time_t ctime() const { return m_ctime; }

  API_NO_DISCARD u32 second() const;
  API_NO_DISCARD u32 minute() const;
  API_NO_DISCARD u32 hour() const;

private:
  time_t m_ctime = 0;
};

class Date {
public:
  class Construct {
    API_AB(Construct, daylight_savings, false);
    API_AF(Construct, int, time_zone, 0);

  public:
    Construct() : m_is_daylight_savings(false) {}
  };

  explicit Date(
    const DateTime &date_time,
    const Construct &options = Construct());

  API_NO_DISCARD var::GeneralString to_string(var::StringView format = "%Y-%m-%d %H:%M:%S") const;

  API_NO_DISCARD int second() const { return m_tm.tm_sec; }
  API_NO_DISCARD int minute() const { return m_tm.tm_min; }
  API_NO_DISCARD int hour() const { return m_tm.tm_hour; }

  enum class Month {
    null API_MAYBE_UNUSED,
    january API_MAYBE_UNUSED,
    february API_MAYBE_UNUSED,
    march API_MAYBE_UNUSED,
    april API_MAYBE_UNUSED,
    may API_MAYBE_UNUSED,
    june API_MAYBE_UNUSED,
    july API_MAYBE_UNUSED,
    august API_MAYBE_UNUSED,
    september API_MAYBE_UNUSED,
    october API_MAYBE_UNUSED,
    november API_MAYBE_UNUSED,
    december API_MAYBE_UNUSED
  };

  static const char * to_cstring(Month value);

  API_NO_DISCARD int day() const { return m_tm.tm_mday; }
  API_NO_DISCARD int weekday() const { return m_tm.tm_wday; }
  API_NO_DISCARD  API_MAYBE_UNUSED int yearday() const { return m_tm.tm_yday; }
  API_NO_DISCARD Month month() const { return Month(m_tm.tm_mon + 1); }
  API_NO_DISCARD int year() const { return m_tm.tm_year + 1900; }

  API_NO_DISCARD API_MAYBE_UNUSED const struct tm &get_tm() const { return m_tm; }

private:
  struct tm m_tm{};
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
Printer &operator<<(Printer &printer, const chrono::Date &a);
} // namespace printer

#endif /* CHRONO_API_CHRONO_TIME_HPP_ */
