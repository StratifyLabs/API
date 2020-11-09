/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.
#ifndef SAPI_HAL_STREAMFFIFO_HPP_
#define SAPI_HAL_STREAMFFIFO_HPP_

#include <sos/dev/stream_ffifo.h>

#include "../api/HalObject.hpp"
#include "FFifo.hpp"

namespace hal {

class StreamFFifo;

class StreamFFifoChannelInfo {
public:

	StreamFFifoChannelInfo(const stream_ffifo_channel_info_t & info) : m_info(info){}
	bool is_valid() const {
		return m_info.ffifo.frame_count != 0;
	}

	FFifoInfo ffifo() const { return m_info.ffifo; }
	FFifoInfo ffifo_info() const { return m_info.ffifo; }

	u32 access_count() const { return m_info.access_count; }
	s32 error() const { return m_info.error; }

private:
	const stream_ffifo_channel_info_t & m_info;
};

class StreamFFifoInfo {
public:
	StreamFFifoInfo() :
		m_receive(m_info.rx),
		m_transmit(m_info.tx)
	{
		memset(&m_info, 0, sizeof(m_info));
	}

	StreamFFifoInfo(const stream_ffifo_info_t & info) :
		m_receive(m_info.rx),
		m_transmit(m_info.tx)
	{
		m_info = info;
	}

	 operator stream_ffifo_info_t& (){ return m_info; }
	const stream_ffifo_info_t& info() const { return m_info; }

	bool is_valid() const {
		return receive().is_valid() || transmit().is_valid();
	}

	bool is_stopped() const {
		return (m_info.o_status & STREAM_FFIFO_FLAG_STOP) == 0;
	}

	bool is_running() const {
		return (m_info.o_status & STREAM_FFIFO_FLAG_START) == 0;
	}

	bool is_reset() const {
		return m_info.o_status == 0;
	}

	const StreamFFifoChannelInfo & receive() const { return m_receive; }
	const StreamFFifoChannelInfo & transmit() const { return m_transmit; }

private:
	stream_ffifo_info_t m_info;
	StreamFFifoChannelInfo m_receive;
	StreamFFifoChannelInfo m_transmit;

};

class StreamFFifoAttributes {
public:
	StreamFFifoAttributes(){
		memset(&m_attr, 0, sizeof(m_attr));
	}

	operator const stream_ffifo_attr_t & () const { return m_attr; }

	StreamFFifoAttributes & set_flags(u32 value){
		m_attr.o_flags = value;
		return *this;
	}

private:
	friend class StreamFFifo;
	stream_ffifo_attr_t m_attr;

};

typedef StreamFFifoAttributes StreamFFifoAttr;


class StreamFFifo : public Device {
public:
	StreamFFifo();

	enum stream_ffifo_flags {
		flag_start = STREAM_FFIFO_FLAG_START,
		flag_stop = STREAM_FFIFO_FLAG_STOP,
		flag_flush = STREAM_FFIFO_FLAG_FLUSH
	};

	int set_attributes(const StreamFFifoAttributes & attributes){
		return ioctl(
					IoRequest(I_STREAM_FFIFO_SETATTR),
					IoConstArgument(&attributes.m_attr)
					);
	}

	StreamFFifo & operator << (const StreamFFifoAttributes & attributes){
		set_attributes(attributes);
		return *this;
	}

	int start();
	int stop();
	int flush();

	int get_info(stream_ffifo_info_t & info);
	StreamFFifoInfo get_info();

};

}

#endif // SAPI_HAL_STREAMFFIFO_HPP_
