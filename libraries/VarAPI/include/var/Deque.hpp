/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
#ifndef VAR_API_DEQUE_HPP_
#define VAR_API_DEQUE_HPP_

#include <deque>

#include "ContainerObject.hpp"

namespace var {

template <typename T>
class Deque : public ContainerObject<Deque<T>, std::deque<T>, T> {
  using Base = ContainerObject<Deque<T>, std::deque<T>, T>;

public:
  Deque() : Base() {}

  Deque &push_front(const T &value) & {
    this->m_container.push_front(value);
    return *this;
  }
  Deque &&push_front(const T &value) && { return std::move(push_front(value)); }

  Deque &push_back(const T &value) & {
    this->m_container.push_back(value);
    return *this;
  }
  Deque &&push_back(const T &value) && { return std::move(push_back(value)); }

  Deque &pop_front() & {
    this->m_container.pop_front();
    return *this;
  }
  Deque &&pop_front(const T &value) && { return std::move(pop_front(value)); }

  Deque &pop_back() & {
    this->m_container.pop_back();
    return *this;
  }
  Deque &&pop_back(const T &value) && { return std::move(pop_back(value)); }

  Deque &clear() & {
    // deconstruct objects in the list using pop
    this->m_container.clear();
    return *this;
  }
  Deque &&clear(const T &value) && { return std::move(clear(value)); }
};
} // namespace var
#endif // VAR_API_DEQUE_HPP_
