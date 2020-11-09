/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.

#ifndef CHRONO_API_CHRONO_CLOCK_TIME_HPP_
#define CHRONO_API_CHRONO_CLOCK_TIME_HPP_

#include <mcu/types.h>
#include <time.h>

#include "DateTime.hpp"

#include "var/StackString.hpp"

namespace chrono {

/*! \brief Clock Time Class
 * \details The ClockTime class is a helper class for using
 * struct timespec times. This is a 64-bit time with a 32-bit
 * seconds element and a 32-bit nanoseconds element.
 *
 *
 */
class ClockTime {
public:
  enum class ClockId { realtime = CLOCK_REALTIME };

  static ClockTime get_system_time(ClockId clock_id = ClockId::realtime);

  /*! \details Gets the resolution of the specified clock. */
  static ClockTime get_system_resolution(ClockId clock_id = ClockId::realtime);

  /*! \details Constructs a clock time object based on the timespec. */
  ClockTime(const struct timespec &nano_time) : m_value(nano_time) {}

  /*! \details Contructs an object from a micro time object. */
  explicit ClockTime(const MicroTime &micro_time);

  /*! \details Constructs a zero value ClockTime object. */
  ClockTime() { reset(); }

  static ClockTime from_seconds(u32 seconds) {
    return ClockTime().set_seconds(seconds);
  }

  /*! \details Resets the value of the clock to zero. */
  ClockTime &reset() {
    m_value.tv_sec = 0;
    m_value.tv_nsec = 0;
    return *this;
  }

  ClockTime &set_seconds(u32 seconds) {
    m_value.tv_sec = seconds;
    return *this;
  }

  ClockTime &set_nanoseconds(u32 value) {
    m_value.tv_nsec = value;
    return *this;
  }

  /*! \details Returns a pointer to the struct timespec.
   *
   * This allows the object to be passed directly to functions
   * that required a pointer to struct timespec (read-only)
   *
   */
  operator const struct timespec *() const { return &m_value; }

  /*! \details Returns a pointer to the struct timespec.
   *
   * This allows the object to be passed directly to functions
   * that required a pointer to struct timespec (read-write)
   *
   */
  operator struct timespec *() { return &m_value; }

  /*! \details Returns true if the time is set to a valid value.
   *
   */
  bool is_valid() const { return *this != invalid(); }

  static ClockTime invalid() {
    return ClockTime().set_seconds(-1).set_nanoseconds(-1);
  }

  /*! \details Returns true if this is greater than \a a. */
  bool operator>(const ClockTime &a) const;
  /*! \details Returns true if this is less than \a a. */
  bool operator<(const ClockTime &a) const;
  /*! \details Returns true if this is greater than or equal to \a a. */
  bool operator>=(const ClockTime &a) const;
  /*! \details Returns true if this is less than or equal to \a a. */
  bool operator<=(const ClockTime &a) const;
  /*! \details Returns true if this is equal to \a a. */
  bool operator==(const ClockTime &a) const;
  /*! \details Returns true if this is not equal to \a a. */
  bool operator!=(const ClockTime &a) const;

  /*! \details Returns the sum of this object and \a a. */
  ClockTime operator+(const ClockTime &a) const { return add(*this, a); }
  /*! \details Returns the difference of this object and \a a. */
  ClockTime operator-(const ClockTime &a) const { return subtract(*this, a); }

  /*! \details Returns the age of this object as a ClockTime value.
   *
   * This will read the current time using Clock::get_time() and returns
   * the difference between the present time and the time held by this object.
   *
   * ```
   * #include <sapi/chrono.hpp>
   *
   * ClockTime instant = Clock::get_time();
   * ClockTime::wait_seconds(5);
   * printf("Age is %d\n", instant.age().seconds());
   * ```
   *
   */
  ClockTime get_age() const;

  /*! \details Adds \a to this and assigned to this. */
  ClockTime &operator+=(const ClockTime &a) {
    *this = add(*this, a);
    return *this;
  }

  /*! \details Subracts \a from this and assigned to this. */
  ClockTime &operator-=(const ClockTime &a) {
    // subtract nano time
    *this = subtract(*this, a);
    return *this;
  }

  /*! \details Returns the seconds component. */
  s32 seconds() const { return m_value.tv_sec; }
  /*! \details Returns the nanoseconds component. */
  s32 nanoseconds() const { return m_value.tv_nsec; }

  using UniqueString = var::KeyString;

  static UniqueString get_unique_string() {
    return std::move(ClockTime::get_system_time().get_string());
  }

  ClockTime age() const { return get_system_time() - *this; }

  UniqueString get_string() const {
    return std::move(
      UniqueString().format("%ld.%09ld", seconds(), nanoseconds()));
  }

  /*! \details Returns a pointer to a strut timespec. */
  struct timespec *timespec() {
    return &m_value;
  }
  /*! \details Returns a pointer to a strut timespec (read-only). */
  const struct timespec *timespec() const { return &m_value; }

  operator MicroTime() const {
    return MicroTime(seconds() * 1000000UL + nanoseconds() / 1000UL);
  }

private:
  void assign(u32 seconds, u32 nanoseconds);
  static ClockTime add(const ClockTime &a, const ClockTime &b);
  static ClockTime subtract(const ClockTime &a, const ClockTime &b);
  struct timespec m_value;
};

} // namespace chrono

namespace printer {
class Printer;
printer::Printer &
operator<<(printer::Printer &printer, const chrono::ClockTime &a);
} // namespace printer

#endif /* CHRONO_API_CHRONO_CLOCK_TIME_HPP_ */
