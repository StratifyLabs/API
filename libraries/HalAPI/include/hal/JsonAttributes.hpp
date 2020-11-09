#ifndef SAPI_HAL_JSON_ATTRIBUTES_HPP
#define SAPI_HAL_JSON_ATTRIBUTES_HPP

#include "../var/Json.hpp"
#include "Pin.hpp"
#include "Uart.hpp"
#include "Spi.hpp"
#include "I2C.hpp"
#include "I2S.hpp"

namespace hal {

class SpiJsonAttributes : public var::JsonObject {
public:

	JSON_ACCESS_INTEGER(SpiJsonAttributes,port);
	JSON_ACCESS_INTEGER(SpiJsonAttributes,bitrate);
	JSON_ACCESS_INTEGER(SpiJsonAttributes,width);
	JSON_ACCESS_INTEGER(SpiJsonAttributes,mode);
	JSON_ACCESS_STRING(SpiJsonAttributes,format);
	JSON_ACCESS_STRING(SpiJsonAttributes,miso);
	JSON_ACCESS_STRING(SpiJsonAttributes,mosi);
	JSON_ACCESS_STRING(SpiJsonAttributes,sck);
	JSON_ACCESS_STRING(SpiJsonAttributes,cs);
};


class UartJsonAttributes : public var::JsonObject {
public:

	JSON_ACCESS_INTEGER(UartJsonAttributes,port);
	JSON_ACCESS_INTEGER(UartJsonAttributes,baudrate);
	JSON_ACCESS_INTEGER(UartJsonAttributes,width);
	JSON_ACCESS_STRING(UartJsonAttributes,parity);
	JSON_ACCESS_STRING_WITH_KEY(UartJsonAttributes,stopBits,stop_bits);
	JSON_ACCESS_STRING(UartJsonAttributes,rx);
	JSON_ACCESS_STRING(UartJsonAttributes,tx);
	JSON_ACCESS_STRING(UartJsonAttributes,rts);
	JSON_ACCESS_STRING(UartJsonAttributes,cts);

	UartAttributes get_attributes() const {
		UartAttributes result;

		result.set_port( get_port() );
		result.set_frequency(get_baudrate());
		result.set_flags( Uart::flag_set_line_coding );
		{
			var::String stop_bits = get_stop_bits();
			if( stop_bits == "0.5" ){
				result.set_flags( result.o_flags() | Uart::flag_is_stop0_5);
			} else if( stop_bits == "1.5" ){
				result.set_flags( result.o_flags() | Uart::flag_is_stop1_5);
			} else if( stop_bits == "2" ){
				result.set_flags( result.o_flags() | Uart::flag_is_stop2);
			} else {
				result.set_flags( result.o_flags() | Uart::flag_is_stop1);
			}
		}

		{
			var::String parity = get_parity();
			if( parity == "odd" ){
				result.set_flags( result.o_flags() | Uart::flag_is_parity_odd);
			} else if( parity == "even" ){
				result.set_flags( result.o_flags() | Uart::flag_is_parity_even);
			} else {
				result.set_flags( result.o_flags() | Uart::flag_is_parity_none);
			}
		}
		result.set_rx( Pin::from_string(get_rx()));
		result.set_tx( Pin::from_string(get_tx()));
		result.set_rts( Pin::from_string(get_rts()));
		result.set_cts( Pin::from_string(get_cts()));
		return result;
	}
};

}

#endif // SAPI_HAL_JSON_ATTRIBUTES_HPP
