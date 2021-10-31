#if !defined __link

#include <unistd.h>

#include "thread/Timer.hpp"

extern "C" useconds_t ualarm(useconds_t useconds, useconds_t interval);

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

  API_SYSTEM_CALL(
      "", timer_settime(m_timer, int(options.flags()), &value, nullptr));
  return *this;
}

Timer::Info Timer::get_info() const {
  API_RETURN_VALUE_IF_ERROR(Info());

  Info result;
  struct itimerspec value{};
  API_SYSTEM_CALL("", timer_gettime(m_timer, &value));
  result.m_interval = chrono::ClockTime(value.it_interval);
  result.m_value = chrono::ClockTime(value.it_value);
  return result;
}

chrono::ClockTime Timer::alarm(const Alarm &options) {
  API_RETURN_VALUE_IF_ERROR(chrono::ClockTime());
  if (options.type() == Alarm::Type::seconds) {
    API_SYSTEM_CALL("", ::alarm(options.value().seconds()));
    return chrono::ClockTime(return_value() * 1_seconds);
  }

  API_SYSTEM_CALL("", ::ualarm(options.value().nanoseconds() / 1000UL,
                               options.interval().nanoseconds() / 1000UL));
  return chrono::ClockTime(return_value() * 1_microseconds);
}

#endif
