/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.
//Copyright 2011-2018 Tyler Gilbert; All Rights Reserved

#include "hal/Emc.hpp"

using namespace hal;

Emc::Emc(port_t port) : Periph(CORE_PERIPH_EMC, port){}
Emc_psram::Emc_psram(port_t port) : Emc(port){}
Emc_ahb::Emc_ahb(port_t port) : Emc(port){}



