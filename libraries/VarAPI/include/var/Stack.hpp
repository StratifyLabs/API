/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
#ifndef VAR_API_STACK_HPP_
#define VAR_API_STACK_HPP_

#include <cstdio>
#include <deque>
#include <new>

#include "api/api.hpp"

namespace var {

/*! \brief Queue Class
 * \details The Queue class is a FIFO data structure
 * that allows data to be pushed on the back
 * and popped from the front. It is similar to the
 * std::queue container class.
 *
 */
template <typename T> class Stack : public api::ExecutionContext {
public:
  /*! \details Returns a reference to the back item.
   *
   * The back item is the one that has most recently
   * been pushed using push().
   *
   */
  T &top() { return m_deque.back(); }

  /*! \details Returns a read-only reference to the back item.
   *
   * The back item is the one that has most recently
   * been pushed using push().
   *
   */
  const T &top() const { return m_deque.back(); }

  /*! \details Pushes an item on the queue.
   *
   * @param value The item to push
   *
   */
  Stack &push(const T &value) {
    m_deque.push_back(value);
    return *this;
  }

  /*! \details Pops an item from the front of the queue. */
  Stack &pop() {
    m_deque.pop_back();
    return *this;
  }

  /*! \details Returns true if the queue is empty. */
  bool is_empty() const { return m_deque.empty(); }

  /*! \details Returns the number of items in the queue. */
  u32 count() const { return m_deque.size(); }

  /*! \details Clears the contents of the queue.
   *
   * This will empty the queue and free all the
   * resources associated with it.
   *
   */
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
