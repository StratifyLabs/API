/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
// Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc

#include "var/String.hpp"
#include "var/Data.hpp"
#include "var/Tokenizer.hpp"

var::String var::operator+(var::StringView lhs, const var::String &rhs) {
  return String(lhs) + rhs;
}

var::String var::operator+(var::StringView lhs, var::String &&rhs) {
  return var::String(lhs) + std::move(rhs);
}

var::String var::operator+(var::StringView lhs, var::StringView rhs) {
  return var::String(lhs) + rhs;
}

var::String var::operator+(const var::String &lhs, var::StringView rhs) {
  return var::String(lhs) += rhs;
}

using namespace var;

namespace {
void string_to_upper(std::string &string) {
  std::for_each(string.begin(), string.end(), [](char &c) {
    c = std::toupper(c);
  });
}

void string_to_lower(std::string &string) {
  std::for_each(string.begin(), string.end(), [](char &c) {
    c = std::tolower(c);
  });
}

} // namespace

String String::m_empty_string;

String::String(const Data &data)
  : m_string(data.view().to_const_char(), data.size()) {}

String::String(const View &view) {
  m_string.assign(view.to_const_char(), view.size());
}

String &String::format(const char *format, ...) & {
  va_list args;
  va_start(args, format);
  vformat(format, args);
  va_end(args);
  return *this;
}

String &&String::format(const char *format, ...) && {
  va_list args;
  va_start(args, format);
  vformat(format, args);
  va_end(args);
  return std::move(*this);
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

String &String::erase(StringView string_to_erase, size_t position) & {
  size_t erase_pos;
  const size_t len = string_to_erase.length();
  while ((erase_pos = StringView(*this).find(string_to_erase, position))
         != npos) {
    erase(Erase().set_position(erase_pos).set_length(len));
    position = erase_pos;
  }
  return *this;
}

String &String::replace(const Replace &options) & {
  if (options.is_character_wise) {
    auto new_options = options;
    new_options.set_character_wise(false);
    for (const auto character : options.old_string) {
      replace(new_options.set_old_string(StringView{&character, 1}));
    }
    return *this;
  }
  size_t pos = options.position;
  const size_t old_length = options.old_string.length();
  const size_t new_length = options.new_string.length();
  size_t replaced_count = 0;
  while (
    ((pos = StringView(*this).find(options.old_string, pos)) != String::npos)
    && (options.count ? replaced_count < options.count : 1)) {

    erase(Erase().set_position(pos).set_length(old_length));

    m_string.insert(pos, options.new_string.m_string_view);
    pos += new_length;
    replaced_count++;
  }
  return *this;
}

String &String::to_upper() & {
  std::for_each(m_string.begin(), m_string.end(), [](char &c) {
    c = std::toupper(c);
  });
  return *this;
}

String &String::to_lower() & {
  std::for_each(m_string.begin(), m_string.end(), [](char &c) {
    c = std::tolower(c);
  });
  return *this;
}

float String::to_float() const { return ::atoff(cstring()); }

StringViewList String::split(StringView delimiter) const {
  return Tokenizer(cstring(), Tokenizer::Construct().set_delimiters(delimiter))
    .list();
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

String &String::remove_whitespace() & {
  return replace(Replace{
    .count = 0,
    .is_character_wise = true,
    .new_string = StringView{},
    .old_string = StringView::whitespace(),
  });
}

String &String::insert(
  const StringView string_to_insert,
  const String::Insert &options) & {
  if (options.sub_position() == npos) {
    m_string.insert(options.position(), string_to_insert.m_string_view);
  } else {
    m_string.insert(
      options.position(),
      string_to_insert.m_string_view,
      options.sub_position(),
      options.sub_length());
  }
  return *this;
}
String &String::clear() & {
  m_string.clear();
  return *this;
}

String &String::free() & { return *this = String(); }

String &String::erase(const String::Erase &options) & {
  m_string.erase(options.position(), options.length());
  return *this;
}
String &String::push_back(char a) & {
  m_string.push_back(a);
  return *this;
}

String &String::pop_front(size_t pop_size) & {
  return erase(Erase().set_position(0).set_length(pop_size));
}

String &String::pop_back(size_t pop_size) & {
  while (length() && pop_size--) {
    m_string.pop_back();
  }
  return *this;
}
String &String::resize(size_t size) & {
  m_string.resize(size);
  return *this;
}
String &String::reserve(size_t size) & {
  m_string.reserve(size);
  return *this;
}

String &String::append(const StringView &a) & {
  m_string.append(a.m_string_view);
  return *this;
}
