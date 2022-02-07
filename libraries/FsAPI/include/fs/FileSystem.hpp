// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef FSAPI_FS_FILESYSTEM_HPP
#define FSAPI_FS_FILESYSTEM_HPP

#include "Dir.hpp"

namespace fs {

using PathContainer = var::Vector<var::PathString>;
using PathList = PathContainer;

class FileSystem : public api::ExecutionContext {
public:
  using IsOverwrite = File::IsOverwrite;
  using IsRecursive = Dir::IsRecursive;
  enum class IsExclude { no, yes };

  using ExcludeCallback = IsExclude (*)(const var::StringView name, void *);

  FileSystem();

#if !defined __link
  API_NO_DISCARD Access access(var::StringView path);
#endif

  API_NO_DISCARD bool exists(var::StringView path) const;

  const FileSystem &remove(var::StringView path) const;
  const FileSystem &remove_directory(var::StringView path) const;

  const FileSystem &
  remove_directory(var::StringView path, IsRecursive recursive) const;

  bool directory_exists(var::StringView path) const;

  const FileSystem &create_directory(
    var::StringView path,
    const Permissions &permissions = Permissions(0)) const;

  const FileSystem &create_directory(
    var::StringView path,
    IsRecursive is_recursive,
    const Permissions &permissions = Permissions(0)) const;

  API_NO_DISCARD size_t get_entry_count(
    var::StringView path,
    IsRecursive is_recursive = IsRecursive::no) const;

  API_NO_DISCARD PathContainer read_directory(
    var::StringView path,
    IsRecursive is_recursive = IsRecursive::no,
    ExcludeCallback exclude = nullptr,
    void *context = nullptr) const;

  class Rename {
    API_AC(Rename, var::StringView, source);
    API_AC(Rename, var::StringView, destination);
  };

  const FileSystem &rename(const Rename &options) const;
  inline const FileSystem &operator()(const Rename &options) const {
    return rename(options);
  }

  const FileSystem &touch(var::StringView path) const;

  API_NO_DISCARD FileInfo get_info(var::StringView path) const;
  API_NO_DISCARD FileInfo get_info(const File &file) const;

#if !defined __link
  int access(var::StringView path, const Access &access);
#endif

protected:
  API_NO_DISCARD Permissions get_permissions(var::StringView path) const;

  API_NO_DISCARD int interface_mkdir(const char *path, int mode) const;
  API_NO_DISCARD int interface_rmdir(const char *path) const;
  API_NO_DISCARD int interface_unlink(const char *path) const;
  API_NO_DISCARD int interface_stat(const char *path, struct stat *stat) const;
  API_NO_DISCARD int interface_fstat(int fd, struct stat *stat) const;
  API_NO_DISCARD int
  interface_rename(const char *old_name, const char *new_name) const;

private:
};

} // namespace fs

namespace printer {
class Printer;
Printer &operator<<(Printer &printer, const fs::PathContainer &a);
} // namespace printer

#endif // FSAPI_FS_FILESYSTEM_HPP
