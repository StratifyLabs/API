/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.

#ifndef SAPI_HAL__PERIPH_HPP_
#define SAPI_HAL__PERIPH_HPP_

#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <signal.h>
#include <sos/link.h>

#include "Device.hpp"

namespace hal {

/*! \brief Periph Object Class
 * \details This class handles general peripheral IO. It re-implments
 * open(), close(), read(), write(), ioctl() in order to manage
 * the file descriptors for MCU peripherals.
 *
 */
class PeriphObject : public Device {
public:
  /*! \details Defines the type to use when specifying a peripheral port. */
  typedef unsigned int port_t;

  /*!  \details This method opens the peripheral.  For each instance, the
   * peripheral only needs to be opened one time.  The port is typically opened
   * with open() and configured with set_attr().  After that, other instances of
   * the peripheral can read and write without opening again.
   */
  int open(const fs::OpenMode &flags = fs::OpenMode::read_write());
  int ioctl(IoRequest request, IoArgument argument) const override;
  int seek(int location, PeriphObject::whence whence) const override;
  int fileno() const;

  int open(const var::String &name, const fs::OpenMode &flags) override;

  int interface_read(void *buf, int size) const override;

  int interface_write(const void *buf, int size) const override;

#ifndef __link
  int read(fs::Aio &aio) const;
  int write(fs::Aio &aio) const;
#endif
  int close() override;

  using Device::ioctl;
  using Device::read;
  using Device::write;

protected:
  u16 m_periph_port;

  using Device::open;

  void update_fileno() const;
  int lookup_fileno() const;

private:
  static u16 m_fd_map[LINK_OPEN_MAX];
};

template <typename attr_t> class PeriphAttributes {
public:
  PeriphAttributes() : m_port(0) { m_attr = {0}; }

  /*! \details Accesses the value of the port. */
  u8 port() const { return m_port; }

  /*! \details Sets the value of the port. */
  PeriphAttributes &set_port(u8 port) {
    m_port = port;
    return *this;
  }

  /*! \details Accesses the value of the flags. */
  u32 o_flags() const { return m_attr.o_flags; }

  /*! \details Sets the value of the flags. */
  PeriphAttributes &set_flags(u32 o_flags) {
    m_attr.o_flags = o_flags;
    return *this;
  }

  /*! \details Access the frequency in hertz (bits/second). */
  u32 frequency() const { return m_attr.freq; }
  u32 freq() const { return frequency(); }

  /*! \details Set the frequency.
   *
   * @param freq_hz The frequency in Hertz (bits/second)
   */
  PeriphAttributes &set_frequency(u32 freq_hz) {
    m_attr.freq = freq_hz;
    return *this;
  }
  PeriphAttributes &set_freq(u32 freq_hz) {
    set_frequency(freq_hz);
    return *this;
  }

  const attr_t &attributes() const { return m_attr; }
  attr_t &attributes() { return m_attr; }

  attr_t *operator->() { return &m_attr; }
  const attr_t *operator->() const { return &m_attr; }

protected:
  attr_t m_attr;

private:
  u8 m_port;
};

template <typename attr_t, typename pin_assignment_t>
class PinAssignmentPeriphAttributes : public PeriphAttributes<attr_t> {
public:
  PinAssignmentPeriphAttributes() {
    memset(
      &PeriphAttributes<attr_t>::m_attr.pin_assignment,
      0xff,
      sizeof(pin_assignment_t));
  }

  /*! \details Gets a pointer of the pin assignment. */
  const pin_assignment_t *pin_assignment() const {
    return &PeriphAttributes<attr_t>::m_attr.pin_assignment;
  }

  PinAssignmentPeriphAttributes &operator<<(const pin_assignment_t &a) {
    memcpy(
      &PeriphAttributes<attr_t>::m_attr.pin_assignment,
      &a,
      sizeof(pin_assignment_t));
    return *this;
  }
};

/*! \brief Peripheral Class
 * \details This is an abstract class for a microcontroller peripheral.
 *
 * All peripherals have a common interface based on the following function:
 * - open()
 * - close()
 * - read()
 * - write()
 * - ioctl()
 *
 * The classes that inherit Periph implement a method for each ioctl() call
 * available on the peripheral.  For example, the UART has an ioctl request
 * called I_UART_SETATTR so the method Uart::set_attr() implements the ioctl
 * request.
 *
 */
template <
  typename info_t,
  typename attr_t,
  typename AttributesClass,
  char ident_char>
class Periph : public PeriphObject {
public:
  /*!
   * \details Constructs an MCU peripheral object
   * \param periph Core peripheral value
   * \param port Port number
   *
   * If the peripheral has been opened by another
   * object, the file descriptor from that object
   * will be used with this object as well.
   *
   */
  Periph(core_periph_t periph, port_t port) {
    m_periph_port = (periph << 8) | port;
    set_fileno(lookup_fileno());
  }

  /*! \details Gets the version of the peripheral driver.
   *
   * @return The BCD version of the driver
   *
   * The version is a 24-bit BCD value. For example, 0x010203 is
   * version 1.2.3 where:
   *
   * - 1 is the major version
   * - 2 is the minor version
   * - 3 is the patch version
   *
   * If the major version of the driver is not the same as the major version of
   * the driver interface header in the SDK, there will be problems using the
   * hardware.
   *
   * Here is a code sample using a Pwm object (which inherits this object)
   *
   * \code
   * #include <sapi.hal.hpp>
   *
   * Pwm pwm(1); //pwm inherits this object
   * pwm.open();
   * if( (pwm.get_version()) >> 16 != (PWM_VERSION >>16) ){
   *  printf("Major versions are not the same\n");
   * } else {
   *  printf("Major versions match\n");
   * }
   * \endcode
   *
   */
  int get_version() const {
    return ioctl(IoRequest(_IOCTL(ident_char, I_MCU_GETVERSION)));
  }

  /*! \details Gets the peripheral info.
   *
   * @param info A reference to the info object that will be written.
   * @return Zero on success, less than one for an error
   *
   */
  int get_info(info_t &info) const {
    return ioctl(
      IoRequest(_IOCTLR(ident_char, I_MCU_GETINFO, info_t)),
      IoArgument(&info));
  }

  /*! \details Sets the default attributes on the hardware.
   *
   * @return Zero on success
   *
   * For this method to work correctly, the board support package
   * must include the configuration information for the device.
   * If the information is not provided, this method will return an error.
   *
   * The system should set the error number to ENOSYS if
   * no default attributes are provided.
   *
   */
  int set_attributes() const {
    return ioctl(IoRequest(_IOCTLW(ident_char, I_MCU_SETATTR, attr_t)));
  }

  /*! \details Initializes the hardware using the default attributes.
   *
   * @return Less than zero on an error.
   *
   * The system should set the error number to ENOSYS if
   * no default attributes are provided.
   *
   */
  int initialize() {
    int result = open();
    if (result < 0) {
      return result;
    }
    return set_attributes();
  }

  /*! \details Initializes the peripheral using the provided attributes
   *
   */
  int initialize(const AttributesClass &attributes) {
    int result = open();
    if (result < 0) {
      return result;
    }
    return set_attributes(attributes);
  }

  /*! \details Sets the peripheral attributes based on the attributes passed.
   *
   * @param attributes A const reference to the attributes used to apply to the
   * peripheral.
   * @return Zero on success or less than zero for an error
   *
   * \code
   * UartAttributes uart_attributes; //default attributes
   * uart_attributes.set_frequency(9600);
   *
   * Uart uart(0);
   * uart.open();
   * uart.set_attributes(uart_attributes);
   *
   * \endcode
   *
   *
   */
  int set_attributes(const AttributesClass &attributes) const {
    return set_attributes(attributes.attributes());
  }

  /*! \details Applies the given attributes to the peripheral.
   *
   * Use error_number() to see if the operation was successful.
   *
   */
  Periph &operator<<(const AttributesClass &attributes) const {
    set_attributes(attributes);
    return *this;
  }

  int set_attributes(const attr_t &attr) const {
    return ioctl(
      IoRequest(_IOCTLW(ident_char, I_MCU_SETATTR, attr_t)),
      IoConstArgument(&attr));
  }

  int set_action(const mcu_action_t &action) const {
    return ioctl(
      IoRequest(_IOCTLW(ident_char, I_MCU_SETACTION, mcu_action_t)),
      IoConstArgument(&action));
  }

  Periph &operator<<(const mcu_action_t &action) {
    set_action(action);
    return *this;
  }

  /*! \details Sets the action callback for the event.
   *
   * @param channel
   * @param o_events
   * @param prio
   * @param callback
   * @param context
   * @return
   */

  int set_action(
    Channel channel,
    Events o_events,
    InterruptPriority priority = InterruptPriority(0),
    McuCallback callback = McuCallback(nullptr),
    Context context = Context(nullptr)) const {
    mcu_action_t action;
    action.prio = priority.argument();
    action.channel = channel.argument();
    action.o_events = o_events.argument();
    action.handler.callback = callback.argument();
    action.handler.context = context.argument();
    return set_action(action);
  }

  /*! \details Adjusts the priority of the hardware interrupt for the MCU
   * peripheral.
   *
   * @return Zero on success
   */
  int set_priority(
    InterruptPriority priority,
    Events o_events,
    Channel channel = Channel(0)) {
    return set_action(
      channel,
      Events(o_events.argument() | MCU_EVENT_FLAG_SET_PRIORITY),
      priority);
  }

  port_t port() const { return m_periph_port & 0xFF; }

protected:
  int set_channel(const mcu_channel_t &channel, int request) const {
    return ioctl(
      IoRequest(_IOCTLR(ident_char, request, mcu_channel_t)),
      IoConstArgument(&channel));
  }

  int set_channel(u32 loc, u32 value, const IoRequest request) const {
    mcu_channel_t channel;
    channel.loc = loc;
    channel.value = value;
    return ioctl(request, IoArgument(&channel));
  }

  int set_channel(const ChannelOptions &options, int request) {
    return set_channel(options.location(), options.value(), IoRequest(request));
  }

  u32 get_channel(u32 loc, const IoRequest request) const {
    mcu_channel_t channel;
    channel.loc = loc;
    if (ioctl(request, IoArgument(&channel)) < 0) {
      return static_cast<u32>(-1);
    }
    return channel.value;
  }
};

} // namespace hal

#endif /* SAPI_HAL__PERIPH_HPP_ */
