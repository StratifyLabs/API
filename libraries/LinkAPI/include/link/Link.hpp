/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.

#ifndef LINKAPI_LINK_LINK_HPP_
#define LINKAPI_LINK_LINK_HPP_

#if defined __link

#include <mcu/types.h>
#include <sos/link.h>

#include "api/api.hpp"

#include "fs/Dir.hpp"
#include "printer/Printer.hpp"
#include "sys/Appfs.hpp"
#include "sys/Sys.hpp"
#include "var/String.hpp"
#include "var/Vector.hpp"

namespace linkns {

/*! \brief Link for Controlling Stratify OS remotely
 * \details This class is used to access devices
 * running Stratify OS from a remote platform (desktop/mobile/web).
 *
 * This class is a wrapper for the Stratify OS serialization protocol
 * which allows complete access to Stratify OS system calls
 * and filesystems.
 *
 * This class is not available on native Stratify OS applications.
 *
 *
 */
class Link {
public:
  class Info {
  public:
    Info() {}
    Info(const var::String &path, const sys::Sys::Info &sys_info) {
      set_path(path);
      set_info(sys_info);
    }

    void clear() {
      m_serial_number.clear();
      m_path.clear();
      m_sys_info.clear();
    }

    Info &set_port(var::StringView port) {
      m_path = var::String(port);
      return *this;
    }

    Info &set_info(const sys::Sys::Info &sys_info) {
      m_sys_info = sys_info;
      m_serial_number = sys_info.serial_number().to_string();
      return *this;
    }

    const var::String &port() const { return m_path; }

  private:
    API_ACCESS_COMPOUND(Info, var::String, path);
    API_READ_ACCESS_COMPOUND(Info, sys::Sys::Info, sys_info);
    API_READ_ACCESS_COMPOUND(Info, var::String, serial_number);
  };

  class Path {
  public:
    Path() { m_driver = nullptr; }

    Path(const var::String &path, link_transport_mdriver_t *driver) {
      if (path.find(host_prefix()) == 0) {
        m_driver = nullptr;
        m_path = path.get_substring_at_position(host_prefix().length());
      } else {
        m_driver = driver;
        size_t position;
        if (path.find(device_prefix()) == 0) {
          position = device_prefix().length();
        } else {
          position = 0;
        }
        m_path = path.get_substring_at_position(position);
      }
    }

    bool is_valid() const { return !m_path.is_empty(); }

    static bool is_device_path(const var::String &path) {
      return path.find(device_prefix()) == 0;
    }

    static bool is_host_path(const var::String &path) {
      return path.find(host_prefix()) == 0;
    }

    static var::String device_prefix() { return var::String("device@"); }

    static var::String host_prefix() { return var::String("host@"); }

    var::String path_description() const {
      return (m_driver ? var::String("device@") : var::String("host@"))
             + m_path;
    }

    bool is_device_path() const { return m_driver != nullptr; }

    bool is_host_path() const { return m_driver == nullptr; }

    var::String prefix() const {
      return is_host_path() ? host_prefix() : device_prefix();
    }

    const var::String &path() const { return m_path; }

    link_transport_mdriver_t *driver() const { return m_driver; }

  private:
    link_transport_mdriver_t *m_driver;
    var::String m_path;
  };

  /*!
   * \brief The LinkDriverPath class
   * \details The LinkDriverPath class
   * creates parses the details of a link driver path. The path
   * takes one of the following forms
   *
   * ```
   * <serial device path>
   * serial@<serial device path>
   * <driver>@<vendor id>/<product id>/<interface number>
   * <driver>@<vendor id>/<product id>/<interface number>/<serial number>
   * <driver>@<vendor id>/<product id>/<interface number>/<serial
   * number>/<device path>
   * ```
   *
   * - `<driver>` can be `serial` or `usb`
   *
   */
  class DriverPath {
  public:
    DriverPath() {}
    DriverPath(const var::String &driver_path) {
      path() = driver_path;
      var::StringList driver_details = m_path.split("@");
      var::String details_string;
      if (driver_details.count() == 1) {
        driver_name() = "serial";
        set_path(var::String("serial@") + driver_path);
        details_string = driver_path;
      } else if (driver_details.count() == 2) {
        m_driver_name = driver_details.at(0);
        details_string = driver_details.at(1);
      }

      if (details_string.is_empty()) {
        return;
      }

      if (details_string.find("/dev") == 0) {
        set_device_path(details_string);
        return;
      }

      if (details_string.length() && details_string.front() == '/') {
        details_string.pop_front();
      }
      var::StringList detail_list = details_string.split("/");

      if (detail_list.count() == 1) {
        set_device_path(detail_list.at(0));
      } else if (detail_list.count() > 2) {
        //<driver>@/<vendor id>/<product id>/<interface number>/<serial
        // number>/<device path>
        set_vendor_id(detail_list.at(0));
        set_product_id(detail_list.at(1));
        set_interface_number(detail_list.at(2));
        if (detail_list.count() > 3) {
          set_serial_number(detail_list.at(3));
        }
        if (detail_list.count() > 4) {
          set_device_path(detail_list.at(4));
        }
      }
    }

    DriverPath &construct_path() {
      set_path(
        driver_name() + "@/" + vendor_id() + "/" + product_id() + "/"
        + interface_number() + "/" + serial_number() + "/" + device_path());

      return *this;
    }

    bool operator==(const DriverPath &a) const {
      // if both values are provided and they are not the same -- they are not
      // the same
      if (
        !vendor_id().is_empty() && !a.vendor_id().is_empty()
        && (vendor_id() != a.vendor_id())) {
        return false;
      }
      if (
        !product_id().is_empty() && !a.product_id().is_empty()
        && (product_id() != a.product_id())) {
        return false;
      }
      if (
        !interface_number().is_empty() && !a.interface_number().is_empty()
        && (interface_number() != a.interface_number())) {
        return false;
      }
      if (
        !serial_number().is_empty() && !a.serial_number().is_empty()
        && (serial_number() != a.serial_number())) {
        return false;
      }
      if (
        !driver_name().is_empty() && !a.driver_name().is_empty()
        && (driver_name() != a.driver_name())) {
        return false;
      }
      if (
        !device_path().is_empty() && !a.device_path().is_empty()
        && (device_path() != a.device_path())) {
        return false;
      }
      return true;
    }

  private:
    API_ACCESS_COMPOUND(DriverPath, var::String, path);
    API_ACCESS_COMPOUND(DriverPath, var::String, device_path);
    API_ACCESS_COMPOUND(DriverPath, var::String, serial_number);
    API_ACCESS_COMPOUND(DriverPath, var::String, interface_number);
    API_ACCESS_COMPOUND(DriverPath, var::String, vendor_id);
    API_ACCESS_COMPOUND(DriverPath, var::String, product_id);
    API_ACCESS_COMPOUND(DriverPath, var::String, driver_name);

    var::String lookup_serial_port_path_from_usb_details();
  };

  Link();
  ~Link();

  enum class Legacy { no, yes };
  enum class IsBootloader { no, yes };

  var::Vector<var::String> get_path_list();
  var::Vector<var::String> get_port_list() { return get_path_list(); }

  /*! \cond */
  typedef struct {
    var::String port;
    sys::Sys::Info sys_info;
  } port_device_t;
  /*! \endcond */

  var::Vector<Info> get_info_list();

  /*! \details Gets the error message if an operation fails.
   */
  const var::String &error_message() const { return m_error_message; }

  /*! \details Gets the current progress of an operation.  This allows
   * multi-threaded applications to update a progress bar while copying files.
   */
  int progress() const { return m_progress; }

  /*! \details Gets the maximum progress value of the current operation.
   *
   */
  int progress_max() const { return m_progress_max; }


  /*! \details Connects to the specified Stratify OS device. After calling this,
   * other applications will not have access to the device.
   *
   * @param path The path to the serial device
   * @param serial_number The serial number to connect to
   * @param is_legacy True if connected to older devices
   *
   */
  int connect(var::StringView path, Legacy is_legacy = Legacy::no);

  /*! \details Reconnects to the last known path and serial number. */
  int reinit() { return connect(path()); }

  int reconnect(int retries = 5, chrono::MicroTime delay = 500_milliseconds);

  /*! \details This disconnects from the device.  After calling this,
   * other applications can access the device.
   */
  int disconnect();

  /*! \details Sets the object to a disconnected state
   * without interacting with the hardware.
   *
   * This can be called if the device was removed without
   * being properly disconnected in software.
   *
   */
  void set_disconnected();

  /*! \details Returns true if the device is connected.
   */
  bool is_connected() const;
  bool get_is_connected() const { return is_connected(); }

  // These are all the file transfer options over Stratify OS Link

  /*! \details Converts the permissions to a
   * string of the format:
   *
   * -rwxrwxrwx
   *
   * The first character indicates:
   * - - File
   * - d Directory
   * - c Character file
   * - b Block file
   *
   * The order is other, group, user.  If the permission
   * is not available, the character is replace by a "-".
   *
   */
  static var::String convert_permissions(link_mode_t mode);

  /*! \details Formats the filesystem on the device.
   *
   * \return Zero on success
   */
  int format(const var::String &path); // Format the drive

  /*! \details Funs an application on the target device.
   *
   * \return The PID of the new process or less than zero for an error
   */
  int run_app(const var::String &path);

  /*! \details Checks to see if the target is in = mode.
   *
   * \return Non zero if = mode is active.
   */
  bool is_bootloader() const { return m_is_bootloader == IsBootloader::yes; }

  bool is_connected_and_is_not_bootloader() const {
    return is_connected() && !is_bootloader();
  }

  bool is_legacy() const { return m_is_legacy == Legacy::yes; }

  /*! \details Resets the device (connection will be terminated).
   *
   * \return Zero on success or less than zero on error
   */
  int reset();

  /*! \details Resets the device and invokes the bootloader.
   *
   * \return Zero on success or less than zero on error
   *
   * The connection to the device is terminated with this call.
   *
   */
  int reset_bootloader();

  int write_flash(int addr, const void *buf, int nbyte);
  int read_flash(int addr, void *buf, int nbyte);
  int get_bootloader_attr(bootloader_attr_t &attr);

  /*! \details Reads the time from
   * the device.
   *
   * \return Zero on success
   *
   */
  int get_time(struct tm *gt);

  /*! \details This function sets the time on the device.
   * \return Zero on success
   */
  int set_time(struct tm *gt);

  enum class IsVerify { no, yes };

  class UpdateOs {
    API_AF(UpdateOs, fs::File *, image, nullptr);
    API_AF(UpdateOs, IsVerify, verify, IsVerify::no);
    API_AF(UpdateOs, const api::ProgressCallback *, progress_callback, nullptr);
    API_AF(UpdateOs, u32, bootloader_retry_count, 20);
    API_AF(UpdateOs, printer::Printer *, printer, nullptr);
  };

  /*!
   * \details Updates the operating system.
   *
   * \param path Path to the new binary image on the host.
   * \param verify true to read back the installation
   * \param update Callback to execute as update is in progress
   * \param context Argument to pass to the update callback
   * \return Zero on success
   *
   * The host must be connected to the target bootloader
   * before calling this method.
   *
   */
  int update_os(const UpdateOs &options);

  /*! \details Returns the driver needed by other API objects.
   *
   * Other objects need the link driver in order to operate correctly.
   * If the driver is not provided, the program will crash.
   *
   * Consider the following example:
   *
   * \code
   * #include <sapi/sys.hpp>
   *
   * Link link;
   *
   * link.connect("path_to_device", "serial_number");
   *
   * File file(link.driver()); //allows File to open a file on the target using
   * this link driver File crash_file; //any operations use this will cause the
   * program to crash
   *
   * \endcode
   *
   */
  const link_transport_mdriver_t *driver() const { return &m_driver_instance; }
  link_transport_mdriver_t *driver() { return &m_driver_instance; }

  /*! \details Assigns the driver options to the link driver.
   *
   */
  Link &set_driver_options(const void *options) {
    m_driver_instance.options = options;
    return *this;
  }

  /*! \details Sets the driver used by this object.
   *
   * If no driver is set, the default driver (serial port) is used.
   *
   */
  Link &set_driver(link_transport_mdriver_t *driver) {
    m_driver_instance = *driver;
    return *this;
  }

  Link &set_progress(int p) {
    m_progress = p;
    return *this;
  }
  Link &set_progress_max(int p) {
    m_progress_max = p;
    return *this;
  }

  /*! \details Returns the serial number of the last device
   * that was connected (including the currently connected device)
   * @return A string containing the serial number of the last connected (or
   * currently connected) device
   */
  var::StringView serial_number() const { return m_link_info.serial_number(); }

  var::StringView serial_no() const { return serial_number(); }

  /*! \details The path of the currently connected (or last connected) device */
  var::StringView path() const { return m_link_info.port(); }

  /*! \details Returns a copy of the system info for the
   * connected device.
   *
   * Each time a device is connected, the system information
   * is loaded. This object keeps a copy.
   *
   */
  const sys::Sys::Info &sys_info() const { return m_link_info.sys_info(); }

  const Info &info() const { return m_link_info; }

private:
  var::String m_notify_path;
  var::String m_error_message;
  int m_stdout_fd = -1;
  int m_stdin_fd = -1;
  volatile int m_progress = 0;
  volatile int m_progress_max = 0;
  volatile int m_lock = 0;
  IsBootloader m_is_bootloader = IsBootloader::no;
  Legacy m_is_legacy = Legacy::no;

  Info m_link_info;
  bootloader_attr_t m_bootloader_attributes = {0};

  link_transport_mdriver_t m_driver_instance = {0};

  u32 validate_os_image_id_with_connected_bootloader(fs::File *source_image);

  int erase_os(const UpdateOs &options);

  int install_os(u32 image_id, const UpdateOs &options);

  int check_error(int err);
  void reset_progress();
};

} // namespace linkns

#endif

#endif // LINKAPI_LINK_LINK_HPP_
