/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
// LICENSE.md for rights.
// Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc

#include <cstdio>
#include <cstring>
#include <fcntl.h>

#include "chrono/ClockTimer.hpp"
#include "fs/ViewFile.hpp"
#include "var/StackString.hpp"

#include "local.h"

using namespace fs;

int ViewFile::interface_read(void *buf, int nbyte) const {

  if (flags().is_write_only()) {
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
    return -1;
  }

  int size_ready = 0;
  if (flags().is_append()) {
    return -1;
  } else {
    // limit writes to the current size of the data
    size_ready = item().size() - m_location;
    if (size_ready > nbyte) {
      size_ready = nbyte;
    }
  }

  if (size_ready < 0) {
    return -1;
  }

  memcpy(item().to_u8() + m_location, buf, size_ready);

  m_location += size_ready;
  return size_ready;
}

int ViewFile::interface_lseek(int offset, int whence) const {
  fake_seek(m_location, m_view.size(), offset, whence);
  return m_location;
}
