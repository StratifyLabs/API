/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.

#ifndef SAPI_HAL_CORE_HPP_
#define SAPI_HAL_CORE_HPP_

#include "Periph.hpp"
#include "sys/Sys.hpp"
#include "var/String.hpp"
#include <mcu/mcu.h>
#include <sos/dev/core.h>

namespace hal {

class CoreFlags {
public:
  enum flags {
    flag_is_reset_software
    = CORE_FLAG_IS_RESET_SOFTWARE /*! Software Reset (default if hardware reset
                                     cannot be determined) */
    ,
    flag_is_reset_power_on = CORE_FLAG_IS_RESET_POR /*! Power on Reset */,
    flag_is_reset_external
    = CORE_FLAG_IS_RESET_EXTERNAL /*! External Reset signal */,
    flag_is_reset_watchdog = CORE_FLAG_IS_RESET_WDT /*! Watchdog Timer Reset */,
    flag_is_reset_brown_out = CORE_FLAG_IS_RESET_BOR /*! Brown Out Reset */,
    flag_is_reset_system
    = CORE_FLAG_IS_RESET_SYSTEM /*! Software System Reset */,
    flag_set_clockout = CORE_FLAG_SET_CLKOUT /*! Use the CPU Clock */,
    flag_is_clockout_cpu = CORE_FLAG_IS_CLKOUT_CPU /*! Use the CPU Clock */,
    flag_is_clockout_main_oscillator
    = CORE_FLAG_IS_CLKOUT_MAIN_OSC /*! Use the Main Oscillator */,
    flag_is_clockout_internal_oscillator
    = CORE_FLAG_IS_CLKOUT_INTERNAL_OSC /*! Use the Internal Oscillator */,
    flag_is_clockout_usb = CORE_FLAG_IS_CLKOUT_USB /*! Use the USB Clock */,
    flag_is_clockout_rtc = CORE_FLAG_IS_CLKOUT_RTC /*! Use the RTC Clock */,
    flag_execute_sleep = CORE_FLAG_EXEC_SLEEP /*! Sleep */,
    flag_execute_deepsleep
    = CORE_FLAG_EXEC_DEEPSLEEP /*! Deep sleep (preserve SRAM) */,
    flag_execute_deepsleep_stop
    = CORE_FLAG_EXEC_DEEPSLEEP_STOP /*! Deep sleep (preserve SRAM, stop clocks)
                                     */
    ,
    flag_execute_deepsleep_standby
    = CORE_FLAG_EXEC_DEEPSLEEP_STANDBY /*! Turn the device off (lose SRAM) */,
    flag_execute_reset
    = CORE_FLAG_EXEC_RESET /*! Set this flag with I_CORE_SETATTR to reset the
                              device */
    ,
    flag_invoke_bootloader
    = CORE_FLAG_EXEC_INVOKE_BOOTLOADER /*! Set this flag with I_CORE_SETATTR to
                                          reset the device and start the
                                          bootloader */
  };

  /*! \details Core functional types */
  enum func {
    function_core /*! Core Functionality */ = CORE_PERIPH_CORE,
    function_adc /*! Analog to Digital Converter */ = CORE_PERIPH_ADC,
    function_dac /*! Digital to Analog Converter */ = CORE_PERIPH_DAC,
    function_uart /*! UART */ = CORE_PERIPH_UART,
    function_spi /*! SPI */ = CORE_PERIPH_SPI,
    function_usb /*! USB */ = CORE_PERIPH_USB,
    function_can /*! CAN */ = CORE_PERIPH_CAN,
    function_enet /*! ENET */ = CORE_PERIPH_ENET,
    function_i2c /*! I2C */ = CORE_PERIPH_I2C,
    function_i2s /*! I2S */ = CORE_PERIPH_I2S,
    function_mem /*! External memory interface */ = CORE_PERIPH_MEM,
    function_rtc /*! RTC */ = CORE_PERIPH_RTC,
    function_cec /*! Consumer Electronic Control (Part of HDMI) */
    = CORE_PERIPH_CEC,
    function_qei /*! Quadrature Encoder Interface */ = CORE_PERIPH_QEI,
    function_pwm /*! PWM */ = CORE_PERIPH_PWM,
    function_pio /*! GPIO */ = CORE_PERIPH_PIO,
    function_tmr /*! Timer (output compare and input capture) */
    = CORE_PERIPH_TMR,
    function_eint /*! External interrupts */ = CORE_PERIPH_EINT,
    function_wdt /*! Watch dog timer */ = CORE_PERIPH_WDT,
    function_bod /*! Brown out detection */ = CORE_PERIPH_BOD,
    function_dma /*! Direct Memory Access */ = CORE_PERIPH_DMA,
    function_jtag /*! JTAG */ = CORE_PERIPH_JTAG,
    function_reset /*! Reset */ = CORE_PERIPH_RESET,
    function_clkout /*! Clockout */ = CORE_PERIPH_CLKOUT,
    function_lcd /*! LCD */ = CORE_PERIPH_LCD,
    function_lcd1 /*! LCD */ = CORE_PERIPH_LCD1,
    function_lcd2 /*! LCD */ = CORE_PERIPH_LCD2,
    function_lcd3 /*! LCD */ = CORE_PERIPH_LCD3,
    function_emc /*! External Memory Controller */ = CORE_PERIPH_EMC,
    function_mci /*! Multimedia Card Interface */ = CORE_PERIPH_MCI,
    function_ssp /*! SSP */ = CORE_PERIPH_SSP,
    function_mcpwm /*! Motor Control PWM */ = CORE_PERIPH_MCPWM,
    function_nmi /*! Non-maskable Interrupt */ = CORE_PERIPH_NMI,
    function_trace /*! Trace data */ = CORE_PERIPH_TRACE,
  };
};

/*!
 * \brief The Core Info class
 */
class CoreInfo : public api::InfoObject, public CoreFlags {
public:
  /*! \details Constructs an empty Core Info object. */
  CoreInfo() { memset(&m_info, 0, sizeof(m_info)); }

  /*! \details Constructs a Core Info object from a core_info_t data structure.
   */
  explicit CoreInfo(const core_info_t &info) : m_info(info) {}

  /*! \details Returns the events that are supported by the core. */
  u32 o_events() const { return m_info.o_events; }
  /*! \details Returns the flags that are supported by the core. */
  u32 o_flags() const { return m_info.o_flags; }

  bool is_software_reset() const {
    return (o_flags() & (flag_is_reset_software | flag_is_reset_system)) != 0;
  }

  bool is_power_on_reset() const {
    return (o_flags() & flag_is_reset_power_on) != 0;
  }

  bool is_external_reset() const {
    return (o_flags() & flag_is_reset_external) != 0;
  }

  bool is_watchdog_timer_reset() const {
    return (o_flags() & flag_is_reset_watchdog) != 0;
  }

  bool is_brown_out_reset() const {
    return (o_flags() & flag_is_reset_brown_out) != 0;
  }

  /*! \details Returns the serial number of the MCU. */
  sys::SerialNumber serial_number() const {
    return sys::SerialNumber(m_info.serial);
  }

private:
  core_info_t m_info;
};

class CoreAttributes : public PeriphAttributes<core_attr_t>, public CoreFlags {
public:
private:
};

/*! \brief Core Class
 * \details This is the Core class.  It is used to
 * access core MCU information such as clock speed and
 * to adjust interrupt priorities.
 *
 * Here is an example of how to read the MCU serial number:
 *
 * \code
 * #include <sapi/hal.hpp>
 * #include <cstdio>
 *
 * int main(int argc, char * argv[]){
 * 	int i;
 * 	Core core(0);
 * 	core_attr_t attr;
 * 	core.open();
 * 	core.get_attr(&attr);
 * 	printf("Serial Number is:");
 * 	for(i=3; i >= 0; i--){
 * 		printf("%X", attr.serial_number[i]);
 * 	}
 * 	printf("\n");
 * 	core.close(); //core is never "powered-down" but this frees the file
 * descriptor
 * }
 * \endcode
 *
 */
class Core : public Periph<
               core_info_t,
               core_attr_t,
               CoreAttributes,
               CORE_IOC_IDENT_CHAR>,
             public CoreFlags {
public:
  /*! \details Contructs a new core object using the specified port.
   *
   * @param port The core port (zero for all single core devices)
   */
  explicit Core(port_t port);

  /*! \details Changes pin functionality using a core_pinfunc_t structure. */
  int set_pin_function(const core_pinfunc_t &req);

  /*! \details Changes pin function.
   *
   * @param port The PIO port
   * @param pin The PIO pin number
   * @param func The function (e.g. Core::UART)
   * @param func_port The functional port (e.g. 0 for UART0)
   * @return Zero on success
   *
   * This can be used if the default pinassign values are not adequate for your
   * application.
   *
   */
  int set_pin_function(mcu_pin_t pin, enum func func, u8 port) {
    core_pinfunc_t f;
    f.io.port = pin.port;
    f.io.pin = pin.pin;
    f.periph_func = func;
    f.periph_port = port;
    return set_pin_function(f);
  }

  static CoreInfo get_info();

  /*! \details Loads the MCU board configuration data
   * provided by the board support package.
   *
   * @param config A reference to the destination data
   * @return Zero on success
   */
  int get_mcu_board_config(mcu_board_config_t &config);

  /*! \details Sets the core CPU clock divider.
   *
   * @param value The amount to divide the clock by
   * @return Zero on success
   *
   * This method will change the CPU clock speed (if supported). If
   * the native clock speed is 120MHz the following code will make
   * it 60MHz
   *
   * \code
   * Core core(0);
   * core.open();
   * core.set_clock_divide(2); //set to 60MHz
   * core.set_clock_divide(1); //restore to 120MHz
   * core.close();
   * \endcode
   *
   */
  int set_clock_divide(u32 value);

  /*! \details Resets the device. */
  void reset();

  /*! \details Invokes the device's bootloader. If no bootloader is available, a
   * normal reset will occur.
   */
  void invoke_bootloader();

private:
};

} // namespace hal

#endif /* SAPI_HAL_CORE_HPP_ */
