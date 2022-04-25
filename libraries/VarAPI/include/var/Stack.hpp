/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
#ifndef VAR_API_VAR_STACK_HPP_
#define VAR_API_VAR_STACK_HPP_

#include <stack>

#include "ContainerObject.hpp"

namespace var {

template <typename T> class Stack : public ContainerObject<Stack<T>, std::stack<T>, T> {
  using Base = ContainerObject<Stack<T>, std::stack<T>, T>;
public:
  Stack() : Base(){}

  T &top() { return this->m_container.top(); }
  const T &top() const { return this->m_container.top(); }

  Stack &push(const T &value) {
    this->m_container.push_back(value);
    return *this;
  }

  template <class... Args> Queue<T> &emplace(Args &&...args) {
    this->m_container.emplace(args...);
    return *this;
  }

  Stack &pop() {
    this->m_container.pop();
    return *this;
  }

  API_NO_DISCARD bool is_empty() const { return this->m_container.empty(); }
  API_NO_DISCARD u32 count() const { return this->m_container.size(); }

  Stack &clear() {
    // deconstruct objects in the list using pop
    this->m_container.clear();
    return *this;
  }

};
} // namespace var
#endif // VAR_API_VAR_STACK_HPP_
