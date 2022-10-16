// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef FSAPI_FS_DATA_FILE_HPP
#define FSAPI_FS_DATA_FILE_HPP

#include "File.hpp"
#include "var/Data.hpp"

namespace fs {

/*! \details
 *
 * This class allows you to create
 * a file out of dynamically allocated memory.
 *
 * This is great when you need to load a file to RAM.
 *
 * ```cpp
 * #include <fs.hpp>
 *
 * DataFile data_file(File("load_to_ram.txt"));
 * ```
 *
 * It uses var::Data as an underlying storage
 * mechanism.
 *
 */
class DataFile : public FileAccess<DataFile> {
public:
  /*! \details Constructs a data file. */

  // DataFile(DataFile &&file) = default;
  // DataFile &operator=(DataFile &&file) = default;

  explicit DataFile(const OpenMode &flags = OpenMode::append_read_write())
    : m_open_flags(flags) {}

  explicit DataFile(const FileObject &file_to_load);

  DataFile &reserve(size_t size) &;
  DataFile &&reserve(size_t size) && { return std::move(reserve(size)); }
  DataFile &resize(size_t size) &;
  DataFile &&resize(size_t size) && { return std::move(resize(size)); }
  DataFile &copy(var::View view) &;
  DataFile &&copy(var::View view) && { return std::move(copy(view)); }

  DataFile &set_flags(OpenMode open_flags) &;
  DataFile &&set_flags(OpenMode open_flags) && {
    return std::move(set_flags(open_flags));
  }
  const OpenMode &flags() const { return m_open_flags; }

  /*! \details Accesses (read-only) the member data object. */
  const var::Data &data() const { return m_data; }
  /*! \details Accesses the member data object. */
  var::Data &data() { return m_data; }

private:
  mutable int m_location = 0; // offset location for seeking/reading/writing
  mutable OpenMode m_open_flags;
  mutable var::Data m_data;

  int interface_read(void *buf, int nbyte) const override;
  int interface_write(const void *buf, int nbyte) const override;
  int interface_lseek(int offset, int whence) const override;
  int interface_ioctl(int request, void *argument) const override {
    return fake_ioctl(request, argument);
  }
};

} // namespace fs

#endif /* FSAPI_FS_DATA_FILE_HPP */
