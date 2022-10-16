/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
#ifndef VAR_API_VAR_QUEUE_HPP_
#define VAR_API_VAR_QUEUE_HPP_

#include <deque>

#include "ContainerObject.hpp"

namespace var {

template <typename T>
class Queue : public ContainerObject<Queue<T>, std::deque<T>, T> {
  using Base = ContainerObject<Queue<T>, std::deque<T>, T>;

public:
  Queue() : Base() {}

  Queue &push(const T &value) & {
    this->m_container.push_back(value);
    return *this;
  }
  Queue &&push(const T &value) && { return std::move(push(value)); }

  template <class... Args> Queue<T> &emplace(Args &&...args) {
    this->m_container.emplace_back(args...);
    return *this;
  }

  Queue &pop() & {
    this->m_container.pop_front();
    return *this;
  }
  Queue &&pop() && { return std::move(pop()); }

  class Erase {
    API_AF(Erase, size_t, position, 0);
    API_AF(Erase, size_t, count, 1);
  };

  Queue &erase(const Erase &options) & {
    this->m_container.erase(
      this->m_container.begin() + options.position(),
      this->m_container.begin() + options.position() + options.count());
    return *this;
  }
  Queue &&erase(const Erase &options) && { return std::move(erase(options)); }

  Queue &operator()(const Erase &options) { return erase(options); }

  Queue &remove(u32 position) & {
    return erase(Erase().set_position(position));
  }
  Queue &&remove(u32 position) && { return std::move(remove(position)); }

  Queue &clear() & {
    this->m_container.clear();
    return *this;
  }
  Queue &&clear() && { return std::move(clear()); }

private:
};
} // namespace var
#endif // VAR_API_VAR_QUEUE_HPP_
