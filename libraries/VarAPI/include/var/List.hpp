/*! \file */
// Copyright 2011-2022 Tyler Gilbert and Stratify Labs, Inc; see
// LICENSE.md for rights.
#ifndef VAR_API_LIST_HPP_
#define VAR_API_LIST_HPP_

#include <list>

#include "ContainerObject.hpp"

namespace var {

/*! \details
 *
 * This class is a wrapper for `std::list` using
 * the API framework to manage containers.
 *
 */
template <typename T>
class List : public ContainerObject<List<T>, std::list<T>, T> {
  using Base = ContainerObject<List<T>, std::list<T>, T>;

public:
  List() : Base() {}

  List &push_front(const T &value) {
    this->m_container.push_front(value);
    return *this;
  }

  List &push_back(const T &value) {
    this->m_container.push_back(value);
    return *this;
  }

  template <class... Args> List<T> &emplace_back(Args&&... args) {
    this->m_container.emplace_back(args...);
    return *this;
  }

  template <class... Args> List<T> &emplace_front(Args&&... args) {
    this->m_container.emplace_front(args...);
    return *this;
  }

  List &pop_front() {
    this->m_container.pop_front();
    return *this;
  }

  List &pop_back() {
    this->m_container.pop_back();
    return *this;
  }

  List &clear() {
    // deconstruct objects in the list using pop
    this->m_container.clear();
    return *this;
  }
};
} // namespace var
#endif // VAR_API_LIST_HPP_
