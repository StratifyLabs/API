/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.
//Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc


#include "hal/Tmr.hpp"

using namespace hal;


Tmr::Tmr(port_t port) : Periph(CORE_PERIPH_TMR, port) {}


int Tmr::enable() const {
	return ioctl(IoRequest(I_TMR_ENABLE));
}

int Tmr::disable() const {
	return ioctl(IoRequest(I_TMR_DISABLE));
}

u32 Tmr::get_value() const {
	u32 value = 0;
	ioctl(IoRequest(I_TMR_GET), IoArgument(&value));
	return value;
}

int Tmr::set_value(u32 value) const {
	return ioctl(IoRequest(I_TMR_SET), IoIntArgument(value));
}


