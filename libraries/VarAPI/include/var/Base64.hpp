/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.

#ifndef SAPI_CALC_BASE64_HPP_
#define SAPI_CALC_BASE64_HPP_

#include "var/View.hpp"

namespace var {

class Base64 : public api::ExecutionContext {
public:
  API_NO_DISCARD var::String encode(var::View input) const;
  API_NO_DISCARD var::Data decode(var::StringView input) const;

  const Base64& encode(var::View input, var::String & output) const;
  const Base64& decode(var::StringView input, var::Data & output) const;

  static constexpr size_t get_decoded_size(size_t nbyte) {
    // adds three bytes to padding, actual is returned by decode method
    return (nbyte * 3 + 3) / 4;
  }

  static constexpr size_t get_encoded_size(size_t nbyte) {
    return ((((nbyte * 4 + 2) / 3) + 3) / 4) * 4;
  }

private:
  friend class Base64Encoder;
  friend class Base64Decoder;

  static int encode(char *dest, const void *src, int nbyte);
  static int decode(void *dest, const char *src, int nbyte);

  static char encode_six(u8 six_bit_value);
  static char decode_eight(u8 eight_bit_value);
};

class Base64Encoder : public Transformer {
public:
  int transform(const Transform &options) const override;
  size_t get_output_size(size_t nbyte) const override {
    return Base64::get_encoded_size(nbyte);
  }

  size_t page_size_boundary() const override { return 3; }
};

class Base64Decoder : public Transformer {
public:
  int transform(const Transform &options) const override;
  size_t get_output_size(size_t nbyte) const override {
    return Base64::get_decoded_size(nbyte);
  }
  size_t page_size_boundary() const override { return 4; }
};

} // namespace var

#endif /* SAPI_CALC_BASE64_HPP_ */
