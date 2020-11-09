/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.
// Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc

#include "hal/Gpio.hpp"

#include "printer/Printer.hpp"

using namespace hal;

printer::Printer &
printer::operator<<(printer::Printer &printer, const hal::Gpio::Attributes &a) {
  printer.key("flags", var::NumberToString(static_cast<u32>(a.o_flags())));
  printer.key("pinmask", var::NumberToString(a.o_pinmask()));
  return printer;
}
