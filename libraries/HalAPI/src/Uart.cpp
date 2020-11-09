/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
// Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc

#include "hal/Uart.hpp"
#include "printer/Printer.hpp"

printer::Printer &
printer::operator<<(printer::Printer &printer, const hal::Uart::Attributes &a) {  
  printer.key("frequency", var::NumberToString(a.frequency()));
  printer.key("width", var::NumberToString(a.width()));
  printer.key("rx", var::String().format("%d.%d", a.rx().port, a.rx().pin));
  printer.key("tx", var::String().format("%d.%d", a.tx().port, a.tx().pin));
  printer.key("rts", var::String().format("%d.%d", a.rts().port, a.rts().pin));
  printer.key("cts", var::String().format("%d.%d", a.cts().port, a.cts().pin));
  return printer;
}

printer::Printer &
printer::operator<<(printer::Printer &printer, const hal::Uart::Info &a) {
  printer.key("valid", a.is_valid());
  printer.key("sizeReady", var::NumberToString(a.size_ready()));
  printer.key("size", var::NumberToString(a.size()));
  return printer;
}

