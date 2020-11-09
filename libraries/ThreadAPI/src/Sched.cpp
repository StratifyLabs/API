/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.

#include <cstring>
#include <sched.h>
#include <unistd.h>

#include "thread/Sched.hpp"

namespace thread {

int Sched::get_priority_max(Policy value) {
  API_RETURN_VALUE_IF_ERROR(-1);
  return API_SYSTEM_CALL("", sched_get_priority_max(static_cast<int>(value)));
}

int Sched::get_priority_min(Policy value) {
  API_RETURN_VALUE_IF_ERROR(-1);
  return API_SYSTEM_CALL("", sched_get_priority_min(static_cast<int>(value)));
}

#if !defined __link
int Sched::get_priority(pid_t pid) {
  API_RETURN_VALUE_IF_ERROR(-1);
  struct sched_param param;
  API_SYSTEM_CALL("", sched_getparam(pid, &param));
  return param.sched_priority;
}

int Sched::get_rr_interval(pid_t pid) {
  API_RETURN_VALUE_IF_ERROR(-1);
  struct timespec t;
  memset(&t, 0, sizeof(t));
  sched_rr_get_interval(pid, &t);
  return t.tv_nsec / 1000;
}

const Sched &Sched::set_scheduler(const SetScheduler &options) const {
  API_RETURN_VALUE_IF_ERROR(*this);
  struct sched_param param;
  param.sched_priority = options.priority();
  API_SYSTEM_CALL(
    "",
    sched_setscheduler(
      options.pid(),
      static_cast<int>(options.policy()),
      &param));
  return *this;
}
#endif

} // namespace thread
