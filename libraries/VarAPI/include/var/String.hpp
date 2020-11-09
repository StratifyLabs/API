/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.

#ifndef VAR_API_STRING_HPP_
#define VAR_API_STRING_HPP_

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sos/link.h>
#include <string>

#include "StringView.hpp"
#include "Vector.hpp"

namespace var {

class View;
class Data;

/*! \brief String class
 * \details This is an embedded friendly string class.  It is similar
 * to the C++ string type but is built on var::Data and
 * cstring functions.  The naming convention follows includes
 * many std::string methods.
 *
 *
 *
 * \code
 * #include <var.hpp>
 *
 * String s1;
 * String s2;
 * s1 = "This is my string";
 * printf("%s", s1.cstring());
 *  //Strings can be compared
 * s2 = "This is another string";
 * if( s1 == s2 ){
 * 	printf("The strings are the same!\n");
 * } else {
 * 	printf("The strings are different\n");
 * }
 * \endcode
 *
 * The above code outputs:
 * \code
 * This is my string 64
 * The strings are different
 * \endcode
 *
 *
 *
 * \note
 *
 * A note about copy initialization:
 *
 * \code
 *
 * String hello("hello"); //OK: const char[6] converted from ConstString
 * String hello = "hello"; //Error: no conversion from const char [6] to String
 * (in copy-initialization)
 *
 * String hello; hello = "hello"; //OK const char[6] converted from ConstString
 * for assignment
 *
 * \endcode
 *
 *
 */
class String : public api::ExecutionContext {
public:
  constexpr static size_t npos = std::string::npos;

  using Base = StringView::Base;

  using iterator = typename std::string::iterator;
  using const_iterator = typename std::string::const_iterator;
  using reverse_iterator = typename std::string::reverse_iterator;
  using const_reverse_iterator = typename std::string::const_reverse_iterator;

  const_iterator begin() const noexcept { return m_string.begin(); }
  iterator begin() noexcept { return m_string.begin(); }

  const_iterator end() const noexcept { return m_string.end(); }
  iterator end() noexcept { return m_string.end(); }

  const_iterator cbegin() const noexcept { return m_string.cbegin(); }
  const_iterator cend() const noexcept { return m_string.cend(); }

  const_reverse_iterator rbegin() const noexcept { return m_string.rbegin(); }
  reverse_iterator rbegin() noexcept { return m_string.rbegin(); }

  const_reverse_iterator rend() const noexcept { return m_string.rend(); }
  reverse_iterator rend() noexcept { return m_string.rend(); }

  const_reverse_iterator crbegin() const noexcept { return m_string.crbegin(); }
  const_reverse_iterator crend() const noexcept { return m_string.crend(); }

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

  explicit String(const char *s) { // cppcheck-suppress[noExplicitConstructor]
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

  bool is_empty() const { return m_string.empty(); }

  String &insert(const String &string_to_insert, const Insert &options) {
    if (options.sub_position() == npos) {
      m_string.insert(options.position(), string_to_insert.m_string);
    } else {
      m_string.insert(
        options.position(),
        string_to_insert.m_string,
        options.sub_position(),
        options.sub_length());
    }
    return *this;
  }

  inline String &
  operator()(const String &string_to_insert, const Insert &options) {
    return insert(string_to_insert, options);
  }

  /*! \details Erases a portion of the string starting with the character at
   * \a pos.
   *
   * @param pos The position to start erasing
   * @param len The number of characters to erase
   * @return A reference to this string.
   *
   */
  String &erase(const Erase &options) {
    m_string.erase(options.position(), options.length());
    return *this;
  }

  inline String &operator()(const Erase &options) { return erase(options); }

  String &erase(StringView string_to_erase, size_t position = 0);

  class Replace {
    API_AC(Replace, StringView, old_string);
    API_AC(Replace, StringView, new_string);
    API_AF(Replace, size_t, position, 0);
    API_AF(Replace, size_t, count, 0);
  };
  String &replace(const Replace &options);
  inline String &operator()(const Replace &options) { return replace(options); }

  size_t count(var::StringView to_count) const;
  size_t length() const { return m_string.length(); }
  ssize_t length_signed() const {
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

  char &at(size_t pos) { return m_string.at(pos); }
  const char &at(size_t pos) const { return m_string.at(pos); }

  char &front() { return m_string.front(); }
  const char &front() const { return m_string.front(); }

  char &back() { return m_string.back(); }
  const char &back() const { return m_string.back(); }

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

  const char *cstring() const { return m_string.c_str(); }
  operator const char *() const { return m_string.c_str(); }

  char *to_char() { return &m_string[0]; }

  int compare(const String &string_to_compare) const {
    return m_string.compare(string_to_compare.m_string);
  }

  /*! \details Compares the object to \a str.
   *
   * @param position The position in this object to start the comparison
   * @param length The length of the compared string (this object)
   * @param string_to_compare A reference to the comparing string
   * @param sub_position The position in the comparing string to start
   * comparing
   * @param sub_length The number string characters to compare
   * @return Zero if the strings match
   *
   */
  int compare(const String &string_to_compare, const Compare &options) const {
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

  int to_integer() const { return ::atoi(cstring()); }

  float to_float() const;

  long to_long(Base base = Base::decimal) const {
    return ::strtol(cstring(), nullptr, static_cast<int>(base));
  }

  unsigned long to_unsigned_long(Base base = Base::decimal) const {
    return ::strtoul(cstring(), nullptr, static_cast<int>(base));
  }

  u32 capacity() const { return m_string.capacity(); }

  StringViewList split(StringView delimiter) const;

  StringView string_view() const { return StringView(cstring(), length()); }

  static const String &empty_string() { return m_empty_string; }

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
