// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef FSAPI_FILEINFO_HPP_
#define FSAPI_FILEINFO_HPP_

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#if defined __win32
#define O_NONBLOCK 0
#else
#if !defined O_BINARY
#define O_BINARY 0
#endif
#endif

#include "var/StringView.hpp"

#include "macros.hpp"

namespace fs {

class FileInfoFlags {
public:
  enum class PermissionFlags {
    none API_MAYBE_UNUSED = 0,
    public_execute API_MAYBE_UNUSED = 0001,
    public_write API_MAYBE_UNUSED = 0002,
    public_read API_MAYBE_UNUSED = 0004,
    group_execute API_MAYBE_UNUSED = 0010,
    group_write API_MAYBE_UNUSED = 0020,
    group_read API_MAYBE_UNUSED = 0040,
    owner_execute API_MAYBE_UNUSED = 0100,
    owner_write API_MAYBE_UNUSED = 0200,
    owner_read API_MAYBE_UNUSED = 0400,
  };

  enum class OpenFlags {
    null = 0,
    read_only /*! Open as read-only */ = O_RDONLY,
    write_only /*! Open as write-only */ = O_WRONLY,
    create /*! Create when opening (files) */ = O_CREAT,
    truncate /*! Truncate when opening (files) */ = O_TRUNC,
    append /*! Append when opening (files)*/ = O_APPEND,
    exclusive /*! Create exclusively (files) */ = O_EXCL,
    read_write /*! Open as read-write */ = O_RDWR,
    non_block /*! Open as non-blocking */ = O_NONBLOCK,
    no_delay /*! Open as non-blocking */ = O_NONBLOCK,
    binary = O_BINARY,
    access_mode /*! Access mode mask */ = O_ACCMODE
  };

  enum class AccessFlags {
    null = 0,
    read_ok /*! Check if read access is allowed */ = R_OK,
    write_ok /*! Check if write access is allowed */ = W_OK,
    execute_ok /*! Check if execute access is allowed */ = X_OK,
    file_ok /*! Check if file exists */ = F_OK
  };

  enum class TypeFlags {
    null = 0,
    mask /*! Mode format mask */ = S_IFMT,
#if defined S_IFSOCK
    file_socket /*! Mode Socket mask */ = S_IFSOCK,
#endif
    regular /*! Mode regular file value */ = S_IFREG,
#if defined S_IFBLK
    block /*! Mode block device value */ = S_IFBLK,
#endif
    character /*! Mode character device value */ = S_IFCHR,
    directory /*! Mode directory value */ = S_IFDIR,
    fifo /*! Mode FIFO value */ = S_IFDIR,
#if defined S_IFLNK
    symbolic_link /*! Mode symbolic link value */ = S_IFLNK
#endif
  };
};

API_OR_NAMED_FLAGS_OPERATOR(FileInfoFlags, OpenFlags)
API_OR_NAMED_FLAGS_OPERATOR(FileInfoFlags, PermissionFlags)
API_OR_NAMED_FLAGS_OPERATOR(FileInfoFlags, AccessFlags)
API_OR_NAMED_FLAGS_OPERATOR(FileInfoFlags, TypeFlags)

class Permissions : public FileInfoFlags {
public:
  explicit Permissions(int mode = 0666) {
    m_permissions = static_cast<PermissionFlags>(mode);
  }

  API_NO_DISCARD API_MAYBE_UNUSED static Permissions all_access() {
    return Permissions(0777);
  }
  API_NO_DISCARD API_MAYBE_UNUSED static Permissions read_only() {
    return Permissions(0444);
  }
  API_NO_DISCARD API_MAYBE_UNUSED static Permissions write_only() {
    return Permissions(0222);
  }

  API_NO_DISCARD API_MAYBE_UNUSED bool is_owner_read() const {
    return m_permissions & PermissionFlags::owner_read;
  }
  API_NO_DISCARD API_MAYBE_UNUSED bool is_owner_write() const {
    return m_permissions & PermissionFlags::owner_write;
  }
  API_NO_DISCARD API_MAYBE_UNUSED bool is_owner_execute() const {
    return m_permissions & PermissionFlags::owner_execute;
  }
  API_NO_DISCARD API_MAYBE_UNUSED bool is_public_read() const {
    return m_permissions & PermissionFlags::public_read;
  }
  API_NO_DISCARD API_MAYBE_UNUSED bool is_public_write() const {
    return m_permissions & PermissionFlags::public_write;
  }
  API_NO_DISCARD API_MAYBE_UNUSED bool is_public_execute() const {
    return m_permissions & PermissionFlags::public_execute;
  }

  API_MAYBE_UNUSED Permissions &set_owner_read() {
    m_permissions |= PermissionFlags::owner_read;
    return *this;
  }
  API_MAYBE_UNUSED Permissions &set_owner_write() {
    m_permissions |= PermissionFlags::owner_write;
    return *this;
  }
  API_MAYBE_UNUSED Permissions &set_owner_execute() {
    m_permissions |= PermissionFlags::owner_execute;
    return *this;
  }

  API_MAYBE_UNUSED Permissions &set_public_read() {
    m_permissions |= PermissionFlags::public_read;
    return *this;
  }
  API_MAYBE_UNUSED Permissions &set_public_write() {
    m_permissions |= PermissionFlags::public_write;
    return *this;
  }
  API_MAYBE_UNUSED Permissions &set_public_execute() {
    m_permissions |= PermissionFlags::public_execute;
    return *this;
  }

  bool operator==(const Permissions &a) const {
    return a.m_permissions == m_permissions;
  }

  API_NO_DISCARD int permissions() const {
    return static_cast<int>(m_permissions) & 0777;
  }

private:
  PermissionFlags m_permissions;
};

class OpenMode : public FileInfoFlags {
public:
  OpenMode() { m_flags = OpenFlags::null; }
  explicit OpenMode(OpenFlags flags) {
    m_flags = static_cast<OpenFlags>(flags) | OpenFlags::binary;
  }

  static OpenMode create() {
    return OpenMode(OpenFlags::create | OpenFlags::read_write);
  }
  static OpenMode create_append_write_only() {
    return OpenMode(
      OpenFlags::create | OpenFlags::write_only | OpenFlags::append);
  }
  static OpenMode create_truncate() {
    return OpenMode(
      OpenFlags::create | OpenFlags::read_write | OpenFlags::truncate);
  }
  static OpenMode append() {
    return OpenMode(OpenFlags::read_write | OpenFlags::append);
  }
  static OpenMode append_read_write() {
    return OpenMode(OpenFlags::read_write | OpenFlags::append);
  }
  static OpenMode read_write() { return OpenMode(OpenFlags::read_write); }
  static OpenMode read_only() { return OpenMode(OpenFlags::read_only); }
  static OpenMode write_only() { return OpenMode(OpenFlags::write_only); }
  static OpenMode append_write_only() {
    return OpenMode(OpenFlags::write_only | OpenFlags::append);
  }

  API_NO_DISCARD bool is_read_only() const {
    return access() == OpenFlags::read_only;
  }
  API_NO_DISCARD bool is_write_only() const {
    return access() == OpenFlags::write_only;
  }
  API_NO_DISCARD bool is_read_write() const {
    return access() == OpenFlags::read_write;
  }
  API_NO_DISCARD OpenFlags access() const {
    OpenFlags result = m_flags;
    return result &= OpenFlags::access_mode;
  }

  API_NO_DISCARD bool is_create() const { return m_flags & OpenFlags::create; }
  API_NO_DISCARD bool is_exclusive() const {
    return m_flags & OpenFlags::exclusive;
  }
  API_NO_DISCARD bool is_truncate() const {
    return m_flags & OpenFlags::truncate;
  }
  API_NO_DISCARD bool is_append() const { return m_flags & OpenFlags::append; }
  API_NO_DISCARD bool is_non_blocking() const {
    return m_flags & OpenFlags::non_block;
  }

  OpenMode &set_read_only() {
    clear_access();
    m_flags |= OpenFlags::read_only;
    return *this;
  }
  OpenMode &set_write_only() {
    clear_access();
    m_flags |= OpenFlags::write_only;
    return *this;
  }
  OpenMode &set_read_write() {
    clear_access();
    m_flags |= OpenFlags::read_write;
    return *this;
  }
  OpenMode &set_create() {
    m_flags |= OpenFlags::create;
    return *this;
  }
  OpenMode &set_truncate() {
    m_flags |= OpenFlags::truncate;
    return *this;
  }
  OpenMode &set_append() {
    m_flags |= OpenFlags::append;
    return *this;
  }
  OpenMode &set_exclusive() {
    m_flags |= OpenFlags::exclusive;
    return *this;
  }
  OpenMode &set_non_blocking() {
    m_flags |= OpenFlags::non_block;
    return *this;
  }

  API_NO_DISCARD OpenFlags o_flags() const { return m_flags; }

private:
  void clear_access() { m_flags &= ~OpenFlags::access_mode; }

  OpenFlags m_flags = OpenFlags::null;
};

class Access : public FileInfoFlags {
public:
  explicit Access(
    AccessFlags access = AccessFlags::read_ok | AccessFlags::write_ok
                         | AccessFlags::file_ok | AccessFlags::execute_ok) {
    m_access = access;
  }

  API_NO_DISCARD bool is_read_ok() const {
    return (m_access & AccessFlags::read_ok);
  }
  API_NO_DISCARD bool is_write_ok() const {
    return (m_access & AccessFlags::write_ok);
  }
  API_NO_DISCARD bool is_file_ok() const {
    return (m_access & AccessFlags::file_ok);
  }
  API_NO_DISCARD bool is_execute_ok() const {
    return (m_access & AccessFlags::execute_ok);
  }

  Access &set_read_ok() {
    m_access |= AccessFlags::read_ok;
    return *this;
  }
  Access &set_write_ok() {
    m_access |= AccessFlags::write_ok;
    return *this;
  }
  Access &set_file_ok() {
    m_access |= AccessFlags::file_ok;
    return *this;
  }
  Access &set_execute_ok() {
    m_access |= AccessFlags::execute_ok;
    return *this;
  }

  API_NO_DISCARD AccessFlags o_access() const { return m_access; }

private:
  AccessFlags m_access;
};

class FileInfo : public OpenMode {
public:
  FileInfo();
  explicit FileInfo(
    const struct stat &st) // cppcheck-suppress[noExplicitConstructor]
    : m_stat(st) {}

  API_NO_DISCARD bool is_valid() const { return m_stat.st_mode != 0; }
  API_NO_DISCARD bool is_directory() const;
  API_NO_DISCARD bool is_file() const;
  API_NO_DISCARD bool is_device() const;
  API_NO_DISCARD bool is_block_device() const;
  API_NO_DISCARD bool is_character_device() const;
  API_NO_DISCARD bool is_socket() const;
  API_NO_DISCARD bool is_fifo() const;
  API_NO_DISCARD u32 size() const;

  API_NO_DISCARD Permissions permissions() const {
    return Permissions(m_stat.st_mode);
  }

  API_NO_DISCARD int owner() const { return m_stat.st_uid; }
  API_NO_DISCARD int group() const { return m_stat.st_gid; }

private:
  struct stat m_stat;
};

} /* namespace fs */

namespace printer {
class Printer;
Printer &operator<<(Printer &printer, const fs::FileInfo &a);
} // namespace printer

#endif /* FSAPI_FILEINFO_HPP_ */
