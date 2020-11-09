/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
#ifndef VAR_API_ARRAY_HPP_
#define VAR_API_ARRAY_HPP_

#include <array>
#include <cstdio>
#include <iterator>

#include "api/api.hpp"

namespace var {

/*! \brief Array Class
 * \details The Array class is a template
 * used to contain a standard C array.
 *
 * It provides methods to access the array
 * safely.
 *
 * \code
 * #include <var.hpp>
 * u32 c_array[64]; //C style array
 * Array<u32, 64> array; //var::Array
 *
 * printf("C array is %ld bytes\n", sizeof(c_array));
 * printf("Array is %ld bytes\n", array.size());
 *
 * printf("C array has %ld items\n", sizeof(c_array)/sizeof(u32));
 * printf("Array has %ld items\n", array.count());
 *
 * printf("C array back is %ld\n",
 * c_array[sizeof(c_array)/sizeofstatic_cast<u32>(-1)]); printf("Array back is
 * %ld\n", array.back()); \endcode
 *
 * The Array class has a fixed number of items. It can be
 * created dynamically with `new` and `delete` or allocated
 * on the stack or heap.
 *
 * If you are looking for dynamic sizing, see var::Vector is
 * an array that is dynamically sized where items can be appended.
 *
 * var::Queue allows for pushing items on the front of a list
 * and popping them from the back.
 *
 */
template <typename T, size_t SizeValue> class Array {
public:
  Array() = default;
  Array(const std::array<T, SizeValue> &array) : m_array(array) {}
  Array(std::array<T, SizeValue> &&array) : m_array(std::move(array)) {}
  Array(std::initializer_list<T> il) : m_array{{il}} {}
  // Array &operator=(std::initializer_list<T> il) { m_array = {il}; }

  typename std::array<T, SizeValue>::const_iterator begin() const noexcept {
    return m_array.begin();
  }
  typename std::array<T, SizeValue>::iterator begin() noexcept {
    return m_array.begin();
  }

  typename std::array<T, SizeValue>::const_iterator end() const noexcept {
    return m_array.end();
  }
  typename std::array<T, SizeValue>::iterator end() noexcept {
    return m_array.end();
  }

  typename std::array<T, SizeValue>::const_iterator cbegin() const noexcept {
    return m_array.cbegin();
  }
  typename std::array<T, SizeValue>::const_iterator cend() const noexcept {
    return m_array.cend();
  }

  typename std::array<T, SizeValue>::const_reverse_iterator
  rbegin() const noexcept {
    return m_array.rbegin();
  }
  typename std::array<T, SizeValue>::reverse_iterator rbegin() noexcept {
    return m_array.rbegin();
  }

  typename std::array<T, SizeValue>::const_reverse_iterator
  rend() const noexcept {
    return m_array.rend();
  }
  typename std::array<T, SizeValue>::reverse_iterator rend() noexcept {
    return m_array.rend();
  }

  typename std::array<T, SizeValue>::const_reverse_iterator
  crbegin() const noexcept {
    return m_array.crbegin();
  }
  typename std::array<T, SizeValue>::const_reverse_iterator
  crend() const noexcept {
    return m_array.crend();
  }

  T &at(size_t position) { return m_array.at(position); }
  const T &at(size_t position) const { return m_array.at(position); }

  T &operator[](size_t position) { return m_array[position]; }
  const T &operator[](size_t position) const { return m_array[position]; }

  T &front() {
    return m_array.front();
  }
  T &back() { return m_array.back(); }
  const T &front() const { return m_array.front(); }
  const T &back() const { return m_array.back(); }

  /*! \details Returns the number of objects in the array.
   *
   * \code
   * #include <var.hpp>
   * Array<u32, 64> array;
   * for(u32 i=0; i < array.count(); i++){
   *   array.at(i) = i;
   * }
   * \endcode
   *
   *
   */
  size_t count() const { return m_array.size(); }

  bool is_empty() const { return m_array.empty(); }

  Array &fill(const T &value) {
    std::fill(begin(), end(), value);
    return *this;
  }

  std::array<T, SizeValue> &array() { return m_array; }
  const std::array<T, SizeValue> &array() const { return m_array; }

  const T *data() const { return m_array.data(); }
  T *data() { return m_array.data(); }

  void *to_void() { return (void *)m_array.data(); }
  const void *to_const_void() const { return (const void *)m_array.data(); }

private:
  std::array<T, SizeValue> m_array;
};

template <typename T> class Pair : public Array<T, 2> {
public:
  Pair() {}
  Pair(const T &k, const T &v) {
    key() = k;
    value() = v;
  }

  T &key() { return Array<T, 2>::at(0); }
  const T &key() const { return Array<T, 2>::at(0); }

  T &value() { return Array<T, 2>::at(1); }
  const T &value() const { return Array<T, 2>::at(1); }
};

} // namespace var

#endif // VAR_API_ARRAY_HPP_
