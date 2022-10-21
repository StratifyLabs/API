/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
// Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc

#include "var/Tokenizer.hpp"
#include "var/Queue.hpp"
#include "var/View.hpp"

using namespace var;

Tokenizer::Tokenizer(var::StringView input, const Construct &options) {
  const auto length = input.length();
  var::Queue<StringView> container;

  auto cursor = size_t{};
  auto sub_position = size_t{};
  auto current_delimiter_position = size_t{};
  struct State {
    size_t delimiter_length{};
    Tokenizer ordered_string_tokens{};
  };

  auto state = [&]() {
    if (
      options.delimiter_type == DelimiterType::characters
      || options.delimiter_type == DelimiterType::ordered_characters) {
      return State{size_t{1}};
    }
    if (options.delimiter_type == DelimiterType::string) {
      return State{options.delimiters.length()};
    }

    const auto delimiters = StringView{options.delimiters}.truncate(1);
    const auto input = StringView{options.delimiters}.pop_front();
    auto result
      = Tokenizer(input, Tokenizer::Construct().set_delimiters(delimiters));
    API_ASSERT(result.count() > 0);
    return State{result.at(0).length(), std::move(result)};
  }();

  if (options.delimiter_type == DelimiterType::ordered_characters) {
    API_ASSERT(options.delimiters.length());
  }

  auto push_token = [&]() {
    container.push(StringView{input}
                     .pop_front(sub_position)
                     .truncate(cursor - sub_position));
    sub_position = cursor + state.delimiter_length;
  };
  auto get_input_string = [&]() {
    return StringView{input}.pop_front(cursor).truncate(state.delimiter_length);
  };
  while (cursor < length) {
    const auto cursor_character = input.at(cursor);
    auto is_match = false;
    if (
      options.delimiter_type == DelimiterType::string
      && get_input_string() == options.delimiters) {
      push_token();
      cursor += state.delimiter_length-1;
    } else if (
      options.delimiter_type == DelimiterType::characters
      && options.delimiters.contains(cursor_character)) {
      push_token();
    } else if (
      options.delimiter_type == DelimiterType::ordered_characters
      && cursor_character
           == options.delimiters.at(current_delimiter_position)) {
      push_token();
      if (current_delimiter_position < options.delimiters.length() - 1) {
        ++current_delimiter_position;
      }
    } else if (
      options.delimiter_type == DelimiterType::ordered_strings
      && get_input_string()
           == state.ordered_string_tokens.at(current_delimiter_position)) {
      push_token();
      if (
        current_delimiter_position < state.ordered_string_tokens.count() - 1) {
        ++current_delimiter_position;
      }
      cursor += state.delimiter_length-1;
      state.delimiter_length
        = state.ordered_string_tokens.at(current_delimiter_position).length();
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
        if (count) {
          ++cursor;
        }
      }
    }

    if (
      options.maximum_delimiter_count
      && (container.count() == options.maximum_delimiter_count)) {
      cursor = length - 1;
    }

    ++cursor;
  }

  // push the last token
  push_token();

  m_token_list.reserve(container.count());
  for (const auto &item : container) {
    m_token_list.push_back(item);
  }
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
