
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

auto StackStringObject::append(const char value) const -> void {
  const auto len = strnlen(buffer, size - 1);
  if (len < size - 1) {
    buffer[len] = value;
    buffer[len + 1] = 0;
  }
}

auto StackStringObject::assign(const var::StringView value) const -> void {
  if (buffer == value.data()) {
    // don't assign to self
    return;
  }
  buffer[size - 1] = 0;
  const auto length = value.length() > size - 1 ? size - 1 : value.length();
  buffer[length] = 0;
  memcpy(buffer, value.data(), length);
}

auto StackStringObject::assign(const char *value) const -> void {
  if (buffer == value) {
    // don't assign to self
    return;
  }
  if (value == nullptr) {
    buffer[0] = 0;
  } else {
    const auto capacity = this->capacity();
    buffer[capacity] = 0;
    strncpy(buffer, value, capacity);
  }
}

auto StackStringObject::copy(const char *other, size_t size) const -> void {
  if (buffer == other) {
    return;
  }
  API_ASSERT(size == this->size);
  const auto capacity = this->capacity();
  buffer[capacity] = '\0';
  strncpy(buffer, other, capacity);
}

auto StackStringObject::move(char *other, size_t other_size) -> void {
  if (buffer == other) {
    // don't assign to self
    return;
  }
  API_ASSERT(size == other_size);
  char tmp[size];
  strncpy(tmp, other, size);
  strncpy(other, buffer, size);
  strncpy(buffer, tmp, size);
}

auto StackStringObject::replace(char old_character, char new_character) const
  -> void {
  for (const auto i : api::Index(size)) {
    if (buffer[i] == old_character) {
      buffer[i] = new_character;
    }
  }
}

auto StackStringObject::append(var::StringView value) const -> void {
  const auto current_length = length();
  const auto append_size = value.length() > size - 1 - current_length
                             ? size - 1 - current_length
                             : value.length();
  buffer[current_length + append_size] = 0;
  memcpy(buffer + current_length, value.data(), append_size);
}

auto StackStringObject::back() const -> char {
  const auto len = length();
  if (len) {
    return buffer[len - 1];
  }
  return '\0';
}
auto StackStringObject::length() const -> size_t {
  return strnlen(buffer, size - 1);
}
auto StackStringObject::at(size_t offset) const -> char {
  if (offset < size) {
    return buffer[offset];
  }
  return '\0';
}
auto StackStringObject::to_upper() const -> void {
  const auto total = capacity();
  for (auto i = 0; i < total && buffer[i]; i++) {
    buffer[i] = std::toupper(buffer[i]);
  }
}
auto StackStringObject::to_lower() const -> void {
  const auto total = capacity();
  for (auto i = 0; i < total && buffer[i]; i++) {
    buffer[i] = std::tolower(buffer[i]);
  }
}
auto StackStringObject::pop_front(size_t count) -> void {
  const auto current_length = length();
  if (count >= current_length) {
    buffer[0] = '\0';
    return;
  }

  const auto total = current_length - count;
  for (auto i = 0; i < total; ++i) {
    buffer[i] = buffer[i + count];
  }
  buffer[total] = '\0';
}
auto StackStringObject::pop_back(size_t count) -> void {
  const auto total = length();
  const auto end = total > count ? total - count : 0;
  buffer[end] = 0;
}

auto StackStringObject::truncate(size_t new_length) -> void {
  const auto current_length = length();
  const auto end = current_length > new_length ? new_length : current_length;
  buffer[end] = 0;
}
auto StackStringObject::capacity() const -> decltype(size) { return size - 1; }

} // namespace var