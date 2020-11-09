/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.

#ifndef SAPI_HAL_I2C_HPP_
#define SAPI_HAL_I2C_HPP_

#include <sos/dev/i2c.h>

#include "Device.hpp"

namespace hal {

class I2CFlags {
public:
  enum class Flags {
    set_master /*! Operate as a master I2C bus */ = I2C_FLAG_SET_MASTER,
    set_slave /*! Operate as a slave (ignored if master is set) */
    = I2C_FLAG_SET_SLAVE,
    is_slave_ack_general_call /*! If slave operation, ack general call */
    = I2C_FLAG_IS_SLAVE_ACK_GENERAL_CALL,
    is_pullup /*! Enable internal pullups if available (ignore otherwise)
               */
    = I2C_FLAG_IS_PULLUP,
    prepare_ptr_data /*! This prepares the driver to write the ptr then
                             read/write data */
    = I2C_FLAG_PREPARE_PTR_DATA,
    is_ptr_16 /*! This prepares the driver to write a 16-bit ptr then
                      read/write data */
    = I2C_FLAG_IS_PTR_16,
    prepare_ptr /*! This will write the ptr value only without writing or
                        reading any data. */
    = I2C_FLAG_PREPARE_PTR,
    prepare_data /*! This will read/write data without first writing the
                         pointer information */
    = I2C_FLAG_PREPARE_DATA,
    is_slave_addr0 /*! If hardware supports multiple slave addrs, use the
                           first slot (default) */
    = I2C_FLAG_IS_SLAVE_ADDR0,
    is_slave_addr1 /*! If hardware supports multiple slave addrs, use the
                           second slot */
    = I2C_FLAG_IS_SLAVE_ADDR1,
    is_slave_addr2 /*! If hardware supports multiple slave addrs, use the
                           third slot */
    = I2C_FLAG_IS_SLAVE_ADDR2,
    is_slave_addr3 /*! If hardware supports multiple slave addrs, use the
                           fourth slot */
    = I2C_FLAG_IS_SLAVE_ADDR3,
    is_slave_ptr_8 /*! Use a 8-bit address pointer when accessing data
                           (default) */
    = I2C_FLAG_IS_SLAVE_PTR_8,
    is_slave_ptr_16 /*! Use a 16-bit address pointer when accessing data
                            (set automatically is size > 255) */
    = I2C_FLAG_IS_SLAVE_PTR_16,
    reset /*! Reset the state of the I2C */ = I2C_FLAG_RESET,
    is_stretch_clock = I2C_FLAG_STRETCH_CLOCK,
    is_no_stop /*! Don't issue a stop condition when complete (use with
                       I2C_FLAG_PREPARE_DATA) */
    = I2C_FLAG_IS_NO_STOP
  };

  enum error {
    error_none /*! No errors */ = I2C_ERROR_NONE,
    error_start /*! Error while starting */ = I2C_ERROR_START,
    error_write /*! Error while writing */ = I2C_ERROR_WRITE,
    error_ack /*! Ack Error (most common error for a mis-wired hardware) */
    = I2C_ERROR_ACK,
    error_stop /*! Error while stopping */ = I2C_ERROR_STOP,
    error_master_ack /*! The master could not create an ACK */
    = I2C_ERROR_MASTER_ACK,
    error_bus_busy /*! The Bus is busy (happens with multi-masters on bus) */
    = I2C_ERROR_BUS_BUSY,
    error_long_slew = I2C_ERROR_LONG_SLEW,
    error_arbitration_lost /*! Arbitration lost on multi-master bus */
    = I2C_ERROR_ARBITRATION_LOST
  };
};

API_OR_NAMED_FLAGS_OPERATOR(I2CFlags, Flags)

class I2C : public DeviceType<I_I2C_GETVERSION>, public I2CFlags {
public:
  class Attributes {
  public:
    Attributes() {
      set_flags(Flags::set_master);
      set_frequency(100000);
    }

    API_ACCESS_MEMBER_FUNDAMENTAL(
      Attributes,
      mcu_pin_t,
      attributes.pin_assignment,
      sda)

    API_ACCESS_MEMBER_FUNDAMENTAL(
      Attributes,
      mcu_pin_t,
      attributes.pin_assignment,
      scl)

    /*! \details Access the slave address value. */
    u8 slave_addr() const { return m_attributes.slave_addr[0].addr8[0]; }

    /*! \details Accesses the 16-bit slave address value. */
    u8 slave_addr16() const { return m_attributes.slave_addr[0].addr16; }

    Attributes &set_flags(Flags value) {
      m_attributes.o_flags = static_cast<u32>(value);
      return *this;
    }

    API_ACCESS_MEMBER_FUNDAMENTAL_WITH_ALIAS(
      Attributes,
      u32,
      attributes,
      frequency,
      freq)

    /*! \details Sets the 7-bit slave address value. */
    Attributes &set_slave_addr(u8 addr) {
      m_attributes.slave_addr[0].addr8[0] = addr;
      return *this;
    }

    /*! \details Sets the 16-bit slave address value. */
    Attributes &set_slave_addr16(u16 addr) {
      m_attributes.slave_addr[0].addr16 = addr;
      return *this;
    }

  private:
    friend class I2C;
    i2c_attr_t m_attributes;
  };

  class Info {
  public:
    Info() { m_info = {0}; }
    Info(const i2c_info_t &info) : m_info(info) {}
    API_ACCESS_MEMBER_FUNDAMENTAL_WITH_ALIAS(Info, u32, info, frequency, freq)
    API_READ_ACCESS_MEMBER_FUNDAMENTAL(Info, u32, info, o_events)
    API_ACCESS_MEMBER_FUNDAMENTAL_WITH_ALIAS(Info, u32, info, error, err)
    Flags o_flags() const { return static_cast<Flags>(m_info.o_flags); }

  private:
    friend class I2C;
    i2c_info_t m_info;
  };

  static Device::Ioctl
  prepare(u8 slave_addr, Flags o_flags = Flags::prepare_ptr_data) {
    Attributes attributes
      = Attributes().set_flags(o_flags).set_slave_addr(slave_addr);
    return Device::Ioctl()
      .set_request(I_I2C_SETATTR)
      .set_argument(&attributes.m_attributes);
  }

  static Device::Ioctl reset() {
    Attributes attributes = Attributes().set_flags(Flags::reset);
    return Device::Ioctl()
      .set_request(I_I2C_SETATTR)
      .set_argument(&attributes.m_attributes);
  }

  /*! \details Gets the last error. */
  static int get_error(Device &device) { return get_info(device).error(); }

  static Device::Ioctl get_info(Info &info) {
    return Device::Ioctl()
      .set_request(I_I2C_GETINFO)
      .set_argument(&info.m_info);
  }

  static Info get_info(Device &device) {
    Info info;
    device.ioctl(get_info(info));
    return info;
  }

  class ModifyRegister {
    API_AF(ModifyRegister, u32, location, 0);
    API_AF(ModifyRegister, u8, bit, 0);
    API_AF(ModifyRegister, bool, value, false);
  };

  static const Device &
  modify_register(const Device &device, const ModifyRegister &options) {
    u8 value;
    device.seek(options.location()).read(var::View(value));
    if (options.value()) {
      value |= (1 << options.bit());
    } else {
      value &= (1 << options.bit());
    }
    return device.seek(options.location()).write(var::View(value));
  }

private:
};

} // namespace hal

namespace printer {
Printer &operator<<(Printer &printer, const hal::I2C::Attributes &a);
Printer &operator<<(Printer &printer, const hal::I2C::Info &a);
} // namespace printer

#endif /* SAPI_HAL_I2C_HPP_ */
