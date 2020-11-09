/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
// LICENSE.md for rights.

#ifndef SAPI_FS_LAMBDA_FILE_HPP_
#define SAPI_FS_LAMBDA_FILE_HPP_

#include <sos/link.h>

#include "File.hpp"

namespace fs {

class LambdaFile : public FileAccess<LambdaFile> {
public:
  using read_callback_t = int (*)(void *context, int location, var::View view);
  using write_callback_t
    = int (*)(void *context, int location, const var::View view);

  LambdaFile() {}

  LambdaFile(const LambdaFile &) = delete;
  LambdaFile &operator=(const LambdaFile &) = delete;
  LambdaFile(LambdaFile &&) = default;
  LambdaFile &operator=(LambdaFile &&) = default;

  LambdaFile &set_size(size_t size) {
    m_size = size;
    return *this;
  }

private:
  mutable int m_location = 0;
  mutable size_t m_size = 0;
  API_AF(LambdaFile, read_callback_t, read_callback, nullptr);
  API_AF(LambdaFile, write_callback_t, write_callback, nullptr);
  API_AF(LambdaFile, void *, context, nullptr);

  int interface_read(void *buf, int nbyte) const override;
  int interface_write(const void *buf, int nbyte) const override;
  int interface_lseek(int offset, int whence) const override;

  int interface_ioctl(int request, void *argument) const override {
    return fake_ioctl(request, argument);
  }
};

} // namespace fs

#endif /* SAPI_FS_LAMBDA_FILE_HPP_ */
