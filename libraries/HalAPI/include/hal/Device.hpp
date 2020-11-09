/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.

#ifndef SAPI_HAL_DEVICE_HPP_
#define SAPI_HAL_DEVICE_HPP_

#include "DeviceSignal.hpp"
#include "fs/Aio.hpp"
#include "fs/File.hpp"

namespace hal {

/*! \brief Device Class
 * \details This is a device class used for accessing MCU peripherals and
 * other devices.
 *
 * - MCU peripheral hardware (most devices have a class that inherits this
 * class)
 * - Devices with built-in drivers (see "/dev" folder on the device)
 *
 * \code
 * #include <sapi/hal.hpp>
 *
 * int main(int argc, char * argv[]){
 *   char buffer[16];
 *   Device device;
 *   device.open("/dev/fifo", Device::RDWR); //open the system fifo (if it
 * exists) device.read(0, buffer, 16);             //read 16 bytes from channel
 * (location) 0 device.close();                         //close the SPI (power
 * it off) return 0;
 * }
 * \endcode
 *
 */
class Device : public fs::FileAccess<Device> {
public:
  class Channel {
    API_ACCESS_FUNDAMENTAL(Channel, u32, location, 0);
    API_ACCESS_FUNDAMENTAL(Channel, u32, value, 0);
  };

  using fs::FileAccess<Device>::ioctl;

  /*! \details Constructs a Device.
   *
   * Unlike fs::File, upon creation the
   * is_close_on_destruct() flag is cleared for
   * all devices (and hal::Periph). In
   * order to close a device, close() must
   * be called explicitly.
   *
   * This is the desired behavior because
   * it is common to create more than one hal::Device
   * object to access the same hardware in different contexts.
   *
   */
  Device(
    var::StringView path,
    fs::OpenMode open_mode
    = fs::OpenMode::read_write() FSAPI_LINK_DECLARE_DRIVER_NULLPTR_LAST);

  const Device &
  set_interrupt_priority(int priority, int request = I_MCU_SETACTION) const;

#if !defined __link
  /*! \details Configures the device to send a signal when an event happens.
   *
   * @param signal The signal to send
   * @param o_events A bitmask of events which will cause the signal to be sent
   * @param channel The hardware channel to listen for events on
   *
   */
  const Device &set_signal_action(
    const DeviceSignal &signal,
    const DeviceSignal::CreateAction &options) {
    mcu_action_t action = signal.create_action(options);
    return ioctl(I_MCU_SETACTION, &action);
  }

  /*! \details Reads the device asynchronously.
   *
   * @param aio A reference to the fs::Aio object to use for reading
   *
   * \sa fs::Aio
   */
  const Device &read(fs::Aio &aio) const;

  /*! \details Writes the device asynchronously.
   *
   * @param aio A reference to the fs::Aio object to use for writing
   *
   * \sa fs::Aio
   */
  const Device &write(fs::Aio &aio) const;

  using fs::FileAccess<Device>::read;
  using fs::FileAccess<Device>::write;

  const Device &cancel_read(int channel = 0) const;
  const Device &cancel_write(int channel = 0) const;
  const Device &cancel(int channel, int o_events) const;

  class Transfer {
    API_AC(Transfer, var::View, source);
    API_AC(Transfer, var::View, destination);
  };

  const Device &transfer(const Transfer &options) const;

#endif

protected:
};

template <int VersionRequest> class DeviceType {
public:
  static int get_version(const Device &device) {
    return device.ioctl(VersionRequest, nullptr).return_value();
  }
};

} // namespace hal

#endif /* SAPI_HAL_DEVICE_HPP_ */
