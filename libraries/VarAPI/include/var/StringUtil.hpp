/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.

#ifndef VAR_API_STRINGUTIL_HPP_
#define VAR_API_STRINGUTIL_HPP_

/*! \cond */

#include <stdint.h>
#include "../api/ApiObject.hpp"

namespace var {

class API_DEPRECATED_NO_REPLACEMENT StringUtil;

class StringUtil {
public:

	enum mode{
		BINARY /*! Binary mode */,
		OCTAL /*! Octal mode */,
		hexadecimal /*! Hexadecimal mode (lowercase) */,
		HEXADECIMAL /*! Hexadecimal mode (uppercase) */,
		DECIMAL /*! Decimal mode (Default); used exclusively by signed types */,
		MODE_TOTAL
	};


	enum {
		BUF_SIZE = 36
	};

	static int utoa_mode(enum StringUtil::mode mode, char dest[BUF_SIZE], uint32_t num, int width);

	static int itoa(char dest[BUF_SIZE], int32_t num, int width = 0);
	static int utoa(char dest[BUF_SIZE], uint32_t num, int base = 10, bool upper = true, int width = 0);
#ifdef USE_FLOAT
	static int ftoa(char dest[BUF_SIZE], float num, int width = 0);
#endif

private:
	static char htoc(int nibble);
	static char Htoc(int nibble);

};

}

/*! \endcond */


#endif /* VAR_API_STRINGUTIL_HPP_ */
