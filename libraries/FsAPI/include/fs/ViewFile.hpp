/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
// LICENSE.md for rights.

#ifndef SAPI_FS_VIEW_FILE_HPP_
#define SAPI_FS_VIEW_FILE_HPP_

#include <sos/link.h>

#include "api/api.hpp"

#include "File.hpp"

namespace fs {

class ViewFile : public FileAccess<ViewFile> {
public:
  /*! \details Constructs a data file. */

  ViewFile(ViewFile &&view_file) = default;
  ViewFile &operator=(ViewFile &&view_file) = default;

  ViewFile(var::View view)
    : m_open_flags(
      view.is_read_only() ? OpenMode::read_only() : OpenMode::read_write()) {
    m_view = view;
  }

  ViewFile &set_flags(const OpenMode &open_flags) {
    m_open_flags = open_flags;
    return *this;
  }

  const OpenMode &flags() const { return m_open_flags; }

  /*! \details Accesses (read-only) the member data object. */
  const var::View &item() const { return m_view; }
  /*! \details Accesses the member data object. */
  var::View &item() { return m_view; }

private:
  mutable int m_location = 0; // offset location for seeking/reading/writing
  mutable OpenMode m_open_flags;
  var::View m_view;

  int interface_ioctl(int request, void *argument) const override {
    return fake_ioctl(request, argument);
  }
  int interface_lseek(int offset, int whence) const override;
  int interface_read(void *buf, int nbyte) const override;
  int interface_write(const void *buf, int nbyte) const override;
};

} // namespace fs

#endif /* SAPI_FS_VIEW_FILE_HPP_ */
