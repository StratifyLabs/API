/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.


#ifndef SAPI_HAL_CFIFO_HPP_
#define SAPI_HAL_CFIFO_HPP_

#include <sos/dev/cfifo.h>

#include "Periph.hpp"
#include "Fifo.hpp"


namespace hal {

/*! \brief Channeled FIFO Information Class
 *
 */
class CFifoInfo : public api::InfoObject {
public:
	CFifoInfo(){ memset(&m_info, 0, sizeof(cfifo_info_t)); }
	CFifoInfo(const cfifo_info_t & info){ m_info = info; }

	u32 o_flags() const { return m_info.o_flags; }
	u16 count() const { return m_info.count; }
	u16 size() const { return m_info.size; }
	u32 o_ready() const { return m_info.o_ready; }

	operator const cfifo_info_t & () const { return m_info; }
private:
	friend class CFifo;
	cfifo_info_t m_info;
};

/*! \brief Channeled FIFO Class
 *
 * \details The Channeled FIFO allows access to channeled fifo devices.
 * A channeled FIFO device is a FIFO with multiple independent channels.
 * The file descriptor's location/offset (updated with lseek()) is used
 * to set the channel.
 *
 *
 */
class CFifo : public Device {
public:

	/*! \details Gets the number of channels in the channeled fifo. */
	int get_count() const;

	/*! \details Gets the info for the channeled fifo. */
	int get_info(cfifo_info_t & info) const;

	/*! \details Gets the owner of the specified channel.
	 *
	 * @param channel The channel that is queried
	 * @param owner A reference to write the owner value
	 * @return Zero on success or less than zero for an error
	 *
	 * This method along with set_owner() provides a mechanism to reserve
	 * the channel for a particular application. If the owner has been
	 * set to a non-zero value, it is already being used by another
	 * process and should not be used.
	 *
	 */
	int get_owner(int channel, int & owner) const;

	/*! \details Sets the owner of a channel.
	 *
	 * @param channel The channel
	 * @param owner The owner (usually the process ID)
	 * @return Zero on success
	 *
	 * This method is used with get_owner() to allow processes
	 * to reserve channels for passing information.
	 *
	 */
	int set_owner(int channel, int owner) const;

	/*! \details Gets a bitmask of channels that have at least
	 * one byte that is ready to be read.
	 *
	 * @return Bitmask of channels that are ready to be read
	 */
	u32 get_ready_channels() const {
		cfifo_info_t info;
		if( get_info(info) < 0 ){
			return 0;
		}
		return info.o_ready;
	}


	/*! \details Initializes the FIFO specified by \a channel.
	 *
	 * @param channel The FIFO channel to initialize
	 * @return Zero on success
	 */
	int initialize(int channel) const;
	int init(int channel) const	{ return initialize(channel); }

	/*! \details Flushes the FIFO specified by \a channel.
	 *
	 * @param channel The channel to flush
	 * @return Zero on success
	 */
	int flush(int channel) const;

	/*! \details Exits the FIFO specified by \a channel.
	 *
	 * @param channel The FIFO channel to de-initialize
	 * @return Zero on success
	 */
	int exit(int channel) const;

	/*! \details Gets the info specified by \a channel.
	 *
	 * @param channel The channel for which to fetch the FIFO info
	 * @param info A reference to the destination information
	 * @return Zero on success
	 */
	int get_info(int channel, fifo_info_t & info) const;

	/*! \details Returns the Fifo info for the specified channel. */
	FifoInfo get_info(int channel);

	/*! \details Sets the FIFO attributes specified by \a channel.
	 *
	 * @param channel The channel for which to set the FIFO attributes
	 * @param attr A reference to the fifo attributes
	 * @return
	 */
	int set_attributes(int channel, const fifo_attr_t & attr) const;
	int set_attr(int channel, const fifo_attr_t & attr) const { return set_attributes(channel, attr); }

	/*! \details Enables or disables write blocking on the FIFO specified by \a channel.
	 *
	 * @param channel The target channel
	 * @param value True to enable write blocking
	 * @return Zero on success
	 *
	 * If write blocking is enabled, the FIFO will block (or return EAGAIN is O_NONBLOCK is on)
	 * if no bytes can be written to the FIFO. If a single byte can be written, write()
	 * will return 1.
	 *
	 * With write blocking disable, write() will never block. It will simply overwrite the data
	 * that is already in the FIFO.
	 */
	int set_writeblock(int channel, bool value = true) const;


};

} /* namespace hal */

#endif /* SAPI_HAL_CFIFO_HPP_ */
