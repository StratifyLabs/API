/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.


#ifndef SAPI_HAL_LED_HPP_
#define SAPI_HAL_LED_HPP_

#include <sos/dev/led.h>
#include "Periph.hpp"

namespace hal {

/*! \brief LED Class
 * \details The LED Class is used to control LEDs based on
 * the standard LED driver.
 */
class Led : public Device {
public:
	Led();

	enum led_flags {
		flag_is_high_impedance /*! See \ref LED_FLAG_IS_HIGH_IMPEDANCE */  = LED_FLAG_IS_HIGH_IMPEDANCE,
		flag_is_duty_cycle /*! See \ref LED_FLAG_IS_DUTY_CYCLE */ = LED_FLAG_IS_DUTY_CYCLE,
		flag_enable /*! See \ref LED_FLAG_ENABLE */ = LED_FLAG_ENABLE,
		flag_disable /*! See \ref LED_FLAG_DISABLE */ = LED_FLAG_DISABLE
	};

	/*! \details Gets the info for the LED.
	 *
	 * @param info A reference to the destination information
	 * @return Zero on success
	 *
	 * After this method is called, the info.o_flags value will indicate
	 * what flags are supported by the driver. If FLAG_IS_DUTY_CYCLE is
	 * set, then the driver supports brightness control and flashing.
	 * Otherwise, the driver can simple enable and disable the LED.
	 *
	 */
	int get_info(led_info_t & info) const;


	/*! \details Enables the LED with the specified duty cycle and period.
	 *
	 * @param duty The duty cycle (in microseconds) to be on
	 * @param period The period in microseconds
	 *
	 * This method can be used to both set the brightness and flash the LED.
	 * To use as brightness control, set the period to a small value.
	 *
	 * @return Zero on success
	 */
	int enable(u32 duty, u32 period) const;

	/*! \details Turns the LED on.
	 *
	 * @return Zero on success
	 */
	int enable() const { return enable(0,0); }

	/*! \details Flashes the LED.
	 *
	 * @param duty_cycle The duty cycle in seconds
	 * @param period The period in seconds
	 * @return Zero on success
	 */
	int flash(float duty_cycle, float period){
		u32 d = duty_cycle*1000000;
		u32 p = period*1000000;
		return enable(d, p);
	}

	/*! \details Enables the LED with the specified brightness.
	 *
	 * @param brightness Brightness from 0.0 to 1.0
	 * @return Zero on success
	 */
	int enable(float brightness) const {
		return enable((u32)(brightness*10000), 10000);
	}

	/*! \details Disables the LED.
	 *
	 * @param high_impedance True to set the off state to float
	 * @return Zero on success
	 *
	 * For the pin to be set to float, the driver must support the FLAG_IS_HIGH_IMPEDANCE flag.
	 *
	 */
	int disable(bool high_impedance = false) const;



};

} /* namespace hal */

#endif /* SAPI_HAL_LED_HPP_ */
