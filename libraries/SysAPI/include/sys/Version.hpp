/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
#ifndef SYSAPI_SYS_VERSION_HPP_
#define SYSAPI_SYS_VERSION_HPP_

#include "var/StackString.hpp"

namespace sys {

class Version {
public:
  Version() = default;
  Version(const var::StringView value) : m_version(value) {}
  // Version(const var::String &value) : m_version(value.string_view()) {}

  u32 to_bcd() const;

  u16 to_bcd16() const { return to_bcd() >> 8; }

  static Version from_triple(u16 major, u8 minor, u8 patch);
  static Version from_u16(u16 major_minor);

  bool operator==(const Version &a) const { return compare(*this, a) == 0; }

  bool operator>(const Version &a) const { return compare(*this, a) > 0; }

  bool operator<(const Version &a) const { return compare(*this, a) < 0; }

  bool operator<=(const Version &a) const { return compare(*this, a) <= 0; }

  /*! \details Returns true if this version string
   * is greater than or equal to a.
   *
   * @param a version compared against.
   *
   * See compare() for more details.
   *
   */
  bool operator>=(const Version &a) const { return compare(*this, a) >= 0; }

  const var::StringView string_view() const { return m_version.string_view(); }
  const char *cstring() const { return m_version.cstring(); }

  /*! \details Compares two version strings.
   *
   * @param a first string
   * @param b second string
   * @return 1 if a > b, 0 if a == b or -1 if a < b
   *
   * If a is formatted as x.y.z and b is formatted
   * as x.y then a is greater than b and 1 will be returned. If b
   * uses x.y.z and a uses x.y then -1 will be returned.
   *
   * Generally, a project uses one format or the other
   * and the two formats should not need to be compared.
   *
   * Also, an empty version is always less than a version that
   * is populated.
   *
   */
  static int compare(const Version &a, const Version &b);

private:
  var::KeyString m_version;
};
} // namespace sys

#endif // SYSAPI_SYS_VERSION_HPP_
