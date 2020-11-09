/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.
#ifndef SAPI_HAL_FFIFO_HPP_
#define SAPI_HAL_FFIFO_HPP_

#include <sos/dev/ffifo.h>

#include "Device.hpp"

namespace hal {

class FFifoAttributes : public api::InfoObject {
public:

	/*! \details Constructs an object set to all zeros. */
	FFifoAttributes(){
		memset(&m_ffifo_attr, 0, sizeof(ffifo_attr_t));
	}

	/*! \details Constructs an object from a ffifo_attr_t data structure. */
	FFifoAttributes(const ffifo_attr_t & attr){
		memcpy(&m_ffifo_attr, &attr, sizeof(ffifo_attr_t));
	}

	/*! \details Sets the overflow flag.
	 *
	 * This will cause the device to overwrite old data rather than
	 * block when the device is full.
	 *
	 */
	void set_overflow(){ m_ffifo_attr.o_flags |= FFIFO_FLAG_IS_OVERFLOW; }

	/*! \details Sets the write block flag.
	 *
	 * This will cause the device to block or return errno EAGAIN if a
	 * write is attempted while the FIFO is full.
	 *
	 */
	void set_write_block(){ m_ffifo_attr.o_flags |= FFIFO_FLAG_SET_WRITEBLOCK; }


private:
	friend class FFifo;
	ffifo_attr_t m_ffifo_attr;
};

typedef FFifoAttributes FFifoAttr;

/*! \brief FFIFO Info Class
 *
 */
class FFifoInfo : public api::InfoObject {
public:

	/*! \details Constructs an object with all zeros. */
	FFifoInfo(){
		memset(&m_ffifo_info, 0, sizeof(m_ffifo_info));
	}

	/*! \details Constructs an object by copying \a info. */
	FFifoInfo(const ffifo_info_t & info){
		memcpy(&m_ffifo_info, &info, sizeof(ffifo_info_t));
	}

	/*! \details Returns true if the info is valid. */
	bool is_valid() const { return m_ffifo_info.frame_size != 0; }

	/*! \details Returns the number of frames in the framed FIFO. */
	u16 frame_count() const { return m_ffifo_info.frame_count; }

	/*! \details Returns the number of frames in the framed FIFO. */
	u16 frame_size() const { return m_ffifo_info.frame_size; }

	/*! \details Returns the number of frames currently in use.
	 *
	 * This is the number of frames that is ready to be read.
	 */
	u16 frame_count_ready() const { return m_ffifo_info.frame_count_ready; }

	/*! \details Returns the total number of bytes used by the FFIFO buffer (frame size * frame count). */
	u32 size() const { return frame_size() * frame_count(); }

	/*! \details Returns true if the FFIFO has overflowed. This flag is cleared on FFifo::get_info(). */
	bool is_overflow() const { return (m_ffifo_info.o_flags & FFIFO_FLAG_IS_OVERFLOW) != 0; }

private:
	friend class FFifo;
	ffifo_info_t m_ffifo_info;
};

/*! \brief FFifo Class
 * \details The FFIFO class is for access devices
 * that are framed FIFOs from <sos/dev/ffifo.h>.
 *
 * A framed FIFO is a FIFO where each read and write operation
 * must match an integer multiple value of the frame size.
 *
 * They are useful for storing audio data streams where fixed
 * frame sizes arrive and need to be buffered before being
 * processed.
 *
 *
 *
 */
class FFifo : public Device {
public:
	FFifo();

	/*! \details Opens and initiliazes the device.
	 *
	 * @param path The path to the device (e.g., /dev/ffifo0)
	 * @param attr The attributes to assign
	 * @param o_flags Flags to use when opening e.g. FFifo::NONBLOCK
	 * @return Zero on success or less than zero for an error
	 *
	 */
	int initialize(
			const var::String & path,
			const FFifoAttributes & attributes,
			const fs::OpenMode & flags = fs::OpenMode()
			);

	/*! \details Flushes the FIFO.
	 *
	 * @returns Zero on success
	 *
	 */
	int flush() const;

	/*! \details Sets the FIFO attributes. */
	int set_attributes(const FFifoAttributes & attributes) const;

	FFifo & operator << (const FFifoAttributes & attributes){
		set_attributes(attributes);
		return *this;
	}

	/*! \details Returns the information for the FFIFO. */
	FFifoInfo get_info() const;

	/*! \details Gets the FFIFO information.
	 *
	 * @param info A reference to the destination value
	 *
	 * \returns Less than zero on an error
	 */
	int get_info(FFifoInfo & info) const;



};

}

#endif // SAPI_HAL_FFIFO_HPP_
