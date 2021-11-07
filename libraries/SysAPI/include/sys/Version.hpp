// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md
#ifndef SOSAPI_VERSION_HPP_
#define SOSAPI_VERSION_HPP_

#include "var/StackString.hpp"

namespace sys {

class Version {
public:
  Version() = default;
  explicit Version(const var::StringView value) : m_version(value) {}

  API_NO_DISCARD u32 to_bcd() const;
  API_NO_DISCARD u16 to_bcd16() const { return to_bcd() >> 8; }

  API_NO_DISCARD static Version from_triple(u16 major, u8 minor, u8 patch);
  API_NO_DISCARD static Version from_u16(u16 major_minor);

  bool operator==(const Version &a) const { return compare(*this, a) == 0; }
  bool operator>(const Version &a) const { return compare(*this, a) > 0; }
  bool operator<(const Version &a) const { return compare(*this, a) < 0; }
  bool operator<=(const Version &a) const { return compare(*this, a) <= 0; }
  bool operator>=(const Version &a) const { return compare(*this, a) >= 0; }

  API_NO_DISCARD var::StringView string_view() const {
    return m_version.string_view();
  }
  API_NO_DISCARD const char *cstring() const { return m_version.cstring(); }
  API_NO_DISCARD static int compare(const Version &a, const Version &b);

private:
  var::KeyString m_version;
};
} // namespace sys

#endif // SOSAPI_VERSION_HPP_
