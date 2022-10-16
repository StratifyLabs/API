// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#include <cstring>

#include "fs/DataFile.hpp"

using namespace fs;
using namespace var;

DataFile::DataFile(const FileObject &file_to_load) {
  m_open_flags = OpenMode::append_read_write();
  API_RETURN_IF_ERROR();
  write(file_to_load, Write());
  seek(0);
  m_open_flags = OpenMode::read_write();
}

int DataFile::interface_read(void *buf, int nbyte) const {

  if (flags().is_write_only()) {
    errno = EBADF;
    return -1;
  }

  auto size_ready = m_data.size_signed() - m_location;
  if (size_ready > nbyte) {
    size_ready = nbyte;
  }

  if (size_ready <= 0) {
    // EOF
    return 0;
  }

  View(buf, nbyte)
    .copy(View(m_data).pop_front(m_location).truncate(size_ready));

  m_location += size_ready;
  return int(size_ready);
}

int DataFile::interface_write(const void *buf, int nbyte) const {

  if (flags().is_read_only()) {
    errno = EBADF;
    return -1;
  }

  const auto size_ready = [&]() {
    if (flags().is_append()) {
      // make room in the m_data object for more bytes
      m_location = static_cast<int>(m_data.size());
      if (m_data.resize(m_data.size() + nbyte).is_error()) {
        return -1;
      }
      return nbyte;
    }
    // limit writes to the current size of the data
    if (static_cast<int>(m_data.size()) > m_location) {
      auto result = int(m_data.size_signed() - m_location);
      if (result > nbyte) {
        result = nbyte;
      }
      return result;
    }
    return -1;
  }();

  if (size_ready < 0) {
    return -1;
  }

  View(m_data).pop_front(m_location).copy(View(buf, size_ready));

  m_location += size_ready;
  return int(size_ready);
}

int DataFile::interface_lseek(int offset, int whence) const {
  fake_seek(m_location, m_data.size(), offset, whence);
  return m_location;
}
DataFile &DataFile::reserve(size_t size) & {
    m_data.reserve(size);
    return *this;
}
DataFile &DataFile::resize(size_t size) & {
  m_data.resize(size);
  return *this;
}
DataFile &DataFile::copy(var::View view) & {
  m_data.copy(view);
  return *this;
}
DataFile &DataFile::set_flags(OpenMode open_flags) & {
  m_open_flags = open_flags;
  return *this;
}
