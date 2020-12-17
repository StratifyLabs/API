/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
#ifndef VAR_API_ARRAY_HPP_
#define VAR_API_ARRAY_HPP_

#include <array>
#include <cstdio>
#include <iterator>

#include "api/api.hpp"

namespace var {

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

  API_NO_DISCARD T &at(size_t position) { return m_array.at(position); }
  API_NO_DISCARD const T &at(size_t position) const {
    return m_array.at(position);
  }

  T &operator[](size_t position) { return m_array[position]; }
  const T &operator[](size_t position) const { return m_array[position]; }

  bool operator==(const Array &a) const { return m_array == a.m_array; }

  T &front() {
    return m_array.front();
  }
  T &back() { return m_array.back(); }
  const T &front() const { return m_array.front(); }
  const T &back() const { return m_array.back(); }

  API_NO_DISCARD size_t count() const { return m_array.size(); }
  API_NO_DISCARD bool is_empty() const { return m_array.empty(); }

  Array &fill(const T &value) {
    std::fill(begin(), end(), value);
    return *this;
  }

  std::array<T, SizeValue> &array() { return m_array; }
  const std::array<T, SizeValue> &array() const { return m_array; }

  API_NO_DISCARD const T *data() const { return m_array.data(); }
  API_NO_DISCARD T *data() { return m_array.data(); }

  API_NO_DISCARD void *to_void() { return (void *)m_array.data(); }
  API_NO_DISCARD const void *to_const_void() const {
    return (const void *)m_array.data();
  }

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
