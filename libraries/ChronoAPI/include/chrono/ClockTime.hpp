// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef CHRONO_API_CHRONO_CLOCK_TIME_HPP_
#define CHRONO_API_CHRONO_CLOCK_TIME_HPP_

#include <sdk/types.h>
#include <ctime>

#include "DateTime.hpp"

#include "var/StackString.hpp"

namespace chrono {

class ClockTime {
public:
  enum class ClockId { realtime = CLOCK_REALTIME };

  static ClockTime get_system_time(ClockId clock_id = ClockId::realtime);
  API_MAYBE_UNUSED static ClockTime get_system_resolution(ClockId clock_id = ClockId::realtime);

  ClockTime() = default;
  explicit ClockTime(const struct timespec &nano_time) : m_value(nano_time) {}
  explicit ClockTime(const MicroTime &micro_time);


  static ClockTime from_seconds(u32 seconds) {
    return ClockTime().set_seconds(seconds);
  }

  static ClockTime from_string(var::StringView value);

  ClockTime &reset() {
    m_value.tv_sec = 0;
    m_value.tv_nsec = 0;
    return *this;
  }

  ClockTime &set_seconds(u32 seconds) {
    m_value.tv_sec = time_t(seconds);
    return *this;
  }

  ClockTime &set_nanoseconds(u32 value) {
    m_value.tv_nsec = value;
    return *this;
  }

  operator const struct timespec *() const { return &m_value; }
  operator struct timespec *() { return &m_value; }

  API_NO_DISCARD bool is_valid() const { return *this != invalid(); }

  static ClockTime invalid() {
    return ClockTime().set_seconds(-1).set_nanoseconds(-1);
  }

  bool operator>(const ClockTime &a) const;
  bool operator<(const ClockTime &a) const;
  bool operator>=(const ClockTime &a) const;
  bool operator<=(const ClockTime &a) const;
  bool operator==(const ClockTime &a) const;
  bool operator!=(const ClockTime &a) const;

  ClockTime operator+(const ClockTime &a) const { return add(*this, a); }
  ClockTime operator-(const ClockTime &a) const { return subtract(*this, a); }
  API_NO_DISCARD API_MAYBE_UNUSED ClockTime get_age() const;

  ClockTime &operator+=(const ClockTime &a) {
    *this = add(*this, a);
    return *this;
  }

  ClockTime &operator-=(const ClockTime &a) {
    // subtract nano time
    *this = subtract(*this, a);
    return *this;
  }

  API_NO_DISCARD s32 seconds() const { return m_value.tv_sec; }
  API_NO_DISCARD s32 nanoseconds() const { return m_value.tv_nsec; }

  using UniqueString = var::KeyString;
  API_NO_DISCARD UniqueString to_unique_string() const {
    return UniqueString().format("%ld.%09ld", seconds(), nanoseconds());
  }

  template<class StringClass> StringClass to_string() const {
    return StringClass().format("%ld.%09ld", seconds(), nanoseconds());
  }

  struct timespec *timespec() {
    return &m_value;
  }
  API_NO_DISCARD const struct timespec *timespec() const { return &m_value; }

  operator MicroTime() const {
    return MicroTime(seconds() * 1000000UL + nanoseconds() / 1000UL);
  }

private:
  void assign(u32 seconds, u32 nanoseconds);
  static ClockTime add(const ClockTime &a, const ClockTime &b);
  static ClockTime subtract(const ClockTime &a, const ClockTime &b);
  struct timespec m_value = {};
};

} // namespace chrono

namespace printer {
class Printer;
printer::Printer &
operator<<(printer::Printer &printer, const chrono::ClockTime &a);
} // namespace printer

#endif /* CHRONO_API_CHRONO_CLOCK_TIME_HPP_ */
