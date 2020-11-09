/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.

#ifndef SAPI_HAL_PINASSIGNMENT_HPP_
#define SAPI_HAL_PINASSIGNMENT_HPP_

#include "var/View.hpp"

namespace hal {

/*! \brief Pin Assignment Class
 * \details The Pin Assignment class is a template
 * class for manipulating pin assignment data structures.
 *
 * The following is an example of how to configure the SPI using
 * the hal::SpiPinAssignment class (which inherits this class).
 *
 * \code
 * #include <sapi/hal.hpp>
 *
 * SpiPinAssignment pin_assignment;
 * pin_assignment->mosi = mcu_pin(2,0);
 * pin_assignment->sck = mcu_pin(2,0);
 * pin_assignment->miso = mcu_pin(2,0);
 *
 * Spi spi(0);
 *
 * spi.init(
 *  Spi::FLAG_SET_MASTER|Spi::FLAG_IS_MODE0|Spi::FLAG_IS_FORMAT_SPI,
 *  10000000, 8, pin_assignment
 * );
 *
 * \endcode
 *
 *
 */
template <typename pin_assignment_type> class PinAssignment {
public:
  /*! \details Contructs a new pin assignment object.
   *
   * All pin assignments are "cleared" when created meaning all
   * ports and pins are set to 0xff so that any access to the pin
   * assignment info will be ignored.
   *
   */
  PinAssignment() { clear(); }

  /*! \details Returns a const pointer to the pin assignment data structure.
   *
   * This operator makes it easy to pass pin assignment data to set_attr()
   * methods.
   *
   */
  operator const pin_assignment_type *() const { return &m_pin_assignment; }

  /*! \details Provides read and write access to the members of
   * the pin assignment structure.
   */
  pin_assignment_type *operator->() { return &m_pin_assignment; }

  /*! \details Clears the pin assignment data structure (assigns 0xff
   * to all ports/pins.
   */
  void clear() { memset(&m_pin_assignment, 0xff, sizeof(m_pin_assignment)); }

  /*! \details Returns the number of bytes in the data structure. */
  u32 size() const { return sizeof(pin_assignment_type); }

  /*! \details Returns the number of pins in the pin assignment data structure.
   */
  u32 count() const { return size() / sizeof(mcu_pin_t); }

  /*! \details Copies the pin assignment information to the object specified.
   *
   * @param pin_assignment A reference to the destination pin assignment data
   */
  void copy(pin_assignment_type &pin_assignment) {
    memcpy(&pin_assignment, &m_pin_assignment, size());
  }

  /*! \details Assigns the value of the pin assignment as specified.
   *
   * @param pin_assignment A reference to the pin assignment which will be
   * assigned to this object
   */
  void assign(const pin_assignment_type &pin_assignment) {
    memcpy(&m_pin_assignment, &pin_assignment, size());
  }

private:
  pin_assignment_type m_pin_assignment;
};

} /* namespace hal */

#endif /* SAPI_HAL_PINASSIGNMENT_HPP_ */
