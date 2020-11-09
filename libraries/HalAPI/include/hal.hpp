/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.

#ifndef SAPI_HAL_HPP_
#define SAPI_HAL_HPP_

/*! \brief Hardware Abstraction Layer
 * \details The hal namespace includes classes for accessing
 * mcu peripheral hardware and other devices.
 *
 * All objects in the hal namespace inherit either:
 *
 * - api::HalWorkObject
 * - api::InfoObject
 *
 * Work objects inherit fs::File and allow access to the hardware
 * using a POSIX style API (open(), close(), read(), write() and ioctl()).
 *
 * Info objects contain attributes that facilitate configuring and
 * querying hardware.
 *
 *
 *
 */
namespace hal {}

#include "hal/Dev.hpp"
#include "hal/Device.hpp"
#include "hal/DeviceSignal.hpp"
#include "hal/Adc.hpp"
#include "hal/Dac.hpp"
#include "hal/Drive.hpp"
#include "hal/Core.hpp"
#include "hal/Eint.hpp"
#include "hal/Fifo.hpp"
#include "hal/FFifo.hpp"
#include "hal/CFifo.hpp"
#include "hal/Led.hpp"
#include "hal/I2C.hpp"
#include "hal/I2S.hpp"
#include "hal/JsonAttributes.hpp"
#include "hal/PinAssignment.hpp"
#include "hal/StreamFFifo.hpp"
#include "hal/Pin.hpp"
#include "hal/Pwm.hpp"
#include "hal/Rtc.hpp"
#include "hal/Tmr.hpp"
#include "hal/Switchboard.hpp"
#include "hal/Spi.hpp"
#include "hal/Uart.hpp"
#include "hal/Usb.hpp"

#if !defined __link
#include "hal/Display.hpp"
#include "hal/DisplayDevice.hpp"
#include "hal/DeviceSignal.hpp"
#endif

using namespace hal;

#endif /* SAPI_HAL_HPP_ */
