/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
#ifndef SAPI_HAL_DRIVE_HPP_
#define SAPI_HAL_DRIVE_HPP_

#include <sos/dev/drive.h>

#include "Device.hpp"
#include "chrono/DateTime.hpp"

namespace hal {

/*!
 * \brief The DriveInfo class
 * \details The Drive Info class
 * provides information on a hal::Drive.
 *
 * It is a wrapper for the drive_info_t
 * found in sos/dev/drive.h.
 *
 *
 */
class DriveInfo {
public:
  DriveInfo() { m_info = {0}; }
  explicit DriveInfo(const drive_info_t &info) : m_info(info) {}

  /*! \details Returns true if the Info is valid.
   *
   * ```
   * DriveInfo info;
   * Drive d;
   * info = d.get_info();
   * if( info.is_valid() ){
   *  //get_info() was successful
   * }
   * ```
   *
   */
  bool is_valid() const { return m_info.num_write_blocks != 0; }

  /*! \details Returns the number of bytes
   * available on the drive.
   */
  u64 size() const { return m_info.num_write_blocks * m_info.write_block_size; }

  u32 o_flags() const { return m_info.o_flags; }
  u32 o_events() const { return m_info.o_events; }

  /*! \details Returns the number of bytes represented
   * by each address value.
   *
   * For small drives, this value is usually 1. For large
   * drives, especially those over 4GB, this value is
   * usually larger than one. For large SD cards, it is typically 512.
   *
   */
  u16 addressable_size() const { return m_info.addressable_size; }

  /*! \details Returns the size of the smallest writeable
   * block on the drive. If each byte can be
   * written individually, this value is 1.
   *
   */
  u32 write_block_size() const { return m_info.write_block_size; }

  /*! \details Returns the number of write blocks on the entire drive.
   *
   * The number of bytes on the drive is write_block_count()  *
   * write_block_size().
   *
   */
  u32 write_block_count() const { return m_info.num_write_blocks; }

  /*! \details Returns the size of the smallest eraseable block on the drive. */
  u32 erase_block_size() const { return m_info.erase_block_size; }

  /*! \details Returns the maximum bitrate that the drive can
   * operate.
   *
   */
  u32 frequency() const { return m_info.bitrate; }

  /*! \details Returns the approximate amount of time it takes
   * to erase the entire drive.
   */
  chrono::MicroTime erase_device_time() const {
    return chrono::MicroTime(m_info.erase_device_time);
  }

  /*! \details Returns the approximate amount of time it takes
   * to erase a single block on the drive.
   */
  chrono::MicroTime erase_block_time() const {
    return chrono::MicroTime(m_info.erase_block_time);
  }

  /*! \details Returns the maximum number of bytes that can
   * be programmed as a single page.
   *
   */
  u32 page_program_size() const { return m_info.page_program_size; }

private:
  drive_info_t m_info;
};

/*!
 * \brief The Drive class
 * \details The Drive class is used
 * for debugging and diagnosing Drive devices (as
 * defined in sos/dev/drive.h).
 *
 * On production systems, the Drive is completely
 * managed by the filesystem that lives on the
 * drive. The OS build can dictate whether
 * the underlying drive is made available
 * to applications or not (and set the permissions).
 *
 * This class mainly exists in developing new
 * drivers for flash devices that are implementing
 * the sos/dev/drive.h driver interface.
 *
 * ```
 * #include <sapi/hal.hpp>
 *
 * Drive d;
 * d.open("/dev/drive0");
 * DriveInfo info = d.get_info();
 * d.close();
 * ```
 *
 */
class Drive : public Device {
public:
  Drive();

  /*! \details Initializes the drive.
   *
   */
  int initialize(const var::String &path);

  /*! \details Powers up the drive.
   *
   */
  int powerup() const;

  /*! \details Powers down the drive.
   *
   */
  int powerdown() const;

  int reset() const;

  int protect() const;
  int unprotect() const;

  /*! \details Erases blocks on the drive.
   *
   * @param start An address containing the first block to erase
   * @param end An address containing the last block to erase
   *
   */
  int erase_blocks(u32 start, u32 end) const;

  /*! \details Erases the drive.
   *
   */
  int erase_device() const;

  /*! \details Returns true if the drive is busy.
   *
   */
  bool is_busy() const;

  /*! \details Returns a DriveInfo object that is
   * populated with the infomration from the drive.
   *
   */
  DriveInfo get_info() const;

private:
  int set_attributes(const drive_attr_t &attributes) const;
};

} // namespace hal

namespace printer {
class Printer;
Printer &operator<<(Printer &printer, const hal::DriveInfo &a);
} // namespace printer

#endif // SAPI_HAL_DRIVE_HPP_
