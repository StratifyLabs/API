/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
// Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc

#include <cstdio>
#include <cstring>
#include <fcntl.h>

#include "chrono/ClockTimer.hpp"
#include "fs/File.hpp"
#include "var/StackString.hpp"

#include "local.h"

using namespace fs;

size_t FileObject::size() const {
  // get current cursor
  API_RETURN_VALUE_IF_ERROR(0);
  const int loc = location();
  seek(0, Whence::end);
  const size_t seek_size = static_cast<size_t>(location());
  seek(loc, Whence::set);
  API_RETURN_VALUE_IF_ERROR(0);
  return seek_size;
}

const FileObject &FileObject::read(void *buf, int nbyte) const {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL("", interface_read(buf, nbyte));
  return *this;
}

const FileObject &FileObject::write(const void *buf, int nbyte) const {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL("", interface_write(buf, nbyte));
  return *this;
}

const FileObject &FileObject::seek(int location, Whence whence) const {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL("", interface_lseek(location, static_cast<int>(whence)));
  return *this;
}

int FileObject::location() const {
  return seek(0, Whence::current).return_value();
}

var::String FileObject::gets(char term) const {
  char c = 0;
  var::String result;
  while ((c != term) && is_success()) {
    if (read(var::View(c)).return_value() == 1) {
      result += c;
    } else {
      c = term;
    }
  }

  return std::move(result);
}

const FileObject &FileObject::ioctl(int request, void *argument) const {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL("", interface_ioctl(request, argument));
  return *this;
}

const FileObject &
FileObject::write(const FileObject &source_file, const Write &options) const {
  API_RETURN_VALUE_IF_ERROR(*this);

  if (options.location() != static_cast<u32>(-1)) {
    seek(options.location(), Whence::set);
  }

  size_t size_processed = 0;

  const size_t file_size = (options.size() == static_cast<size_t>(-1))
                             ? source_file.size()
                             : options.size();

  if (file_size == 0) {
    if (options.progress_callback()) {
      options.progress_callback()->update(0, 100);
      options.progress_callback()->update(100, 100);
      options.progress_callback()->update(0, 0);
    }
    return *this;
  }

  chrono::ClockTimer clock_timer;

  const size_t effective_page_size
    = options.page_size() ? options.page_size() : FSAPI_LINK_DEFAULT_PAGE_SIZE;

  const size_t page_size_with_boundary
    = (options.transformer() == nullptr)
        ? (effective_page_size)
        : (
          (effective_page_size / options.transformer()->page_size_boundary())
          * options.transformer()->page_size_boundary());

  const size_t read_buffer_size
    = options.terminator() != '\0' ? 1 : page_size_with_boundary;

  u8 file_read_buffer[read_buffer_size];

  clock_timer.start();
  do {
    const size_t page_size = ((file_size - size_processed) < read_buffer_size)
                               ? file_size - size_processed
                               : read_buffer_size;

    const int bytes_read
      = source_file.read(file_read_buffer, page_size).return_value();

    if (bytes_read > 0) {
      if (options.transformer()) {
        const int transform_size
          = options.transformer()->get_output_size(page_size);
        u8 file_write_buffer[transform_size];
        const int bytes_to_write = options.transformer()->transform(
          var::Transformer::Transform()
            .set_input(var::View(file_read_buffer, page_size))
            .set_output(var::View(file_write_buffer, transform_size)));

        write(file_write_buffer, bytes_to_write);
      } else {
        write(file_read_buffer, bytes_read);
      }

      if (is_error()) {
        return *this;
      }

      size_processed += static_cast<size_t>(bytes_read);
      if (
        options.terminator() != 0
        && static_cast<char>(file_read_buffer[0]) == options.terminator()) {
        break;
      }

    } else {
      // are we on a timeout?
      if (options.timeout() > 0_microseconds) {
        if (clock_timer.micro_time() > options.timeout()) {
          break;
        }

        if (bytes_read < 0) {
          reset_error();
        }

        chrono::wait(options.retry_delay());
      }
    }

    if (options.progress_callback()) {
      // abort the transaction
      if (
        options.progress_callback()->update(
          static_cast<int>(size_processed),
          static_cast<int>(file_size))
        == true) {
        options.progress_callback()->update(0, 0);
        API_SYSTEM_CALL("aborted", size_processed);
        return *this;
      }
    }

  } while ((source_file.return_value() > 0) && (file_size > size_processed));

  // this will terminate the progress operation
  if (options.progress_callback()) {
    options.progress_callback()->update(0, 0);
  }

  if ((source_file.is_error()) && (size_processed == 0)) {
    API_SYSTEM_CALL("", -1);
  } else {
    API_SYSTEM_CALL("", size_processed);
  }

  return *this;
}

void FileObject::fake_seek(
  int &location,
  const size_t size,
  int offset,
  int whence) {
  switch (static_cast<Whence>(whence)) {
  case Whence::current:
    location += offset;
    break;
  case Whence::end:
    location = static_cast<int>(size);
    break;
  case Whence::set:
    location = offset;
    break;
  }

  if (location > static_cast<int>(size)) {
    location = static_cast<int>(size);
  } else if (location < 0) {
    location = 0;
  }
}

File::File(var::StringView name, OpenMode flags) { open(name, flags); }

File::File(
  IsOverwrite is_overwrite,
  var::StringView path,
  OpenMode open_mode,
  Permissions perms) {
  internal_create(is_overwrite, path, open_mode, perms);
}

File::~File() {
  if (fileno() >= 0) {
    close();
  }
}

int File::fileno() const { return m_fd; }

const File &File::sync() const {
  API_RETURN_VALUE_IF_ERROR(*this);
#if defined __link
  if (driver()) {
    return *this;
  }
#endif
  if (m_fd >= 0) {
#if !defined __win32
    API_SYSTEM_CALL("", internal_fsync(m_fd));
#else
    ret = 0;
#endif
  }
  return *this;
}

int File::flags() const {
  API_RETURN_VALUE_IF_ERROR(-1);
#if defined __link
  return -1;
#else
  if (fileno() < 0) {
    API_SYSTEM_CALL("", -1);
    return return_value();
  }
  return _global_impure_ptr->procmem_base->open_file[m_fd].flags;
#endif
}

int File::fstat(struct stat *st) {
  API_RETURN_VALUE_IF_ERROR(-1);
  return API_SYSTEM_CALL("", FSAPI_LINK_FSTAT(driver(), m_fd, st));
}

void File::close() {
  if (m_fd >= 0) {
    internal_close(m_fd);
    m_fd = -1;
  }
}

int File::internal_open(const char *path, int flags, int mode) const {
  return FSAPI_LINK_OPEN(driver(), path, flags, mode);
}

int File::interface_read(void *buf, int nbyte) const {
  return FSAPI_LINK_READ(driver(), m_fd, buf, nbyte);
}

int File::interface_write(const void *buf, int nbyte) const {
  return FSAPI_LINK_WRITE(driver(), m_fd, buf, nbyte);
}

int File::interface_ioctl(int request, void *argument) const {
  return FSAPI_LINK_IOCTL(driver(), m_fd, request, argument);
}

int File::internal_close(int fd) const {
  return FSAPI_LINK_CLOSE(driver(), fd);
}

int File::internal_fsync(int fd) const {
#if defined __link
  return 0;
#else
  return ::fsync(fd);
#endif
}

int File::interface_lseek(int offset, int whence) const {
  return FSAPI_LINK_LSEEK(driver(), m_fd, offset, whence);
}

void File::open(var::StringView path, OpenMode flags, Permissions permissions) {
  API_ASSERT(m_fd == -1);
  API_RETURN_IF_ERROR();
  const var::PathString path_string(path);
  API_SYSTEM_CALL(
    path_string.cstring(),
    m_fd = internal_open(
      path_string.cstring(),
      static_cast<int>(flags.o_flags()),
      permissions.permissions()));
}

void File::internal_create(
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

  open(path, flags, perms);
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
