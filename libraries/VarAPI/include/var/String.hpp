/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.

#ifndef VAR_API_STRING_HPP_
#define VAR_API_STRING_HPP_

#include <cstdarg>

#include <string>

#include "StringView.hpp"
#include "Vector.hpp"

namespace var {

class View;
class Data;

class String : public api::ExecutionContext {
public:
  constexpr static size_t npos = std::string::npos;
  using Base = StringView::Base;

  using iterator = typename std::string::iterator;
  using const_iterator = typename std::string::const_iterator;
  using reverse_iterator = typename std::string::reverse_iterator;
  using const_reverse_iterator = typename std::string::const_reverse_iterator;

  API_NO_DISCARD const_iterator begin() const noexcept { return m_string.begin(); }
  API_NO_DISCARD iterator begin() noexcept { return m_string.begin(); }

  API_NO_DISCARD const_iterator end() const noexcept { return m_string.end(); }
  API_NO_DISCARD iterator end() noexcept { return m_string.end(); }

  API_NO_DISCARD  const_iterator cbegin() const noexcept { return m_string.cbegin(); }
  API_NO_DISCARD const_iterator cend() const noexcept { return m_string.cend(); }

  API_NO_DISCARD const_reverse_iterator rbegin() const noexcept { return m_string.rbegin(); }
  API_NO_DISCARD reverse_iterator rbegin() noexcept { return m_string.rbegin(); }

  API_NO_DISCARD const_reverse_iterator rend() const noexcept { return m_string.rend(); }
  API_NO_DISCARD reverse_iterator rend() noexcept { return m_string.rend(); }

  API_NO_DISCARD const_reverse_iterator crbegin() const noexcept { return m_string.crbegin(); }
  API_NO_DISCARD const_reverse_iterator crend() const noexcept { return m_string.crend(); }

  class Erase {
    API_AF(Erase, size_t, position, 0);
    API_AF(Erase, size_t, length, npos);
  };

  class Insert {
    API_ACCESS_FUNDAMENTAL(Insert, size_t, position, 0);
    API_ACCESS_FUNDAMENTAL(Insert, size_t, length, 0);
    API_ACCESS_FUNDAMENTAL(Insert, size_t, sub_position, 0);
    API_ACCESS_FUNDAMENTAL(Insert, size_t, sub_length, npos);
  };

  class Compare {
    API_ACCESS_FUNDAMENTAL(Compare, size_t, position, 0);
    API_ACCESS_FUNDAMENTAL(Compare, size_t, length, 0);
    API_ACCESS_FUNDAMENTAL(Compare, size_t, sub_position, 0);
    API_ACCESS_FUNDAMENTAL(Compare, size_t, sub_length, npos);
  };

  String() = default;

  explicit String(const char *s) {
    if (s != nullptr) {
      m_string = s;
    }
  }

  explicit String(const Data &data);

  explicit String(StringView s) : m_string(s.m_string_view) {}
  String(const String &s) : m_string(s.m_string) {}
  String(const char *s, size_t length) : m_string(s, length) {}
  String(size_t length, char c) : m_string(length, c) {}
  String(String &&s) noexcept : m_string(std::move(s.m_string)) {}
  String(
    std::initializer_list<char> il) // cppcheck-suppress[noExplicitConstructor]
    : m_string(il) {}
  String &operator=(const char *s) {
    if (s == nullptr) {
      m_string = std::string();
    } else {
      m_string = s;
    }
    return *this;
  }
  String &operator=(const String &s) {
    m_string = s.m_string;
    return *this;
  }
  String &operator=(char c) {
    m_string = c;
    return *this;
  }

  explicit String(const std::string &a) : m_string(a) {}
  explicit String(std::string &&s) : m_string(s) {}
  explicit String(const var::View &item);

  String &operator+=(char a) {
    m_string += a;
    return *this;
  }
  String &operator+=(const String &a) {
    m_string += a.m_string;
    return *this;
  }
  String &operator+=(StringView a) {
    m_string += a.m_string_view;
    return *this;
  }

  String & append(const StringView &a){
    m_string.append(a.m_string_view);
    return *this;
  }

  String &operator+=(std::initializer_list<char> il) {
    m_string += il;
    return *this;
  }

  String &operator*=(u32 a) {
    reserve(a * length());
    for (u32 i = 0; i < a; i++) {
      m_string += m_string;
    }
    return *this;
  }

  String operator*(u32 a) const {
    String result;
    result.reserve(a * length());
    for (u32 i = 0; i < a; i++) {
      result.m_string += m_string;
    }
    return result;
  }

  String operator+(const String &rhs) const {
    return String(m_string + rhs.m_string);
  }

  String operator+(String &&rhs) const {
    return String(m_string + std::move(rhs.m_string));
  }

  String operator+(char rhs) const { return String(m_string + rhs); }

  API_NO_DISCARD bool is_empty() const { return m_string.empty(); }

  String &insert(const StringView string_to_insert, const Insert &options) {
    if (options.sub_position() == npos) {
      m_string.insert(options.position(), string_to_insert.m_string_view);
    } else {
      m_string.insert(options.position(), string_to_insert.m_string_view,
                      options.sub_position(), options.sub_length());
    }
    return *this;
  }

  String &operator()(const StringView string_to_insert, const Insert &options) {
    return insert(string_to_insert, options);
  }

  String &erase(const Erase &options) {
    m_string.erase(options.position(), options.length());
    return *this;
  }


  String &erase(StringView string_to_erase, size_t position = 0);
  String &operator()(const Erase &options) { return erase(options); }

  class Replace {
    API_AC(Replace, StringView, old_string);
    API_AC(Replace, StringView, new_string);
    API_AF(Replace, size_t, position, 0);
    API_AF(Replace, size_t, count, 0);
  };
  String &replace(const Replace &options);
  String &operator()(const Replace &options) { return replace(options); }

  API_NO_DISCARD size_t count(var::StringView to_count) const;
  API_NO_DISCARD size_t length() const { return m_string.length(); }
  API_NO_DISCARD ssize_t length_signed() const {
    return static_cast<ssize_t>(m_string.length());
  }

  String &clear() {
    m_string.clear();
    return *this;
  }

  String &free() { return *this = String(); }

  String &push_back(char a) {
    m_string.push_back(a);
    return *this;
  }

  String &pop_back(size_t pop_size = 1) {
    while (length() && pop_size--) {
      m_string.pop_back();
    }
    return *this;
  }

  String &pop_front(size_t pop_size = 1) {
    return erase(Erase().set_position(0).set_length(pop_size));
  }

  API_NO_DISCARD char &at(size_t pos) { return m_string.at(pos); }
  API_NO_DISCARD const char &at(size_t pos) const { return m_string.at(pos); }

  API_NO_DISCARD char &front() { return m_string.front(); }
  API_NO_DISCARD const char &front() const { return m_string.front(); }

  API_NO_DISCARD char &back() { return m_string.back(); }
  API_NO_DISCARD const char &back() const { return m_string.back(); }

  String &resize(size_t size) {
    m_string.resize(size);
    return *this;
  }

  String &reserve(size_t size) {
    m_string.reserve(size);
    return *this;
  }

  String &format(const char *format, ...);
  String &vformat(const char *fmt, va_list list);

  String &to_upper();
  String &to_lower();

  API_NO_DISCARD const char *cstring() const { return m_string.c_str(); }
  API_NO_DISCARD char *to_char() { return &m_string[0]; }

  API_NO_DISCARD int compare(const String &string_to_compare) const {
    return m_string.compare(string_to_compare.m_string);
  }

  API_NO_DISCARD int compare(const String &string_to_compare,
                             const Compare &options) const {
    return m_string.compare(
      options.position(),
      options.length(),
      string_to_compare.m_string,
      options.sub_position(),
      options.sub_length());
  }

  bool operator==(const String &a) const { return m_string == a.m_string; }
  bool operator!=(const String &a) const { return m_string != a.m_string; }

  bool operator==(StringView a) const { return m_string == a.m_string_view; }
  bool operator!=(StringView a) const { return m_string != a.m_string_view; }

  bool operator==(const char *a) const { return m_string == a; }
  bool operator!=(const char *a) const { return m_string != a; }

  bool operator>(const String &a) const { return m_string > a.m_string; }
  bool operator<(const String &a) const { return m_string < a.m_string; }
  bool operator>=(const String &a) const { return m_string >= a.m_string; }
  bool operator<=(const String &a) const { return m_string <= a.m_string; }

  API_NO_DISCARD int to_integer() const { return ::atoi(cstring()); }

  API_NO_DISCARD float to_float() const;

  API_NO_DISCARD long to_long(Base base = Base::decimal) const {
    return ::strtol(cstring(), nullptr, static_cast<int>(base));
  }

  API_NO_DISCARD unsigned long
  to_unsigned_long(Base base = Base::decimal) const {
    return ::strtoul(cstring(), nullptr, static_cast<int>(base));
  }

  API_NO_DISCARD u32 capacity() const { return m_string.capacity(); }

  API_NO_DISCARD StringViewList split(StringView delimiter) const;

  API_NO_DISCARD StringView string_view() const {
    return {cstring(), length()};
  }

  API_NO_DISCARD static const String &empty_string() { return m_empty_string; }

private:
  friend class StringView;
  std::string m_string;
  static String m_empty_string;
};

String operator+(StringView lhs, const String &rhs);
String operator+(StringView lhs, StringView rhs);
String operator+(const String &lhs, StringView rhs);
String operator+(StringView lhs, String &&rhs);

using StringList = Vector<String>;

} // namespace var

#endif /* VAR_API_STRING_HPP_ */
