/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.

#ifndef SAPI_CALC_BASE64_HPP_
#define SAPI_CALC_BASE64_HPP_

#include "var/View.hpp"

namespace var {

/*! \brief Base64 Encode/Decode Class
 * \details This class includes methods to encode and decode data
 * using the base64 algorithm.  Base64 is useful for representing binary
 * data using text characters.  This can be useful when
 * transmitting data over certain serial links that do not support binary
 * transfers.
 *
 * The following example can be used to encode and decode
 * using Base64.
 *
 * First, include the Stratify API headers that we will
 * need for these examples.
 *
 * \code
 * //md2code:include
 * #include <sapi/calc.hpp>
 * #include <var.hpp>
 * #include <sapi/fs.hpp>
 * \endcode
 *
 * Now do some encoding and decoding like a boss.
 *
 * \code
 * //md2code:main
 * Data data_to_encode(128);
 * data_to_encode.fill<u8>(32);
 *
 * String encoded_string = Base64::encode(
 *   arg::SourceData(data_to_encode)
 * );
 *
 * //You can then decode the data using this code snippet:
 *
 * Data original_data = Base64::decode(encoded_string);
 *
 * if( original_data == data_to_encode ){
 *   printf("It works!\n");
 * }
 * \endcode
 *
 */
class Base64 : public api::ExecutionContext {
public:
  var::String encode(var::View input) const;
  var::Data decode(var::StringView input) const;

private:
  friend class Base64Encoder;
  friend class Base64Decoder;

  static size_t get_decoded_size(size_t nbyte);
  static size_t get_encoded_size(size_t nbyte);

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
