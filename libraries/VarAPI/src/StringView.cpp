/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
#include "var/StringView.hpp"
#include "var/StackString.hpp"
#include "var/String.hpp"
#include "var/Tokenizer.hpp"

using namespace var;

StringView::StringView(const String &value) : m_string_view(value.m_string) {}
StringView::StringView(const IdString &value)
  : m_string_view(value.cstring()) {}
StringView::StringView(const KeyString &value)
  : m_string_view(value.cstring()) {}
StringView::StringView(const NumberString &value)
  : m_string_view(value.cstring()) {}
StringView::StringView(const PathString &value)
  : m_string_view(value.cstring()) {}
StringView::StringView(const NameString &value)
  : m_string_view(value.cstring()) {}
StringView::StringView(const GeneralString &value)
  : m_string_view(value.cstring()) {}

StringView StringView::get_substring(const GetSubstring &options) const {
  if (options.length() != StringView::npos) {
    return StringView(
      m_string_view.substr(options.position(), options.length()));
  }
  return StringView(m_string_view.substr(options.position()));
}

StringView StringView::get_substring_at_position(size_t position) const {
  if (position < length()) {
    return StringView(m_string_view.substr(position));
  }

  return StringView();
}

StringView StringView::get_substring_with_length(size_t length) const {
  return StringView(m_string_view.substr(0, length));
}

StringViewList StringView::split(StringView delimeters) const {
  return std::move(
    Tokenizer(*this, Tokenizer::Construct().set_delimeters(delimeters)).list());
}

float StringView::to_float() const {
#ifndef __link
  return ::atoff(NumberString(*this).cstring());
#else
  return ::atof(NumberString(*this).cstring());
#endif
}

long StringView::to_long(Base base) const {
  return ::strtol(
    NumberString(*this).cstring(),
    nullptr,
    static_cast<int>(base));
}

unsigned long StringView::to_unsigned_long(Base base) const {
  return ::strtoul(
    NumberString(*this).cstring(),
    nullptr,
    static_cast<int>(base));
}

int StringView::to_integer() const {
  return ::atoi(NumberString(*this).cstring());
}

String StringView::get_string() const {
  return std::move(String(data(), length()));
}

String StringView::get_string(const StringView &a) { return a.get_string(); }

bool StringView::operator==(const String &a) const {
  return m_string_view == a.m_string;
}

bool StringView::operator!=(const String &a) const {
  return m_string_view != a.m_string;
}
