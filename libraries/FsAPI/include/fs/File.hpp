// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef FS_API_FS_FILE_HPP_
#define FS_API_FS_FILE_HPP_

#include "FileObject.hpp"

namespace fs {

class File : public FileAccess<File> {
public:
  File() = default;
  explicit File(var::StringView name, OpenMode flags = OpenMode::read_only());

  File(
    IsOverwrite is_overwrite,
    var::StringView path,
    OpenMode flags = OpenMode::read_write(),
    Permissions perms = Permissions(0666));

  API_NO_DISCARD bool is_valid() const { return fileno() >= 0; }

  API_NO_DISCARD int fileno() const;
  API_NO_DISCARD int flags() const;
  File &set_fileno(int fd) {
    m_fd.set_value(fd);
    return *this;
  }

  class DescriptorScope {
  public:
    DescriptorScope(File &file, int file_descriptor) : m_file(&file) {
      file.set_fileno(file_descriptor);
    }

    DescriptorScope(const DescriptorScope &) = delete;
    DescriptorScope& operator =(const DescriptorScope &) = delete;
    DescriptorScope(DescriptorScope &&) = delete;
    DescriptorScope& operator =(DescriptorScope &&) = delete;

    ~DescriptorScope() { m_file->set_fileno(-1); }

  private:
    File * m_file = nullptr;
  };

protected:
  API_NO_DISCARD int interface_lseek(int offset, int whence) const override;
  API_NO_DISCARD int interface_read(void *buf, int nbyte) const override;
  API_NO_DISCARD int interface_write(const void *buf, int nbyte) const override;
  API_NO_DISCARD int
  interface_ioctl(int request, void *argument) const override;

  API_NO_DISCARD int interface_fsync() const override;

private:
  static void file_descriptor_deleter(int * fd_ptr);
  using FileDescriptor = api::SystemResource<int, decltype(&file_descriptor_deleter)>;
  FileDescriptor m_fd = FileDescriptor(-1);

  API_NO_DISCARD int fstat(struct stat *st) const;

  int internal_create(
    IsOverwrite is_overwrite,
    var::StringView path,
    OpenMode open_mode,
    Permissions perms);

  int open(
    var::StringView name,
    OpenMode flags = OpenMode::read_write(),
    Permissions perms = Permissions(0666));

  // open/close are part of construction/deconstruction and can't be virtual
  static void internal_close(int fd);
  API_NO_DISCARD static int
  internal_open(const char *path, int flags, int mode);
};

class NullFile : public FileAccess<NullFile> {
public:
  explicit NullFile(size_t size = 0) : m_size(size) {}

  NullFile(const NullFile &) = delete;
  NullFile &operator=(const NullFile &) = delete;
  NullFile(NullFile &&) = default;
  NullFile &operator=(NullFile &&) = default;

private:
  mutable int m_location = 0;
  mutable size_t m_size;

  API_NO_DISCARD int interface_read(void *buf, int nbyte) const override;
  API_NO_DISCARD int interface_write(const void *buf, int nbyte) const override;
  API_NO_DISCARD int interface_lseek(int offset, int whence) const override;

  API_NO_DISCARD int
  interface_ioctl(int request, void *argument) const override {
    return fake_ioctl(request, argument);
  }
};

} // namespace fs

#endif /* FS_API_FS_FILE_HPP_ */
