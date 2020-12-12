/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
/*
 * Ring.hpp
 *
 *  Created on: Apr 11, 2017
 *      Author: tgil
 */

#ifndef VAR_API_RING_HPP_
#define VAR_API_RING_HPP_

#include <new>

#include "Data.hpp"

namespace var {

template <typename T> class Ring : public Data {
public:
  Ring(size_t count) : Data(count * sizeof(T)) {
    m_count = count;
    m_head = 0;
    m_tail = 0;
    m_is_overflow_allowed = true;
  }

  ~Ring() {
    while (is_empty() == false) {
      pop();
    }
  }

  u32 count() const { return m_count; }

  u32 count_ready() const {
    // how many item are available
    if (m_tail == m_count) {
      return m_count; // ring is full
    }

    if (m_head > m_tail) {
      return m_head - m_tail;
    }

    return m_count - (m_tail - m_head);
  }

  bool is_full() const { return m_tail == m_count; }
  bool is_empty() const { return m_tail == m_head; }

  Ring<T> &set_overflow_allowed(bool value = true) {
    m_is_overflow_allowed = value;
    return *this;
  }

  T &at(size_t position) {
    u32 offset = m_head + position;
    return View(*this).at<T>(offset % count());
  }

  const T &at(size_t position) const {
    u32 offset = m_head + position;
    return View(*this).at<T>(offset % count());
  }

  T &back() {
    if (m_tail == m_count) {
      return View(*this).at<T>(m_head);
    }
    return View(*this).at<T>(m_tail);
  }

  const T &back() const {
    if (m_tail == m_count) {
      return View(*this).at<T>(m_head);
    }
    return View(*this).at<T>(m_tail);
  }

  T &front() {
    if (m_head) {
      return View(*this).at<T>(m_head - 1);
    }
    return View(*this).at<T>(m_count - 1);
  }

  const T &front() const {
    if (m_head) {
      return View(*this).at<T>(m_head - 1);
    }
    return View(*this).at<T>(m_count - 1);
  }

  Ring<T> &push(const T &value) {
    if (m_tail == m_count) {
      if (m_is_overflow_allowed) {
        back().~T(); // destruct item that will be lost
      } else {
        // can't overflow
        return *this;
      }
    }

    // construct a new item at head
    new ((void *)(static_cast<T *>(data()) + m_head)) T(value);

    // increment the head
    m_head++;
    if (m_head == m_count) {
      m_head = 0;
    }

    if (m_head == m_tail) {
      m_tail = m_count;
    } // ring is full
    return *this;
  }

  Ring<T> &pop() {
    if (m_head == m_tail) {
      // Ring is empty
      return *this;
    }
    back().~T();
    if (m_tail == m_count) {
      // ring is full
      m_tail = m_head;
    }
    m_tail++;
    if (m_tail == m_count) {
      m_tail = 0;
    }
    return *this;
  }

  API_NO_DISCARD Data to_linear_data() const {
    Data result(size());
    // this needs to be constructed
    for (u32 i = 0; i < count(); i++) {
      new ((void *)(View(result).to<T>() + i)) T(at(i));
    }
    return result;
  }

  Ring &operator<<(const Data &data) {
    for (u32 i = 0; i < data.size() / sizeof(T); i++) {
      push(View(data).at<T>(i));
    }
    return *this;
  }

  Ring &rotate_forward() {
    if (m_tail == m_count) {
      // buffer is full - just rewind the head the head
      if (m_head) {
        m_head--;
      } else {
        m_head = m_count - 1;
      }
    }
    return *this;
  }

  Ring &rotate_backward() {
    if (m_tail == m_count) {
      // buffer is full - just increment the head
      m_head++;
      if (m_head == m_count) {
        m_head = 0;
      }
    }
    return *this;
  }

private:
  u32 m_head;
  u32 m_tail;
  u32 m_count;
  bool m_is_overflow_allowed;

  u32 frame_size() { return sizeof(T); }
};

} /* namespace var */

#if USE_PRINTER
namespace sys {
Printer &operator<<(Printer &printer, const var::Ring<u32> &a);
Printer &operator<<(Printer &printer, const var::Ring<s32> &a);
Printer &operator<<(Printer &printer, const var::Ring<u16> &a);
Printer &operator<<(Printer &printer, const var::Ring<s16> &a);
Printer &operator<<(Printer &printer, const var::Ring<u8> &a);
Printer &operator<<(Printer &printer, const var::Ring<s8> &a);
} // namespace sys
#endif

#endif /* VAR_API_RING_HPP_ */
