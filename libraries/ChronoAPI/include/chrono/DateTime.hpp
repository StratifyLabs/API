/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.

#ifndef CHRONO_API_CHRONO_TIME_HPP_
#define CHRONO_API_CHRONO_TIME_HPP_

#include <ctime>

#include "var/String.hpp"

#include "MicroTime.hpp"

namespace chrono {

/*! \brief Time Class
 * \details This class is for accessing the current time as well
 * as adding and subtracting times and dates.
 *
 * The time is based on the value of the RTC in the system. The RTC
 * will keep the same value even when the device is reset. This class
 * should provide accurate access to the current data and time.
 *
 * It holds a c style time_t value that can be managed which is
 * a 32-bit value with accuracy to the second.
 *
 * \code
 * Time now; //current time
 * Time ten_minutes(0, 10, 0); //duration of 10 minutes
 *
 * now += ten_minutes; //adds ten minutes to now
 * \endcode
 *
 */
class DateTime {
public:
  /*! \details Constructs using current time. */
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

  /*! \details Adds to the current value. */
  DateTime &operator+=(const DateTime &a);

  /*! \details Subtracts from the current value. */
  DateTime &operator-=(const DateTime &a);

  /*! \details Assigns the system time of day to the time stored in this object
   * and returns the current system time.
   */
  static DateTime get_system_time();

  /*! \details Sets the current value.
   *
   */
  DateTime &set_time(time_t tm) {
    m_ctime = tm;
    return *this;
  }

  /*! \details Returns the time value (number of seconds since epoch). */
  time_t ctime() const { return m_ctime; }

  /*! \details Returns seconds (from 0 to 59). */
  u32 second() const;
  /*! \details Returns minutes (from 0 to 59). */
  u32 minute() const;
  /*! \details Returns hours (from 0 to 23). */
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

  var::String get_string(var::StringView format = "%Y-%m-%d %H:%M:%S") const;

  /*! \details Returns seconds (from 0 to 59). */
  int second() const { return m_tm.tm_sec; }
  /*! \details Returns minutes (from 0 to 59). */
  int minute() const { return m_tm.tm_min; }
  /*! \details Returns hours (from 0 to 23). */
  int hour() const { return m_tm.tm_hour; }

  /*! \details Returns the day of month (from 1 to 31). */
  int day() const { return m_tm.tm_mday; }
  /*! \details Returns the day of week (from 1 to 7). */
  int weekday() const { return m_tm.tm_wday; }
  /*! \details Returns the day of the year (1 to 366). */
  int yearday() const { return m_tm.tm_yday; }
  /*! \details Returns the month (from 1 to 12). */
  int month() const { return m_tm.tm_mon + 1; }
  /*! \details Returns the year (e.g. 2014) */
  int year() const { return m_tm.tm_year + 1900; }

  /*! \details Converts the time to a struct tm. */
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
