/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
// Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc

#include "var/Tokenizer.hpp"
#include "var/View.hpp"

using namespace var;

Tokenizer::Tokenizer(var::StringView input, const Construct &options) {
  parse(input, options);
}

void Tokenizer::parse(var::StringView input, const Construct &options) {

  const auto length = input.length();

  const auto delimeter_length = options.delimeters.length();

  m_token_list = StringViewList();
  size_t cursor = 0;
  size_t sub_position = 0;

  while (cursor < length) {
    if (
      options.delimeter_type == DelimeterType::string
      && StringView{input}.pop_front(cursor).truncate(delimeter_length)
           == options.delimeters) {
      m_token_list.push_back(input(StringView::GetSubstring()
                                     .set_position(sub_position)
                                     .set_length(cursor - sub_position)));

      sub_position = cursor + delimeter_length;
    } else if (
      options.delimeter_type == DelimeterType::characters
      && options.delimeters.contains(input.at(cursor))) {
      m_token_list.push_back(input(StringView::GetSubstring()
                                     .set_position(sub_position)
                                     .set_length(cursor - sub_position)));

      sub_position = cursor + 1;
    } else if (options.ignore_between.contains(input.at(cursor))) {
      // skip the space between specific characters
      const auto start = input.at(cursor);
      const auto end = [start]() {
        switch (start) {
        case '{':
          return '}';
        case '[':
          return ']';
        case '(':
          return ')';
        case '<':
          return '>';
        }
        return start;
      }();
      cursor++;
      while ((cursor < length) && (input.at(cursor) != end)) {
        cursor++;
      }
    }

    if (
      options.maximum_delimeter_count
      && (m_token_list.count() == options.maximum_delimeter_count)) {
      cursor = length - 1;
    }

    cursor++;
  }

  // push the last token
  m_token_list.push_back(input(StringView::GetSubstring()
                                 .set_position(sub_position)
                                 .set_length(cursor - sub_position)));
}

StringView Tokenizer::at(u32 n) const {
  if (n < m_token_list.count()) {
    return m_token_list.at(n);
  }
  return {};
}

Tokenizer &Tokenizer::sort(SortBy sort_option) {
  switch (sort_option) {
  case SortBy::ascending:
    m_token_list.sort(StringViewList::ascending);
    break;
  case SortBy::descending:
    m_token_list.sort(StringViewList::descending);
    break;
  case SortBy::none:
    break;
  }
  return *this;
}

var::String Tokenizer::join(StringView delimeter) const {
  var::String result;
  result.reserve(m_input.length() + list().count() * delimeter.length());

  for (const auto &item : list()) {
    result += item + delimeter;
  }

  for (size_t i = 0; i < delimeter.length(); i++) {
    result.pop_back();
  }

  return result;
}
