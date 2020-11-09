/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.


#include "hal/Led.hpp"

namespace hal {

Led::Led(){}


int Led::enable(u32 duty_cycle, u32 period) const{
	led_attr_t attr;
	attr.o_flags = flag_enable;
	if( period ){
		attr.duty_cycle = duty_cycle;
		attr.period = period;
		attr.o_flags |= flag_is_duty_cycle;
	}
	return ioctl(
				IoRequest(I_LED_SETATTR),
				IoArgument(&attr)
				);
}

int Led::disable(bool high_impedance) const {
	led_attr_t attr;
	attr.o_flags = flag_disable;
	if( high_impedance ){
		attr.o_flags |= flag_is_high_impedance;
	}
	return ioctl(
				IoRequest(I_LED_SETATTR),
				IoArgument(&attr)
				);
}

int Led::get_info(led_info_t & info) const {
	return ioctl(
				IoRequest(I_LED_GETINFO),
				IoArgument(&info)
				);
}

} /* namespace hal */
