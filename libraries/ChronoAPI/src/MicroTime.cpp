/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.
//Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc

#include <unistd.h>

#include "chrono/MicroTime.hpp"
#include "printer/Printer.hpp"
#include "var/StackString.hpp"

printer::Printer &
printer::operator<<(printer::Printer &printer, const chrono::MicroTime &a) {
  printer.key(
    "duration",
    var::NumberString(a.microseconds(), F32U "us").string_view());
  return printer;
}

void chrono::wait(const chrono::MicroTime &duration) {
  API_RETURN_IF_ERROR();
  chrono::MicroTime period = duration;
  u32 seconds = period.seconds();
  if (seconds > 0) {
    ::sleep(seconds);
    period = period - MicroTime(period.seconds() * 1000000UL);
  }
  ::usleep(period.microseconds());
}

chrono::MicroTime &chrono::MicroTime::wait() {
  chrono::wait(*this);
  return *this;
}
