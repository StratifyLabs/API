/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
// LICENSE.md for rights.
// Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc

#include <cstdio>
#include <cstring>
#include <fcntl.h>

#include "chrono/ClockTimer.hpp"
#include "fs/LambdaFile.hpp"
#include "var/StackString.hpp"

#include "local.h"

using namespace fs;

int LambdaFile::interface_read(void *buf, int nbyte) const {
  if (m_read_callback == nullptr) {
    return -1;
  }

  int result = m_read_callback(m_context, m_location, var::View(buf, nbyte));
  if (result > 0) {
    m_location += result;
  }
  return result;
}

int LambdaFile::interface_write(const void *buf, int nbyte) const {

  if (m_write_callback == nullptr) {
    return -1;
  }

  int result = m_write_callback(m_context, m_location, var::View(buf, nbyte));
  if (result > 0) {
    m_location += result;
  }
  if (m_size < m_location) {
    m_size = m_location;
  }

  return result;
}

int LambdaFile::interface_lseek(int offset, int whence) const {
  fake_seek(m_location, m_size, offset, whence);
  return m_location;
}
