/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.

#ifndef VAR_API_TOKENIZER_HPP_
#define VAR_API_TOKENIZER_HPP_

#include "String.hpp"
#include "Vector.hpp"

namespace var {

class Tokenizer : public api::ExecutionContext {
public:

  enum class DelimiterType {
    characters,
    string
  };

  struct Construct {
    API_PMAZ(delimiters, Construct, StringView, {});
    API_PMAZ(delimiter_type, Construct, DelimiterType, DelimiterType::characters);
    API_PMAZ(ignore_between, Construct, StringView, {});
    API_PMAZ(maximum_delimiter_count, Construct, u32, {});
  };

  Tokenizer(StringView input, const Construct &options);

  enum class SortBy { none, ascending, descending };

  Tokenizer &sort(SortBy sort_option);

  API_NO_DISCARD u32 count() const { return m_token_list.count(); }
  API_NO_DISCARD StringView at(u32 n) const;

  API_NO_DISCARD const StringViewList &list() const { return m_token_list; }
  API_NO_DISCARD String join(StringView delimeter) const;

protected:
private:
  StringViewList m_token_list;
  StringView m_input;
  void parse(StringView input, const Construct &options);
};

typedef Tokenizer Token;

} // namespace var

#endif /* VAR_API_TOKENIZER_HPP_ */
