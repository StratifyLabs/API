
#include "var/StackString.hpp"

using namespace var;

u32 m_stack_string_unused = 0;

int NumberString::to_integer() const { return ::atoi(cstring()); }
float NumberString::to_float() const { return ::atof(cstring()); }

long NumberString::to_long(Base base) const {
  return ::strtol(cstring(), nullptr, static_cast<int>(base));
}

unsigned long NumberString::to_unsigned_long(Base base) const {
  return ::strtoul(cstring(), nullptr, static_cast<int>(base));
}

PathString var::operator&(const StringView lhs, const StringView rhs) {
  return PathString(lhs).append(rhs);
}

PathString var::operator/(const StringView lhs, const StringView rhs) {
  return PathString(lhs).append("/").append(rhs);
}

GeneralString var::operator|(const StringView lhs, const StringView rhs) {
  return GeneralString(lhs).append(rhs);
}
