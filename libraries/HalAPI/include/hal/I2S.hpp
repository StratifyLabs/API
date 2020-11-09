/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.
#ifndef SAPI_HAL_I2S_HPP_
#define SAPI_HAL_I2S_HPP_

#include <sos/dev/i2s.h>
#include "Periph.hpp"
#include "PinAssignment.hpp"

namespace hal {

/*! \brief I2S Pin Assignment
 * \details This class allows simple manipulation of the i2c_pin_assignment_t.
 *
 * \sa hal::I2S
 * \sa hal::I2SAttr
 *
 */
class I2SPinAssignment : public PinAssignment<i2s_pin_assignment_t>{};

/*! \brief I2S Attr Class
 * \details The I2S attribute class is used for configuring and storing
 * I2S port settings.
 *
 * \sa hal::I2SPinAssignment
 * \sa hal::I2S
 *
 */
class I2SAttributes : public PinAssignmentPeriphAttributes<i2s_attr_t, i2s_pin_assignment_t> {
public:
	I2SAttributes(){
		set_flags(I2S_FLAG_SET_MASTER);
		set_frequency(16000);
		m_attr.mck_mult = 256;
	}

	/*! \details Accesses the serial data input pin assignment value. */
	mcu_pin_t sdin() const { return m_attr.pin_assignment.sdin; }
	/*! \details Access the serial data output pin assignment value. */
	mcu_pin_t sdout() const { return m_attr.pin_assignment.sdout; }

	/*! \details Sets the SDA pin assignment value. */
	I2SAttributes & set_sdin(const mcu_pin_t & pin){ m_attr.pin_assignment.sdin = pin; return *this; }

	/*! \details Sets the SCL pin assignment value. */
	I2SAttributes & set_sdout(const mcu_pin_t & pin){ m_attr.pin_assignment.sdout = pin; return *this; }

	/*! \details Sets the SCL pin assignment value. */
	I2SAttributes & set_ws(const mcu_pin_t & pin){ m_attr.pin_assignment.ws = pin; return *this; }

	/*! \details Sets the SCL pin assignment value. */
	I2SAttributes & set_sck(const mcu_pin_t & pin){ m_attr.pin_assignment.sck = pin; return *this; }

	/*! \details Sets the SCL pin assignment value. */
	I2SAttributes & set_mck(const mcu_pin_t & pin){ m_attr.pin_assignment.mck = pin; return *this; }

	/*! \details Sets the frequency (rate for left/right clock). */
	I2SAttributes & set_frequency(u32 frequency){ m_attr.freq = frequency; return *this; }

	/*! \details Sets the o_flags value as specified. */
	I2SAttributes & set_flags(u32 o_flags){ m_attr.o_flags = o_flags; return *this; }

};

typedef I2SAttributes I2SAttr;

class I2S : public Periph<i2s_info_t, i2s_attr_t, I2SAttributes, 'I'> {
public:
	I2S(port_t port);

	enum i2s_flags {
		flag_is_width_8 /*! I2S Word Width 8 bits */ = I2S_FLAG_IS_WIDTH_8,
		flag_is_width_16 /*! I2S Word Width 16 bits */ = I2S_FLAG_IS_WIDTH_16,
		is_width_24 /*! I2S Word Width 24 bits */ = I2S_FLAG_IS_WIDTH_24,
		flag_is_width_32 /*! I2S Word Width 32 bits */ = I2S_FLAG_IS_WIDTH_32,
		flag_is_mono /*! I2S Mono mode */ = I2S_FLAG_IS_MONO,
		flag_is_stereo /*! I2S Stereo mode (default behavoir) */ = I2S_FLAG_IS_STEREO,
		flag_set_master /*! Set the I2S as a master */ = I2S_FLAG_SET_MASTER,
		flag_set_slave /*! Set the I2S as a slave */ = I2S_FLAG_SET_SLAVE,
		flag_is_transmitter /*! Set the I2S transmitter (master or slave) */ = I2S_FLAG_IS_TRANSMITTER,
		flag_is_receiver /*! Set the I2S receiver (master or slave) */ = I2S_FLAG_IS_RECEIVER,
		flag_is_format_msb /*! Set this bit for MSB format */ = I2S_FLAG_IS_FORMAT_MSB,
		flag_is_format_lsb /*! Set this bit for LSB format */ = I2S_FLAG_IS_FORMAT_LSB,
		flag_is_mck_enabled /*! Set this bit to enable the mclk output */ = I2S_FLAG_IS_MCK_ENABLED,
		flag_is_format_pcm_short /*! Set this bit for PCM Short format*/ = I2S_FLAG_IS_FORMAT_PCM_SHORT,
		flag_is_format_pcm_long /*! Set this bit for PCM Long format*/ = I2S_FLAG_IS_FORMAT_PCM_LONG,
		flag_is_width_16_extended /*! I2S has 16-bits of data in 32-bit blocks */ = I2S_FLAG_IS_WIDTH_16_EXTENDED
	};

private:


};

/*! \endcond */


}

#endif // SAPI_HAL_I2S_HPP_
