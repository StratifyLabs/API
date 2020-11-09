/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
#ifndef VAR_API_STRING_VIEW_HPP
#define VAR_API_STRING_VIEW_HPP

#include <cstring>
#include <string>
#include <string_view>

#include "api/api.hpp"

#include "Vector.hpp"

namespace var {

class String;
class Data;
class IdString;
class KeyString;
class NumberString;
class PathString;
class NameString;
class GeneralString;

class StringView {
public:
  constexpr static size_t npos = std::string_view::npos;

  enum class Base { octal = 8, decimal = 10, hexadecimal = 16 };

  StringView() : m_string_view("") {}
  StringView(const char value) : m_string_view(&value, 1) {}
  StringView(const char *value) : m_string_view(value) {}
  StringView(const String &value);
  StringView(const IdString &value);
  StringView(const KeyString &value);
  StringView(const NumberString &value);
  StringView(const PathString &value);
  StringView(const NameString &value);
  StringView(const GeneralString &value);

  StringView(const char *value, size_t length) {
    m_string_view = std::string_view(value, length);
  }

  bool is_null() const { return m_string_view.data() == nullptr; }

  StringView &set_null() {
    m_string_view = std::string_view(nullptr, 0);
    return *this;
  }

  bool is_null_terminated() const { return data() && (data()[length()] == 0); }

  char at(size_t value) const { return m_string_view.at(value); }
  char front() const { return m_string_view.front(); }
  char back() const { return m_string_view.back(); }
  size_t length() const { return m_string_view.length(); }

  bool is_empty() const { return m_string_view.empty(); }

  StringView &pop_front(size_t length = 1) {
    m_string_view.remove_prefix(length);
    return *this;
  }

  StringView &pop_back(size_t length = 1) {
    m_string_view.remove_suffix(length);
    return *this;
  }

  class GetSubstring {
    API_AF(GetSubstring, size_t, position, 0);
    API_AF(GetSubstring, size_t, length, npos);
  };

  StringView get_substring(const GetSubstring &options) const;
  inline StringView operator()(const GetSubstring &options) const {
    return get_substring(options);
  }

  StringView get_substring_at_position(size_t position) const;
  StringView get_substring_with_length(size_t length) const;

  var::Vector<StringView> split(StringView delimeters) const;

  using iterator = typename std::string_view::iterator;
  using const_iterator = typename std::string_view::const_iterator;
  using reverse_iterator = typename std::string_view::reverse_iterator;
  using const_reverse_iterator =
    typename std::string_view::const_reverse_iterator;

  const_iterator begin() const noexcept { return m_string_view.begin(); }
  iterator begin() noexcept { return m_string_view.begin(); }

  const_iterator end() const noexcept { return m_string_view.end(); }
  iterator end() noexcept { return m_string_view.end(); }

  const_iterator cbegin() const noexcept { return m_string_view.cbegin(); }
  const_iterator cend() const noexcept { return m_string_view.cend(); }

  const_reverse_iterator rbegin() const noexcept {
    return m_string_view.rbegin();
  }
  reverse_iterator rbegin() noexcept { return m_string_view.rbegin(); }

  const_reverse_iterator rend() const noexcept { return m_string_view.rend(); }
  reverse_iterator rend() noexcept { return m_string_view.rend(); }

  const_reverse_iterator crbegin() const noexcept {
    return m_string_view.crbegin();
  }
  const_reverse_iterator crend() const noexcept {
    return m_string_view.crend();
  }

  size_t find(StringView a, size_t position = 0) const {
    return m_string_view.find(a.m_string_view, position);
  }

  size_t find(char a, size_t position = 0) const {
    return m_string_view.find(a, position);
  }

  size_t find_first_of(StringView a, size_t position = 0) const {
    return m_string_view.find_first_of(a.m_string_view, position);
  }

  size_t find_first_not_of(StringView a, size_t position = 0) const {
    return m_string_view.find_first_not_of(a.m_string_view, position);
  }

  size_t reverse_find(StringView a, size_t position = npos) const {
    return m_string_view.rfind(a.m_string_view, position);
  }

  size_t reverse_find(char a, size_t position = npos) const {
    return m_string_view.rfind(a, position);
  }

  size_t find_last_of(StringView a, size_t position = 0) const {
    return m_string_view.find_last_of(a.m_string_view, position);
  }

  size_t find_last_not_of(StringView a, size_t position = 0) const {
    return m_string_view.find_last_not_of(a.m_string_view, position);
  }

  bool operator==(const StringView a) const {
    return a.m_string_view == m_string_view;
  }

  bool operator!=(const StringView a) const {
    return a.m_string_view != m_string_view;
  }

  bool operator==(const char *a) const { return StringView(a) == *this; }
  bool operator!=(const char *a) const { return StringView(a) != *this; }

  bool operator==(const String &a) const;
  bool operator!=(const String &a) const;

  bool operator>(StringView a) const { return m_string_view > a.m_string_view; }

  bool operator<(StringView a) const { return m_string_view < a.m_string_view; }

  long to_long(Base base = Base::decimal) const;
  float to_float() const;
  unsigned long to_unsigned_long(Base base = Base::decimal) const;
  int to_integer() const;

  const char *data() const { return m_string_view.data(); }

  String get_string() const;

  // static StringView boolean(bool a) { return a ? "true" : "false"; }

  static String get_string(const StringView &a);

private:
  friend class String;
  std::string_view m_string_view;

  StringView(const std::string_view string_view) : m_string_view(string_view) {}
};

inline bool operator==(const char *lhs, StringView rhs) { return rhs == lhs; }

using StringViewList = Vector<StringView>;

} // namespace var


#endif // VAR_API_STRING_VIEW_HPP
