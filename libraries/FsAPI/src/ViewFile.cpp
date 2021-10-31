// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#include "fs/ViewFile.hpp"
#include "var/StackString.hpp"

using namespace fs;

int ViewFile::interface_read(void *buf, int nbyte) const {

  if (flags().is_write_only()) {
    errno = EBADF;
    return -1;
  }

  int size_ready = item().size() - m_location;
  if (size_ready > nbyte) {
    size_ready = nbyte;
  }

  if (size_ready <= 0) {
    // EOF
    return 0;
  }

  memcpy(buf, item().to_const_u8() + m_location, size_ready);

  m_location += size_ready;
  return size_ready;
}

int ViewFile::interface_write(const void *buf, int nbyte) const {

  if (flags().is_read_only()) {
    errno = EBADF;
    return -1;
  }

  int size_ready = 0;
  if (flags().is_append()) {
    errno = EINVAL;
    return -1;
  } else {
    // limit writes to the current size of the data
    size_ready = item().size() - m_location;
    if (size_ready > nbyte) {
      size_ready = nbyte;
    }
  }

  if (size_ready < 0) {
    // EOF should return 0 bytes written
    errno = ENOSPC;
    return -1;
  }

  memcpy(var::View(item()).to_u8() + m_location, buf, size_ready);

  m_location += size_ready;
  return size_ready;
}

int ViewFile::interface_lseek(int offset, int whence) const {
  fake_seek(m_location, m_view.size(), offset, whence);
  return m_location;
}
