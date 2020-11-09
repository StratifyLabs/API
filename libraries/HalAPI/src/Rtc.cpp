/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.
#include "hal/Rtc.hpp"

using namespace hal;

Rtc::Rtc(port_t port) : Periph(CORE_PERIPH_RTC, port){

}


int Rtc::set_time(const rtc_time_t & time) const {
	return ioctl(
				IoRequest(I_RTC_SET),
				IoConstArgument(&time)
				);
}

int Rtc::get_time(rtc_time_t & time) const {
	return ioctl(
				IoRequest(I_RTC_GET),
				IoArgument(&time)
				);
}
