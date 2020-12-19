// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md
#ifndef SYSAPI_SYS_VERSION_HPP_
#define SYSAPI_SYS_VERSION_HPP_

#include "var/StackString.hpp"

namespace sys {

class Version {
public:
  Version() = default;
  Version(const var::StringView value) : m_version(value) {}

  u32 to_bcd() const;

  u16 to_bcd16() const { return to_bcd() >> 8; }

  static Version from_triple(u16 major, u8 minor, u8 patch);
  static Version from_u16(u16 major_minor);

  bool operator==(const Version &a) const { return compare(*this, a) == 0; }
  bool operator>(const Version &a) const { return compare(*this, a) > 0; }
  bool operator<(const Version &a) const { return compare(*this, a) < 0; }
  bool operator<=(const Version &a) const { return compare(*this, a) <= 0; }
  bool operator>=(const Version &a) const { return compare(*this, a) >= 0; }

  const var::StringView string_view() const { return m_version.string_view(); }
  const char *cstring() const { return m_version.cstring(); }
  static int compare(const Version &a, const Version &b);

private:
  var::KeyString m_version;
};
} // namespace sys

#endif // SYSAPI_SYS_VERSION_HPP_
