/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
// Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc

#include <cctype>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <errno.h>

#include "var/Data.hpp"
#include "var/String.hpp"
#include "var/Tokenizer.hpp"

var::String var::operator+(var::StringView lhs, const var::String &rhs) {
  return std::move(String(lhs) + rhs);
}

var::String var::operator+(var::StringView lhs, var::String &&rhs) {
  return std::move(var::String(lhs) + std::move(rhs));
}

var::String var::operator+(var::StringView lhs, var::StringView rhs) {
  return std::move(var::String(lhs) + rhs);
}

var::String var::operator+(const var::String &lhs, var::StringView rhs) {
  return std::move(var::String(lhs) += rhs);
}

using namespace var;

String String::m_empty_string;

String::String(const Data &data)
  : m_string(data.view().to_const_char(), data.size()) {}

String::String(const View &view) {
  m_string.assign(view.to_const_char(), view.size());
}

String &String::format(const char *format, ...) {
  va_list args;
  va_start(args, format);
  vformat(format, args);
  va_end(args);
  return *this;
}

String &String::vformat(const char *fmt, va_list list) {

  API_ASSERT(fmt != nullptr);

  va_list list_copy;
  va_copy(list_copy, list);
  const int buffer_size = api::ApiInfo::malloc_chunk_size();
  char buffer[buffer_size];
  int size = vsnprintf(buffer, buffer_size - 1, fmt, list);
  if (size <= buffer_size - 1) {
    *this = String(buffer);
  } else {
    Data tmp(size + 1);
    View tmp_item(tmp);
    size = vsnprintf(tmp_item.to_char(), tmp_item.size(), fmt, list_copy);

    if (size > 0) {
      *this = String(tmp_item.to_const_char());
    } else {
      clear();
    }
  }
  va_end(list_copy);

  return *this;
}

String &String::erase(StringView string_to_erase, size_t position) {
  size_t erase_pos;
  const size_t len = string_to_erase.length();
  while ((erase_pos = StringView(*this).find(string_to_erase, position))
         != npos) {
    erase(Erase().set_position(erase_pos).set_length(len));
    position = erase_pos;
  }
  return *this;
}

String &String::replace(const Replace &options) {
  size_t pos = options.position();
  const size_t old_length = options.old_string().length();
  const size_t new_length = options.new_string().length();
  size_t replaced_count = 0;
  while (
    ((pos = StringView(*this).find(options.old_string(), pos)) != String::npos)
    && (options.count() ? replaced_count < options.count() : 1)) {

    erase(Erase().set_position(pos).set_length(old_length));

    m_string.insert(pos, options.new_string().m_string_view);
    // insert(pos, options.new_string());
    pos += new_length;
    replaced_count++;
  }
  return *this;
}

String &String::to_upper() {
  for (auto &c : m_string) {
    c = std::toupper(c);
  }
  return *this;
}

String &String::to_lower() {
  for (auto &c : m_string) {
    c = std::tolower(c);
  }
  return *this;
}

float String::to_float() const {
#ifndef __link
  return ::atoff(cstring());
#else
  return ::atof(cstring());
#endif
}

StringViewList String::split(StringView delimiter) const {
  return std::move(
    Tokenizer(cstring(), Tokenizer::Construct().set_delimeters(delimiter))
      .list());
}

size_t String::count(var::StringView occurance) const {
  size_t pos = 0;
  u32 item_count = 0;
  while ((pos < length()) && (pos != String::npos)) {
    pos = StringView(*this).find(occurance, pos);
    if (pos != String::npos) {
      item_count++;
      pos += occurance.length();
    }
  }
  return item_count;
}
