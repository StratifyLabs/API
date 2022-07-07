// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#include <cstring>

#include "fs/DataFile.hpp"
#include "var/StackString.hpp"

using namespace fs;

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

  memcpy(buf, m_data.data_u8() + m_location, size_ready);

  m_location += size_ready;
  return int(size_ready);
}

int DataFile::interface_write(const void *buf, int nbyte) const {

  if (flags().is_read_only()) {
    errno = EBADF;
    return -1;
  }

  long size_ready = 0;
  if (flags().is_append()) {
    // make room in the m_data object for more bytes
    m_location = static_cast<int>(m_data.size());
    if (m_data.resize(m_data.size() + nbyte).is_error()) {
      return -1;
    }
    size_ready = nbyte;
  } else {
    // limit writes to the current size of the data
    if (static_cast<int>(m_data.size()) > m_location) {
      size_ready = m_data.size_signed() - m_location;
      if (size_ready > nbyte) {
        size_ready = nbyte;
      }
    } else {
      return -1;
    }
  }

  memcpy(m_data.data_u8() + m_location, buf, size_ready);

  m_location += size_ready;
  return int(size_ready);
}

int DataFile::interface_lseek(int offset, int whence) const {
  fake_seek(m_location, m_data.size(), offset, whence);
  return m_location;
}
