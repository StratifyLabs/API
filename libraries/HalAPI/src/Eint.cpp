/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.
//Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc




#include <unistd.h>
#include <fcntl.h>
#include "hal/Eint.hpp"
using namespace hal;

Eint::Eint(port_t port) : Periph(CORE_PERIPH_EINT, port){}
