/*! \file */ // Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see
// LICENSE.md for rights.
#ifndef VAR_API_CONTAINER_OBJECT_HPP_
#define VAR_API_CONTAINER_OBJECT_HPP_

#include <algorithm>
#include <array>
#include <cstdio>
#include <iterator>
#include <numeric>
#include <optional>

#include "api/api.hpp"

namespace var {


/*! \details This is the parent class of the standard containers
 * that are wrapped in this library.
 *
 * @tparam Derived Name of the Derived class
 * @tparam Container std::container type
 * @tparam T Type that is contained
 *
 * It declares the iterators that allow for range-based for loops:
 *
 * ```cpp
 * var::Vector<int> container; //inherits ContainerObject
 * for(auto value: constainer){
 *  printf("value is %d\n", value);
 * }
 * ```
 *
 * It also provides member functions for various std::algorithms.
 *
 * ```cpp
 * container.fill(24);
 * container.sort(Vector<int>::ascending)
 * container.assign_adjacent_difference();
 * ```
 *
 *
 */

template <class Derived, typename Container, typename T>
class ContainerObjectForwardOnly : public api::ExecutionContext {
public:
  typename Container::const_iterator begin() const noexcept {
    return m_container.begin();
  }
  typename Container::iterator begin() noexcept { return m_container.begin(); }

  typename Container::const_iterator end() const noexcept {
    return m_container.end();
  }
  typename Container::iterator end() noexcept { return m_container.end(); }

  typename Container::const_iterator cbegin() const noexcept {
    return m_container.cbegin();
  }
  typename Container::const_iterator cend() const noexcept {
    return m_container.cend();
  }

  API_NO_DISCARD size_t count() const { return m_container.size(); }

  API_NO_DISCARD bool is_empty() const { return m_container.empty(); }

  API_NO_DISCARD T &back() { return this->m_container.back(); }
  API_NO_DISCARD const T &back() const { return this->m_container.back(); }

  API_NO_DISCARD T &front() { return this->m_container.front(); }
  API_NO_DISCARD const T &front() const { return this->m_container.front(); }

  API_NO_DISCARD T &at(size_t position) { return m_container.at(position); }
  API_NO_DISCARD const T &at(size_t position) const {
    return m_container.at(position);
  }

  API_NO_DISCARD T accumulate(T initial_value = T()) const {
    return std::accumulate(begin(), end(), initial_value);
  }

  Derived &fill(const T &value) {
    std::fill(begin(), end(), value);
    return self();
  }

  API_NO_DISCARD size_t find_offset(const T &a) const {
    return std::find(begin(), end(), a) - begin();
  }

  API_NO_DISCARD const T &find(const T &a) const {
    const size_t offset = find_offset(a);
    if (offset == count()) {
      static T not_found{};
      return not_found;
    }
    return at(offset);
  }

  API_NO_DISCARD T &find(const T &a) {
    const size_t offset = find_offset(a);
    if (offset == count()) {
      static T not_found{};
      return not_found;
    }
    return at(offset);
  }

  API_NO_DISCARD static bool ascending(const T &a, const T &b) { return a < b; }
  API_NO_DISCARD static bool descending(const T &a, const T &b) {
    return b < a;
  }

  using SortComparator = bool (*)(const T &a, const T &b);
  using sort_compartor_t = SortComparator;

  template<typename CompareFunction> Derived &sort(CompareFunction compare_function) {
    std::sort(begin(), end(), compare_function);
    return self();
  }

  Derived &populate_by_incrementing(const T &initial_value = T()) {
    std::iota(begin(), end(), initial_value);
    return self();
  }

  template<typename Function> const Derived &for_each(Function function) const {
    std::for_each(begin(), end(), function);
    return self();
  };

  template<typename Function> Derived &for_each(Function function) {
    std::for_each(begin(), end(), function);
    return self();
  };

  Derived &assign_adjacent_difference(const T &initial_value = T()) {
    std::adjacent_difference(begin(), end(), initial_value);
    return self();
  }

  Derived &rotate_left(size_t count) {
    std::rotate(begin(), std::advance(begin(), count), end());
    return self();
  }

  template<typename CompareFunction> bool is_sorted(CompareFunction compare_function) const {
    return std::is_sorted(begin(), end(), compare_function);
  }

  API_NO_DISCARD const T &get_maximum() const {
    return *std::max_element(cbegin(), cend());
  }

  T &get_maximum() { return *std::max_element(begin(), end()); }

  API_NO_DISCARD const T &get_minimum() const {
    return *std::min_element(cbegin(), cend());
  }

  T &get_minimum() { return *std::min_element(begin(), end()); }

  bool operator==(const Derived &a) const {
    return m_container == a.m_container;
  }

  bool operator!=(const Derived &a) const { return !(*this == a); }

  API_NO_DISCARD const auto &container() const { return m_container; }
  auto &container() { return m_container; }

  API_NO_DISCARD T sum() const { return std::accumulate(begin(), end(), T()); }
  API_NO_DISCARD T mean() const { return sum() / count(); }
  API_NO_DISCARD T variance() const {
    const auto local_mean = this->mean();
    const auto result = std::accumulate(
      begin(),
      end(),
      T(),
      [local_mean](const T &a, const T &b) {
        return a + (b - local_mean) * (b - local_mean);
      });
    return result / count();
  }

protected:
  ContainerObjectForwardOnly() = default;
  explicit ContainerObjectForwardOnly(const Container &value) : m_container(value) {}
  explicit ContainerObjectForwardOnly(Container &&value) : m_container(std::move(value)) {}
  explicit ContainerObjectForwardOnly(std::initializer_list<T> il) : m_container(il) {}
  Container m_container;

  Derived &self() { return static_cast<Derived &>(*this); }
};

template <class Derived, typename Container, typename T>
class ContainerObject : public ContainerObjectForwardOnly<Derived, Container, T> {
  using Base = ContainerObject<Derived, Container, T>;
public:

  typename Container::const_reverse_iterator rbegin() const noexcept {
    return this->m_container.rbegin();
  }
  typename Container::reverse_iterator rbegin() noexcept {
    return this->m_container.rbegin();
  }

  typename Container::const_reverse_iterator rend() const noexcept {
    return this->m_container.rend();
  }
  typename Container::reverse_iterator rend() noexcept {
    return this->m_container.rend();
  }

  typename Container::const_reverse_iterator crbegin() const noexcept {
    return this->m_container.crbegin();
  }

  typename Container::const_reverse_iterator crend() const noexcept {
    return this->m_container.crend();
  }


protected:
  using Parent = ContainerObjectForwardOnly<Derived, Container, T>;
  ContainerObject() = default;
  explicit ContainerObject(const Container &value) : Parent(value) {}
  explicit ContainerObject(Container &&value) : Parent(std::move(value)) {}
  explicit ContainerObject(std::initializer_list<T> il) : Parent(il) {}

};

} // namespace var

#endif // VAR_API_CONTAINER_OBJECT_HPP_
