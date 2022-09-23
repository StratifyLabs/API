// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#include "fs/LambdaFile.hpp"

using namespace fs;

int LambdaFile::interface_read(void *buf, int nbyte) const {
  if (m_read_callback == nullptr) {
    return -1;
  }

  int result = m_read_callback(m_location, var::View(buf, nbyte));
  if (result > 0) {
    m_location += result;
  }
  return result;
}

int LambdaFile::interface_write(const void *buf, int nbyte) const {

  if (m_write_callback == nullptr) {
    return -1;
  }

  int result = m_write_callback(m_location, var::View(buf, nbyte));
  if (result > 0) {
    m_location += result;
  }
  if (m_size < size_t(m_location)) {
    m_size = m_location;
  }

  return result;
}

int LambdaFile::interface_lseek(int offset, int whence) const {
  fake_seek(m_location, m_size, offset, whence);
  return m_location;
}
