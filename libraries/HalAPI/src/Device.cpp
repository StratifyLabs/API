/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
// Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc

#include "hal/Device.hpp"

using namespace hal;

Device::Device(
  var::StringView path,
  fs::OpenMode open_mode FSAPI_LINK_DECLARE_DRIVER_LAST)
  : FileAccess(path, open_mode FSAPI_LINK_INHERIT_DRIVER_LAST) {
  set_keep_open(true);
}

#ifndef __link
const Device &Device::read(fs::Aio &aio) const {
  API_RETURN_VALUE_IF_ERROR(*this);
  aio.m_aio_var.aio_fildes = fileno();
  API_SYSTEM_CALL("", ::aio_read(&(aio.m_aio_var)));
  return *this;
}

const Device &Device::write(fs::Aio &aio) const {
  API_RETURN_VALUE_IF_ERROR(*this);
  aio.m_aio_var.aio_fildes = fileno();
  API_SYSTEM_CALL("", ::aio_write(&(aio.m_aio_var)));
  return *this;
}

const Device &Device::cancel_read(int channel) const {
  return cancel(channel, MCU_EVENT_FLAG_DATA_READY);
}

const Device &Device::cancel_write(int channel) const {
  return cancel(channel, MCU_EVENT_FLAG_WRITE_COMPLETE);
}

const Device &Device::cancel(int channel, int o_events) const {
  mcu_action_t action;
  memset(&action, 0, sizeof(action));
  action.channel = channel;
  action.o_events = o_events;
  return ioctl(I_MCU_SETACTION, &action);
}

const Device &Device::transfer(const Transfer &options) const {
  fs::Aio aio(options.destination());
  read(aio).write(options.source());
  while (aio.is_busy() && status().is_success()) {
    // aio must live until the read completes -- or big problems will happen
    chrono::wait(chrono::MicroTime(200));
  }
  return *this;
}

#endif

const Device &Device::set_interrupt_priority(int priority, int request) const {
  mcu_action_t action;
  memset(&action, 0, sizeof(action));
  action.o_events = MCU_EVENT_FLAG_SET_PRIORITY;
  action.prio = priority;
  return ioctl(request, &action);
}
