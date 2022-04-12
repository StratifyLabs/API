
#include "var/StackString.hpp"

namespace var {

int NumberString::to_integer() const { return ::atoi(cstring()); }
float NumberString::to_float() const {
#if defined __link
  return ::atof(cstring());
#else
  return ::atoff(cstring());
#endif
}


long NumberString::to_long(Base base) const {
  return ::strtol(cstring(), nullptr, static_cast<int>(base));
}

unsigned long NumberString::to_unsigned_long(Base base) const {
  return ::strtoul(cstring(), nullptr, static_cast<int>(base));
}

PathString operator&(const StringView lhs, const StringView rhs) {
  return PathString(lhs).append(rhs);
}

PathString operator/(const StringView lhs, const StringView rhs) {
  return PathString(lhs).append("/").append(rhs);
}

GeneralString operator|(const StringView lhs, const StringView rhs) {
  return GeneralString(lhs).append(rhs);
}


} // namespace var