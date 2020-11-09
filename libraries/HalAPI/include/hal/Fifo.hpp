/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.

#ifndef SAPI_HAL_FIFO_HPP_
#define SAPI_HAL_FIFO_HPP_

#include <cstring>
#include <sos/dev/fifo.h>
#include "Device.hpp"

namespace hal {


class CFifo;
class Fifo;

class FifoFlags {
public:
	enum flags {
		flag_set_writeblock = FIFO_FLAG_SET_WRITEBLOCK,
		flag_is_overflow = FIFO_FLAG_IS_OVERFLOW,
		flag_is_notify_write = FIFO_FLAG_NOTIFY_WRITE,
		flag_is_notify_read = FIFO_FLAG_NOTIFY_READ,
		flag_initialize = FIFO_FLAG_INIT,
		flag_exit = FIFO_FLAG_EXIT,
		flag_flush = FIFO_FLAG_FLUSH
	};
};

API_OR_FLAGS_OPERATOR(FifoFlags)


/*! \brief Fifo Attributes Class
 *
 */
class FifoInfo :
		public api::InfoObject,
		public FifoFlags {
public:

	/*! \details Constructs an object with all zeros. */
	FifoInfo(){ m_info = {0}; }

	/*! \details Constructs an object from a fifo_info_t reference. */
	FifoInfo(const fifo_info_t & info) : m_info(info){}

	/*! \details Returns true if the FIFO info object is valid. */
	bool is_valid() const { return m_info.size > 0; }

	/*! \details The number of bytes in the FIFO that are currently used (ie available
							* for reading.
							*
							* @return The number of bytes available for reading.
							*/
	u32 size_ready() const { return m_info.size_ready; }

	/*! \details This method accesses the maximum number of bytes allocated for the FIFO.
							*
							*/
	u32 size() const { return m_info.size; }

	/*! \details This method accesses whether or not the FIFO has overflowed
							* since the last time the FIFO attributes have been read.
							*/
	bool is_overflow() const { return m_info.overflow != 0; }
	bool overflow() const { return m_info.overflow != 0; }
private:
	friend class CFifo;
	friend class Fifo;
	fifo_info_t m_info;
};

/*! \brief FIFO Class */
/*! \details The Fifo class connects to Fifo devices which can be used for:
 *
 * - Inter-process communication
 * - Buffering serial I/O from SPI, I2S, USB, etc
 *
 * For example, the default STDIO is implemented as two fifo buffers: one for input
 * and one for output. A typical application will write the STDOUT fifo while
 * the USB protocol will read the fifo and display it on the screen. Alternatively,
 * a separate application or the kernel could read the STDOUT and print it on a display
 * or send it out the UART.
 *
 * Fifo's can be opened in blocking and non-blocking modes when both reading and writing.
 * If Fifo::set_writeblock() is called, a write will block when the Fifo is full. Otherwise,
 * the Fifo will overflow and FifoInfo::is_overflow() will return true.
 *
 *
 * \code
 * #include <cstdio>
 * #include <sapi/hal.hpp>
 *
 * Fifo fifo;
 * FifoInfo attr;
 *
 * if( fifo.open("/dev/fifo", Fifo::RDWR) < 0 ){
 * 	perror("failed to open fifo");
 * }
 *
 * if( fifo.attr().used() > 0){
 * 	//fifo is not empty
 * }
 *
 *	//write some data to the fifo
 * fifo.write("Testing fifo write\n");
 *
 * fifo.close();
 * \endcode
 *
 */
class Fifo :
		public hal::Device,
		public FifoFlags {
public:
	Fifo();

	/*! \details Reads the Fifo Attributes. */
	int get_info(FifoInfo & info) const;

	/*! \details Returns the fifo info. */
	FifoInfo get_info() const;

	/*! \details Flushes the FIFO. */
	int flush() const;

	/*! \details Initialize the FIFO. This function should only be called once
	 * even if several contexts access the FIFO.
	 *
	 *  @return Less than zero for an error.
	 *
	 */
	int initialize() const;

	int finalize() const;

	/*! \details Sets the FIFO in write block mode.
	 *
	 * @param value True to enable write block or false to disable it
	 *
	 * If write blocking is enabled, the FIFO will block (or return EAGAIN is O_NONBLOCK is on)
	 * if no bytes can be written to the FIFO. If a single byte can be written, write()
	 * will return 1.
	 *
	 * With write blocking disable, write() will never block. It will simply overwrite the data
	 * that is already in the FIFO.
	 *
	 */
	int set_writeblock(bool value = true) const;

};

}

#endif /* SAPI_HAL_FIFO_HPP_ */
