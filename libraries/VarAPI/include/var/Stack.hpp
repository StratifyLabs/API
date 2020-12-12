/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
#ifndef VAR_API_STACK_HPP_
#define VAR_API_STACK_HPP_

#include <cstdio>
#include <deque>
#include <new>

#include "api/api.hpp"

namespace var {

template <typename T> class Stack : public api::ExecutionContext {
public:
  T &top() { return m_deque.back(); }
  const T &top() const { return m_deque.back(); }

  Stack &push(const T &value) {
    m_deque.push_back(value);
    return *this;
  }

  Stack &pop() {
    m_deque.pop_back();
    return *this;
  }

  API_NO_DISCARD bool is_empty() const { return m_deque.empty(); }
  API_NO_DISCARD u32 count() const { return m_deque.size(); }

  Stack &clear() {
    // deconstruct objects in the list using pop
    m_deque.clear();
    return *this;
  }

private:
  std::deque<T> m_deque;
};
} // namespace var
#endif // VAR_API_STACK_HPP_
