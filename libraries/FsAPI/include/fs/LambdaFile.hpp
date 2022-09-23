// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef SAPI_FS_LAMBDA_FILE_HPP_
#define SAPI_FS_LAMBDA_FILE_HPP_

#include "File.hpp"

namespace fs {


/*! \details
 *
 * This class is used to execute a function whenever
 * a file is read or written.  It is great if you want to
 * perform an operation on data read from a file (or an inet::Socket).
 *
 *
 *
 *
 */
class LambdaFile : public FileAccess<LambdaFile> {
public:
  using ReadCallback = api::Function<int(int, var::View)>;
  using WriteCallback = api::Function<int(int, const var::View)>;

  LambdaFile() = default;

  LambdaFile &set_size(size_t size) {
    m_size = size;
    return *this;
  }

private:
  mutable int m_location = 0;
  mutable size_t m_size = 0;
  API_AF(LambdaFile, ReadCallback, read_callback, nullptr);
  API_AF(LambdaFile, WriteCallback, write_callback, nullptr);

  int interface_read(void *buf, int nbyte) const override;
  int interface_write(const void *buf, int nbyte) const override;
  int interface_lseek(int offset, int whence) const override;

  int interface_ioctl(int request, void *argument) const override {
    return fake_ioctl(request, argument);
  }
};

} // namespace fs

#endif /* SAPI_FS_LAMBDA_FILE_HPP_ */
