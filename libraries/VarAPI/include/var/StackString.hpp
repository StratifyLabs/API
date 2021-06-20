#ifndef VARAPI_VAR_STACKSTRING_HPP
#define VARAPI_VAR_STACKSTRING_HPP

#include <limits.h>

#include "String.hpp"
#include "StringView.hpp"

namespace var {

template <class Derived, int Size> class StackString {
public:
  using Base = StringView::Base;
  Derived &clear() {
    m_buffer[0] = 0;
    m_buffer[Size - 1] = 0;
    return static_cast<Derived &>(*this);
  }

  bool is_empty() const { return m_buffer[0] == 0; }

  Derived &append(const char a) {
    const size_t len = strnlen(m_buffer, Size - 1);
    if (len < Size - 1) {
      m_buffer[len] = a;
      m_buffer[len + 1] = 0;
    }
    return static_cast<Derived &>(*this);
  }

  Derived &append(const StringView a) {
    const size_t len = strnlen(m_buffer, Size - 1);
    const size_t s = a.length() > Size - 1 - len ? Size - 1 - len : a.length();
    m_buffer[len + s] = 0;
    memcpy(m_buffer + len, a.data(), s);
    return static_cast<Derived &>(*this);
  }

  size_t length() const { return strnlen(m_buffer, Size - 1); }
  char back() const {
    const size_t len = length();
    if (len) {
      return m_buffer[length() - 1];
    }
    return 0;
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

  API_NO_DISCARD constexpr size_t capacity() const { return Size - 1; }
  API_NO_DISCARD char *data() { return m_buffer; }
  API_NO_DISCARD const char *cstring() const { return m_buffer; }
  API_NO_DISCARD StringView string_view() const { return StringView(m_buffer); }

  API_NO_DISCARD char at(size_t offset) const {
    if (offset < Size) {
      return m_buffer[offset];
    }
    return 0;
  }

  template <typename... Args>
  Derived &format(const char *format, Args... args) {
    ::snprintf(m_buffer, capacity(), format, args...);
    return static_cast<Derived &>(*this);
  }

  Derived &to_upper() {
    for (size_t i = 0; i < capacity(); i++) {
      m_buffer[i] = std::toupper(m_buffer[i]);
    }
    return static_cast<Derived &>(*this);
  }

  Derived &to_lower() {
    for (size_t i = 0; i < capacity(); i++) {
      m_buffer[i] = std::tolower(m_buffer[i]);
    }
    return static_cast<Derived &>(*this);
  }

  Derived &pop_front(size_t count = 1){
    const auto safe_count = count < capacity() ? count : capacity();
    for (size_t i = safe_count; i < capacity(); i++) {
      m_buffer[i-safe_count] = m_buffer[i];
    }
    return static_cast<Derived &>(*this);
  }

  Derived &pop_back(size_t count = 1){
    const auto end = length() > count ? length() - count : 0;
    m_buffer[end] = 0;
    return static_cast<Derived &>(*this);
  }

  class Replace {
    API_AF(Replace, char, old_character, 0);
    API_AF(Replace, char, new_character, 0);
  };

  Derived &replace(const Replace &options) {
    for (size_t i = 0; i < capacity(); i++) {
      if (m_buffer[i] == options.old_character()) {
        m_buffer[i] = options.new_character();
      }
    }
    return static_cast<Derived &>(*this);
  }

  inline Derived &operator()(const Replace &options) {
    return replace(options);
  }


protected:
  StackString() { m_buffer[0] = 0; }
  StackString(const StringView a) {
    m_buffer[Size - 1] = 0;
    const size_t s = a.length() > Size - 1 ? Size - 1 : a.length();
    m_buffer[s] = 0;
    memcpy(m_buffer, a.data(), s);
  }

  StackString(const char *a) {
    m_buffer[Size - 1] = 0;
    if( a == nullptr ){
      m_buffer[0] = 0;
    } else {
      strncpy(m_buffer, a, Size - 1);
    }
  }


  char m_buffer[Size];
};

class IdString : public StackString<IdString, 24> {
public:
  IdString() {}
  IdString(const StringView a) : StackString(a) {}
  IdString(const char *a) : StackString(a) {}
  // implicit conversion
  operator const char *() const { return m_buffer; }
};

class NameString : public StackString<NameString, NAME_MAX + 1> {
public:
  NameString() {}
  NameString(const StringView a) : StackString(a) {}
  NameString(const char *a) : StackString(a) {}

  // implicit conversion
  operator const char *() const { return m_buffer; }
};

class KeyString : public StackString<KeyString, 48> {
public:
  KeyString() {}
  KeyString(const StringView a) : StackString(a) {}
  KeyString(const char *a) : StackString(a) {}
  // implicit conversion
  operator const char *() const { return m_buffer; }
};

class PathString : public StackString<PathString, PATH_MAX + 1> {
public:
  PathString() {}
  PathString(const StringView a) : StackString(a) {}
  PathString(const char *a) : StackString(a) {}

  PathString &operator&=(const StringView a) { return append(a); }

  PathString operator/(const var::StringView a) {
    return PathString(*this).append("/").append(a);
  }

  PathString operator&(const var::StringView a) {
    return PathString(*this).append(a);
  }

  // implicit conversion
  operator const char *() const { return m_buffer; }
};

PathString operator&(const StringView lhs, const StringView rhs);
PathString operator/(const StringView lhs, const StringView rhs);

class GeneralString : public StackString<GeneralString, 256> {
public:
  GeneralString() {}
  GeneralString(const StringView a) : StackString(a) {}
  GeneralString(const char *a) : StackString(a) {}
  // implicit conversion
  operator const char *() const { return m_buffer; }

  GeneralString &operator|=(const StringView a) { return append(a); }
  GeneralString operator|(const var::StringView a) {
    return GeneralString(string_view()).append(a);
  }
};

GeneralString operator|(const StringView lhs, const StringView rhs);

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
          : std::is_same<T, long>::value
              ? "%ld"
              : std::is_same<T, long long>::value
                  ? "%lld"
                  : (std::is_same<T, unsigned>::value
                     || std::is_same<T, unsigned short>::value
                     || std::is_same<T, unsigned char>::value)
                      ? "%u"
                      : std::is_same<T, unsigned long>::value
                          ? "%lu"
                          : std::is_same<T, unsigned long long>::value
                              ? "%lld"
                              : std::is_same<T, float>::value ? "%f" : nullptr;
    static_assert(fmt != nullptr, "NumberString can't handle type");

    snprintf(m_buffer, capacity(), fmt, value);
  }

  template <typename T> NumberString(T value, const char *format) {
    m_buffer[capacity()] = 0;
    ::snprintf(m_buffer, capacity(), format, value);
  }

  NumberString() {}
  NumberString(const StringView a) : StackString(a) {}
  NumberString(const char *a) : StackString(a) {}

  int to_integer() const;
  float to_float() const;
  long to_long(Base base = Base::decimal) const;
  unsigned long to_unsigned_long(Base base = Base::decimal) const;

  // implicit conversion
  operator const char *() const { return m_buffer; }
};

using StackString64 = NumberString;

} // namespace var

#endif // VARAPI_VAR_STACKSTRING_HPP
