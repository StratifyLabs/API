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
