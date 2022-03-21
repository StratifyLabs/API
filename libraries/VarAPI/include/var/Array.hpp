/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
#ifndef VAR_API_ARRAY_HPP_
#define VAR_API_ARRAY_HPP_

#include <array>
#include <cstdio>
#include <iterator>
#include <numeric>

#include "api/api.hpp"

#include "ContainerObject.hpp"

namespace var {

/*! \details
 *
 * This class is a wrapper for std::array. The functions
 * are API framework friendly and simplified compared to
 * std::array.
 *
 * @tparam T The underlying type to store
 * @tparam SizeValue The number of T to store in the array
 *
 *
 * ```cpp
 * #include <var.hpp>
 *
 * Array<u32, 5> values;
 *
 *
 *
 * ```
 *
 */
template <typename T, size_t SizeValue>
class Array
  : public ContainerObject<Array<T, SizeValue>, std::array<T, SizeValue>, T> {
  using Base
    = ContainerObject<Array<T, SizeValue>, std::array<T, SizeValue>, T>;

public:
  Array() : Base(){}
  Array(const std::array<T, SizeValue> &array) : Base(array) {}
  Array(std::array<T, SizeValue> &&array) : Base(std::move(array)) {}
  Array(std::initializer_list<T> il) : Base(il) {}

  T &operator[](size_t position) { return this->m_container[position]; }
  const T &operator[](size_t position) const {
    return this->m_container[position];
  }

  bool operator==(const Array &a) const {
    return this->m_container == a.m_container;
  }

  T &front() { return this->m_container.front(); }
  T &back() { return this->m_container.back(); }
  const T &front() const { return this->m_container.front(); }
  const T &back() const { return this->m_container.back(); }

  API_NO_DISCARD size_t count() const { return this->m_container.size(); }
  API_NO_DISCARD bool is_empty() const { return this->m_container.empty(); }

  std::array<T, SizeValue> &array() { return this->m_container; }
  const std::array<T, SizeValue> &array() const { return this->m_container; }

  API_NO_DISCARD const T *data() const { return this->m_container.data(); }
  API_NO_DISCARD T *data() { return this->m_container.data(); }

  API_NO_DISCARD void *to_void() { return (void *)this->m_container.data(); }
  API_NO_DISCARD const void *to_const_void() const {
    return (const void *)this->m_container.data();
  }

private:
  // std::array<T, SizeValue> this->m_container;
};

template <typename T> class Pair : public Array<T, 2> {
public:
  Pair() = default;
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
