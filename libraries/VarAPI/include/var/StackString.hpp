#ifndef VARAPI_VAR_STACKSTRING_HPP
#define VARAPI_VAR_STACKSTRING_HPP

#include <climits>

#include "String.hpp"
#include "StringView.hpp"

namespace var {

struct ReplaceCharacter {
  API_PMAZ(new_character, ReplaceCharacter, char, 0);
  API_PMAZ(old_character, ReplaceCharacter, char, 0);
};

struct StackStringObject {
  char *buffer = nullptr;
  size_t size{};

  auto capacity() const -> decltype(size);
  auto copy(const char *other, size_t size) const -> void;
  auto append(const char value) const -> void;
  auto append(var::StringView value) const -> void;
  auto assign(const var::StringView value) const -> void;
  auto assign(const char *value) const -> void;
  auto move(char *other, size_t other_size) -> void;
  auto replace(char old_character, char new_character) const -> void;
  API_NO_DISCARD auto length() const -> size_t;
  API_NO_DISCARD auto back() const -> char;
  auto at(size_t offset) const -> char;
  auto to_upper() const -> void;
  auto to_lower() const -> void;
  auto pop_front(size_t count) -> void;
  auto pop_back(size_t count) -> void;
  auto truncate(size_t new_length) -> void;
};

template <class Derived, size_t Size> class StackString {
protected:
  char m_buffer[Size];
  char * buffer() const {
    return const_cast<char*>(m_buffer);
  }

public:
  using Base = StringView::Base;

  auto &clear() {
    m_buffer[0] = 0;
    m_buffer[Size - 1] = 0;
    return static_cast<Derived &>(*this);
  }

  API_NO_DISCARD bool is_empty() const { return m_buffer[0] == 0; }
  API_NO_DISCARD explicit operator bool() const { return m_buffer[0] != 0; }

  auto &append(const char a) {
    StackStringObject{buffer(), Size}.append(a);
    return static_cast<Derived &>(*this);
  }

  auto &append(const StringView a) {
    StackStringObject{buffer(), Size}.append(a);
    return static_cast<Derived &>(*this);
  }

  API_NO_DISCARD auto length() const {
    return StackStringObject{buffer(), Size}.length();
  }
  API_NO_DISCARD auto front() const { return m_buffer[0]; }
  API_NO_DISCARD auto back() const {
    return StackStringObject{buffer(), Size}.back();
  }

  API_NO_DISCARD constexpr size_t capacity() const { return Size - 1; }
  API_NO_DISCARD auto *data() { return buffer(); }
  API_NO_DISCARD const char *cstring() const { return m_buffer; }
  API_NO_DISCARD StringView string_view() const { return StringView(m_buffer); }

  Derived operator*(unsigned a) const {
    Derived result;
    for (auto i = 0U; i < a; i++) {
      result.append(string_view());
    }
    return result;
  }

  bool operator==(const StringView a) const { return string_view() == a; }
  bool operator!=(const StringView a) const { return string_view() != a; }

  bool operator==(const StackString &a) const {
    return string_view() == a.string_view();
  }

  bool operator!=(const StackString &a) const {
    return string_view() != a.string_view();
  }

  bool operator==(const char *a) const {
    return string_view() == StringView(a);
  }

  bool operator!=(const char *a) const {
    return string_view() != StringView(a);
  }

  bool operator<(const StackString &a) const {
    return string_view() < a.string_view();
  }

  bool operator>(const StackString &a) const {
    return string_view() > a.string_view();
  }

  API_NO_DISCARD char at(size_t offset) const {
    return StackStringObject{buffer(), Size}.at(offset);
  }

  template <typename... Args> auto &format(const char *format, Args... args) & {
    ::snprintf(m_buffer, capacity(), format, args...);
    return static_cast<Derived &>(*this);
  }

  template <typename... Args>
  auto &&format(const char *format, Args... args) && {
    ::snprintf(m_buffer, capacity(), format, args...);
    return static_cast<Derived &&>(*this);
  }

  auto &to_upper() {
    StackStringObject{buffer(), Size}.to_upper();
    return static_cast<Derived &>(*this);
  }

  auto &to_lower() {
    StackStringObject{buffer(), Size}.to_lower();
    return static_cast<Derived &>(*this);
  }

  auto &pop_front(size_t count = 1) {
    StackStringObject{buffer(), Size}.pop_front(count);
    return static_cast<Derived &>(*this);
  }

  auto &pop_back(size_t count = 1) {
    StackStringObject{buffer(), Size}.pop_back(count);
    return static_cast<Derived &>(*this);
  }

  auto &truncate(size_t new_length) {
    StackStringObject{buffer(), Size}.truncate(new_length);
    return static_cast<Derived &>(*this);
  }

  using Replace = ReplaceCharacter;

  auto &replace(const Replace &options) {
    StackStringObject{buffer(), Size}.replace(
      options.old_character,
      options.new_character);
    return static_cast<Derived &>(*this);
  }

  auto &operator()(const Replace &options) { return replace(options); }

protected:
  StackString() { m_buffer[0] = '\0'; }
  StackString(const StringView a) {
    StackStringObject{buffer(), Size}.assign(a);
  }
  StackString(const char *a) { StackStringObject{buffer(), Size}.assign(a); }

};

class IdString : public StackString<IdString, 24> {
public:
  IdString() = default;
  IdString(const StringView a) : StackString(a) {}
  IdString(const char *a) : StackString(a) {}
  // implicit conversion
  operator const char *() const { return m_buffer; }
};
using StackString24 = IdString;

class KeyString : public StackString<KeyString, 48> {
public:
  KeyString() = default;
  KeyString(const StringView a) : StackString(a) {}
  KeyString(const char *a) : StackString(a) {}
  // implicit conversion
  operator const char *() const { return m_buffer; }
};
using StackString48 = IdString;

class NameString : public StackString<NameString, NAME_MAX + 1> {
public:
  NameString() = default;
  NameString(const StringView a) : StackString(a) {}
  NameString(const char *a) : StackString(a) {}

  // implicit conversion
  operator const char *() const { return m_buffer; }
};

#if defined __win32
// on windows PATH_MAX is too small (261 chars)
#define PATH_STRING_LENGTH 4096
#else
#define PATH_STRING_LENGTH (PATH_MAX + 1)
#endif

class PathString : public StackString<PathString, PATH_STRING_LENGTH> {
public:
  PathString() = default;
  PathString(const StringView a) : StackString(a) {}
  PathString(const char *a) : StackString(a) {}

  PathString &operator&=(const StringView a) { return append(a); }

  PathString operator/(const var::StringView a) {
    return PathString(*this).append('/').append(a);
  }

  PathString operator&(const var::StringView a) {
    return PathString(*this).append(a);
  }

  // implicit conversion
  operator const char *() const { return m_buffer; }
};

PathString operator&(const StringView lhs, const StringView rhs);
PathString operator/(const StringView lhs, const StringView rhs);

#if defined __link
#define VAR_API_GENERAL_STRING_SIZE 4096
#else
#define VAR_API_GENERAL_STRING_SIZE 512
#endif

class GeneralString
  : public StackString<GeneralString, VAR_API_GENERAL_STRING_SIZE> {
public:
  GeneralString() = default;
  GeneralString(const StringView a) : StackString(a) {}
  GeneralString(const char *a) : StackString(a) {}
  // implicit conversion
  operator const char *() const { return m_buffer; }

  GeneralString &operator|=(const StringView a) { return append(a); }
  GeneralString operator|(const var::StringView a) {
    return GeneralString(string_view()).append(a);
  }
};

GeneralString operator|(StringView lhs, StringView rhs);

class NumberString : public StackString<NumberString, 64> {
public:
  template <typename T> NumberString(T value) {
    // guarantee null termination
    m_buffer[capacity()] = 0;
    constexpr const char *fmt
      = (std::is_same<T, int>::value || std::is_same<T, signed int>::value
         || std::is_same<T, short>::value
         || std::is_same<T, signed short>::value || std::is_same<T, char>::value
         || std::is_same<T, signed char>::value)
          ? "%d"
        : std::is_same<T, long>::value      ? "%ld"
        : std::is_same<T, long long>::value ? "%lld"
        : (std::is_same<T, unsigned>::value
           || std::is_same<T, unsigned short>::value
           || std::is_same<T, unsigned char>::value)
          ? "%u"
        : std::is_same<T, unsigned long>::value      ? "%lu"
        : std::is_same<T, unsigned long long>::value ? "%lld"
#if defined __link
        : std::is_same<T, double>::value ? "%f"
#endif
        : std::is_same<T, float>::value ? "%f"
                                        : nullptr;
    static_assert(fmt != nullptr, "NumberString can't handle type");

    snprintf(m_buffer, capacity(), fmt, value);
  }

  template <typename T> NumberString(T value, const char *format) {
    m_buffer[capacity()] = 0;
    ::snprintf(m_buffer, capacity(), format, value);
  }

  NumberString() = default;
  NumberString(const StringView a) : StackString(a) {}
  NumberString(const char *a) : StackString(a) {}

  API_NO_DISCARD int to_integer() const;
  API_NO_DISCARD float to_float() const;
  API_NO_DISCARD long to_long(Base base = Base::decimal) const;
  API_NO_DISCARD unsigned long
  to_unsigned_long(Base base = Base::decimal) const;

  // implicit conversion
  operator const char *() const { return m_buffer; }
};

using StackString64 = NumberString;

} // namespace var

#endif // VARAPI_VAR_STACKSTRING_HPP
