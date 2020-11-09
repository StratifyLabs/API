/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
// Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc

#include "var/Tokenizer.hpp"
#include "var/View.hpp"
#include <cstdio>
#include <cstring>

using namespace var;

Tokenizer::Tokenizer(var::StringView input, const Construct &options) {
  parse(input, options);
}

void Tokenizer::parse(var::StringView input, const Construct &options) {

  const u32 max_delimeter_count = options.maximum_delimeter_count();
  const u32 length = input.length();

  m_token_list = StringViewList();
  u32 cursor = 0;
  u32 sub_position = 0;

  while (cursor < length) {
    if (options.delimeters().find(input.at(cursor)) != String::npos) {
      m_token_list.push_back(input(StringView::GetSubstring()
                                     .set_position(sub_position)
                                     .set_length(cursor - sub_position)));

      sub_position = cursor + 1;
      if (
        max_delimeter_count && (m_token_list.count() == max_delimeter_count)) {
        cursor = length - 1;
      }
    } else if (
      options.ignore_between().find(input.at(cursor)) != String::npos) {
      // skip the space between specific characters
      char end = input.at(cursor);
      cursor++;
      while ((cursor < length) && (input.at(cursor) != end)) {
        cursor++;
      }
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
  } else {
    return StringView();
  }
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

  return std::move(result);
}
