/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
#ifndef VAR_API_STRING_VIEW_HPP
#define VAR_API_STRING_VIEW_HPP

#include <cstring>
#include <string>
#include <string_view>

#include "Vector.hpp"
#include "api/api.hpp"

#if defined __link
#define atoff atof
#else
extern float atoff(const char *);
#endif

namespace var {

class String;
class Data;
class IdString;
class KeyString;
class NumberString;
class PathString;
class NameString;
class GeneralString;

class StringView;
using StringViewList = Vector<StringView>;

/*! \brief StringView (wrapper for std::string_view)
 *
 *
 * \details The StringView class is meant to be the cheapest
 * way to refer to strings. It can be implicitly constructed
 * from all the other common string types.
 *
 * When passing a string as a parameter, use `StringView` passed by
 * value rather than reference.
 *
 */
class StringView {
public:
  constexpr static size_t npos = std::string_view::npos;

  enum class Base { auto_ = 0, octal = 8, decimal = 10, hexadecimal = 16 };

  /*! \details This is constructed so that is points
   * to an empty string rather than a null string.
   *
   * The default for `std::string_view` is to create
   * a null string i.e `data() == nullptr`.
   */
  constexpr StringView() : m_string_view{""} {}
  constexpr StringView(const char *value) : m_string_view(value) {}
  StringView(const String &value);
  StringView(const IdString &value);
  StringView(const KeyString &value);
  StringView(const NumberString &value);
  StringView(const PathString &value);
  StringView(const NameString &value);
  StringView(const GeneralString &value);
  explicit constexpr StringView(const std::string_view string_view)
    : m_string_view(string_view) {}

  StringView(const char *value, size_t length) : m_string_view{value, length} {}

  static constexpr StringView whitespace() { return StringView{"\t\n\v\f\r "}; }

  /*! \details This allows you to quickly check for an empty string.
   *
   * ```cpp
   * StringView value;
   * if( value ){
   *  //string is not empty
   * }
   * ```
   *
   * @return `true` is string is not empty.
   */
  API_NO_DISCARD explicit operator bool() const { return !is_empty(); }

  API_NO_DISCARD bool is_null() const {
    return m_string_view.data() == nullptr;
  }

  StringView &set_null() {
    m_string_view = std::string_view(nullptr, 0);
    return *this;
  }

  /*! \details `StringView` data is not guaranteed to
   * be null terminated. With this function, you can check
   * to see if it is null terminated.
   *
   * Try to avoid using this function.
   *
   * @return `true` if the string is null terminated
   */
  API_NO_DISCARD bool is_null_terminated() const {
    return data() && (data()[length()] == 0);
  }

  API_NO_DISCARD char at(size_t value) const { return m_string_view.at(value); }
  API_NO_DISCARD char front() const { return m_string_view.front(); }
  API_NO_DISCARD char back() const { return m_string_view.back(); }
  API_NO_DISCARD size_t length() const { return m_string_view.length(); }

  API_NO_DISCARD bool is_empty() const { return m_string_view.empty(); }

  StringView &strip_leading_containing(StringView value);

  StringView &strip_trailing_containing(StringView value);

  StringView &strip_leading_whitespace() {
    return strip_leading_containing(whitespace());
  }

  StringView &strip_trailing_whitespace() {
    return strip_trailing_containing(whitespace());
  }

  StringView &pop_front(size_t length = 1);
  StringView &pop_back(size_t length = 1);
  StringView &truncate(size_t length);
  StringView& pop_encapsulated(StringView start);

  class GetSubstring {
    API_AF(GetSubstring, size_t, position, 0);
    API_AF(GetSubstring, size_t, length, npos);
  };

  API_NO_DISCARD StringView get_substring(const GetSubstring &options) const;
  API_NO_DISCARD StringView operator()(const GetSubstring &options) const {
    return get_substring(options);
  }

  API_NO_DISCARD StringView get_substring_at_position(size_t position) const;
  API_NO_DISCARD StringView get_substring_with_length(size_t length) const;

  API_NO_DISCARD StringViewList split(StringView delimiters) const;

  API_NO_DISCARD StringView get_encapsulated(StringView start) const;

  using iterator = typename std::string_view::iterator;
  using const_iterator = typename std::string_view::const_iterator;
  using reverse_iterator = typename std::string_view::reverse_iterator;
  using const_reverse_iterator =
    typename std::string_view::const_reverse_iterator;

  API_NO_DISCARD const_iterator begin() const noexcept {
    return m_string_view.begin();
  }
  API_NO_DISCARD iterator begin() noexcept { return m_string_view.begin(); }

  API_NO_DISCARD const_iterator end() const noexcept {
    return m_string_view.end();
  }
  API_NO_DISCARD iterator end() noexcept { return m_string_view.end(); }

  API_NO_DISCARD const_iterator cbegin() const noexcept {
    return m_string_view.cbegin();
  }
  API_NO_DISCARD const_iterator cend() const noexcept {
    return m_string_view.cend();
  }

  API_NO_DISCARD const_reverse_iterator rbegin() const noexcept {
    return m_string_view.rbegin();
  }
  API_NO_DISCARD reverse_iterator rbegin() noexcept {
    return m_string_view.rbegin();
  }

  API_NO_DISCARD const_reverse_iterator rend() const noexcept {
    return m_string_view.rend();
  }
  API_NO_DISCARD reverse_iterator rend() noexcept {
    return m_string_view.rend();
  }

  API_NO_DISCARD const_reverse_iterator crbegin() const noexcept {
    return m_string_view.crbegin();
  }
  API_NO_DISCARD const_reverse_iterator crend() const noexcept {
    return m_string_view.crend();
  }

  API_NO_DISCARD size_t find(StringView a, size_t position = 0) const {
    return m_string_view.find(a.m_string_view, position);
  }

  API_NO_DISCARD size_t find(char a, size_t position = 0) const {
    return m_string_view.find(a, position);
  }

  API_NO_DISCARD size_t find_first_of(StringView a, size_t position = 0) const {
    return m_string_view.find_first_of(a.m_string_view, position);
  }

  API_NO_DISCARD size_t
  find_first_not_of(StringView a, size_t position = 0) const {
    return m_string_view.find_first_not_of(a.m_string_view, position);
  }

  API_NO_DISCARD size_t
  reverse_find(StringView a, size_t position = npos) const {
    return m_string_view.rfind(a.m_string_view, position);
  }

  API_NO_DISCARD size_t reverse_find(char a, size_t position = npos) const {
    return m_string_view.rfind(a, position);
  }

  API_NO_DISCARD size_t
  find_last_of(StringView a, size_t position = npos) const {
    return m_string_view.find_last_of(a.m_string_view, position);
  }

  API_NO_DISCARD size_t
  find_last_not_of(StringView a, size_t position = npos) const {
    return m_string_view.find_last_not_of(a.m_string_view, position);
  }

  API_NO_DISCARD bool starts_with(const StringView a) const {
    return find(a) == 0;
  }

  API_NO_DISCARD bool ends_with(const StringView a) const {
    return find(a) == length() - a.length();
  }

  API_NO_DISCARD bool contains(const StringView a) const {
    return find(a) != npos;
  }

  API_NO_DISCARD bool contains(char a) const { return find(a) != npos; }

  API_NO_DISCARD bool contains_any_of(StringView a) const;

  template <class Container>
  API_NO_DISCARD bool contains_any_of(const Container &a) const {
    for (const auto &value : a) {
      if (find(value) != npos) {
        return true;
      }
    }
    return false;
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

  bool operator>(const StringView a) const {
    return m_string_view > a.m_string_view;
  }

  bool operator>=(const StringView a) const {
    return m_string_view >= a.m_string_view;
  }

  bool operator<(const StringView a) const {
    return m_string_view < a.m_string_view;
  }

  bool operator<=(const StringView a) const {
    return m_string_view <= a.m_string_view;
  }

  API_NO_DISCARD long to_long(Base base = Base::decimal) const;
  API_NO_DISCARD float to_float() const;
  API_NO_DISCARD unsigned long
  to_unsigned_long(Base base = Base::decimal) const;
  API_NO_DISCARD int to_integer() const;

  API_NO_DISCARD const char *data() const { return m_string_view.data(); }

  API_NO_DISCARD String to_string() const;
  API_NO_DISCARD static String to_string(const StringView &a);
  API_NO_DISCARD std::string_view to_std_string_view() const {
    return m_string_view;
  }

  static char get_closing_character(char input);

private:
  friend class String;
  std::string_view m_string_view;

  API_NO_DISCARD Base get_base(Base input) const;
};

inline bool operator==(const char *lhs, StringView rhs) { return rhs == lhs; }

inline StringView operator"" _string_view(const char *value) {
  return StringView{value};
}

} // namespace var

#endif // VAR_API_STRING_VIEW_HPP
