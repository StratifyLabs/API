/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.

#ifndef SAPI_HAL_DISPLAY_HPP_
#define SAPI_HAL_DISPLAY_HPP_

#include <mcu/types.h>
#include <sos/dev/display.h>

#include "../var/View.hpp"
#include "../var/Data.hpp"
#include "../sgfx/Bitmap.hpp"
#include "../api/HalObject.hpp"

namespace hal {

class DisplayInfo {
public:
	DisplayInfo(){ memset(&m_info, 0, sizeof(m_info)); }
	DisplayInfo(const display_info_t & info) : m_info(info){}

	/*! \details Returns true if this object is valid.
	 *
	 *
	 * ```
	 * DisplayInfo info;
	 * Display display;
	 *
	 * info = display.get_info();
	 * if( info.is_valid() ){
	 *   //info was successfully retrieved
	 * }
	 * ```
	 *
	 *
	 */
	bool is_valid() const { return memory_size() != 0; }

	/*! \details Returns the width of the display. */
	sg_size_t width() const { return m_info.width; }
	/*! \details Returns the height of the display. */
	sg_size_t height() const { return m_info.width; }

	/*! \details Returns the right margin of the display. */
	sg_size_t margin_right() const { return m_info.margin_right; }
	/*! \details Returns the left margin of the display. */
	sg_size_t margin_left() const { return m_info.margin_left; }
	/*! \details Returns the top margin of the display. */
	sg_size_t margin_top() const { return m_info.margin_top; }
	/*! \details Returns the bottom margin of the display. */
	sg_size_t margin_bottom() const { return m_info.margin_bottom; }

	u16 bits_per_pixel() const { return m_info.bits_per_pixel; }

	/*! \details Returns the number of bytes needed for video memory for the entire display. */
	u32 memory_size() const {
		//number of bytes needed to store an image
		return width() * height() * bits_per_pixel() / 8;
	}

	/*! \details Returns the maximum update frequency of the display. */
	u32 frequency() const { return m_info.freq; }

	u16 columns() const { return m_info.cols; }
	u16 rows() const { return m_info.rows; }


private:
	display_info_t m_info;
};

/*! \brief Display Class
 * \details The Display class is for drawing on a display such as an OLED or LCD.
 *
 */
class Display : public sgfx::Bitmap {
public:

	using IsAllocate = arg::Argument<bool, struct DisplayDeviceIsAllocateTag>;
	using BitsPerPixel = sgfx::Bitmap::BitsPerPixel;

	/*! \details Constructs a new object with no video memory. */
	Display(){}

	/*! \details Constructs a new object with the provided memory buffer
	 *
	 */
	Display(
			ReadWriteBuffer buffer,
			const sgfx::Area & area
			) : sgfx::Bitmap(buffer,area){
	}

	/*! \details Constructs a new object and dynamically allocates memory for
	 * the buffer.
	 *
	 * @param w The width of the display
	 * @param h The height of the display
	 */
	Display(
			const sgfx::Area & area,
			BitsPerPixel bpp = BitsPerPixel(1)
			) : sgfx::Bitmap(area, bpp){}

	/*! \details Initializes the display. */
	virtual int initialize(
			const var::String & path = var::String(),
			IsAllocate is_allocate = IsAllocate(true)
			) = 0;

	/*! \details Turns the display on. */
	virtual int enable() const = 0;

	/*! \details Turns the display off. */
	virtual int disable() const = 0;

	/*! \details Returns a DisplayInfo object that desribes
	 * the display.
	 *
	 */
	virtual DisplayInfo get_info() const {
		return DisplayInfo();
	}

	virtual sgfx::Palette get_palette() const {
		return sgfx::Palette();
	}

	virtual int set_palette(const sgfx::Palette & palette) const {
		MCU_UNUSED_ARGUMENT(palette);
		return -1;
	}

	virtual int set_window(const sgfx::Region & region) const {
		return 0;
	}

	virtual int write(const sgfx::Bitmap & bitmap) const {
		return 0;
	}
};

} /* namespace hal */

#endif /* SAPI_HAL_DISPLAY_HPP_ */
