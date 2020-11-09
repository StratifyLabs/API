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
#include "Vector.hpp"

#if !defined __link
#include <malloc.h>
#endif

namespace var {

class Data;

/*! \brief View Class
 * \details The View class
 * is for referring to data. The data has a
 * pointer to a buffer and a size.
 *
 * ```
 * //md2code:include
 * #include <var.hpp>
 * #include <sapi/fs.hpp>
 * ```
 *
 * The reference includes a pointer to some data
 * and the size of the data.
 *
 * This class allows passing the data reference as
 * an argument without passing the size separately.
 * Here is a quick example of how this is useful (and good).
 *
 * ```
 * //this is good because you can't mess up the size
 * int write(const DataItem & data);
 *
 * //this is not good because you can mess up the size
 * int write(const void * data, int bytes_in_data);
 * ```
 *
 * Now let's see this in practice.
 *
 * ```
 * //md2code:main
 *
 * File f;
 * f.open(
 *   arg::FilePath("/home/test.txt"),
 *   OpenFlags::append()
 *   );
 *
 * u32 data[4];
 *
 * f.write(
 *   arg::SourceData(DataItem(data))
 *   ); //writes 4 * sizeof(u32) bytes
 * //or
 * f.write(
 *   arg::SourceBuffer(data),
 *   //above cases needn't worry about size
 *   arg::Size(sizeof(data))
 *   );
 * ```
 *
 *
 *
 */
class View : public api::ExecutionContext {
public:
  class Construct {
    API_AF(Construct, const void *, read_buffer, nullptr);
    API_AF(Construct, void *, write_buffer, nullptr);
    API_AF(Construct, size_t, size, 0);
  };

  View() = default;

  View(const Construct &options);

  View(const Data &data);
  View(Data &data);

  View(const char *str) {
    set_view(Construct().set_read_buffer(str).set_size(strlen(str)));
  }

  View(StringView str) {
    set_view(Construct().set_read_buffer(str.data()).set_size(str.length()));
  }

  View(const String &str) {
    set_view(Construct().set_read_buffer(str.cstring()).set_size(str.length()));
  }

  View(String &str) {
    set_view(
      Construct().set_write_buffer(str.to_char()).set_size(str.length()));
  }

  View(const void *buffer, size_t size) {
    set_view(Construct().set_read_buffer(buffer).set_size(size));
  }

  View(void *buffer, size_t size) {
    set_view(Construct().set_write_buffer(buffer).set_size(size));
  }

  var::String to_string() const;

  template <typename T> View(const Vector<T> &vector) {
    set_view(Construct()
               .set_read_buffer(vector.to_const_void())
               .set_write_buffer(nullptr)
               .set_size(vector.count() * sizeof(T)));
  }

  template <typename T> View(Vector<T> &vector) {
    set_view(Construct()
               .set_read_buffer(vector.to_const_void())
               .set_write_buffer(vector.to_void())
               .set_size(vector.count() * sizeof(T)));
  }

  template <typename T, size_t size_value>
  View(const Array<T, size_value> &array) {
    set_view(Construct()
               .set_read_buffer(array.to_const_void())
               .set_write_buffer(nullptr)
               .set_size(size_value * sizeof(T)));
  }

  template <typename T, size_t size_value> View(Array<T, size_value> &array) {
    set_view(Construct()
               .set_read_buffer(array.to_const_void())
               .set_write_buffer(array.to_void())
               .set_size(size_value * sizeof(T)));
  }

  template <typename T> explicit View(T &item) {
    // catch all
    static_assert(
      std::is_trivial<T>::value && std::is_standard_layout<T>::value,
      "Cannot construct reference from non-trivial non-standard-layout "
      "types");

    static_assert(
      !std::is_same<T, const char *>::value,
      "Cannot view a `const char *`");
    static_assert(!std::is_same<T, char *>::value, "Cannot view a `char *`");

    if (std::is_const<T>::value == false) {
      set_view(Construct()
                 .set_read_buffer(&item)
                 .set_write_buffer((void *)&item)
                 .set_size(sizeof(T)));
    } else {
      set_view(
        Construct().set_read_buffer(&item).set_write_buffer(nullptr).set_size(
          sizeof(T)));
    }
  }

  bool is_valid() const { return size() > 0; }
  bool is_null() const { return m_data == nullptr; }

  template <typename T> View &fill(const T &value) {
    for (u32 i = 0; i < this->count<T>(); i++) {
      to<T>()[i] = value;
    }
    return *this;
  }

  template <typename T> size_t count() const { return size() / sizeof(T); }

  enum class SwapBy { byte, half_word, word };

  /*! \details Swaps the byte order of the data.
   *
   * @param size 4 to swap as 32-bit words, otherwise swap 16-bit words
   * (default is 4)
   *
   * If the data is read-only, no change is made
   * and error_number() is set to EINVAL.
   *
   * On Cortex-M chips this method makes use of the built-in byte
   * swapping instructions (so it is fast).
   *
   * ```
   * //md2code:include
   * #include <var.hpp>
   * #include <sapi/hal.hpp>
   * ```
   *
   * ```
   * //md2code:main
   * char buffer[16];
   * View data_reference(buffer);
   *
   * //assume the spi outputs big endian data -- swaps 32-bit words
   * data_reference.swap_byte_order();
   * data_reference.swap_byte_order(4); //this is the same as calling
   * swap_byte_order()
   *
   * //or for swapping bytes in 16-bit words
   * data_reference.swap_byte_order(2);
   * ```
   *
   *
   */
  View &swap_byte_order(SwapBy order);

  /*! \details Returns true if the contents
   * of both View objects are the same.
   *
   */
  bool operator==(const View &a) const {
    if (a.size() == size()) {
      return memcmp(read_data(), a.read_data(), size()) == 0;
    }
    return false;
  }

  /*! \details Returns true if the contents of the
   * data objects are not the same.
   *
   */
  bool operator!=(const View &a) const { return !(*this == a); }

  /*!
   * \details Returns the effective size of the data.
   *
   *
   */
  size_t size() const { return m_size_read_only & ~m_size_read_only_flag; }

  View &truncate(size_t new_size) {
    if (size() > new_size) {
      m_size_read_only
        = (m_size_read_only & m_size_read_only_flag) | (new_size);
    }
    return *this;
  }

  View &pop_back(size_t pop_size = 1) {
    if (size() > pop_size) {
      m_size_read_only
        = (m_size_read_only & m_size_read_only_flag) | (size() - pop_size);
    }
    return *this;
  }

  View &pop_front(size_t pop_size = 1) {
    if (size() > pop_size) {
      m_size_read_only
        = (m_size_read_only & m_size_read_only_flag) | (size() - pop_size);
      m_data = (static_cast<u8 *>(m_data)) + pop_size;
    }
    return *this;
  }

  ssize_t size_signed() const { return static_cast<ssize_t>(size()); }

  /*! \details Returns true if the data object is read only.
   *
   */
  bool is_read_only() const {
    return m_size_read_only & (m_size_read_only_flag);
  }

  View &copy(const View &source);

  /*! \details Returns a pointer to the data (read/write)
   * This will return zero if the data is readonly.
   *
   * ```
   * //md2code:main
   * char buffer[64];
   * View a(buffer); //allocate 64 bytes of data
   * u32 * value = a.to<u32>(); //casts data as u32*
   * const u32 * const_value = a.to<const u32>(); //works with read only
   * data if( value == const_value ){ printf("prints for read-write
   * objects but not read-only\n");
   * }
   * ```
   *
   * Many common types are implemented as a non-template
   * function.
   *
   * See to_u8(), to_u16(), to_s32(), etc
   *
   */
  template <typename T> T *to() const {
    if (std::is_const<T>::value) {
      return (T *)read_data();
    }
    return static_cast<T *>(write_data());
  }

  const char *to_const_char() const { return to<const char>(); }
  char *to_char() const { return to<char>(); }

  const void *to_const_void() const { return to<const void>(); }
  void *to_void() const { return to<void>(); }

  const u8 *to_const_u8() const { return to<const u8>(); }
  u8 *to_u8() const { return to<u8>(); }

  const u16 *to_const_u16() const { return to<const u16>(); }
  u16 *to_u16() const { return to<u16>(); }

  const u32 *to_const_u32() const { return to<const u32>(); }
  u32 *to_u32() const { return to<u32>(); }

  const u64 *to_const_u64() const { return to<const u64>(); }
  u64 *to_u64() const { return to<u64>(); }

  const s8 *to_const_s8() const { return to<const s8>(); }
  s8 *to_s8() const { return to<s8>(); }

  const s16 *to_const_s16() const { return to<const s16>(); }
  s16 *to_s16() const { return to<s16>(); }

  const s32 *to_const_s32() const { return to<const s32>(); }
  s32 *to_s32() const { return to<s32>(); }

  const s64 *to_const_s64() const { return to<const s64>(); }
  s64 *to_s64() const { return to<s64>(); }

  const float *to_const_float() const { return to<const float>(); }
  float *to_float() const { return to<float>(); }

  /*! \details Accesses a value in the data.
   *
   *
   * If the index exceeds the size of the data, the index is set to 0.
   *
   * ```
   * //md2code:main
   * char buffer[64];
   * DataReference a(buffer); //a is 64 bytes
   * a.at<char>(arg::Position(0)) = 'a'; //assign 'a' to the first char location
   * a.at<u32>(arg::Position(4)) = 0xAAAA5555; //assigns a u32 value assuming a
   * is a u32 array u32 value = a.at<u32>(arg::Position(4)); //reads a value as
   * if a is a u32 array printf("value is 0x%lx\n", value);
   * ```
   *
   *
   */
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

  const char at_const_char(size_t position) const {
    return at<const char>(position);
  }
  char &at_char(size_t position) { return at<char>(position); }

  u8 at_const_u8(size_t position) const { return at<const u8>(position); }
  u8 &at_u8(size_t position) { return at<u8>(position); }

  u16 at_const_u16(size_t position) const { return at<const u16>(position); }
  u16 &at_u16(size_t position) { return at<u16>(position); }

  u32 at_const_u32(size_t position) const { return at<const u32>(position); }
  u32 &at_u32(size_t position) { return at<u32>(position); }

  u64 at_const_u64(size_t position) const { return at<const u64>(position); }
  u64 &at_u64(size_t position) { return at<u64>(position); }

  s8 at_const_s8(size_t position) const { return at<const s8>(position); }
  s8 &at_s8(size_t position) { return at<s8>(position); }

  s16 at_const_s16(size_t position) const { return at<const s16>(position); }
  s16 &at_s16(size_t position) { return at<s16>(position); }

  s32 at_const_s32(size_t position) const { return at<const s32>(position); }
  s32 &at_s32(size_t position) { return at<s32>(position); }

  s64 at_const_s64(size_t position) const { return at<const s64>(position); }
  s64 &at_s64(size_t position) { return at<s64>(position); }

  float at_const_float(size_t position) const {
    return at<const float>(position);
  }
  float &at_float(size_t position) { return at<float>(position); }

protected:
  void set_view(const Construct &options);

private:
  const void *read_data() const { return m_data; }
  void *write_data() const {
    if (is_read_only()) {
      return nullptr;
    }
    return m_data;
  }
  void *m_data = nullptr;
  size_t m_size_read_only = 0;
  static constexpr size_t m_size_read_only_flag = 0x80000000;

  // friend in order to assign null string to zero-length
  static const int m_zero_value;
};

class Transformer {
public:
  class Transform {
    API_AC(Transform, var::View, input);
    API_AC(Transform, var::View, output);
  };

  virtual int transform(const Transform &options) const = 0;
  virtual size_t get_output_size(size_t nbyte) const { return nbyte; }
  virtual size_t page_size_boundary() const { return 1; }

protected:
};

} // namespace var

#if USE_PRINTER
namespace sys {
class Printer;
Printer &operator<<(Printer &printer, const var::View &a);
} // namespace sys
#endif

#endif /* VAR_API_ITEM_HPP_ */
