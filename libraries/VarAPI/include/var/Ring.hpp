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

#include "Data.hpp"
#include <new>
#include <sos/dev/fifo.h>
#include <sys/types.h>

namespace var {

/*! \brief Ring Buffer
 * \details Ring is a ring buffer (or circular buffer)
 * that uses a local memory buffer for the data. It is
 * a first in/first out style buffer. Where push() adds
 * data to the front() and pop() removes data from the back().
 *
 * The push() method can will pop() a value if the buffer is full
 * and overflow is allowed.
 *
 * The Ring can handle items of any type.
 *
 * \code
 *
 * Ring<u32> ring(32); //32 32-bit word ring buffer
 * u32 next = 20;
 * ring.write(&next, 1);
 * ring.read(&next, 1); //read into next variable
 *
 * \endcode
 *
 *
 *
 */
template <typename T> class Ring : public Data {
public:
  /*! \details Constructs a new ring buffer.
   *
   * @param size The number of bytes to allocate for the new buffer.
   *
   */
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

  /*! \details Returns the number of items in the Ring
   * that are ready to be popped.
   *
   * If this value is zero, then front() and back()
   * have undefined results.  Also at() should
   * not be passed parameters that are greater
   * than or equaly to count_ready().
   *
   */
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

  /*! \details Sets a flag to allow overflow.
   *
   * @param value true to allow overflow
   *
   * If overflow is allowed, writes will keep the newest
   * data and drop the oldest data.
   *
   * If overflow is disallowed, writes will only work
   * until the buffer is full and will then return an error.
   *
   */
  Ring<T> &set_overflow_allowed(bool value = true) {
    m_is_overflow_allowed = value;
    return *this;
  }

  /*! \details Returns true if overflow is allowed. */
  bool is_overflow_allowed() const { return m_is_overflow_allowed; }

  /*! \details Accesses the item at the specified position.
   *
   * @param pos The position in the ring with 0 being the oldest valid data.
   * @return A reference to the item at *pos*.
   *
   */
  T &at(size_t position) {
    u32 offset = m_head + position;
    return View(*this).at<T>(offset % count());
    // return View(*this).at<T>(offset % count());
  }

  /*! \details Accesses a read-only copy of the item at the specified position.
   *
   * @param pos The position in the ring with 0 being the oldest valid data.
   * @return A read-only reference to the item at *pos*.
   *
   */
  const T &at(size_t position) const {
    u32 offset = m_head + position;
    return View(*this).at<T>(offset % count());
  }

  /*! \details Access the item at the back of the ring (the oldest valid data).
   */
  T &back() {
    if (m_tail == m_count) {
      return View(*this).at<T>(m_head);
    }
    return View(*this).at<T>(m_tail);
  }

  /*! \details Access the item (read-only) at the back of the ring (the oldest
   * valid data). */
  const T &back() const {
    if (m_tail == m_count) {
      return View(*this).at<T>(m_head);
    }
    return View(*this).at<T>(m_tail);
  }

  /*! \details Access the item at the back of the ring (the newest valid data).
   */
  T &front() {
    if (m_head) {
      return View(*this).at<T>(m_head - 1);
    }
    return View(*this).at<T>(m_count - 1);
  }

  /*! \details Access the item (read-only) at the back of the ring (the newest
   * valid data). */
  const T &front() const {
    if (m_head) {
      return View(*this).at<T>(m_head - 1);
    }
    return View(*this).at<T>(m_count - 1);
  }

  /*! \details Pushes a value on the front of the buffer.
   *
   * The ring buffer is a first-in first-out buffer. So
   * The first object pushed is the first one popped.
   *
   */
  int push(const T &value) {
    if (m_tail == m_count) {
      if (m_is_overflow_allowed) {
        back().~T(); // destruct item that will be lost
      } else {
        // can't overflow
        return -1;
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
    return 0;
  }

  /*! \details Pops a value from the back of the buffer.
   *
   * \sa push()
   *
   */
  void pop() {
    if (m_head == m_tail) {
      // Ring is empty
      return;
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
  }

  /*! \details Puts the data in the Ring buffer in a
   * linear data object.
   *
   */
  Data to_linear_data() const {
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

  /*!
   * \details Rotates all the values in the buffer from front to
   * back.
   *
   * @return Zero if the ring is full and the rotate is completed, -1 if the
   * ring is not full (no action taken)
   *
   * All items will be shifted toward the front. The front
   * item will be carried to the back.
   *
   * This method requires the buffer to be full (is_full() == true) or
   * no action is taken.
   *
   * The operation is completed by adjusting the head and the tail
   * of the ring. Data does not move location in memory.
   *
   */
  int rotate_forward() {
    if (m_tail == m_count) {
      // buffer is full - just rewind the head the head
      if (m_head) {
        m_head--;
      } else {
        m_head = m_count - 1;
      }
      return 0;
    }
    return -1;
  }

  /*!
   * \details Rotates all the values in the buffer from front to
   * back.
   *
   * @return Zero if the ring is full and the rotate is completed, -1 if the
   * ring is not full (no action taken)
   *
   * All items will be shifed toward the back. The back item
   * will be carried to the front.
   *
   * This method requires the buffer to be full (is_full() == true) or
   * no action is taken.
   *
   * The operation is completed by adjusting the head and the tail
   * of the ring. Data does not move location in memory.
   *
   */
  int rotate_backward() {
    if (m_tail == m_count) {
      // buffer is full - just increment the head
      m_head++;
      if (m_head == m_count) {
        m_head = 0;
      }
      return 0;
    }
    return -1;
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
