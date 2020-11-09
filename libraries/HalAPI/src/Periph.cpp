/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
// Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "chrono/Timer.hpp"
#include "hal/Periph.hpp"

using namespace hal;
using namespace sys;

static const char *const periph_name[CORE_PERIPH_TOTAL] = {
  "resd" /* CORE_PERIPH_RESERVED RESERVED */,
  "core" /* CORE_PERIPH_CORE Core Functionality */,
  "adc" /* CORE_PERIPH_ADC Analog to Digital Converter */,
  "dac" /* CORE_PERIPH_DAC Digital to Analog Converter */,
  "uart" /* CORE_PERIPH_UART UART */,
  "spi" /* CORE_PERIPH_SPI SPI */,
  "usb" /* CORE_PERIPH_USB USB */,
  "can" /* CORE_PERIPH_CAN CAN */,
  "enet" /* CORE_PERIPH_ENET ENET */,
  "i2c" /* CORE_PERIPH_I2C I2C */,
  "i2s" /* CORE_PERIPH_I2S I2S */,
  "mem" /* CORE_PERIPH_MEM External memory interface */,
  "rtc" /* CORE_PERIPH_RTC RTC */,
  "cec" /* CORE_PERIPH_CEC Consumer Electronic Control (Part of HDMI) */,
  "qei" /* CORE_PERIPH_QEI Quadrature Encoder Interface */,
  "pwm" /* CORE_PERIPH_PWM PWM */,
  "pio" /* CORE_PERIPH_PIO GPIO */,
  "tmr" /* CORE_PERIPH_TMR Timer (output compare and input capture) */,
  "eint" /* CORE_PERIPH_EINT External interrupts */,
  "wdt" /* CORE_PERIPH_WDT Watch dog timer */,
  "bod" /* CORE_PERIPH_BOD Brown out detection */,
  "dma" /* CORE_PERIPH_DMA Direct Memory Access */,
  "jtag" /* CORE_PERIPH_JTAG JTAG */,
  "reset" /* CORE_PERIPH_RESET Reset */,
  "clkout" /* CORE_PERIPH_CLKOUT Clockout */,
  "lcd" /* CORE_PERIPH_LCD LCD */,
  "lcd" /* CORE_PERIPH_LCD1 LCD */,
  "lcd" /* CORE_PERIPH_LCD2 LCD */,
  "lcd" /* CORE_PERIPH_LCD3 LCD */,
  "emc" /* CORE_PERIPH_EMC External Memory Controller */,
  "mci" /* CORE_PERIPH_MCI Multimedia Card Interface */,
  "ssp" /* CORE_PERIPH_SSP SSP */,
  "mcpwm" /* CORE_PERIPH_MCPWM Motor Control PWM */,
  "nmi" /* CORE_PERIPH_NMI Non-maskable Interrupt */,
  "trace" /* CORE_PERIPH_TRACE Trace data */,
  "sys" /*! System data */,
  "qspi" /*! Quad SPI */,
  "usart" /*! USART */,
  "sdio" /*! SD Input/output */,
  "spdif" /*! SPDIF */,
  "hdmi" /*! HDMI CEC */,
  "mco" /*! MCO Pins */,
  "dfsdm" /*! DFSDM Pins */,
  "i2c" /*! I2C */,
  "dcmi" /*! Digital Camera interface */
};

u16 PeriphObject::m_fd_map[LINK_OPEN_MAX];

int PeriphObject::lookup_fileno() const {
  int i;
  for (i = 0; i < LINK_OPEN_MAX; i++) {
    if (m_fd_map[i] == m_periph_port) {
      return i;
    }
  }
  return -1;
}

void PeriphObject::update_fileno() const {
  if ((m_fd >= 0) && (m_fd_map[m_fd] == 0)) { // fd is no longer valid
    set_fileno(-1);                           // kill the fileno
  }
}

int PeriphObject::open(const var::String &name, const fs::OpenMode &flags) {
  // check map
  int fd;
  int ret;
  fd = lookup_fileno();
  if (fd < 0) {
    ret = Device::open(name, flags);
    if (m_fd >= 0) {
      m_fd_map[m_fd] = m_periph_port;
    } else {
      return ret;
    }
  } else {
    set_fileno(fd);
  }

  return 0;
}

int PeriphObject::open(const fs::OpenMode &flags) {
  char buffer[LINK_NAME_MAX];
  const char *name;
  u8 periph_type = m_periph_port >> 8;

  if (periph_type != CORE_PERIPH_RTC) { // RTC is at /dev/rtc (there can only be
                                        // one)
    if (m_periph_port != 0) {
      name = periph_name[periph_type];
      snprintf(
        buffer,
        LINK_NAME_MAX - 1,
        "/dev/%s%d",
        name,
        (m_periph_port & 0xff));
    } else {
      return -1;
    }
  } else {
    strncpy(buffer, "/dev/rtc", LINK_NAME_MAX - 1);
  }
  return open(buffer, flags);
}

int PeriphObject::close() {
  int ret = 0;
  update_fileno();
  if (m_fd >= 0) {
    m_fd_map[m_fd] = 0;
    Device::close();
    set_fileno(-1);
  }
  return ret;
}

int PeriphObject::read(void *buf, Size size) const {
  update_fileno();
  return File::read(buf, size);
}

int PeriphObject::write(const void *buf, Size size) const {
  update_fileno();
  return File::write(buf, size);
}

#ifndef __link
int PeriphObject::read(fs::Aio &aio) const {
  update_fileno();
  return Device::read(aio);
}

int PeriphObject::write(fs::Aio &aio) const {
  update_fileno();
  return Device::write(aio);
}
#endif

int PeriphObject::ioctl(IoRequest request, IoArgument argument) const {
  update_fileno();
  return Device::ioctl(request, argument);
}

int PeriphObject::seek(int location, enum whence whence) const {
  update_fileno();
  return Device::seek(location, whence);
}

int PeriphObject::fileno() const {
  update_fileno();
  return Device::fileno();
}
