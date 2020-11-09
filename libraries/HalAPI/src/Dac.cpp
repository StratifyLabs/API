/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.
//Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc

#include <unistd.h>
#include <fcntl.h>
#include "hal/Dac.hpp"
#include <stdlib.h>

using namespace hal;

Dac::Dac(port_t port) : Periph(CORE_PERIPH_DAC, port){}


