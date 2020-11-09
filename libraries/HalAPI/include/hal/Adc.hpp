/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.

#ifndef SAPI_HAL_ADC_HPP_
#define SAPI_HAL_ADC_HPP_

#include <sos/dev/adc.h>
#include "PinAssignment.hpp"
#include "Periph.hpp"

namespace hal {

class AdcFlags {
public:

	enum flags {
		flag_set_converter /*! See ADC_FLAG_SET_CONVERTER */ = ADC_FLAG_SET_CONVERTER,
		flag_is_left_justified /*! See ADC_FLAG_IS_LEFT_JUSTIFIED */ = ADC_FLAG_IS_LEFT_JUSTIFIED,
		flag_is_right_justified /*! Set to specify right justified data */ = ADC_FLAG_IS_RIGHT_JUSTIFIED,
		flag_set_master = ADC_FLAG_SET_MASTER /*! Used with MCUs that have more than one ADC that can operate in master/slave mode */,
		flag_set_slave = ADC_FLAG_SET_SLAVE /*! Used with MCUs that have more than one ADC that can operate in master/slave mode */,
		flag_is_trigger_tmr = ADC_FLAG_IS_TRIGGER_TMR /*! Used to trigger the ADC read on a timer event */,
		flag_is_trigger_eint = ADC_FLAG_IS_TRIGGER_EINT /*! Used to trigger the ADC read on a external interrupt */,
		flag_set_channels = ADC_FLAG_SET_CHANNELS /*! Configure the channels withouth changing ADC settings */,
		flag_is_scan_mode = ADC_FLAG_IS_SCAN_MODE /*! ADC will read every enabled channel when reading rather than the channel based on the location value */,
		flag_is_trigger_eint_edge_rising /*! Trigger the sample on the rising edge */ = ADC_FLAG_IS_TRIGGER_EINT_EDGE_RISING,
		flag_is_trigger_eint_edge_falling /*! Trigger the sample on the falling edge */ = ADC_FLAG_IS_TRIGGER_EINT_EDGE_FALLING,
		flag_is_group /*! Set channel as part of a group */ = ADC_FLAG_IS_GROUP,
		flag_is_continous_conversion /*! Start the next conversion as soon as the previous conversion completes */ = ADC_FLAG_IS_CONTINOUS_CONVERSION

	};
};

/*! \brief ADC Info Class
 *
 *
 */
class AdcInfo {
public:
	AdcInfo(){ m_adc_info = {0}; }
	AdcInfo(const adc_info_t & info) : m_adc_info(info) {}

	bool is_valid() const { return m_adc_info.bytes_per_sample; }

	u32 o_flags() const { return m_adc_info.o_flags; }
	u32 o_events() const { return m_adc_info.o_events; }
	u32 resolution() const { return m_adc_info.resolution; }
	u8 bytes_per_sample() const { return m_adc_info.bytes_per_sample; }
	u32 frequency() const { return m_adc_info.freq; }
	u32 maximum_value() const { return m_adc_info.maximum; }
	u32 reference_millivolts() const { return m_adc_info.reference_mv; }
	u8 vref_internal_channel() const { return m_adc_info.internal_vref_channel; }
	u8 temperature_internal_channel() const { return m_adc_info.internal_temperature_channel; }
	u8 vbat_internal_channel() const { return m_adc_info.internal_vbat_channel; }


	u32 calculate_millivolts(u32 sample_value) const {
		return (sample_value * reference_millivolts() + maximum_value()/2) / maximum_value();
	}


	const adc_info_t & info() const{ return m_adc_info; }
	adc_info_t & info(){ return m_adc_info; }

private:
	adc_info_t m_adc_info;
};


/*! \brief ADC Attributes Class
 * \details This class is for containing ADC attributes.
 */
class AdcAttributes :
		public PinAssignmentPeriphAttributes<adc_attr_t, adc_pin_assignment_t>,
		public AdcFlags {
public:


	enum pin_assignments {
		pin_assignment_channel_0,
		pin_assignment_channel_1,
		pin_assignment_channel_2,
		pin_assignment_channel_3,
	};

	AdcAttributes(){}

	AdcAttributes(u32 o_flags, u32 freq){
		set_flags(o_flags);
		set_freq(freq);
	}

	AdcAttributes & set_channel(u16 channel){ m_attr.channel = channel; return *this; }
	AdcAttributes & set_rank(u32 rank){ m_attr.rank = rank; return *this; }
	AdcAttributes & set_sampling_time(u32 sampling_time){ m_attr.sampling_time = sampling_time; return *this; }

	AdcAttributes & set_pin_assignment(enum pin_assignments channel, mcu_pin_t pin){
		m_attr.pin_assignment.channel[channel] = pin;
		return *this;
	}

	/*! \details Configures a channel in a group for sampling.
	 *
	 * @param channel The channel number to sample
	 * @param rank The rank (order) of the channel
	 * @param sampling_time The sampling time (in ADC clocks for the channel)
	 *
	 * \code
	 * AdcAttributes adc_attributes;
	 * adc_attributes.configure_group_channel(0, 1, 15);
	 * Adc adc(0);
	 *
	 * adc.init();
	 * adc.set_attributes(adc_attributes);
	 * \endcode
	 *
	 */
	AdcAttributes & configure_group_channel(
			u16 channel,
			u32 rank,
			u32 sampling_time = 15){
		set_flags(flag_set_channels | flag_is_group);
		set_channel(channel);
		set_rank(rank);
		set_sampling_time(sampling_time);
		return *this;
	}

};

typedef AdcAttributes AdcAttr;

/*! \brief ADC Pin Assignment
 * \details This class allows simple manipulation of the adc_pin_assignment_t.
 */
class AdcPinAssignment : public PinAssignment<adc_pin_assignment_t>{};


/*! \brief ADC Peripheral Class
 * \details This class implements ADC device peripherals.
 *
 * \code
 * #include <sapi/hal.hpp>
 *
 * int main(int argc, char * argv[]){
 * 	Adc adc(0);  //create an instance of ADC to access port 0
 * 	u32 samples[16];
 * 	adc.init(); //initialize the ADC using the default configuration
 * 	adc.read(0, samples, 16*sizeof(u32)); //read 16 samples from channel 0
 * 	adc.read(1, samples, 16*sizeof(u32)); //read 16 samples from channel 1
 * 	adc.close(); //close the ADC
 * }
 * \endcode
 *
 */
class Adc :
		public Periph<adc_info_t, adc_attr_t, AdcAttributes, ADC_IOC_IDENT_CHAR>,
		public AdcFlags{
public:

	/*! \details Initializes the object with \a port. */
	explicit Adc(port_t port);

	/*! \details Returns an AdcInfo object associated with the ADC.
	 *
	 */
	AdcInfo get_info() const;

private:

};

}

#endif /* SAPI_HAL_ADC_HPP_ */
