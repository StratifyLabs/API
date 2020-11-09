/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.


#include "hal/CFifo.hpp"
#include "hal/Fifo.hpp"

namespace hal {

int CFifo::get_count() const {
	cfifo_info_t info;
	if( get_info(info) < 0 ){ return -1; }
	return info.count;
}

int CFifo::get_info(cfifo_info_t & info) const {
	return ioctl(
				IoRequest(I_CFIFO_GETINFO),
				IoArgument(&info)
				);
}

int CFifo::get_owner(int channel, int & owner) const {
	mcu_channel_t c;
	int ret;
	c.loc = channel;
	c.value = static_cast<u32>(-1);
	ret = ioctl(
				IoRequest(I_CFIFO_GETOWNER),
				IoArgument(&c)
				);
	if( ret >= 0 ){
		owner = c.value;
	}
	return ret;
}

int CFifo::set_owner(int channel, int owner) const {
	mcu_channel_t c;
	c.loc = channel;
	c.value = owner;
	return ioctl(
				IoRequest(I_CFIFO_SETOWNER),
				IoArgument(&c)
				);
}

int CFifo::get_info(int channel, fifo_info_t & info) const {
	cfifo_fifoinfo_t fifo_info;
	fifo_info.channel = channel;
	if( ioctl(
			 IoRequest(I_CFIFO_FIFOGETINFO),
			 IoArgument(&fifo_info)
			 ) >= 0 ){
		info = fifo_info.info;
	}
	return 0;
}

FifoInfo CFifo::get_info(int channel){
	FifoInfo info;
	get_info(channel, info.m_info);
	return info;
}


int CFifo::set_attributes(int channel, const fifo_attr_t & attr) const {
	cfifo_fifoattr_t fifo_attr;
	fifo_attr.channel = channel;
	fifo_attr.attr = attr;
	return ioctl(
				IoRequest(I_CFIFO_FIFOSETATTR),
				IoArgument(&fifo_attr)
				);
}

int CFifo::initialize(int channel) const {
	cfifo_fiforequest_t request;
	request.channel = channel;
	return ioctl(
				IoRequest(I_CFIFO_FIFOINIT),
				IoArgument(&request)
				);
}

int CFifo::flush(int channel) const {
	cfifo_fiforequest_t request;
	request.channel = channel;
	return ioctl(
				IoRequest(I_CFIFO_FIFOFLUSH),
				IoArgument(&request)
				);
}

int CFifo::exit(int channel) const {
	cfifo_fiforequest_t request = {0};
	request.channel = channel;
	return ioctl(
				IoRequest(I_CFIFO_FIFOEXIT),
				IoArgument(&request)
				);
}

int CFifo::set_writeblock(int channel, bool value) const {
	fifo_attr_t attr = {0};
	attr.o_flags = FifoFlags::flag_set_writeblock;
	if( value == false ){
		attr.o_flags |= FifoFlags::flag_is_overflow;
	}
	return set_attributes(channel, attr);
}


} /* namespace hal */
