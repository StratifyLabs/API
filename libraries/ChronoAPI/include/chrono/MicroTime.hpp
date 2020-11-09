/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.

#ifndef CHRONO_API_CHRONO_MICRO_TIME_HPP_
#define CHRONO_API_CHRONO_MICRO_TIME_HPP_

#include <mcu/types.h>
#include <time.h>

namespace chrono {
#include "chrono/MicroTime.hpp"

/*! \details Defines the type for a chrono::MicroTime value. */
typedef u32 micro_time_t;

/*! \brief MicroTime Class
 * \details The MicroTime class is used for keeping track
 * of microsecond accurate time intervals. It uses
 * a 32-bit value so it is good for 4 billion microseconds
 * (or about 66 minutes).
 *
 * It is very handy for converting between microseconds,
 * milliseconds, and seconds. It also serves
 * to remove ambiguity when specifying short time intervals.
 *
 * For example:
 * ```
 * void set_period(const Microseconds & microseconds); //un-ambiguous and nice
 * code completion void set_period(u32 value); //the units here are not clear
 * void set_period_milliseconds(u32 value); //this is better but adds complexity
 * ```
 *
 *
 * ```
 * //md2code:include
 * #include <sapi/chrono.hpp>
 * ```
 *
 */
class MicroTime {
public:
  /*! \details Constructs a Microseconds object using a u32 microsecond value.
   *
   *
   * The default initial value is zero.
   *
   * ```
   * //md2code:main
   * //must be explicitly constructed
   * Microseconds duration = Microseconds(5);
   * printf("Duration is %ld microseconds\n", duration.microseconds());
   * ```
   *
   */
  explicit MicroTime(u32 microseconds = 0)
    : m_value_microseconds(microseconds) {}

  /*! \details Returns a MicroTime object set to the invalid time value. */
  static MicroTime invalid() { return MicroTime(static_cast<u32>(-1)); }

  bool is_valid() const { return *this != invalid(); }

  /*! \details Assignment addition to another MicroTime object. */
  MicroTime &operator+=(const MicroTime &a) {
    m_value_microseconds += a.microseconds();
    return *this;
  }

  /*! \details Assignment addition to another MicroTime object. */
  MicroTime &operator-=(const MicroTime &a) {
    m_value_microseconds -= a.microseconds();
    return *this;
  }

  MicroTime operator+(const MicroTime &a) const {
    return MicroTime(microseconds() + a.microseconds());
  }

  MicroTime operator*(const MicroTime &a) const {
    return MicroTime(microseconds() * a.microseconds());
  }

  MicroTime operator*(u32 a) const { return MicroTime(microseconds() * a); }

  MicroTime operator-(const MicroTime &a) const {
    return MicroTime(microseconds() - a.microseconds());
  }

  /*! \details Compares equality to another MicroTime object. */
  bool operator==(const MicroTime &a) const {
    return microseconds() == a.microseconds();
  }

  /*! \details Compares inequality to another MicroTime object. */
  bool operator!=(const MicroTime &a) const {
    return microseconds() != a.microseconds();
  }

  /*! \details Compares > to another MicroTime object. */
  bool operator>(const MicroTime &a) const {
    return microseconds() > a.microseconds();
  }

  /*! \details Compares < to another MicroTime object. */
  bool operator<(const MicroTime &a) const {
    return microseconds() < a.microseconds();
  }

  /*! \details Compares >= to another MicroTime object. */
  bool operator>=(const MicroTime &a) const {
    return microseconds() >= a.microseconds();
  }

  /*! \details Compares <= to another MicroTime object. */
  bool operator<=(const MicroTime &a) const {
    return microseconds() <= a.microseconds();
  }

  /*! \details Returns the value in seconds. */
  u32 seconds() const { return microseconds() / 1000000UL; }

  /*! \details Returns the value in microseconds. */
  micro_time_t microseconds() const { return m_value_microseconds; }

  /*! \details Returns the value in milliseconds. */
  u32 milliseconds() const { return microseconds() / 1000UL; }

  /*! \details Waits for the value of the microtime.
   *
   */
  MicroTime &wait();

private:
  micro_time_t m_value_microseconds;
};

using Microseconds = MicroTime;

void wait(const MicroTime &duration);

inline MicroTime operator*(u32 lhs, MicroTime rhs) {
  return MicroTime(rhs.microseconds() * lhs);
}

} // namespace chrono

inline chrono::MicroTime operator"" _seconds(unsigned long long int value) {
  return chrono::MicroTime(value * 1000000UL);
}

inline chrono::MicroTime
operator"" _milliseconds(unsigned long long int value) {
  return chrono::MicroTime(value * 1000UL);
}

inline chrono::MicroTime
operator"" _microseconds(unsigned long long int value) {
  return chrono::MicroTime(value);
}

inline chrono::MicroTime operator"" _nanoseconds(unsigned long long int value) {
  return chrono::MicroTime(value / 1000UL);
}

namespace printer {
class Printer;
Printer &operator<<(Printer &printer, const chrono::MicroTime &a);
} // namespace printer

#endif /* CHRONO_API_CHRONO_MICRO_TIME_HPP_ */
