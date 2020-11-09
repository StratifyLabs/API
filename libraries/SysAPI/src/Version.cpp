/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
#include "sys/Version.hpp"
#include "var/Tokenizer.hpp"

using namespace sys;

Version Version::from_triple(u16 major, u8 minor, u8 patch) {
  Version result;
  result.m_version.format("%d.%d.%d", major, minor, patch);
  return std::move(result);
}

Version Version::from_u16(u16 major_minor) {
  Version result;
  result.m_version.format("%d.%d", major_minor >> 8, major_minor & 0xff);
  return std::move(result);
}

u32 Version::to_bcd() const {
  var::StringViewList tokens = m_version.string_view().split(".");
  if (tokens.count() == 0) {
    return 0;
  }

  if (tokens.count() == 1) {
    return tokens.at(0).to_unsigned_long();
  }

  if (tokens.count() == 2) {
    return (tokens.at(0).to_unsigned_long() << 16)
           | (tokens.at(1).to_unsigned_long() << 8);
  }

  return (tokens.at(0).to_unsigned_long() << 16)
         | (tokens.at(1).to_unsigned_long() << 8)
         | (tokens.at(2).to_unsigned_long());
}

int Version::compare(const Version &a, const Version &b) {
  var::StringViewList a_tokens = a.m_version.string_view().split(".");
  var::StringViewList b_tokens = b.m_version.string_view().split(".");

  if (a_tokens.count() > b_tokens.count()) {
    return 1;
  }

  if (a_tokens.count() < b_tokens.count()) {
    return -1;
  }

  // count is equal -- check the numbers
  for (u32 i = 0; i < a_tokens.count(); i++) {
    if (a_tokens.at(i).to_unsigned_long() > b_tokens.at(i).to_unsigned_long()) {
      return 1;
    }
    if (a_tokens.at(i).to_unsigned_long() < b_tokens.at(i).to_unsigned_long()) {
      return -1;
    }
  }

  // versions are equal
  return 0;
}
