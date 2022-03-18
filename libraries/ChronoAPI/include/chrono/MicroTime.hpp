// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef CHRONO_API_CHRONO_MICRO_TIME_HPP_
#define CHRONO_API_CHRONO_MICRO_TIME_HPP_

#include <sdk/types.h>
#include <ctime>

#include "api/macros.hpp"

namespace chrono {

using micro_time_t = u32;

/*! \details
 *
 * This class is the basis for short duration
 * timing units in the API framework. It is a
 * 32-bit value representing microseconds. The
 * maximum period it can represent is about 71.58 minutes.
 *
 * It is best for dealing with small wait times or timing
 * the performance of computing operations. For longer
 * times, use chrono::ClockTime.
 *
 * `MicroTime` can be construction using string literal operators:
 *
 * ```cpp
 * #include <chrono.hpp>
 *
 * wait(2_seconds);
 * wait(100_milliseconds);
 * wait(100_microseconds);
 * ```
 *
 */
class MicroTime {
public:
  explicit MicroTime(u32 microseconds = 0)
    : m_value_microseconds(microseconds) {}

  static MicroTime invalid() { return MicroTime(static_cast<u32>(-1)); }

  API_NO_DISCARD bool is_valid() const { return *this != invalid(); }

  MicroTime &operator+=(const MicroTime &a) {
    m_value_microseconds += a.microseconds();
    return *this;
  }

  MicroTime &operator-=(const MicroTime &a) {
    m_value_microseconds -= a.microseconds();
    return *this;
  }

  MicroTime &operator *= (u32 a) {
    m_value_microseconds *= a;
    return *this;
  }

  MicroTime &operator /= (u32 a) {
    m_value_microseconds /= a;
    return *this;
  }


  MicroTime operator+(const MicroTime &a) const {
    return MicroTime(microseconds() + a.microseconds());
  }


  MicroTime operator*(u32 a) const { return MicroTime(microseconds() * a); }
  MicroTime operator/(u32 a) const { return MicroTime(microseconds() / a); }

  MicroTime operator-(const MicroTime &a) const {
    return MicroTime(microseconds() - a.microseconds());
  }

  bool operator==(const MicroTime &a) const {
    return microseconds() == a.microseconds();
  }

  bool operator!=(const MicroTime &a) const {
    return microseconds() != a.microseconds();
  }

  bool operator>(const MicroTime &a) const {
    return microseconds() > a.microseconds();
  }

  bool operator<(const MicroTime &a) const {
    return microseconds() < a.microseconds();
  }

  bool operator>=(const MicroTime &a) const {
    return microseconds() >= a.microseconds();
  }

  bool operator<=(const MicroTime &a) const {
    return microseconds() <= a.microseconds();
  }

  API_NO_DISCARD u32 seconds() const { return microseconds() / 1000000UL; }
  API_NO_DISCARD micro_time_t microseconds() const { return m_value_microseconds; }
  API_NO_DISCARD u32 milliseconds() const { return microseconds() / 1000UL; }
  const MicroTime &wait() const;
  MicroTime& wait(){
    return API_CONST_CAST_SELF(MicroTime, wait);
  }

private:
  micro_time_t m_value_microseconds;
};

using Microseconds = MicroTime;

/*! \details
 *
 * This function waits using `usleep()` and `sleep()`
 * as needed.
 *
 * @param duration The amount of time to sleep.
 *
 * ```cpp
 * wait(1_milliseconds);
 * wait(MicroTime(1000));
 * ```
 * 
 */
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
