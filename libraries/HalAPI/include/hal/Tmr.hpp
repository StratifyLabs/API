/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.

#ifndef SAPI_HAL_TMR_HPP_
#define SAPI_HAL_TMR_HPP_


#include <sos/dev/tmr.h>
#include "PinAssignment.hpp"
#include "Periph.hpp"


namespace hal {

class TmrFlags {
public:
	enum flags {
		flag_set_timer /*! See \ref TMR_FLAG_SET_TIMER */ = TMR_FLAG_SET_TIMER,
		flag_is_source_cpu /*! See \ref TMR_FLAG_IS_SOURCE_CPU */ = TMR_FLAG_IS_SOURCE_CPU,
		flag_is_source_ic0 /*! See \ref TMR_FLAG_IS_SOURCE_IC0 */ = TMR_FLAG_IS_SOURCE_IC0,
		flag_is_source_ic1 /*! See \ref TMR_FLAG_IS_SOURCE_IC1 */ = TMR_FLAG_IS_SOURCE_IC1,
		flag_is_source_ic2 /*! See \ref TMR_FLAG_IS_SOURCE_IC2 */ = TMR_FLAG_IS_SOURCE_IC2,
		flag_is_source_ic3 /*! See \ref TMR_FLAG_IS_SOURCE_IC3 */ = TMR_FLAG_IS_SOURCE_IC3,
		flag_is_source_edgerising /*! See \ref TMR_FLAG_IS_SOURCE_EDGERISING */ = TMR_FLAG_IS_SOURCE_EDGERISING,
		flag_is_source_edgefalling /*! See \ref TMR_FLAG_IS_SOURCE_EDGEFALLING */ = TMR_FLAG_IS_SOURCE_EDGEFALLING,
		flag_is_source_edgeboth /*! See \ref TMR_FLAG_IS_SOURCE_EDGEBOTH */ = TMR_FLAG_IS_SOURCE_EDGEBOTH,
		flag_is_source_countdown /*! See \ref TMR_FLAG_IS_SOURCE_COUNTDOWN */ = TMR_FLAG_IS_SOURCE_COUNTDOWN,
		flag_is_auto_reload /*! See \ref TMR_FLAG_IS_AUTO_RELOAD */ = TMR_FLAG_IS_AUTO_RELOAD,
		flag_set_channel /*! See \ref TMR_FLAG_SET_CHANNEL */ = TMR_FLAG_SET_CHANNEL,
		flag_is_channel_stop_on_reset /*! See \ref TMR_FLAG_IS_CHANNEL_STOP_ON_RESET */ = TMR_FLAG_IS_CHANNEL_STOP_ON_RESET,
		flag_is_channel_reset_on_match /*! See \ref TMR_FLAG_IS_CHANNEL_RESET_ON_MATCH */ = TMR_FLAG_IS_CHANNEL_RESET_ON_MATCH,
		flag_is_channel_stop_on_match /*! See \ref TMR_FLAG_IS_CHANNEL_STOP_ON_MATCH */ = TMR_FLAG_IS_CHANNEL_STOP_ON_MATCH,
		flag_is_channel_set_output_on_match /*! See \ref TMR_FLAG_IS_CHANNEL_SET_OUTPUT_ON_MATCH */ = TMR_FLAG_IS_CHANNEL_SET_OUTPUT_ON_MATCH,
		flag_is_channel_clear_output_on_match /*! See \ref TMR_FLAG_IS_CHANNEL_CLEAR_OUTPUT_ON_MATCH */ = TMR_FLAG_IS_CHANNEL_CLEAR_OUTPUT_ON_MATCH,
		flag_is_channel_toggle_output_on_match /*! See \ref TMR_FLAG_IS_CHANNEL_TOGGLE_OUTPUT_ON_MATCH */ = TMR_FLAG_IS_CHANNEL_TOGGLE_OUTPUT_ON_MATCH,
		flag_is_channel_pwm_mode /*! See \ref TMR_FLAG_IS_CHANNEL_PWM_MODE */ = TMR_FLAG_IS_CHANNEL_PWM_MODE,
		flag_set_trigger /*! See \ref TMR_FLAG_SET_TRIGGER */ = TMR_FLAG_SET_TRIGGER,
		flag_is_slave /*! See \ref TMR_FLAG_IS_SLAVE */ = TMR_FLAG_IS_SLAVE,
		flag_is_master /*! See \ref TMR_FLAG_IS_MASTER */ = TMR_FLAG_IS_MASTER,
		flag_is_trigger_reload /*! See \ref TMR_FLAG_IS_TRIGGER_RELOAD */ = TMR_FLAG_IS_TRIGGER_RELOAD,
		flag_is_trigger_reset /*! See \ref TMR_FLAG_IS_TRIGGER_RESET */ = TMR_FLAG_IS_TRIGGER_RESET,
		flag_is_trigger_enable /*! See \ref TMR_FLAG_IS_TRIGGER_ENABLE */ = TMR_FLAG_IS_TRIGGER_ENABLE,
		flag_is_trigger_oc0 /*! See \ref TMR_FLAG_IS_TRIGGER_OC0 */ = TMR_FLAG_IS_TRIGGER_OC0,
		flag_is_trigger_oc1 /*! See \ref TMR_FLAG_IS_TRIGGER_OC1 */ = TMR_FLAG_IS_TRIGGER_OC1,
		flag_is_trigger_oc2 /*! See \ref TMR_FLAG_IS_TRIGGER_OC2 */ = TMR_FLAG_IS_TRIGGER_OC2,
		flag_is_trigger_oc3 /*! See \ref TMR_FLAG_IS_TRIGGER_OC3 */ = TMR_FLAG_IS_TRIGGER_OC3,
	};
};

/*! \brief Tmr Pin Assignment
 * \details This class allows simple manipulation of the tmr_pin_assignment_t.
 */
class TmrPinAssignment : public PinAssignment<tmr_pin_assignment_t>{};

class TmrAttributes :
		public PinAssignmentPeriphAttributes<
		tmr_attr_t,
		tmr_pin_assignment_t
		>, public TmrFlags {
public:

	TmrAttributes(){
		set_flags(0);
		set_frequency(0);
		set_period(0);
	}


	mcu_pin_t channel(u8 channel) const {
		if( channel < 4 ){ return m_attr.pin_assignment.channel[channel]; }
		return mcu_pin(0xff, 0xff);
	}

	u32 period() const { return m_attr.period; }

	TmrAttributes & set_port(u32 value){ PinAssignmentPeriphAttributes::set_port(value); return *this; }
	TmrAttributes & set_flags(u32 value){ PinAssignmentPeriphAttributes::set_flags(value); return *this; }
	TmrAttributes & set_frequency(u32 value){ PinAssignmentPeriphAttributes::set_frequency(value); return *this; }

	TmrAttributes & set_channel_pin(u8 channel, const mcu_pin_t & pin){
		if( channel < 4 ){
			m_attr.pin_assignment.channel[channel] = pin;
		}
		return *this;
	}

	TmrAttributes & assign_pin(
			Device::Location position,
			Device::Port port,
			Device::PinNumber pin){
		if( position.argument() <
			 (int)(sizeof(tmr_pin_assignment_t)/sizeof(mcu_pin_t)) ){
			m_attr.pin_assignment.channel[position.argument()] =
					mcu_pin(port.argument(), pin.argument());
		}
		return *this;
	}

	TmrAttributes & set_channel(
			Device::Location location,
			u32 value
			){
		m_attr.channel = mcu_channel(
					location.argument(),
					value
					);
		return *this;
	}

	TmrAttributes & set_channel_pin(
			Device::Channel channel,
			Device::Port port,
			Device::PinNumber pin
			){
		if( channel.argument() < 4 ){
			m_attr.pin_assignment.channel[channel.argument()] = mcu_pin(
						port.argument(),
						pin.argument()
						);
		}
		return *this;
	}

	TmrAttributes & set_period(u32 period){ m_attr.period = period; return *this; }

	TmrAttributes & set_channel(const mcu_channel_t & channel){
		m_attr.channel = channel;
		return *this;
	}

};

typedef TmrAttributes TmrAttr;

/*! \brief Tmr (hardware timer) Class
 * \details This class implements a hardware timer.  The Timer class implements
 * a logical timer that is based on the system clock and can be used for many timing functions.
 *
 * The Tmr class can be used to configure a timer to count rising edges on an input capture pin
 * or to generate waveforms on an output compare pin.  It can also configure the timer
 * to use the internal CPU clock at various frequencies.
 *
 *
 * ```
 * //md2code:include
 * #include <sapi/hal.hpp>
 * #include <sapi/chrono.hpp>
 * ```
 *
 * For example this will start a microsecond timer (1Mhz) using an internal clock:
 *
 * ```
 * //md2code:main
 * Tmr tmr(0); //use /dev/tmr0
 * tmr.initialize(); //initialize the timer
 * tmr.set(0); //set the value to zero
 * tmr.enable(); //turn the timer on
 * chrono::wait(Milliseconds(100));
 * printf(
 *   "My timer value is %ld\n",
 *   tmr.value()
 * ); //The value will be about 100,000
 * ```
 *
 * Here is an example using the Tmr to count external edges on input capture 0
 *
 * ```
 * //md2code:main
 *
 * ```
 *
 * You can also use the output compare channels to set the top value of the timer.
 *
 * ```
 *	//md2code:main
 *
 * ```
 *
 * Some timers support PWM mode.
 *
 *
 * ```
 * //md2code:main
 *	Tmr pwm_timer(3);
 *	TmrAttributes pwm_timer_attributes;
 *	pwm_timer_attributes.set_flags(
 *				Tmr::SET_TIMER |
 *				Tmr::IS_SOURCE_CPU |
 *				Tmr::IS_AUTO_RELOAD |
 *				Tmr::SET_CHANNEL |
 *				Tmr::IS_CHANNEL_PWM_MODE
 *				)
 *			.set_period(pwm_timer_period)
 *			.set_frequency(pwm_timer_frequency)
 *			.set_channel(
 *				arg::Location(pmw_channel_number),
 *				arg::Value(0)
 *				)
 *			.assign_pin( //assign PD15 to use as a channel
 *				arg::Position(0), //use slot zero to assign this pin
 *				Pin::Port(3), //PORTA -> 0 ... PORTD -> 3
 *				Pin::Number(15) //Pin 15
 *				);
 *
 *
 *	printf("Initialize PWM timer\n");
 *	pwm_timer.initialize(
 *				pwm_timer_attributes
 *				);

 *	if( pwm_timer.return_value() < 0 ){
 *		printf(
 *					"Failed to initialize PWM timer (%d, %d)\n",
 *					pwm_timer.return_value(),
 *					pwm_timer.error_number()
 *				 );
 *		exit(1);
 *	}
 *
 *	pwm_timer.enable();
 * ```
 *
 *
 */
class Tmr :
		public Periph<
		tmr_info_t,
		tmr_attr_t,
		TmrAttributes,
		TMR_IOC_IDENT_CHAR>,
		public TmrFlags {
public:

	/*! \details Constructs a new timer object using \a port. */
	Tmr(port_t port);


	/*! \details Turns the TMR on (start counting) */
	int enable() const;

	/*! \details Turns the TMR off (stop counting) */
	int disable() const;

	/*! \details Sets the value of the specified channel.
	 *
	 * @param loc The channel number
	 * @param value The value to assign to the channel
	 * @return Zero on success
	 *
	 * The \a loc parameter is the input or output channel. Input channels
	 * should be or'd with the MCU_CHANNEL_FLAG_IS_INPUT value.
	 *
	 */
	int set_channel(
			Device::Location loc,
			u32 value
			){
		return Periph::set_channel(
					loc.argument(),
					value,
					IoRequest(I_TMR_SETCHANNEL)
					);
	}

	int set_channel(const ChannelOptions & options){
		return Periph::set_channel(options, I_TMR_SETCHANNEL);
	}

	/*! \details Gets the value of the specified channel.
	 *
	 * @param loc The channel number
	 * @return The value of the channel or static_cast<u32>(-1) if the IOCTL request fails
	 *
	 * The \a loc parameter is the input or output channel. Input channels
	 * should be or'd with the MCU_CHANNEL_FLAG_IS_INPUT value.
	 *
	 */
	u32 get_channel(Device::Location location){
		return Periph::get_channel(
					location.argument(),
					IoRequest(I_TMR_GETCHANNEL)
					);
	}

	/*! \details Gets the value of the timer. */
	u32 get_value() const;

	/*! \details Sets the value of the timer. */
	int set_value(u32 value) const;


private:

};

}

#endif /* SAPI_HAL_TMR_HPP_ */
