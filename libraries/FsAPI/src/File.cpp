// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#include <cstring>
#include <fcntl.h>

#if defined __win32
#define posix_open _open
#define posix_close _close
#define posix_read _read
#define posix_write _write
#define posix_lseek _lseek
#define posix_stat _stat
#define posix_fstat _fstat
#define POSIX_OPEN_FLAGS (O_BINARY)
#define posix_nbyte_t unsigned int
#else
#include <sys/ioctl.h>
#define posix_open open
#define posix_close close
#define posix_read read
#define posix_write write
#define posix_lseek lseek
#define posix_stat stat
#define posix_fstat fstat
#define POSIX_OPEN_FLAGS (0)
#define posix_nbyte_t int
#endif

#include "fs/File.hpp"
#include "var/StackString.hpp"

using namespace fs;

File::File(var::StringView name, OpenMode flags) : m_fd(open(name, flags), &file_descriptor_deleter){ }

File::File(
  IsOverwrite is_overwrite,
  var::StringView path,
  OpenMode open_mode,
  Permissions perms) : m_fd(internal_create(is_overwrite, path, open_mode, perms),
    &file_descriptor_deleter){

}

#if 0
File::~File() {
  if (fileno() >= 0) {
    api::ErrorGuard error_guard;
    close();
  }
}
#endif

int File::fileno() const { return m_fd.value(); }

int File::flags() const {
  API_RETURN_VALUE_IF_ERROR(-1);
#if defined __link
  return -1;
#else
  if (fileno() < 0) {
    API_SYSTEM_CALL("", -1);
    return return_value();
  }
  return _global_impure_ptr->procmem_base->open_file[m_fd.value()].flags;
#endif
}

int File::fstat(struct stat *st) const {
  API_RETURN_VALUE_IF_ERROR(-1);
  return API_SYSTEM_CALL("", ::fstat(m_fd.value(), st));
}

#if 0
void File::close() {
  if (m_system_resource.value() >= 0) {
    internal_close(m_system_resource.value());
    m_system_resource.value() = -1;
  }
}
#endif

int File::internal_open(const char *path, int flags, int mode) {
  return ::posix_open(path, flags, mode);
}

int File::interface_read(void *buf, int nbyte) const {
  return ::posix_read(m_fd.value(), buf, nbyte);
}

int File::interface_write(const void *buf, int nbyte) const {
  return ::posix_write(m_fd.value(), buf, nbyte);
}

int File::interface_ioctl(int request, void *argument) const {
#if defined __win32
  errno = ENOTSUP;
  return -1;
#else
  return ::ioctl(m_fd.value(), request, argument);
#endif
}

void File::internal_close(int fd) { ::posix_close(fd); }

int File::interface_fsync() const {
#if defined __link
  return 0;
#else
  return ::fsync(m_fd.value());
#endif
}

int File::interface_lseek(int offset, int whence) const {
  return ::posix_lseek(m_fd.value(), offset, whence);
}

int File::open(var::StringView path, OpenMode flags, Permissions permissions) {
  API_RETURN_VALUE_IF_ERROR(-1);
  const var::PathString path_string(path);
  return API_SYSTEM_CALL(
    path_string.cstring(),
    internal_open(
      path_string.cstring(),
      static_cast<int>(flags.o_flags()),
      permissions.permissions()));
}

int File::internal_create(
  IsOverwrite is_overwrite,
  var::StringView path,
  OpenMode open_mode,
  Permissions perms) {
  OpenMode flags = OpenMode(open_mode).set_create();
  if (is_overwrite == IsOverwrite::yes) {
    flags.set_truncate();
  } else {
    flags.set_exclusive();
  }

  return open(path, flags, perms);
}

void File::file_descriptor_deleter(const int *fd_ptr) {
  const auto fd = *fd_ptr;
  if( fd >= 0 ) {
    internal_close(fd);
  }
}

int NullFile::interface_read(void *buf, int nbyte) const {
  MCU_UNUSED_ARGUMENT(buf);
  int size_ready = m_size - m_location;
  if (size_ready > nbyte) {
    size_ready = nbyte;
  }

  if (size_ready < 0) {
    return -1;
  }

  m_location += size_ready;
  return size_ready;
}

int NullFile::interface_write(const void *buf, int nbyte) const {
  MCU_UNUSED_ARGUMENT(buf);
  return nbyte;
}

int NullFile::interface_lseek(int offset, int whence) const {
  fake_seek(m_location, m_size, offset, whence);
  return m_location;
}
