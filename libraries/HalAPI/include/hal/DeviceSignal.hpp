/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.

#ifndef SAPI_HAL_DEVICESIGNAL_HPP_
#define SAPI_HAL_DEVICESIGNAL_HPP_

#if !defined __link

#include <sos/fs/devfs.h>

#include "Device.hpp"
#include "thread/Signal.hpp"
#include "thread/Thread.hpp"

namespace hal {

/*! \brief Class for bridging device events with Signal events */
/*! \details This class allows you to configure physical events
 * to trigger signals.  For example, a rising edge on a pin
 * can cause the system to send a signal to a thread.  Here is an example:
 * \code
 *
 * #include <sapi/sys.hpp>
 * #include <sapi/hal.hpp>
 *
 * volatile bool my_var;
 * void my_handler(int a){
 * 	//this executes on the rising edge of EINT0
 * 	my_var = true;
 * 	//you shouldn't use any non re-entrant functions here (such as printf()
 * and malloc())
 *
 * }
 *
 * int main(int argc, char * argv[]){
 * 	Eint eint(0);
 *
 * 	DeviceSignal dev_signal(true, Signal::USR1);  //send SIGUSR1 to this
 * thread on every rising edge SignalHandler handler(my_handler);
 *
 * 	eint.init(0);
 * 	event.set_handler(handler);
 *
 * 	//this configures the hardware to send the signal to this thread
 * (my_handler() will execute)
 * 	//dev_signal MUST exist as long as this action is set
 * 	eint.set_action( dev_signal.create_action(EINT_ACTION_EVENT_RISING) );
 *
 * 	while(my_var == false){
 * 		Timer::wait_sec(1);
 * 	}
 *
 * 	return 0;
 * }
 *
 *
 * \endcode
 */
class DeviceSignal : public thread::Signal {
public:
  enum class IsPersistent { no, yes };

  /*! \details Constructs a signal event based on a hardware device action.
   *
   * @param persistent If false, the signal will be sent only on the first
   * hardware event
   * @param signo The signal number
   * @param sigcode The signal code
   * @param sigvalue The signal value
   */
  DeviceSignal(
    IsPersistent persistent,
    thread::Signal::Number signo,
    int sigvalue = 0)
    : thread::Signal(signo, sigvalue) {
    m_context.tid = thread::Thread::self();
    m_context.si_signo = static_cast<int>(signo);
    m_context.si_sigcode = LINK_SI_USER;
    m_context.sig_value = sigvalue;
    m_context.keep = persistent == IsPersistent::yes;
  }

  /*! \details Constructs a signal event based on a hardware device action.
   *
   * @param persistent If false, the signal will be sent only on the first
   * hardware event
   * @param signo The signal number
   * @param sigcode The signal code
   * @param sigptr The signal value as a pointer
   */
  DeviceSignal(
    IsPersistent persistent,
    thread::Signal::Number signo,
    void *sigvalue = nullptr)
    : thread::Signal(signo, sigvalue) {
    m_context.tid = pthread_self();
    m_context.si_signo = static_cast<int>(signo);
    m_context.si_sigcode = LINK_SI_USER;
    m_context.sig_ptr = sigvalue;
    m_context.keep = persistent == IsPersistent::yes;
  }

  /*! \details Constructs a signal event based on a hardware device action using
   * a signal_callback_t data structure.
   *
   * @param context A copy of the signal_callback_t data to use to handle the
   * event.
   */
  explicit DeviceSignal(const devfs_signal_callback_t &context)
    : thread::Signal(
      static_cast<thread::Signal::Number>(context.si_signo),
      context.sig_value) {
    this->m_context = context;
  }

  class CreateAction {
    API_AF(CreateAction, u32, o_events, 0);
    API_AF(CreateAction, u8, channel, 0);
    API_AF(CreateAction, u32, priority, 0);
  };

  /*! \details This returns a mcu_action_t data structure that can
   * be used to set the action associated with a hardware event.
   *
   * @param event The hardware event
   * @param channel The hardware channel
   * @return a copy of a mcu_action_t data structure
   *
   */
  mcu_action_t create_action(const CreateAction &options) const {
    mcu_action_t a;
    a.handler.callback = devfs_signal_callback;
    a.handler.context = (void *)&m_context;
    a.channel = options.channel();
    a.o_events = options.o_events();
    a.prio = options.priority();
    return a;
  }

private:
  devfs_signal_callback_t m_context;
};

} /* namespace hal */

#endif

#endif /* SAPI_HAL_DEVICESIGNAL_HPP_ */
