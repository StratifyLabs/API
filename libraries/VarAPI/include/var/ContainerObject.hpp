/*! \file */ // Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see
// LICENSE.md for rights.
#ifndef VAR_API_CONTAINER_OBJECT_HPP_
#define VAR_API_CONTAINER_OBJECT_HPP_

#include <array>
#include <cstdio>
#include <iterator>
#include <numeric>

#include "api/api.hpp"

namespace var {

template <class Derived, typename Container, typename T>
class ContainerObject : public api::ExecutionContext {
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

  typename Container::const_reverse_iterator rbegin() const noexcept {
    return m_container.rbegin();
  }
  typename Container::reverse_iterator rbegin() noexcept {
    return m_container.rbegin();
  }

  typename Container::const_reverse_iterator rend() const noexcept {
    return m_container.rend();
  }
  typename Container::reverse_iterator rend() noexcept {
    return m_container.rend();
  }

  typename Container::const_reverse_iterator crbegin() const noexcept {
    return m_container.crbegin();
  }

  typename Container::const_reverse_iterator crend() const noexcept {
    return m_container.crend();
  }

  API_NO_DISCARD T accumulate(T initial_value = T()) const {
    return std::accumulate(begin(), end(), initial_value);
  }

protected:
  Container m_container;
};

} // namespace var

#endif // VAR_API_CONTAINER_OBJECT_HPP_
