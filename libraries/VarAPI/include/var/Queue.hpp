/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
#ifndef VAR_API_QUEUE_HPP_
#define VAR_API_QUEUE_HPP_

#include <cstdio>

#include <algorithm>
#include <deque>
#include <new>
#include <numeric>

#include "ContainerObject.hpp"

namespace var {

template <typename T> class Queue : public ContainerObject<Queue<T>, std::deque<T>, T> {
  using Base = ContainerObject<Queue<T>, std::deque<T>, T>;
public:
  Queue() = default;

  Queue &push(const T &value) {
    this->m_container.push_back(value);
    return *this;
  }

  Queue &pop() {
    this->m_container.pop_front();
    return *this;
  }

  class Erase {
    API_AF(Erase, size_t, position, 0);
    API_AF(Erase, size_t, count, 1);
  };

  Queue &erase(const Erase &options) {
    this->m_container.erase(
      this->m_container.begin() + options.position(),
      this->m_container.begin() + options.position() + options.count());
    return *this;
  }
  Queue &operator()(const Erase &options) { return erase(options); }

  Queue &remove(u32 pos) { return erase(Erase().set_position(pos)); }

  Queue &clear() {
    this->m_container.clear();
    return *this;
  }


private:
};
} // namespace var
#endif // VAR_API_QUEUE_HPP_
