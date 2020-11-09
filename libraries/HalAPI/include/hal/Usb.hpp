/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.

#ifndef SAPI_HAL_USB_HPP_
#define SAPI_HAL_USB_HPP_

#include <sos/dev/usb.h>
#include "PinAssignment.hpp"
#include "Periph.hpp"

namespace hal {

class UsbFlags {
public:
	enum flags {
		flag_set_unconfigured= USB_FLAG_SET_UNCONFIGURED,
		flag_set_device = USB_FLAG_SET_DEVICE,
		flag_set_host = USB_FLAG_SET_HOST,
		flag_set_otg = USB_FLAG_SET_OTG,
		flag_reset = USB_FLAG_RESET,
		flag_attach = USB_FLAG_ATTACH,
		flag_detach = USB_FLAG_DETACH,
		flag_configure = USB_FLAG_CONFIGURE,
		flag_unconfigure = USB_FLAG_UNCONFIGURE,
		flag_set_address = USB_FLAG_SET_ADDRESS,
		flag_reset_endpoint = USB_FLAG_RESET_ENDPOINT,
		flag_enable_endpoint = USB_FLAG_ENABLE_ENDPOINT,
		flag_disable_endpoint = USB_FLAG_DISABLE_ENDPOINT,
		flag_stall_endpoint = USB_FLAG_STALL_ENDPOINT,
		flag_unstall_endpoint = USB_FLAG_UNSTALL_ENDPOINT,
		flag_configure_endpoint = USB_FLAG_CONFIGURE_ENDPOINT
	};
};


/*! \brief USB Pin Assignment
 * \details This class allows simple manipulation of the usb_pin_assignment_t.
 */
class UsbPinAssignment : public PinAssignment<usb_pin_assignment_t>{};

class UsbAttributes :
		public PinAssignmentPeriphAttributes<usb_attr_t, usb_pin_assignment_t>,
		public UsbFlags {

};

/*! \brief USB Class
 * \details This class implements a USB transceiver.
 */
class Usb :
		public Periph<usb_info_t, usb_attr_t, UsbAttributes, 'u'>,
		public UsbFlags {
public:
	Usb(port_t port);

	int reset() const;
	int attach() const;
	int configure() const;
	int detach() const;
	int disable_endpoint(int ep) const;
	int enable_endpoint(int ep) const;
	bool is_connected() const;
	int reset_endpoint(int ep) const;
	int set_addr(int addr) const;
	int stall_endpoint(int ep) const;
	int unstall_endpoint(int ep) const;

private:

};

}

#endif /* SAPI_HAL_USB_HPP_ */
