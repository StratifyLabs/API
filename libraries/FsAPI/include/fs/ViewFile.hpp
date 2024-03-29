// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef SAPI_FS_VIEW_FILE_HPP_
#define SAPI_FS_VIEW_FILE_HPP_

#include "api/api.hpp"

#include "File.hpp"

namespace fs {

/*! \details
 *
 * This class lets you convert any var::View object
 * into a file-like object.
 *
 */
class ViewFile : public FileAccess<ViewFile> {
public:
  explicit ViewFile(var::View view) { m_view = view; }

  ViewFile &set_flags(const OpenMode &open_flags) &;
  ViewFile &&set_flags(const OpenMode &open_flags) && {
    return std::move(set_flags(open_flags));
  }

  const OpenMode &flags() const { return m_open_flags; }

  /*! \details Accesses (read-only) the member data object. */
  const var::View &item() const { return m_view; }
  /*! \details Accesses the member data object. */
  var::View &item() { return m_view; }

private:
  mutable int m_location = 0; // offset location for seeking/reading/writing
  mutable OpenMode m_open_flags = OpenMode::read_write();
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
