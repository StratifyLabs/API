/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.
//Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc

#include "var/Ring.hpp"

#if USE_PRINTER
#include "sys/Printer.hpp"

using namespace sys;

Printer& sys::operator << (Printer& printer, const var::Ring<u32> & a){
	for(u32 i=0; i < a.count_ready(); i++){
		printer.key(nullptr, F32U, a.at(i));
	}
	return printer;
}

Printer& sys::operator << (Printer& printer, const var::Ring<s32> & a){
	for(u32 i=0; i < a.count_ready(); i++){
		printer.key(nullptr, F32D, a.at(i));
	}
	return printer;
}

Printer& sys::operator << (Printer& printer, const var::Ring<u16> & a){
	for(u32 i=0; i < a.count_ready(); i++){
		printer.key(nullptr, "%u", a.at(i));
	}
	return printer;
}

Printer& sys::operator << (Printer& printer, const var::Ring<s16> & a){
	for(u32 i=0; i < a.count_ready(); i++){
		printer.key(nullptr, "%d", a.at(i));
	}
	return printer;
}

Printer& sys::operator << (Printer& printer, const var::Ring<u8> & a){
	for(u32 i=0; i < a.count_ready(); i++){
		printer.key(nullptr, "%u", a.at(i));
	}
	return printer;
}

Printer& sys::operator << (Printer& printer, const var::Ring<s8> & a){
	for(u32 i=0; i < a.count_ready(); i++){
		printer.key(nullptr, "%d", a.at(i));
	}
	return printer;
}
#endif

namespace var {

int var_api_var_ring_unused;

} /* namespace var */
