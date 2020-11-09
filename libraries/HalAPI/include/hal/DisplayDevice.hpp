/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.

#ifndef SAPI_HAL_DISPLAYDEVICE_HPP_
#define SAPI_HAL_DISPLAYDEVICE_HPP_

#include "Device.hpp"
#include "Display.hpp"

namespace hal {


/*! \brief Display Device
 * \details This class is a display device. It inherits
 * both Display and Dev so that a display
 * found at, for example, "/dev/display0" can
 * be drawn on.
 */
class DisplayDevice :
      public Display,
      public Device {
public:
	DisplayDevice();

	int initialize(
			const var::String & name,
			IsAllocate is_allocate = IsAllocate(true)
			);

	/*! \details Refreshes the display.
	 *
	 * This method will cause the driver to write the
	 * current video memory to the display.
	 */
	void refresh() const override;

	void clear() override;

	int set_window(const sgfx::Region & region) const override;

	using Device::write;
	int write(const sgfx::Bitmap & bitmap) const override;

	enum mode {
		mode_palette,
		mode_raw
	};

	DisplayInfo get_info() const override;
	sgfx::Palette get_palette() const override;

	int set_palette(const sgfx::Palette & display_palette) const override;

	int set_mode(enum mode value);

	/*! \details Returns true if the display is
	 * actively copying the video buffer to the display
	 *
	 * @return True if the LCD is busy
	 */
	bool is_busy() const override;

	/*! \details Blocks until the display is not busy anymore. */
	void wait(const chrono::MicroTime & resolution) const override;

	int enable() const override;
	int disable() const override;

	using Data::size;
};

} /* namespace hal */

#endif /* SAPI_HAL_DISPLAYDEVICE_HPP_ */
