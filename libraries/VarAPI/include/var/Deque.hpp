/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
#ifndef VAR_API_DEQUE_HPP_
#define VAR_API_DEQUE_HPP_

#include <cstdio>
#include <deque>
#include <new>

#include "api/api.hpp"

namespace var {

template <typename T> class Deque : public api::ExecutionContext {
public:
  using iterator = typename std::deque<T>::iterator;
  using const_iterator = typename std::deque<T>::const_iterator;
  using reverse_iterator = typename std::deque<T>::reverse_iterator;
  using const_reverse_iterator = typename std::deque<T>::const_reverse_iterator;

  const_iterator begin() const noexcept { return m_deque.begin(); }
  iterator begin() noexcept { return m_deque.begin(); }

  const_iterator end() const noexcept { return m_deque.end(); }
  iterator end() noexcept { return m_deque.end(); }

  const_iterator cbegin() const noexcept { return m_deque.cbegin(); }
  const_iterator cend() const noexcept { return m_deque.cend(); }

  const_reverse_iterator rbegin() const noexcept { return m_deque.rbegin(); }
  reverse_iterator rbegin() noexcept { return m_deque.rbegin(); }

  const_reverse_iterator rend() const noexcept { return m_deque.rend(); }
  reverse_iterator rend() noexcept { return m_deque.rend(); }

  const_reverse_iterator crbegin() const noexcept { return m_deque.crbegin(); }
  const_reverse_iterator crend() const noexcept { return m_deque.crend(); }

  API_NO_DISCARD T &back() { return m_deque.back(); }
  API_NO_DISCARD const T &back() const { return m_deque.back(); }

  API_NO_DISCARD const T &front() const { return m_deque.front(); }
  API_NO_DISCARD T &front() { return m_deque.front(); }

  Deque &push_front(const T &value) {
    m_deque.push_front(value);
    return *this;
  }

  Deque &push_back(const T &value) {
    m_deque.push_back(value);
    return *this;
  }

  Deque &pop_front() {
    m_deque.pop_front();
    return *this;
  }

  Deque &pop_back() {
    m_deque.pop_back();
    return *this;
  }

  bool is_empty() const { return m_deque.empty(); }
  u32 count() const { return m_deque.size(); }

  Deque &clear() {
    // deconstruct objects in the list using pop
    m_deque.clear();
    return *this;
  }

private:
  std::deque<T> m_deque;
};
} // namespace var
#endif // VAR_API_DEQUE_HPP_
