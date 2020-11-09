/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.
//Copyright 2011-2018 Tyler Gilbert; All Rights Reserved

#include "../../include/hal/DisplayDevice.hpp"

#include "sys.hpp"

namespace hal {

DisplayDevice::DisplayDevice(){}

/*! \brief Pure virtual function to initialize the LCD */
int DisplayDevice::initialize(
		const var::String & name,
		IsAllocate is_allocate
		){
	//open and populate attr

	if( name.is_empty() == false ){

		//only open the device if it isn't already open
		if ( Device::open(
				  name,
				  fs::OpenFlags::read_write()) < 0 ){
			return -1;
		}

		display_info_t info;
		if( ioctl(
				 IoRequest(I_DISPLAY_GETINFO),
				 IoArgument(&info)
				 ) < 0 ){
			return -1;
		}

		if( is_allocate.argument() ){
			allocate(
						sgfx::Area(info.width, info.height),
						BitsPerPixel(info.bits_per_pixel)
						);
		} else {
			refer_to(
						ReadOnlyBuffer(nullptr),
						sgfx::Area(info.width, info.height),
						BitsPerPixel(info.bits_per_pixel)
						);
		}

		set_margin_left(info.margin_left);
		set_margin_right(info.margin_right);
		set_margin_top(info.margin_top);
		set_margin_bottom(info.margin_bottom);

		display_attr_t attr;
		attr.o_flags = DISPLAY_FLAG_INIT;
		if( ioctl(
				 IoRequest(I_DISPLAY_SETATTR),
				 IoArgument(&attr)
				 ) < 0 ){
			return -1;
		}

		return 0;
	}
	return -1;
}

DisplayInfo DisplayDevice::get_info() const {
	display_info_t info;
	if( ioctl(
			 IoRequest(I_DISPLAY_GETINFO),
			 IoArgument(&info)
			 ) < 0 ){
		return DisplayInfo();
	}
	return DisplayInfo(info);
}

sgfx::Palette DisplayDevice::get_palette() const {
	display_palette_t display_palette;
	if( ioctl(
			 IoRequest(I_DISPLAY_GETPALETTE),
			 IoArgument(&display_palette)
			 ) < 0 ){
		return sgfx::Palette();
	}

	//copy colors from display_palette_t
	sgfx::Palette result;
	result
			.set_pixel_format(
				static_cast<enum sgfx::Palette::pixel_format>(
					display_palette.pixel_format
					)
				)
			.set_color_count(
				static_cast<enum sgfx::Palette::color_count>(
					display_palette.count
					)
				);

	const sg_color_t * display_palette_colors =
			static_cast<const sg_color_t *>(display_palette.colors);
	for(size_t i=0; i < result.colors().count(); i++){
		result.colors().at(i) = display_palette_colors[i];
	}

	return result;
}

int DisplayDevice::set_palette(
		const sgfx::Palette & palette
		) const {

	display_palette_t display_palette;
	display_palette.pixel_format = palette.pixel_format();
	display_palette.count = palette.colors().count();
	display_palette.colors = (void*)palette.colors().to_const_void();

	return ioctl(
				Device::IoRequest(I_DISPLAY_SETPALETTE),
				Device::IoConstArgument(&display_palette)
				);
}

int DisplayDevice::set_window(const sgfx::Region & region) const {
	display_attr_t attr;
	attr.o_flags = DISPLAY_FLAG_SET_WINDOW;
	attr.window_x = region.point().x();
	attr.window_y = region.point().y();
	attr.window_width = region.area().width();
	attr.window_height = region.area().height();
	return ioctl(
				IoRequest(I_DISPLAY_SETATTR),
				IoArgument(&attr)
				);
}

int DisplayDevice::write(const sgfx::Bitmap & bitmap) const {
	return write(
				var::Reference(*bitmap.bmap())
				);
}

int DisplayDevice::set_mode(enum mode value){
	display_attr_t attr;
	attr.o_flags = DISPLAY_FLAG_SET_MODE;
	if( value == mode_palette ){
		attr.o_flags |= DISPLAY_FLAG_IS_MODE_PALETTE;
	} else {
		attr.o_flags |= DISPLAY_FLAG_IS_MODE_RAW;
	}
	return ioctl(
				IoRequest(I_DISPLAY_SETATTR),
				IoArgument(&attr)
				);
}

void DisplayDevice::refresh() const {

	//write the bitmap to the display

	ioctl(IoRequest(I_DISPLAY_REFRESH));
}

int DisplayDevice::enable() const {
	display_attr_t attr;
	attr.o_flags = DISPLAY_FLAG_ENABLE;
	return ioctl(
				IoRequest(I_DISPLAY_SETATTR),
				IoArgument(&attr)
				);
}

void DisplayDevice::clear(){
	display_attr_t attributes;
	attributes.o_flags = DISPLAY_FLAG_CLEAR;
	if( ioctl(
			 IoRequest(I_DISPLAY_CLEAR),
			 IoArgument(&attributes)
			 ) < 0 ){
		Data::clear();
	}
}

int DisplayDevice::disable() const {
	display_attr_t attr;
	attr.o_flags = DISPLAY_FLAG_DISABLE;
	return ioctl(
				IoRequest(I_DISPLAY_SETATTR),
				IoArgument(&attr)
				);
}

void DisplayDevice::wait(const chrono::MicroTime & resolution) const{
	bool ret;
	do {
		if( (ret = is_busy()) ){
			resolution.wait();
		}
	} while( ret );
}

bool DisplayDevice::is_busy() const {
	return ioctl(IoRequest(I_DISPLAY_ISBUSY)) == 1;
}

} /* namespace hal */
