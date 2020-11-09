/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
#ifndef CHRONO_API_CHRONO_TIMER_HPP_
#define CHRONO_API_CHRONO_TIMER_HPP_

#include "ClockTime.hpp"
#include "MicroTime.hpp"

namespace chrono {

/*! \brief ClockTimer Class
 * \details This class implements a logical timer based on the Stratify OS
 * system timer.
 *
 * Physical timers are controlled using the hal::Tmr class.
 *
 * The Timer has the following states:
 *
 * - Reset: not started, not running. stopped
 * - Running: started, running, not stopped
 * - Stopped: started, not running, stopped
 *
 * These methods are used to jump between states:
 *
 * - start(): start running if not already running
 * - restart(): restart running from zero even if already running
 * - stop(): stop running (if running)
 * - resume(): resume counting after a stop
 * - reset(): set to not running, not stopped, zero value
 *
 * These methods can check the state:
 *
 * - is_reset(): Is in reset state
 * - is_started(): has been started (not in reset state) possibly stopped
 * - is_running(): started and not stopped
 * - is_stopped(): started and stopped
 *
 * ```
 * //md2code:include
 * #include <sapi/chrono.hpp>
 * ```
 *
 * ```
 * //md2code:main
 *	Timer t;
 *	t.start(); //start
 *	wait(Microseconds(500));
 *	t.stop();
 *	printf("value after 500usec is %ld\n", t.microseconds());
 *
 * t.resume();
 * wait(Microseconds(500));
 * t.stop();
 *	printf("value after another 500usec is %ld\n", t.microseconds());
 *
 * if( t.is_started() ){
 *   printf("t has been started (not in reset state)\n");
 * }
 *
 * //comparing to time values
 * if( t > Seconds(1) ){
 *   printf("Greater than a second\n");
 * }
 *
 * if( t > Milliseconds(1) ){
 *   printf("Greater than a millisecond\n");
 * }
 *
 * if( t < Microseconds(500) ){
 *   printf("Greater than a microsecond\n");
 * }
 *
 * t.start(); //this will start from zero again
 * t.start(); //calling start again has no effect
 * if( t.is_running() ){
 *   printf("t is running\n");
 * }
 * if( t.is_stopped() ){
 *   printf("t is not stopped\n");
 *	}
 * t.restart(); //start from zero even if timer is running
 * t.reset(); //reset to initial state: not running, stopped and reset
 * if( t.is_reset() && t.is_stopped() ){
 *   printf("t is reset\n");
 * }
 * if( t.is_started() ){
 *   printf("this won't print in reset state\n");
 * }
 * ```
 *
 * The output of the above code varies depending on the MCU clock cycles and the
 * scheduler.  The following is a sample output.
 *
 * <pre>
 *	value after 500usec is 502
 *	value after another 500usec is 1005
 * t has been started (not in reset state)
 * Greater than a millisecond
 * t is running
 * t is reset
 * </pre>
 *
 *
 */
class ClockTimer : public api::ExecutionContext {
public:
  /*! \details Constructs an empty Timer. */
  ClockTimer();

  /*! \details Starts the timer.
   *
   * If the timer is currently running, this method has no effect.  If the timer
   * has been stopped, it will restart.  Use resume() to resume running a
   * stopped timer.
   *
   */
  ClockTimer &start(); // start counting

  /*! \details Restarts the timer.
   *
   * If the timer is currently running,
   * it starts over.  If it is not running, it is started.
   *
   */
  ClockTimer &restart();

  /*! \details Resumes counting after a stop().
   *
   * If the timer is currently running
   * this method has no effect.  If the timer has not been started, this method
   * will start the timer.
   */
  ClockTimer &resume();

  /*! \details Stops the timer from counting.
   *
   * Subsequent calls to value() will return the same number.  Once the timer
   * has been stopped(), a call to resume() will resume counting and a call to
   * start() or restart() will restart counting from zero.
   */
  ClockTimer &stop();

  /*! \details Resets the value of the timer.
   *
   *  After calling this method, is_running(), and is_started() will both
   *  all return false;
   *
   */
  ClockTimer &reset();

  /*! \details Returns true if the timer is currently counting meaning
   * it has been started but has not been stopped.
   *
   * If the timer has been stopped and resumed, this method will return true;
   *
   */
  bool is_running() const { return !is_stopped(); }

  /*! \details Returns true if the timer has been started.
   *
   * It the timer has been started and stopped, this method will return true.
   * If the timer has been reset() or never started, this method will return
   * false.
   *
   */
  bool is_started() const {
    return (m_start.nanoseconds() + m_start.seconds()) != 0;
  }

  /*! \details Returns true if the timer is stopped.
   *
   * If the timer has not yet been started or has been reset(), this method will
   * return true. If the timer is currently running, this method will return
   * false.
   *
   *
   */
  bool is_stopped() const {
    return (m_stop.seconds() != -1) || (m_stop.seconds() == 0);
  }

  /*! \details Returns true if the timer is in a reset state.
   *
   */
  bool is_reset() const { return m_stop.seconds() == 0; }

  /*! \details Calculates the timer value in milliseconds.
   *
   * @return The number of milliseconds that have elapsed since start.  This
   * value can be read when the timer is running to get a live value or after it
   * has been stopped to get the time elapsed between start() and stop()
   */
  u32 milliseconds() const { return calc_value().milliseconds(); }

  /*! \details Calculates the timer value in microseconds.
   *
   * This is similar to calc_msec() but returns
   * the value in microseconds rather than milliseconds.
   *
   * @return The number of microseconds that have elapsed since start.
   */
  u32 microseconds() const { return calc_value().microseconds(); }

  /*! \details Calculates the timer value in seconds.
   *
   * This is similar to calc_msec() but returns
   * the value in seconds rather than milliseconds.
   *
   * @return The number of seconds that have elapsed since start.
   */
  u32 seconds() const { return calc_value().seconds(); }

  /*! \details Returns the value of the timer as a ClockTime object. */
  ClockTime clock_time() const;

  MicroTime micro_time() const { return calc_value(); }

private:
  ClockTime m_start;
  ClockTime m_stop;

  MicroTime calc_value() const;
};

inline bool operator==(const ClockTimer &lhs, const MicroTime &rhs) {
  return lhs.micro_time() == rhs;
}

inline bool operator!=(const ClockTimer &lhs, const MicroTime &rhs) {
  return lhs.micro_time() != rhs;
}

inline bool operator>(const ClockTimer &lhs, const MicroTime &rhs) {
  return lhs.micro_time() > rhs;
}

inline bool operator<(const ClockTimer &lhs, const MicroTime &rhs) {
  return lhs.micro_time() < rhs;
}

inline bool operator<=(const ClockTimer &lhs, const MicroTime &rhs) {
  return lhs.micro_time() <= rhs;
}

inline bool operator>=(const ClockTimer &lhs, const MicroTime &rhs) {
  return lhs.micro_time() >= rhs;
}

inline bool operator==(const MicroTime &lhs, const ClockTimer &rhs) {
  return lhs == rhs.micro_time();
}

inline bool operator!=(const MicroTime &lhs, const ClockTimer &rhs) {
  return lhs != rhs.micro_time();
}

inline bool operator>(const MicroTime &lhs, const ClockTimer &rhs) {
  return lhs > rhs.micro_time();
}

inline bool operator<(const MicroTime &lhs, const ClockTimer &rhs) {
  return lhs < rhs.micro_time();
}

inline bool operator<=(const MicroTime &lhs, const ClockTimer &rhs) {
  return lhs <= rhs.micro_time();
}

inline bool operator>=(const MicroTime &lhs, const ClockTimer &rhs) {
  return lhs >= rhs.micro_time();
}

} // namespace chrono

#endif // CHRONO_API_CHRONO_TIMER_HPP_
