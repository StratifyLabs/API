/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
// Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <errno.h>

#include "var/Data.hpp"
#include "var/String.hpp"

#if !defined __link
#include <mcu/arch.h>
#include <reent.h>
#endif

#include "var/StackString.hpp"
#include "var/View.hpp"

using namespace var;

// This is here so that by default that data can point to a null value rather
// than be a null value
const int View::m_zero_value MCU_ALIGN(4) = 0;

// this value corresponds to the malloc chunk size used in Stratify OS
// this may be something that could be determined through a system call

void View::set_view(const Construct &options) {
  if (options.size()) {
    m_size_read_only = options.size();
    if (options.write_buffer()) {
      m_data = options.write_buffer();
    } else {
      m_data = (void *)options.read_buffer();
      m_size_read_only |= m_size_read_only_flag;
    }
  } else {
    m_data = nullptr;
    m_size_read_only = 0;
  }
}

View::View(const Data &data) {
  set_view(Construct().set_read_buffer(data.data()).set_size(data.size()));
}

View::View(Data &data) {
  set_view(Construct().set_write_buffer(data.data()).set_size(data.size()));
}

View &View::swap_byte_order(SwapBy swap) {
  API_RETURN_VALUE_IF_ERROR(*this);
  if (write_data()) {
    if (swap == SwapBy::word) {
      u32 *p = to_u32();
      if (p == nullptr) {
        API_RETURN_VALUE_ASSIGN_ERROR(*this, "read only data", EINVAL);
      }
      u32 i;
      for (i = 0; i < this->size() / 4; i++) {
#if !defined __link
        p[i] = __REV(p[i]);
#else
        // swap manually
        API_RETURN_VALUE_ASSIGN_ERROR(*this, "swap not supported", ENOTSUP);
#endif
      }
    } else {
      u16 *p = to_u16();
      if (p == nullptr) {
        API_RETURN_VALUE_ASSIGN_ERROR(*this, "read only data", EINVAL);
      }
      u16 i;
      for (i = 0; i < this->size() / 2; i++) {
#if !defined __link
        p[i] = __REV16(p[i]);
#else
        // swap manually
#endif
      }
    }
  }
  return *this;
}

View &View::copy(const View &source) {

  // bytes to copy is lowests of source, options and this objects size -
  // destination position
  const size_t bytes_to_copy = size() < source.size() ? size() : source.size();
  memcpy(to_char(), source.to_const_void(), bytes_to_copy);

  return *this;
}

var::String View::to_string() const {
  var::String result = var::String().reserve(size() * 2);
  for (u32 i = 0; i < size(); i++) {
    result += NumberString(to_const_u8()[i], "%02X").string_view();
  }
  return result;
}
