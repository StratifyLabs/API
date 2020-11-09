// Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for
// rights.

#include "hal/Spi.hpp"
#include "printer/Printer.hpp"

using namespace hal;

printer::Printer &
printer::operator<<(printer::Printer &printer, const hal::Spi::Attributes &a) {
  printer.key("frequency", var::NumberToString(a.frequency()));
  printer.key("width", var::NumberToString(a.width()));
  printer.key(
    "miso",
    var::String().format("%d.%d", a.miso().port, a.miso().pin));
  printer.key(
    "mosi",
    var::String().format("%d.%d", a.mosi().port, a.mosi().pin));
  printer.key("sck", var::String().format("%d.%d", a.sck().port, a.sck().pin));
  printer.key("cs", var::String().format("%d.%d", a.cs().port, a.cs().pin));
  return printer;
}

printer::Printer &
printer::operator<<(printer::Printer &printer, const hal::Spi::Info &a) {
  printer.key("flags", var::NumberToString(static_cast<u32>(a.o_flags())));
  printer.key("events", var::NumberToString(a.o_events()));
  return printer;
}
