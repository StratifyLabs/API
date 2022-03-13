// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef FSAPI_FS_DATA_FILE_HPP
#define FSAPI_FS_DATA_FILE_HPP

#include "File.hpp"
#include "var/Data.hpp"

namespace fs {

class DataFile : public FileAccess<DataFile> {
public:
  /*! \details Constructs a data file. */

  DataFile(DataFile &&file) = default;
  DataFile &operator=(DataFile &&file) = default;

  explicit DataFile(const OpenMode &flags = OpenMode::append_read_write())
    : m_open_flags(flags) {}

  explicit DataFile(const FileObject &file_to_load);

  DataFile &reserve(size_t size) {
    m_data.reserve(size);
    return *this;
  }

  DataFile &resize(size_t size) {
    m_data.resize(size);
    return *this;
  }

  DataFile &copy(var::View view) {
    m_data.copy(view);
    return *this;
  }

  DataFile &set_flags(OpenMode open_flags) {
    m_open_flags = open_flags;
    return *this;
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
