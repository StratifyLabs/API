/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.

#ifndef VAR_API_VAR_RING_HPP_
#define VAR_API_VAR_RING_HPP_

#include "Array.hpp"

namespace var {

template <typename T, size_t ItemCount> class Ring {
public:
  using Buffer = Array<T, ItemCount>;
  API_NO_DISCARD u32 count_ready() const {
    // how many item are available
    if (m_tail == ItemCount) {
      return ItemCount; // ring is full
    }

    if (m_head > m_tail) {
      return m_head - m_tail;
    }

    return ItemCount - (m_tail - m_head);
  }
  API_NO_DISCARD bool is_full() const { return m_tail == ItemCount; }
  API_NO_DISCARD bool is_empty() const {
    return m_tail == m_head; }

  Ring &set_overflow_allowed(bool value = true) & {
    m_is_overflow_allowed = value;
    return *this;
  }
  Ring &&set_overflow_allowed(bool value = true) && {
    return std::move(set_overflow_allowed(value));
  }

  T &at(size_t position) {
    u32 offset = m_head + position;
    return m_buffer.at(offset % ItemCount);
  }

  const T &at(size_t position) const {
    u32 offset = m_head + position;
    return m_buffer.at(offset % ItemCount);
  }

  T &back() {
    if (m_tail == ItemCount) {
      return m_buffer.at(m_head);
    }
    return m_buffer.at(m_tail);
  }

  const T &back() const {
    if (m_tail == ItemCount) {
      return m_buffer.at(m_head);
    }
    return m_buffer.at(m_tail);
  }

  T &front() {
    if (m_head) {
      return m_buffer.at(m_head - 1);
    }
    return m_buffer.at(ItemCount - 1);
  }

  const T &front() const {
    if (m_head) {
      return m_buffer.at(m_head - 1);
    }
    return m_buffer.at(ItemCount - 1);
  }

  Ring &push(const T &value) & {
    if (m_tail == ItemCount) {
      if (m_is_overflow_allowed) {
        back().~T(); // destruct item that will be lost
      } else {
        // can't overflow
        return *this;
      }
    }

    // construct a new item at head
    m_buffer.at(m_head) = value;

    // increment the head
    if (++m_head == ItemCount) {
      m_head = 0;
    }

    if (m_head == m_tail) {
      m_tail = ItemCount;
    } // ring is full
    return *this;
  }
  Ring &&push(const T &value) && { return std::move(push(value)); }

  Ring &pop() & {
    if (m_head == m_tail) {
      // Ring is empty
      return *this;
    }
    back().~T();
    if (m_tail == ItemCount) {
      // ring is full
      m_tail = m_head;
    }
    if (++m_tail == ItemCount) {
      m_tail = 0;
    }
    return *this;
  }
  Ring &&pop() && { return std::move(pop()); }

  API_NO_DISCARD Array<T, ItemCount> to_linear_data() const {
    Array<T, ItemCount> result;
    // this needs to be constructed
    for (size_t i = 0; i < ItemCount; i++) {
      result.at(i) = at(i);
    }
    return result;
  }

  Ring &rotate_forward() & {
    if (m_tail == ItemCount) {
      // buffer is full - just rewind the head the head
      if (m_head) {
        --m_head;
      } else {
        m_head = ItemCount - 1;
      }
    }
    return *this;
  }
  Ring &&rotate_forward() && { return std::move(rotate_forward()); }

  Ring &rotate_backward() & {
    if (m_tail == ItemCount) {
      // buffer is full - just increment the head
      if (++m_head == ItemCount) {
        m_head = 0;
      }
    }
    return *this;
  }
  Ring &&rotate_backward() && { return std::move(rotate_backward()); }

private:
  size_t m_head{};
  size_t m_tail{};
  bool m_is_overflow_allowed = true;
  Buffer m_buffer;
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

#endif /* VAR_API_VAR_RING_HPP_ */
