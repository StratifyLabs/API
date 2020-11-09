/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.
//Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc


#include "hal/Fifo.hpp"
using namespace hal;

Fifo::Fifo(){}

int Fifo::get_info(FifoInfo & info) const {
	return ioctl(
				IoRequest(I_FIFO_GETINFO),
				IoArgument(&info.m_info)
				);
}
FifoInfo Fifo::get_info() const {
	FifoInfo a;
	set_error_number_if_error(get_info(a));
	return a;
}
int Fifo::flush() const {
	return ioctl(IoRequest(I_FIFO_FLUSH));
}
int Fifo::initialize() const { return ioctl(IoRequest(I_FIFO_INIT)); }
int Fifo::finalize() const { return ioctl(IoRequest(I_FIFO_EXIT)); }
int Fifo::set_writeblock(bool value) const {
	fifo_attr_t attr;
	attr.o_flags = flag_set_writeblock;
	if( value == false ){
		attr.o_flags |= flag_is_overflow;
	}
	return ioctl(
				IoRequest(I_FIFO_SETATTR),
				IoConstArgument(&attr)
				);
}
