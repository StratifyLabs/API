/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.

#ifndef SAPI_HAL_EINT_HPP_
#define SAPI_HAL_EINT_HPP_


#include <sos/dev/eint.h>
#include "PinAssignment.hpp"
#include "Periph.hpp"
#include "Pin.hpp"


namespace hal {

/*! \brief EINT Pin Assignment
 * \details This class allows simple manipulation of the eint_pin_assignment_t.
 */
class EintPinAssignment : public PinAssignment<eint_pin_assignment_t>{};

class EintAttributes : public PinAssignmentPeriphAttributes<eint_attr_t, eint_pin_assignment_t>{
public:
	//construct with default values


};

/*! \brief External Interrupt Class
 * \details This class gives access to external interrupt circuitry.  You can use this class
 * to have the interrupt trigger a function or block a thread until the interrupt arrives.
 *
 * Here is an example:
 *
 * \code
 *
 * #include <sapi/hal.hpp>
 * #include <sapi/sys.hpp>
 *
 *  //This will be executed when the event is triggered
 * int event_callback(void * args, const void * data){
 * 	volatile int * done = (int*)args;
 * 	*done = 1;
 * 	return 0; //return 0 to clear the callback and 1 to keep it
 * }
 *
 * void eint_example(){
 * 	volatile int done;
 * 	Eint eint(0); //use eint port 0 (pin 2.10 on lpc17xx devices)
 *
 * 	eint.init(); //open and set attributes
 *
 * 	eint.set_action(0, //use channel 0
 * 		EINT_ACTION_EVENT_FALLING, //trigger on a falling edge
 * 		event_callback, //execute this function (in privileged mode when complete)
 * 		&done //pass this to event_callback as the first argumen
 * 		);
 *
 * 	while( done == 0 ){
 * 		Timer::wait_milliseconds(1); //wait for the signal to arrive
 * 	}
 *
 * }
 *
 *  //alternatively you can configure (set_action() and block by writing hwpl_action_t to the device)
 *
 *  mcu_action_t action;
 *  action.channel = 0;
 *  action.event = EINT_ACTION_EVENT_FALLING;
 *  action.callback = 0; //this is ignored and doesn't need to be set
 *  action.context = 0; //this is ignored and doesn't need to be set
 *  eint.write(&action, sizeof(action)); //this will block until a falling edge arrives
 *
 * \endcode
 *
 */
class Eint : public Periph<eint_info_t, eint_attr_t, EintAttributes, 'e'> {
public:
	Eint(port_t port);

	/*! \details Reads the value of the pin */
	bool get_value(){
		eint_info_t a;
		get_info(a);
		return a.value != 0;
	}



private:

};

}

#endif /* SAPI_HAL_EINT_HPP_ */
