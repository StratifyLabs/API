// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef THREADAPI_THREAD_SCHED_HPP_
#define THREADAPI_THREAD_SCHED_HPP_

#include <pthread.h>
#include <sched.h>
#include <unistd.h>

#if defined __win32
// typedef int pid_t;
#else
#include <sys/types.h>
#endif

#include "api/api.hpp"

namespace thread {

/*! \brief Sched Class
 * \details The Sched class is used
 * to change the scheduing policy of the current
 * thread or process.
 *
 * Stratify OS has three scheduling policies:
 *
 * - Other
 * - Round Robin
 * - FIFO
 *
 * Other (Sched::OTHER) is the default. It is a round robin scheduler with a
 * single priority (lowest priority). When a thread or process is using
 * Sched::OTHER, it will yield the CPU in the following cases:
 *
 * - It's round robin time is expired and it will be pre-empted
 * - It makes a call to a blocking function:
 *   - usleep() (chrono::Timer::wait_microseconds())
 *   - sleep() (chrono::Timer::wait_seconds())
 *   - read() or write() (not all read or writes will yield the CPU, only those
 * that can be accomplished in the background)
 *   - sched_yield() (Sched::yield())
 *   - mutexes (Sys::Mutex), semaphores (Sys::Sem), message queues (Sys::Mq),
 * and other system sync mechanisms can also cause the thread to block and yield
 * the processor
 * - It receives a signal that pauses the process (SIGSTOP for example)
 *
 * Round Robin (Sched::RR) scheduling behaves the same as Sched::OTHER but
 * allows different priorities to be set. Lower priority threads will ONLY get
 * CPU time if higher priority threads are blocked. The thread will block in the
 * same cases as Sched::OTHER.
 *
 * FIFO (Sched::FIFO) scheduling will not be pre-empted by the round robin
 * timer. It will keep control of the CPU until it calls a function had yields
 * (same as the functions for Sched::OTHER). FIFO scheduling is good for high
 * priority data processing (such as handling a packet arriving from the
 * network).
 *
 * None of the scheduling modes will meet hard real-time constraints. In those
 * cases, it is nessary to write a kernel driver or request (Sys::request())
 * (integrated with the Board support package) that can handle real-time
 * constraints in interrupt services routines with very low latency.
 *
 *
 *
 */
class Sched : public api::ExecutionContext {
public:
  enum class Policy {
#if defined __win32
    round_robin,
    fifo,
    other
#else
    round_robin = SCHED_RR,
    fifo = SCHED_FIFO,
    other = SCHED_OTHER
#endif
  };

  const Sched &yield() const {
    sched_yield();
    return *this;
  }

  API_NO_DISCARD static pid_t get_pid() { return getpid(); }

  API_NO_DISCARD static int get_priority_max(Policy value);
  API_NO_DISCARD static int get_priority_min(Policy value);

#if !defined __link
  API_NO_DISCARD static int get_priority(pid_t pid);
  API_NO_DISCARD static int get_rr_interval(pid_t pid);

  class SetScheduler {
    API_AF(SetScheduler, Policy, policy, Policy::round_robin);
    API_AF(SetScheduler, u8, priority, 0);
    API_AF(SetScheduler, int, pid, 0);
  };

  const Sched &set_scheduler(const SetScheduler &options) const;
#endif
};

} // namespace thread

#endif /* THREADAPI_THREAD_SCHED_HPP_ */
