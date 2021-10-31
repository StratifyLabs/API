/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.

#ifndef VAR_API_ITEM_HPP_
#define VAR_API_ITEM_HPP_

#include <cstdio>
#include <cstring>
#include <type_traits>

#include "api/api.hpp"

#include "Array.hpp"
#include "String.hpp"
#include "StackString.hpp"
#include "Vector.hpp"

#if !defined __link
#include <malloc.h>
#endif

namespace var {

class Data;

class View : public api::ExecutionContext {
public:
  View() = default;

  View(const Data &data);
  View(Data &data);

  View(const char *str) { set_view(str, strlen(str)); }
  View(StringView str) { set_view(str.data(), str.length()); }
  View(const String &str) { set_view(str.cstring(), str.length()); }
  View(String &str) { set_view(str.to_char(), str.length()); }
  View(const void *buffer, size_t size){ set_view(buffer, size); }
  View(void *buffer, size_t size) { set_view(buffer, size); }

  template<class StringType> StringType to_string() const {
    StringType result;
    for (u32 i = 0; i < size(); i++) {
      result.append(NumberString(to_const_u8()[i], "%02X").string_view());
    }
    return result;
  }

  template <typename T> View(const Vector<T> &vector) {
    set_view(vector.data(), vector.count() * sizeof(T));
  }

  template <typename T> View(Vector<T> &vector) {
    set_view(vector.data(), vector.count() * sizeof(T));
  }

  template <typename T, size_t size_value>
  View(const Array<T, size_value> &array) {
    set_view(array.data(), size_value * sizeof(T));
  }

  template <typename T, size_t size_value> View(Array<T, size_value> &array) {
    set_view(array.data(), size_value * sizeof(T));
  }

  template <typename T> explicit View(T &item) {
    // catch all
    static_assert(
        std::is_trivial<T>::value && std::is_standard_layout<T>::value,
        "Cannot construct reference from non-trivial non-standard-layout "
        "types");

    static_assert(!std::is_same<T, const char *>::value,
                  "Cannot view a `const char *`");
    static_assert(!std::is_same<T, char *>::value, "Cannot view a `char *`");

    set_view(&item, sizeof(T));
  }

  API_NO_DISCARD bool is_valid() const { return size() > 0; }
  API_NO_DISCARD bool is_null() const { return m_data == nullptr; }

  template <typename T> View &fill(const T &value) {
    for (u32 i = 0; i < this->count<T>(); i++) {
      to<T>()[i] = value;
    }
    return *this;
  }

  template <typename T> size_t find_offset(const T &value) {
    const auto count = this->count<T>();
    for (u32 i = 0; i < count; i++) {
      if (to<T>()[i] == value) {
        return i;
      }
    }
    return count;
  }

  constexpr static size_t npos = static_cast<size_t>(-1);
  size_t find(const View & view, size_t alignment = 1) const;

  template <typename Type> size_t count() const { return size() / sizeof(Type); }


  template <typename Type> bool verify_zero_sum() const {
    Type sum = 0;
    const auto count = size() / sizeof(Type);
    for(size_t i = 0; i < count; i++){
      sum += to<Type>()[i];
    }
    return sum == 0;
  }

  enum class SwapBy { half_word, word };
  View &swap_byte_order(SwapBy order);

  bool operator==(const View &a) const {
    return a.size() == size() && memcmp(data(), a.data(), size()) == 0;
  }

  bool operator!=(const View &a) const { return !(*this == a); }

  API_NO_DISCARD size_t size() const { return m_size; }

  View &truncate(size_t new_size) {
    if (size() > new_size) {
      m_size = new_size;
    }
    return *this;
  }

  View &pop_back(size_t pop_size = 1) {
    if (size() >= pop_size) {
      m_size = size() - pop_size;
    }
    return *this;
  }

  View &pop_front(size_t pop_size = 1) {
    if (size() >= pop_size) {
      m_size = (size() - pop_size);
      m_data = (static_cast<u8 *>(m_data)) + pop_size;
    }
    return *this;
  }

  API_NO_DISCARD ssize_t size_signed() const { return static_cast<ssize_t>(size()); }

  View &copy(const View &source);

  template <typename T> const T *to() const {
    return static_cast<const T *>(data());
  }

  template <typename T> T *to() { return static_cast<T *>(data()); }

  API_NO_DISCARD const char *to_const_char() const { return to<char>(); }
  API_NO_DISCARD char *to_char() { return to<char>(); }

  API_NO_DISCARD const void *to_const_void() const { return to<const void>(); }
  API_NO_DISCARD void *to_void() { return to<void>(); }

  API_NO_DISCARD const u8 *to_const_u8() const { return to<const u8>(); }
  API_NO_DISCARD u8 *to_u8() { return to<u8>(); }

  API_NO_DISCARD const u16 *to_const_u16() const { return to<const u16>(); }
  API_NO_DISCARD u16 *to_u16() { return to<u16>(); }

  API_NO_DISCARD const u32 *to_const_u32() const { return to<const u32>(); }
  API_NO_DISCARD u32 *to_u32() { return to<u32>(); }

  API_NO_DISCARD const u64 *to_const_u64() const { return to<const u64>(); }
  API_NO_DISCARD u64 *to_u64() { return to<u64>(); }

  API_NO_DISCARD const s8 *to_const_s8() const { return to<const s8>(); }
  API_NO_DISCARD s8 *to_s8() { return to<s8>(); }

  API_NO_DISCARD const s16 *to_const_s16() const { return to<const s16>(); }
  API_NO_DISCARD s16 *to_s16() { return to<s16>(); }

  API_NO_DISCARD const s32 *to_const_s32() const { return to<const s32>(); }
  API_NO_DISCARD s32 *to_s32() { return to<s32>(); }

  API_NO_DISCARD const s64 *to_const_s64() const { return to<const s64>(); }
  API_NO_DISCARD s64 *to_s64() { return to<s64>(); }

  API_NO_DISCARD const float *to_const_float() const { return to<const float>(); }
  API_NO_DISCARD float *to_float() { return to<float>(); }

  template <typename T> T &at(size_t position) {
    u32 local_count = size() / sizeof(T);
    position = position % local_count;
    return to<T>()[position];
  }

  template <typename T> const T &at(size_t position) const {
    u32 count = size() / sizeof(T);
    position = position % count;
    return to<T>()[position];
  }

  API_NO_DISCARD char at_const_char(size_t position) const { return at<const char>(position); }
  API_NO_DISCARD char &at_char(size_t position) { return at<char>(position); }

  API_NO_DISCARD u8 at_const_u8(size_t position) const { return at<const u8>(position); }
  API_NO_DISCARD u8 &at_u8(size_t position) { return at<u8>(position); }

  API_NO_DISCARD u16 at_const_u16(size_t position) const { return at<const u16>(position); }
  API_NO_DISCARD u16 &at_u16(size_t position) { return at<u16>(position); }

  API_NO_DISCARD u32 at_const_u32(size_t position) const { return at<const u32>(position); }
  API_NO_DISCARD u32 &at_u32(size_t position) { return at<u32>(position); }

  API_NO_DISCARD u64 at_const_u64(size_t position) const { return at<const u64>(position); }
  API_NO_DISCARD u64 &at_u64(size_t position) { return at<u64>(position); }

  API_NO_DISCARD s8 at_const_s8(size_t position) const { return at<const s8>(position); }
  API_NO_DISCARD s8 &at_s8(size_t position) { return at<s8>(position); }

  API_NO_DISCARD s16 at_const_s16(size_t position) const { return at<const s16>(position); }
  API_NO_DISCARD s16 &at_s16(size_t position) { return at<s16>(position); }

  API_NO_DISCARD s32 at_const_s32(size_t position) const { return at<const s32>(position); }
  API_NO_DISCARD s32 &at_s32(size_t position) { return at<s32>(position); }

  API_NO_DISCARD s64 at_const_s64(size_t position) const { return at<const s64>(position); }
  API_NO_DISCARD s64 &at_s64(size_t position) { return at<s64>(position); }

  API_NO_DISCARD float at_const_float(size_t position) const {
    return at<const float>(position);
  }
  API_NO_DISCARD float &at_float(size_t position) { return at<float>(position); }

  API_NO_DISCARD const void *data() const { return m_data; }
  API_NO_DISCARD void *data() { return m_data; }

  View& from_string(StringView value) {
    //bytes to process
    const size_t bytes_to_process = value.length() / 2 > size() ? size() : value.length()/2;
    for (u32 i = 0; i < bytes_to_process; i++) {
      to_u8()[i]
        = value(StringView::GetSubstring().set_position(i * 2).set_length(2))
            .to_unsigned_long(String::Base::hexadecimal);
    }
    return *this;
  }

protected:
  void set_view(void *buffer, size_t size) {
    m_data = buffer;
    m_size = size;
  }
  void set_view(const void *buffer, size_t size) {
    m_size = size;
    m_data = const_cast<void *>(buffer);
  }

private:
  void *m_data = nullptr;
  size_t m_size = 0;

  // friend in order to assign null string to zero-length
  static const int m_zero_value;
};

class Transformer {
public:
  class Transform {
    API_AC(Transform, var::View, input);
    API_AC(Transform, var::View, output);
  };

  API_NO_DISCARD virtual int transform(const Transform &options) const = 0;
  API_NO_DISCARD virtual size_t get_output_size(size_t nbyte) const { return nbyte; }
  API_NO_DISCARD virtual size_t page_size_boundary() const { return 1; }

protected:
};

} // namespace var

#endif /* VAR_API_ITEM_HPP_ */
