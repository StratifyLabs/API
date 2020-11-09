/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
/* Copyright 2016-2018 Tyler Gilbert ALl Rights Reserved */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sos/dev/sys.h>
#include <sos/fs/sysfs.h>
#include <sstream>
#include <string>

#define MAX_TRIES 3

#include "chrono/ClockTimer.hpp"
#include "fs/File.hpp"
#include "link/Link.hpp"
#include "sys/Appfs.hpp"

using namespace sys;
using namespace fs;
using namespace linkns;

static var::String gen_error(const var::String &msg, int err_number) {
  var::String s;
  s.format("%s (%d)", msg.cstring(), err_number);
  return s;
}

Link::Link() { link_load_default_driver(driver()); }

Link::~Link() {}

int Link::check_error(int err) {
  switch (err) {
  case LINK_PHY_ERROR:
    m_error_message = "Physical Connection Error";
    this->disconnect();
    return LINK_PHY_ERROR;
  case LINK_PROT_ERROR:
    m_error_message = "Protocol Error";
    return LINK_PROT_ERROR;
  }
  return err;
}

void Link::reset_progress() {
  m_progress = 0;
  m_progress_max = 0;
}

var::Vector<var::String> Link::get_path_list() {
  var::Vector<var::String> result;
  var::Data device_name(256);
  var::String last_device;

  while (driver()->getname(
           var::View(device_name).to_char(),
           last_device.cstring(),
           static_cast<int>(device_name.capacity()))
         == 0) {

    var::String device_string(var::View(device_name).to_const_char());

    result.push_back(device_string); // this will make a copy of device name and
                                     // put it on the list
    last_device = device_string;
  }

  return result;
}

var::Vector<Link::Info> Link::get_info_list() {
  var::Vector<Info> result;
  var::Vector<var::String> port_list = get_path_list();

  // disconnect if already connected
  disconnect();

  for (u32 i = 0; i < port_list.count(); i++) {
    // ping and grab the info
    if (connect(port_list.at(i)) < 0) {
      // couldn't connect
    } else {
      result.push_back(Info(port_list.at(i), sys_info()));
      disconnect();
    }
  }

  return result;
}

int Link::connect(var::StringView path, Legacy is_legacy) {
  int err = -1;

  reset_progress();

  if (driver()->phy_driver.handle == LINK_PHY_OPEN_ERROR) {

    driver()->transport_version = 0;
    driver()->phy_driver.handle
      = driver()->phy_driver.open(path.cstring(), driver()->options);
    if (driver()->phy_driver.handle == LINK_PHY_OPEN_ERROR) {
      m_error_message = "Failed to Connect to Device";
      return -1;
    }

  } else {
    m_error_message.format("Already Connected (%d)", 1);
    return -1;
  }

  m_is_legacy = is_legacy;

  if (m_is_legacy == Legacy::yes) {
    err = link_isbootloader_legacy(driver());
  } else {
    err = link_isbootloader(driver());
  }

  if (err > 0) {
    m_is_bootloader = IsBootloader::yes;
  } else if (err == 0) {
    m_is_bootloader = IsBootloader::no;
  } else {
    m_error_message.format(
      "Failed to check for Bootloader status (%d)",
      link_errno);
    driver()->phy_driver.close(&driver()->phy_driver.handle);
    return -1;
  }

  sys_info_t sys_info;
  if (m_is_bootloader == IsBootloader::no) {
    link_get_sys_info(driver(), &sys_info);
  } else {
    get_bootloader_attr(m_bootloader_attributes);
    memset(&sys_info, 0, sizeof(sys_info));
    strcpy(sys_info.name, "bootloader");
    sys_info.hardware_id = m_bootloader_attributes.hardware_id;
    memcpy(
      &sys_info.serial,
      m_bootloader_attributes.serialno,
      sizeof(mcu_sn_t));
  }

  m_link_info.set_port(path).set_info(Sys::Info(sys_info));

  return 0;
}

int Link::reconnect(int retries, chrono::MicroTime delay) {
  int result;
  Info last_info(info());
  for (u32 i = 0; i < retries; i++) {
    result = connect(last_info.port());
    if (result >= 0) {
      if (last_info.serial_number() == info().serial_number()) {
        return 0;
      }
      disconnect();
    }

    var::Vector<var::String> port_list = get_path_list();
    for (u32 j = 0; j < port_list.count(); j++) {
      result = connect(port_list.at(j));
      if (result < 0) {
        // didn't connect
      } else {
        if (last_info.serial_number() == info().serial_number()) {
          return 0;
        }
        disconnect();
      }
    }

    delay.wait();
  }

  // restore the last known information on failure
  m_link_info = last_info;

  return -1;
}

int Link::read_flash(int addr, void *buf, int nbyte) {
  int err = -1;

  for (int tries = 0; tries < MAX_TRIES; tries++) {
    err = link_readflash(driver(), addr, buf, nbyte);
    if (err != LINK_PROT_ERROR)
      break;
  }
  if (err < 0) {
    m_error_message.format("Failed to read flash", link_errno);
  }

  return check_error(err);
}

int Link::write_flash(int addr, const void *buf, int nbyte) {
  int err = -1;

  for (int tries = 0; tries < MAX_TRIES; tries++) {
    err = link_writeflash(driver(), addr, buf, nbyte);
    if (err != LINK_PROT_ERROR)
      break;
  }
  if (err < 0) {
    m_error_message.format("Failed to write flash", link_errno);
  }

  return check_error(err);
}

int Link::disconnect() {

  if (driver()->phy_driver.handle != LINK_PHY_OPEN_ERROR) {
    link_disconnect(driver());

    if (driver()->phy_driver.handle != LINK_PHY_OPEN_ERROR) {
      // can't unlock the device if it has been destroyed
    }
  }

  m_is_bootloader = IsBootloader::no;
  m_error_message = "";
  m_stdout_fd = -1;
  m_stdin_fd = -1;
  return 0;
}

void Link::set_disconnected() {
  driver()->transport_version = 0;
  driver()->phy_driver.handle = LINK_PHY_OPEN_ERROR;
}

bool Link::is_connected() const {
  if (driver()->phy_driver.handle == LINK_PHY_OPEN_ERROR) {
    return false;
  }

  return true;
}

int Link::get_time(struct tm *gt) {
  int err = -1;
  struct link_tm ltm;
  if (is_bootloader()) {
    return -1;
  }

  for (int tries = 0; tries < MAX_TRIES; tries++) {
    err = link_gettime(driver(), &ltm);
    if (err != LINK_PROT_ERROR)
      break;
  }

  if (err < 0) {
    m_error_message.format("Failed to Get Time", link_errno);
  } else {
    gt->tm_hour = ltm.tm_hour;
    gt->tm_isdst = ltm.tm_isdst;
    gt->tm_mday = ltm.tm_mday;
    gt->tm_min = ltm.tm_min;
    gt->tm_mon = ltm.tm_mon;
    gt->tm_sec = ltm.tm_sec;
    gt->tm_wday = ltm.tm_wday;
    gt->tm_yday = ltm.tm_yday;
    gt->tm_year = ltm.tm_year;
  }
  return check_error(err);
}

int Link::set_time(struct tm *gt) {
  int err = -1;
  struct link_tm ltm;

  ltm.tm_hour = gt->tm_hour;
  ltm.tm_isdst = gt->tm_isdst;
  ltm.tm_mday = gt->tm_mday;
  ltm.tm_min = gt->tm_min;
  ltm.tm_mon = gt->tm_mon;
  ltm.tm_sec = gt->tm_sec;
  ltm.tm_wday = gt->tm_wday;
  ltm.tm_yday = gt->tm_yday;
  ltm.tm_year = gt->tm_year;

  if (is_bootloader()) {
    m_error_message.format("can't set time for bootloader");
    return -1;
  }

  for (int tries = 0; tries < MAX_TRIES; tries++) {
    err = link_settime(driver(), &ltm);
    if (err != LINK_PROT_ERROR)
      break;
  }

  if (err < 0) {
    m_error_message.format(
      "failed to set time with device errno %d",
      link_errno);
  }
  return check_error(err);
}

var::String Link::convert_permissions(link_mode_t mode) {
  var::String result;

  link_mode_t type;
  type = mode & LINK_S_IFMT;
  switch (type) {
  case LINK_S_IFDIR:
    result = "d";
    break;
  case LINK_S_IFCHR:
    result = "c";
    break;
  case LINK_S_IFBLK:
    result = "b";
    break;
  case LINK_S_IFLNK:
    result = "l";
    break;
  case LINK_S_IFREG:
    result = "-";
    break;
  default:
    result = "x";
  }

  if (mode & LINK_S_IROTH) {
    result += "r";
  } else {
    result += "-";
  }

  if (mode & LINK_S_IWOTH) {
    result += "w";
  } else {
    result += "-";
  }

  if (mode & LINK_S_IXOTH) {
    result += "x";
  } else {
    result += "-";
  }

  if (mode & LINK_S_IRGRP) {
    result += "r";
  } else {
    result += "-";
  }

  if (mode & LINK_S_IWGRP) {
    result += "w";
  } else {
    result += "-";
  }

  if (mode & LINK_S_IXGRP) {
    result += "x";
  } else {
    result += "-";
  }

  if (mode & LINK_S_IRUSR) {
    result += "r";
  } else {
    result += "-";
  }

  if (mode & LINK_S_IWUSR) {
    result += "w";
  } else {
    result += "-";
  }

  if (mode & LINK_S_IXUSR) {
    result += "x";
  } else {
    result += "-";
  }

  return result;
}

int Link::run_app(const var::String &path) {
  int err = -1;
  if (is_bootloader()) {
    return -1;
  }

  if (path.length() >= LINK_PATH_ARG_MAX - 1) {
    m_error_message = "Path argument exceeds max";
    return -1;
  }

  for (int tries = 0; tries < MAX_TRIES; tries++) {
    err = link_exec(driver(), path.cstring());
    if (err != LINK_PROT_ERROR)
      break;
  }

  if (err < 0) {
    if (err == LINK_TRANSFER_ERR) {
      m_error_message = "Connection Failed";
      this->disconnect();
      return -2;
    } else {
      m_error_message.format(
        "Failed to run program -> %s (%d, %d)",
        path.cstring(),
        err,
        link_errno);
      return -1;
    }
  }
  return err;
}

int Link::format(const var::String &path) {
  int err = -1;
  if (is_bootloader()) {
    return -1;
  }
  m_error_message = "";
  // Format the filesystem

  for (int tries = 0; tries < MAX_TRIES; tries++) {
    err = link_mkfs(driver(), path.cstring());
    if (err != LINK_PROT_ERROR)
      break;
  }

  if (err < 0) {
    m_error_message.format(
      "failed to format filesystem with device errno %d",
      link_errno);
  }
  return check_error(err);
}

int Link::reset_bootloader() {

  link_resetbootloader(driver());

  driver()->transport_version = 0;
  driver()->phy_driver.handle = LINK_PHY_OPEN_ERROR;
  return 0;
}

int Link::get_bootloader_attr(bootloader_attr_t &attr) {
  int err = -1;
  if (!is_bootloader()) {
    m_error_message = "Target is not a bootloader";
    return -1;
  }

  if (is_legacy()) {
    err = link_bootloader_attr_legacy(driver(), &attr, 0);
  } else {
    err = link_bootloader_attr(driver(), &attr, 0);
  }
  if (err < 0) {
    m_error_message = "Failed to read attributes";
    return -1;
  }

  return 0;
}

u32 Link::validate_os_image_id_with_connected_bootloader(File *source_image) {
  int err = -1;
  u32 image_id;

  if (!is_bootloader()) {
    m_error_message = "Target is not a bootloader";
    return 0;
  }

  // now write the OS to the device using link_writeflash()
  m_progress_max = 0;
  m_progress = 0;

  if (source_image->seek(BOOTLOADER_HARDWARE_ID_OFFSET)
        .read(var::View(image_id))
        .seek(0)
        .status()
        .is_error()) {
    return 0;
  }

  m_progress_max = static_cast<int>(source_image->size());

  if ((image_id & ~0x01) != (m_bootloader_attributes.hardware_id & ~0x01)) {
    err = -1;
    return 0;
  }

  return image_id;
}

int Link::erase_os(const UpdateOs &options) {
  int err;

  if (!is_bootloader()) {
    m_error_message = "Target is not a bootloader";
    return -1;
  }

  const api::ProgressCallback *progress_callback = options.progress_callback();

  options.printer()->progress_key() = "erasing";

  if (progress_callback) {
    progress_callback->update(
      0,
      api::ProgressCallback::indeterminate_progress_total());
  }
  // first erase the flash
  err = link_eraseflash(driver());

  if (err < 0) {
    if (progress_callback) {
      progress_callback->update(0, 0);
    }
    m_error_message = "Failed to erase flash";
    return check_error(err);
  }

  bootloader_attr_t attr;
  memset(&attr, 0, sizeof(attr));
  int retry = 0;
  do {
    chrono::wait(500_milliseconds);
    err = get_bootloader_attr(attr);
    if (progress_callback) {
      progress_callback->update(
        retry,
        api::ProgressCallback::indeterminate_progress_total());
    }
  } while ((err < 0) && (retry++ < options.bootloader_retry_count()));

  chrono::wait(250_milliseconds);

  // flush just incase the protocol gets filled with get attr requests
  driver()->phy_driver.flush(driver()->phy_driver.handle);

  if (progress_callback) {
    progress_callback->update(0, 0);
  }

  if (err < 0) {
    var::String error = m_error_message;
    m_error_message.format(
      "Failed to ping bootloader after erase -> %s",
      error.cstring());
    return err;
  }

  return 0;
}

int Link::install_os(u32 image_id, const UpdateOs &options) {

  // must be connected to the bootloader with an erased OS
  int err = -1;
  const int buffer_size = 1024;

  const api::ProgressCallback *progress_callback
    = options.printer()->progress_callback();

  var::Data start_address_buffer(256);
  var::Data buffer(buffer_size);
  var::Data compare_buffer(buffer_size);

  if (!is_bootloader()) {
    m_error_message = "Target is not a bootloader";
    return -1;
  }

  if (options.image()->seek(0).status().is_error()) {
    return -1;
  }

  u32 start_address = m_bootloader_attributes.startaddr;
  u32 loc = start_address;

  options.printer()->progress_key() = "installing";

  if (progress_callback) {
    progress_callback->update(0, 100);
  }

  var::View(buffer).fill<u8>(0xff);

  bootloader_attr_t attr;
  if (get_bootloader_attr(attr) < 0) {
    m_error_message = "failed to get bootloader attributes before write";
    return -1;
  }

  while (options.image()->read(buffer).status().value() > 0) {
    const int bytes_read = options.image()->status().value();
    if (loc == start_address) {
      // we want to write the first 256 bytes last because the bootloader checks
      // this for a valid image
      var::View buffer_view
        = var::View(buffer).reduce_size(start_address_buffer.size());
      start_address_buffer.copy_contents(buffer_view);

      // memcpy(stackaddr, buffer, 256);

      buffer_view.fill<u8>(0xff);
    }

    if (
      (err = link_writeflash(driver(), loc, buffer.data(), bytes_read))
      != bytes_read) {
      m_error_message.format(
        "Failed to write to link flash at 0x%x (%d, %d) -> try the operation "
        "again",
        loc,
        err,
        link_errno);
      if (err < 0) {
        err = -1;
      }
      break;
    }

    loc += bytes_read;
    m_progress += bytes_read;
    if (
      progress_callback
      && (progress_callback->update(m_progress, m_progress_max) == true)) {
      break;
    }
    err = 0;
  }

  if (err == 0) {

    if (options.verify() == IsVerify::yes) {

      options.image()->seek(0);
      loc = start_address;
      m_progress = 0;

      options.printer()->progress_key() = "verifying";

      while ((options.image()->read(buffer).status().value()) > 0) {
        const int bytes_read = options.image()->status().value();

        if (
          (err
           = link_readflash(driver(), loc, compare_buffer.data(), bytes_read))
          != bytes_read) {
          m_error_message.format("Failed to read flash memory", link_errno);
          if (err > 0) {
            err = -1;
          }
          break;

        } else {

          if (loc == start_address) {
            var::View(buffer)
              .reduce_size(start_address_buffer.size())
              .fill<u8>(0xff);
          }

          compare_buffer.resize(bytes_read);
          buffer.resize(bytes_read);

          if (var::View(compare_buffer) != var::View(buffer)) {
            return -1;
          }

          loc += bytes_read;
          m_progress += bytes_read;
          if (
            progress_callback
            && (progress_callback->update(m_progress, m_progress_max) == true)) {
            break;
          }
          err = 0;
        }
      }
    }

    if (image_id != m_bootloader_attributes.hardware_id) {
      // if the LSb of the image_id doesn't match the bootloader HW ID, this
      // will correct it
      memcpy(
        start_address_buffer.data_u8() + BOOTLOADER_HARDWARE_ID_OFFSET,
        &m_bootloader_attributes.hardware_id,
        sizeof(u32));
    }

    // write the start block
    if (
      (err = link_writeflash(
         driver(),
         start_address,
         start_address_buffer.data(),
         start_address_buffer.size()))
      != start_address_buffer.size()) {

      if (progress_callback) {
        progress_callback->update(0, 0);
      }

      m_error_message.format(
        "Failed to write %d bytes to first block 0x%x (%d, %d)",
        start_address_buffer.size(),
        start_address,
        SYSFS_GET_RETURN(err),
        SYSFS_GET_RETURN_ERRNO(err));

      link_eraseflash(driver());
      return -1;
    }

    if (options.verify() == IsVerify::yes) {
      // verify the stack address
      buffer.resize(start_address_buffer.size());
      if (
        (err = link_readflash(
           driver(),
           start_address,
           buffer.data(),
           start_address_buffer.size()))
        != start_address_buffer.size()) {
        m_error_message.format("Failed to write stack addr %d", err);
        if (progress_callback) {
          progress_callback->update(0, 0);
        }

        return -1;
      }

      if (var::View(buffer) != var::View(start_address_buffer)) {
        m_error_message = "Failed to verify stack address block";
        if (progress_callback) {
          progress_callback->update(0, 0);
        }
        link_eraseflash(driver());
        return -1;
      }
    }
  }

  if (progress_callback) {
    progress_callback->update(0, 0);
  }

  return check_error(err);
}

int Link::update_os(const UpdateOs &options) {

  API_ASSERT(options.image() != nullptr);
  API_ASSERT(options.printer() != nullptr);

  u32 image_id
    = validate_os_image_id_with_connected_bootloader(options.image());

  if (image_id == 0) {
    return -1;
  }

  var::String progress_key = var::String(options.printer()->progress_key());

  if (erase_os(options)) {
    options.printer()->error(
      var::String("failed to erase os ") + error_message());
    options.printer()->progress_key() = progress_key;
    return -1;
  }

  if (install_os(image_id, options) < 0) {
    options.printer()->error(
      var::String("failed to install os ") + error_message());
    options.printer()->progress_key() = progress_key;
    return -1;
  }

  options.printer()->progress_key() = progress_key;
  return 0;
}

var::String Link::DriverPath::lookup_serial_port_path_from_usb_details() {

#if defined __win32

#endif
  return var::String();
}
