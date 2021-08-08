#include "thread/Timer.hpp"

using namespace thread;

Timer::Timer(Signal::Event &signal_event, ClockId clock_id) {
  API_RETURN_IF_ERROR();
  API_SYSTEM_CALL(
      "", timer_create(clockid_t(clock_id), &signal_event.m_event, &m_timer));
}

Timer::~Timer() {
  if (is_valid()) {
    timer_delete(m_timer);
  }
}

Timer &Timer::set_time(const SetTime &options) {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_ASSERT(is_valid());

  struct itimerspec value = {.it_interval = *options.interval().timespec(),
                             .it_value = *options.value().timespec()};

  API_SYSTEM_CALL("", timer_settime(m_timer, int(options.flags()), &value, nullptr));
  return *this;
}


Timer::Info Timer::get_info() const {
  API_RETURN_VALUE_IF_ERROR(Info());

  Info result;
  struct itimerspec value;
  API_SYSTEM_CALL("", timer_gettime(m_timer, &value));
  result.m_interval = value.it_interval;
  result.m_value = value.it_value;
  return result;
}

