/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
#ifndef VAR_API_QUEUE_HPP_
#define VAR_API_QUEUE_HPP_

#include <cstdio>

#include <algorithm>
#include <deque>
#include <new>

#include "api/api.hpp"

namespace var {

template <typename T> class Queue : public api::ExecutionContext {
public:
  Queue() {}
  ~Queue() {}

  using iterator = typename std::deque<T>::iterator;
  using const_iterator = typename std::deque<T>::const_iterator;
  using reverse_iterator = typename std::deque<T>::reverse_iterator;
  using const_reverse_iterator =
    typename std::vector<T>::const_reverse_iterator;

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

  iterator insert(const_iterator position, const T &value) {
    return m_deque.insert(position, value);
  }

  T &at(size_t position) { return m_deque.at(position); }
  const T &at(size_t position) const { return m_deque.at(position); }

  T &back() { return m_deque.back(); }
  const T &back() const { return m_deque.back(); }

  const T &front() const { return m_deque.front(); }
  T &front() { return m_deque.front(); }

  Queue &push(const T &value) {
    m_deque.push_back(value);
    return *this;
  }

  Queue &pop() {
    m_deque.pop_front();
    return *this;
  }

  class Erase {
    API_AF(Erase, size_t, position, 0);
    API_AF(Erase, size_t, count, 1);
  };

  Queue &erase(const Erase &options) {
    m_deque.erase(
      m_deque.begin() + options.position(),
      m_deque.begin() + options.position() + options.count());
    return *this;
  }
  Queue &operator()(const Erase &options) { return erase(options); }

  Queue &remove(u32 pos) { return erase(Erase().set_position(pos)); }

  size_t find_offset(const T &a) const {
    size_t offset = std::find(begin(), end(), a) - begin();
    return offset;
  }

  const T &find(const T &a, const T &not_found = T()) const {
    size_t offset = find_offset(a);
    if (offset == count()) {
      return not_found;
    }
    return at(offset);
  }

  bool is_empty() const { return m_deque.empty(); }
  u32 count() const { return m_deque.size(); }

  Queue &clear() {
    m_deque.clear();
    return *this;
  }

private:
  std::deque<T> m_deque;
};
} // namespace var
#endif // VAR_API_QUEUE_HPP_
