/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
#ifndef VAR_API_VECTOR_HPP_
#define VAR_API_VECTOR_HPP_

#include <functional>
#include <utility>
#include <vector>

#include "ContainerObject.hpp"

namespace var {

template <typename T>
class Vector : public ContainerObject<Vector<T>, std::vector<T>, T> {
  using Base = ContainerObject<Vector<T>, std::vector<T>, T>;

public:
  Vector() : Base() {}
  explicit Vector(size_t count) { this->m_container.resize(count); }
  Vector(std::initializer_list<T> il) : Base(il) {}

  Vector<T> &operator<<(const T &a) { return push_back(a); }

  using iterator = typename std::vector<T>::iterator;
  using const_iterator = typename std::vector<T>::const_iterator;
  using reverse_iterator = typename std::vector<T>::reverse_iterator;
  using const_reverse_iterator =
    typename std::vector<T>::const_reverse_iterator;

  iterator insert(const_iterator position, const T &value) {
    return this->m_container.insert(position, value);
  }

  Vector<T> &insert(size_t position, const T &value) & {
    insert(this->begin() + position, value);
    return *this;
  }

  Vector<T> &&insert(size_t position, const T &value) && {
    return std::move(insert(position, value));
  }

  iterator insert(const_iterator position, size_t n, const T &value) {
    return this->m_container.insert(position, n, value);
  }

  iterator insert(const_iterator position, T &&value) {
    return this->m_container(position, value);
  }

  Vector<T> &insert(size_t position, T &&value) & {
    insert(this->begin() + position, value);
    return *this;
  }

  Vector<T> &&insert(size_t position, T &&value) && {
    return std::move(insert(position, value));
  }

  iterator insert(const_iterator position, std::initializer_list<T> il) {
    return this->m_container.insert(position, il);
  }

  Vector<T> &operator<<(const Vector<T> &a) & {
    for (size_t i = 0; i < a.count(); i++) {
      *this << a.at(i);
    }
    return *this;
  }

  Vector<T> &&operator<<(const Vector<T> &a) && {
    return std::move(*this << a);
  }

  Vector<T> &push_back(const T &a) & {
    this->m_container.push_back(a);
    return *this;
  }
  Vector<T> &&push_back(const T &a) && { return std::move(push_back(a)); }

  Vector<T> &push_back(T &&a) & {
    this->m_container.push_back(std::forward<T>(a));
    return *this;
  }
  Vector<T> &&push_back(T &&a) && { return std::move(push_back(a)); }

  Vector<T> &pop_back() & {
    this->m_container.pop_back();
    return *this;
  }
  Vector<T> &&pop_back() && { return std::move(pop_back()); }

  template <class... Args> T &emplace_back(Args &&...args) {
    return this->m_container.emplace_back(args...);
  }

  Vector &shrink_to_fit() & {
    this->m_container.shrink_to_fit();
    return *this;
  }

  Vector &&shrink_to_fit() && { return std::move(shrink_to_fit()); }

  class Erase {
    API_AF(Erase, size_t, position, 0);
    API_AF(Erase, size_t, count, 1);
  };

  Vector &erase(const Erase &options) & {
    this->m_container.erase(
      this->m_container.begin() + options.position(),
      this->m_container.begin() + options.position() + options.count());
    return *this;
  }

  Vector &&erase(const Erase &options) && { return std::move(erase(options)); }

  Vector &operator()(const Erase &options) { return erase(options); }

  Vector &remove(u32 pos) & { return erase(Erase().set_position(pos)); }
  Vector &&remove(u32 pos) && { return std::move(remove(pos)); }

  API_NO_DISCARD const T &operator[](size_t offset) const {
    return this->m_container[offset];
  }
  API_NO_DISCARD T &operator[](size_t offset) {
    return this->m_container[offset];
  }

  API_NO_DISCARD T *search(const T &a) {
    return reinterpret_cast<T *>(bsearch(
      &a,
      std::vector<T>::data(),
      this->count(),
      sizeof(T),
      Base::ascending));
  }

  API_NO_DISCARD T *
  search(const T &a, int (*compare)(const void *, const void *)) {
    return reinterpret_cast<T *>(
      bsearch(&a, std::vector<T>::data(), this->count(), sizeof(T), compare));
  }

  Vector<T> &resize(size_t count) & {
    this->m_container.resize(count);
    return *this;
  }

  Vector<T> &&resize(size_t count) && { return std::move(resize(count)); }

  Vector<T> &reserve(size_t count) & {
    this->m_container.reserve(count);
    return *this;
  }
  Vector<T> &&reserve(size_t count) && { return std::move(reserve(count)); }

  Vector<T> &free() & {
    this->m_container = Vector<T>();
    return *this;
  }
  Vector<T> &&free() && { return std::move(free()); }

  template <typename ConvertedType> Vector<ConvertedType> convert() const {
    Vector<ConvertedType> result;
    result.reserve(this->count());
    for (const auto &item : *this) {
      result.push_back(item);
    }
    return result;
  }

  template <typename ConvertedType>
  Vector<ConvertedType>
  convert(ConvertedType (*convert_function)(const T &value)) const {
    Vector<ConvertedType> result;
    result.reserve(this->count());
    for (const auto &item : *this) {
      result.push_back(convert_function(item));
    }
    return result;
  }

  Vector<T> operator+(const Vector<T> &a) const { return operate(a, add); }
  Vector<T> operator-(const Vector<T> &a) const { return operate(a, subtract); }
  Vector<T> operator*(const Vector<T> &a) const { return operate(a, multiply); }
  Vector<T> operator/(const Vector<T> &a) const { return operate(a, divide); }
  Vector<T> operator+(const T &a) const { return operate_single(a, add); }
  Vector<T> operator-(const T &a) const { return operate_single(a, subtract); }
  Vector<T> operator*(const T &a) const { return operate_single(a, multiply); }
  Vector<T> operator/(const T &a) const { return operate_single(a, divide); }

  Vector<T> operator<<(u32 a) const {
    auto result = Vector<T>().resize(this->count());
    if (a < this->count()) {
      for (u32 i = 0; i < this->count() - a; i++) {
        result.at(i) = this->at(i + a);
      }
    }
    return result;
  }

  Vector<T> operator>>(u32 a) const {
    auto result = Vector<T>().resize(this->count());
    if (a < this->count()) {
      for (u32 i = 0; i < this->count() - a; i++) {
        result.at(i + a) = this->at(i);
      }
    }
    return result;
  }

  Vector<T> &clear() &{
    this->m_container.clear();
    return *this;
  }
  Vector<T> &&clear() &&{
    return std::move(clear());
  }

  API_NO_DISCARD bool is_empty() const { return this->m_container.empty(); }

  API_NO_DISCARD std::vector<T> &vector() { return this->m_container; }
  API_NO_DISCARD const std::vector<T> &vector() const {
    return this->m_container;
  }

  API_NO_DISCARD const T *data() const { return this->m_container.data(); }
  API_NO_DISCARD T *data() { return this->m_container.data(); }

  API_NO_DISCARD void *to_void() { return (void *)this->m_container.data(); }
  API_NO_DISCARD const void *to_const_void() const {
    return (const void *)this->m_container.data();
  }

private:
  Vector<T> operate(const Vector<T> &a, T (*fn)(const T &, const T &)) const {
    Vector<T> result;
    u32 c = a.count() < this->count() ? a.count() : this->count();
    for (u32 i = 0; i < c; i++) {
      result.push_back(fn(this->at(i), a.at(i)));
    }
    return result;
  }

  Vector<T> operate_single(const T &a, T (*fn)(const T &, const T &)) const {
    Vector<T> result;
    u32 c = this->count();
    for (u32 i = 0; i < c; i++) {
      result.push_back(fn(this->at(i), a));
    }
    return result;
  }

  static T add(const T &a, const T &b) { return a + b; }
  static T subtract(const T &a, const T &b) { return a - b; }
  static T multiply(const T &a, const T &b) { return a * b; }
  static T divide(const T &a, const T &b) { return a / b; }

  static bool compare(const Vector<T> &a, const Vector<T> &b) {
    u32 i;
    if (a.count() != b.count()) {
      return false;
    }
    for (i = 0; i < a.count(); i++) {
      if (a[i] != b[i]) {
        return false;
      }
    }
    return true;
  }
};

} // namespace var

#endif // VAR_API_VECTOR_HPP_
