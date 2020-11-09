/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.
//Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc


#include <unistd.h>
#include <fcntl.h>
#include "hal/Core.hpp"
using namespace hal;

Core::Core(port_t port) : Periph(CORE_PERIPH_CORE, port){}


int Core::set_pin_function(const core_pinfunc_t & req){
	return ioctl(
				IoRequest(I_CORE_SETPINFUNC),
				IoConstArgument(&req)
				);
}

int Core::get_mcu_board_config(mcu_board_config_t & config){
	return ioctl(
				IoRequest(I_CORE_GETMCUBOARDCONFIG),
				IoArgument(&config)
				);
}

int Core::set_clock_divide(u32 value){
	return ioctl(
				IoRequest(I_CORE_SETCLKDIVIDE),
				IoIntArgument(value)
				);
}

CoreInfo Core::get_info(){
	Core core(0);
	if( core.open() < 0 ){
		return CoreInfo();
	}
	core.set_keep_open(false);
	core_info_t info;
	if( core.ioctl(
			 IoRequest(I_CORE_GETINFO),
			 IoArgument(&info)
			 ) < 0 ){
		return CoreInfo();
	}
	return CoreInfo(info);
}


void Core::reset(){
	core_attr_t attr;
	attr.o_flags = CORE_FLAG_EXEC_RESET;
	set_attributes(attr);
}

void Core::invoke_bootloader(){
	core_attr_t attr;
	attr.o_flags = CORE_FLAG_EXEC_INVOKE_BOOTLOADER;
	set_attributes(attr);
}

