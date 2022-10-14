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

  const auto delimiter_length = options.delimiters.length();

  m_token_list = StringViewList();
  size_t cursor = 0;
  size_t sub_position = 0;

  while (cursor < length) {
    const auto cursor_character = input.at(cursor);
    if (
      options.delimiter_type == DelimiterType::string
      && StringView{input}.pop_front(cursor).truncate(delimiter_length)
           == options.delimiters) {
      m_token_list.push_back(input(StringView::GetSubstring()
                                     .set_position(sub_position)
                                     .set_length(cursor - sub_position)));

      sub_position = cursor + delimiter_length;
    } else if (
      options.delimiter_type == DelimiterType::characters
      && options.delimiters.contains(cursor_character)) {
      m_token_list.push_back(input(StringView::GetSubstring()
                                     .set_position(sub_position)
                                     .set_length(cursor - sub_position)));

      sub_position = cursor + 1;
    } else if (options.ignore_between.contains(cursor_character)) {
      // skip the space between specific characters
      const auto start = cursor_character;
      const auto end = StringView::get_closing_character(start);
      ++cursor;
      auto count = 1;
      while ((cursor < length) && count) {
        const auto current_cursor_character = input.at(cursor);
        if (current_cursor_character == end) {
          --count;
        } else if ((end != start) && (current_cursor_character == start)) {
          ++count;
        }
        if(count) {
          ++cursor;
        }
      }
    }

    if (
      options.maximum_delimiter_count
      && (m_token_list.count() == options.maximum_delimiter_count)) {
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

var::String Tokenizer::join(StringView delimiter) const {
  var::String result;
  result.reserve(m_input.length() + list().count() * delimiter.length());
  for (const auto &item : list()) {
    result += item + delimiter;
  }
  result.pop_back(delimiter.length());
  return result;
}
