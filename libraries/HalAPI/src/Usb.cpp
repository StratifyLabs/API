/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.
//Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc


#include "hal/Usb.hpp"
using namespace hal;

Usb::Usb(port_t port) : Periph(CORE_PERIPH_USB, port){}


int Usb::reset() const {
	usb_attr_t attr;
	attr.o_flags = Usb::flag_reset;
	return set_attributes(attr);
}

int Usb::attach() const {
	usb_attr_t attr;
	attr.o_flags = Usb::flag_attach;
	return set_attributes(attr);
}

int Usb::configure() const {
	usb_attr_t attr;
	attr.o_flags = Usb::flag_configure;
	return set_attributes(attr);
}

int Usb::detach() const {
	usb_attr_t attr;
	attr.o_flags = Usb::flag_detach;
	return set_attributes(attr);
}

int Usb::disable_endpoint(int ep) const {
	usb_attr_t attr;
	attr.o_flags = flag_disable_endpoint;
	attr.address = ep;
	return set_attributes(attr);
}

int Usb::enable_endpoint(int ep) const {
	usb_attr_t attr;
	attr.o_flags = flag_enable_endpoint;
	attr.address = ep;
	return set_attributes(attr);
}

bool Usb::is_connected() const {
	return ioctl(IoRequest(I_USB_ISCONNECTED));
}

int Usb::reset_endpoint(int ep) const {
	usb_attr_t attr;
	attr.o_flags = flag_reset_endpoint;
	attr.address = ep;
	return set_attributes(attr);
}

int Usb::set_addr(int addr) const {
	usb_attr_t attr;
	attr.o_flags = flag_set_address;
	attr.address = addr;
	return set_attributes(attr);
}

int Usb::stall_endpoint(int ep) const {
	usb_attr_t attr;
	attr.o_flags = flag_stall_endpoint;
	attr.address = ep;
	return set_attributes(attr);
}

int Usb::unstall_endpoint(int ep) const {
	usb_attr_t attr;
	attr.o_flags = flag_unstall_endpoint;
	attr.address = ep;
	return set_attributes(attr);
}
