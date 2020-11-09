/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.
//Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc


#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include "hal/I2C.hpp"
#include "printer/Printer.hpp"

using namespace hal;

printer::Printer &
printer::operator<<(printer::Printer &printer, const hal::I2C::Attributes &a) {
  printer.key("frequency", var::NumberToString(a.frequency()));
  printer.key("scl", var::String().format("%d.%d", a.scl().port, a.scl().pin));
  printer.key("sda", var::String().format("%d.%d", a.sda().port, a.sda().pin));
  return printer;
}

printer::Printer &
printer::operator<<(printer::Printer &printer, const hal::I2C::Info &a) {
  printer.key("frequency", var::NumberToString(a.frequency()));
  printer.key("error", var::NumberToString(a.error()));
  return printer;
}
