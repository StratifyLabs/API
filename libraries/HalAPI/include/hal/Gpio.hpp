/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.

#ifndef SAPI_HAL_PIO_HPP_
#define SAPI_HAL_PIO_HPP_

#include <sos/dev/pio.h>

#include "Device.hpp"

namespace hal {

class GpioFlags {
public:
  enum class Flags {
    set_input /*! Sets the pinmask as input */ = PIO_FLAG_SET_INPUT,
    set_output /*! Sets the pinmask as output */ = PIO_FLAG_SET_OUTPUT,
    is_pullup /*! When setting as input, enables the pullup */
    = PIO_FLAG_IS_PULLUP,
    is_pulldown /*! When setting as input, enables the pulldown */
    = PIO_FLAG_IS_PULLDOWN,
    is_repeater /*! When setting as input, enables repeater mode (if
                        available) */
    = PIO_FLAG_IS_REPEATER,
    is_float /*! When setting as input, enables floating mode (no pullup or
                     pulldown) */
    = PIO_FLAG_IS_FLOAT,
    is_speed_low /*! When setting as output, enables low speed mode */
    = PIO_FLAG_IS_SPEED_LOW,
    is_speed_medium /*! When setting as output, enables medium speed mode
                     */
    = PIO_FLAG_IS_SPEED_MEDIUM,
    is_speed_high /*! When setting as output, enables high speed mode */
    = PIO_FLAG_IS_SPEED_HIGH,
    is_speed_blazing /*! When setting as output, enables blazing speed mode
                      */
    = PIO_FLAG_IS_SPEED_BLAZING,
    is_opendrain /*! When setting as output, enables open drain mode */
    = PIO_FLAG_IS_OPENDRAIN,
    is_hysteresis /*! When setting as input, enables hysteresis */
    = PIO_FLAG_IS_HYSTERESIS,
    is_direction_only /*! When set, only affects the direction withouth
                              setting other attributes */
    = PIO_FLAG_IS_DIRONLY,
    is_analog /*! When setting as input, sets pin as analog mode */
    = PIO_FLAG_IS_ANALOG,
    is_invert /*! See \ref PIO_FLAG_IS_INVERT */ = PIO_FLAG_IS_INVERT,
    is_filter /*! See \ref PIO_FLAG_IS_FILTER */ = PIO_FLAG_IS_FILTER,
    set /*! Assigns the value of the port to one if the corresponding bit
                in the pin mask is set. */
    = PIO_FLAG_SET,
    clear /*! Assigns the value of the port to zero if the corresponding
                  bit in the pin mask is set. */
    = PIO_FLAG_CLEAR,
    assign /*! Assigns the value of the port to the value of the pin mask.
            */
    = PIO_FLAG_ASSIGN
  };
};

API_OR_NAMED_FLAGS_OPERATOR(GpioFlags, Flags)

class Gpio : public DeviceType<I_PIO_GETVERSION>, public GpioFlags {
public:
  class Attributes {
  public:
    Attributes(Flags o_flags, u32 o_pinmask) {
      set_flags(o_flags);
      set_pinmask(o_pinmask);
    }

    Flags o_flags() const { return static_cast<Flags>(m_attributes.o_flags); }
    u32 o_pinmask() const { return m_attributes.o_pinmask; }

    Attributes &set_flags(Flags value) {
      m_attributes.o_flags = static_cast<u32>(value);
      return *this;
    }
    Attributes &set_pinmask(u32 value) {
      m_attributes.o_pinmask = value;
      return *this;
    }

  private:
    friend class Gpio;
    pio_attr_t m_attributes;
  };

  static Device::Ioctl set_mask(u32 mask) {
    return Device::Ioctl()
      .set_request(I_PIO_SETMASK)
      .set_argument(MCU_INT_CAST(mask));
  }

  static Device::Ioctl clear_mask(u32 mask) {
    return Device::Ioctl()
      .set_request(I_PIO_CLRMASK)
      .set_argument(MCU_INT_CAST(mask));
  }

  static Device::Ioctl assign(u32 value) {
    Attributes a(Flags::assign, value);
    return Device::Ioctl().set_request(I_PIO_SET).set_argument(
      &a.m_attributes);
  }

  static Device::Ioctl set_value(u32 value) {
    return Device::Ioctl().set_request(I_PIO_SET).set_argument(
      MCU_INT_CAST(value));
  }

  static Device::Ioctl get_value() {
    return Device::Ioctl().set_request(I_PIO_GET);
  }

  static u32 get_value(Device &device) {
    return device.ioctl(get_value()).return_value();
  }

private:
};

} // namespace hal

namespace printer {
Printer &operator<<(Printer &printer, const hal::Gpio::Attributes &a);
} // namespace printer

#endif /* SAPI_HAL_PIO_HPP_ */
