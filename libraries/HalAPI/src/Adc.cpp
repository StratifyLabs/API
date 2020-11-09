/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.
//Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "hal/Adc.hpp"

using namespace hal;

Adc::Adc(port_t port) : Periph(CORE_PERIPH_ADC, port){}

AdcInfo Adc::get_info() const {
	adc_info_t info;
	if( Periph::get_info(info) < 0 ){
		return AdcInfo();
	}
	return AdcInfo(info);
}



