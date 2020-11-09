/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.

#ifndef SAPI_HAL_DAC_HPP_
#define SAPI_HAL_DAC_HPP_

#include <sos/dev/dac.h>
#include "PinAssignment.hpp"
#include "Periph.hpp"

namespace hal {

class DacFlags {
public:
	enum flags {
		flag_set_converter /*! Set to configure the converter */ = DAC_FLAG_SET_CONVERTER,
		flag_is_left_justified /*! Set to left justify the data */ = DAC_FLAG_IS_LEFT_JUSTIFIED,
		flag_is_right_justified /*! Set to right justify the data */ = DAC_FLAG_IS_RIGHT_JUSTIFIED
	};

};

/*! \brief DAC Attributes Class
 * \details This class is for containing DAC attributes.
 */
class DacAttributes :
		public PinAssignmentPeriphAttributes<dac_attr_t, dac_pin_assignment_t>,
		public DacFlags {
public:
	DacAttributes(){

	}

	DacAttributes & set_flags(u32 o_flags){
		PinAssignmentPeriphAttributes::set_flags(o_flags);
		return *this;
	}

	DacAttributes & set_frequency(u32 value){
		PinAssignmentPeriphAttributes::set_frequency(value);
		return *this;
	}

};

typedef DacAttributes DacAttr;

/*! \brief DAC Pin Assignment
 * \details This class allows simple manipulation of the dac_pin_assignment_t.
 */
class DacPinAssignment : public PinAssignment<dac_pin_assignment_t>{};

/*! \brief DAC Class
 * \details DAC (Digital to Analog Converter) Class
 *
 * The DAC class is used to write data to the digital to analog converter.  Here is an example:
 *
 * \code
 * #include <sapi/hal.hpp>
 * #include <sapi/sys.hpp>
 *
 * int main(int argc, char * argv[]){
 * 	Dac dac(0);
 * 	u32 samples[50];
 * 	dac.init(); //init with default settings
 *
 *  //here, write meaningful values to samples
 *
 * 	dac.write(0, samples, 50*sizeof(u32)); //This returns when all 50 samples are written
 *
 *  //if you want to do other things while the sample is written use AIO
 * 	Aio aio(samples, 50*sizeof(u32));
 *
 * 	dac.write(aio);
 *  //Here you can do other things while the data is written
 * 	while( aio.is_busy() == true ){
 * 		Timer::wait_usec(500); //wait until the write is complete
 * 	}
 *
 * 	dac.close(); //this will power off the DAC if nothing else has it open
 *
 * 	return 0;
 * }
 *
 * \endcode
 *
 */
class Dac :
		public Periph<dac_info_t, dac_attr_t, DacAttributes, 'd'>,
		public DacFlags{
public:

	explicit Dac(port_t port);

	/*! \details Sets the value of the DAC channel.
	 *
	 * @param value Value to write to the DAC
	 * @param loc The DAC channel
	 * @return Zero on success
	 */
	int set_channel(
			u32 loc,
			u32 value
			) const {
		return Periph::set_channel(loc, value, IoRequest(I_DAC_SET));
	}

	/*! \details Gets the current value of the DAC channel.
	 *
	 * @param loc The DAC channel to get
	 * @return The current value of the channel or static_cast<u32>(-1) if ther is an error
	 */
	u32 get_channel(u32 loc) const {
		return Periph::get_channel(loc, IoRequest(I_DAC_GET));
	}

private:



};

}

#endif /* SAPI_HAL_DAC_HPP_ */
