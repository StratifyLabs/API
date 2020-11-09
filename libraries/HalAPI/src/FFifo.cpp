/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.
#include "hal/FFifo.hpp"

using namespace hal;

FFifo::FFifo(){}

int FFifo::initialize(
		const var::String & path,
		const FFifoAttributes & attributes,
		const fs::OpenFlags & flags
		){
	int ret;
	ret = open(
				path,
				fs::OpenFlags(flags).set_read_write()
				);
	if( ret < 0 ){
		return ret;
	}

	ret = set_attributes(attributes);
	if( ret < 0 ){
		return ret;
	}

	return set_error_number_if_error(
				ioctl(IoRequest(I_FFIFO_INIT))
				);
}

int FFifo::flush() const {
	return set_error_number_if_error(
				ioctl(IoRequest(I_FFIFO_FLUSH))
				);
}

int FFifo::set_attributes(const FFifoAttributes & attr) const {
	return set_error_number_if_error(
				ioctl(
					IoRequest(I_FFIFO_SETATTR),
					IoConstArgument(&attr.m_ffifo_attr)
					)
				);
}

FFifoInfo FFifo::get_info() const {
	FFifoInfo info;
	set_error_number_if_error(
				ioctl(
					IoRequest(I_FFIFO_GETINFO),
					IoArgument(&info.m_ffifo_info)
					)
				);
	return info;
}

int FFifo::get_info(FFifoInfo & info) const {
	return set_error_number_if_error(
				ioctl(
					IoRequest(I_FFIFO_GETINFO),
					IoArgument(&info.m_ffifo_info)
					)
				);
}
