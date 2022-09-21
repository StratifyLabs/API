// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef FSAPI_FS_FILESYSTEM_HPP
#define FSAPI_FS_FILESYSTEM_HPP

#include "Dir.hpp"

namespace fs {

/*! \details
 *
 * This is used when reading a FileSystem directory.
 *
 */
using PathContainer = var::Vector<var::PathString>;
using PathList = PathContainer;

/*! \details
 *
 * This class is used for interacting with a filesystem. It makes
 * it easy to check if a file exists, read the contents of a directory,
 * or check is a file can be created on a specified path.
 *
 *
 */
class FileSystem : public api::ExecutionContext {
public:
  using IsOverwrite = File::IsOverwrite;
  using IsRecursive = Dir::IsRecursive;
  enum class IsExclude { no, yes };

  using ExcludeCallback = IsExclude (*)(var::StringView name, void *);

  FileSystem() = default;

#if !defined __link
  API_NO_DISCARD Access access(var::StringView path);
#endif

  API_NO_DISCARD bool exists(var::StringView path) const;

  /*! \details
   *
   * Check to see if it is OK to create a file.
   *
   * @param path Path to the new file
   * @param is_overwrite Is it ok to overwrite an existing file?
   * @return true if a file can be created at `path`
   *
   * If this function returns `false`, it will update the error
   * context with a message and error number.
   *
   * The function checks:
   *
   * - If a parent directory is specified, does it exist (and is it a directory)
   * - Does a non-file already exist at `path`
   * - If `is_overwrite` is no, does a file exist at `path`
   *
   */
  API_NO_DISCARD bool is_create_file_ok(var::StringView path, IsOverwrite is_overwrite) const;

  /*! \details
   *
   * Check to see if it is OK to create a directory.
   *
   * @param path Path to the new file
   * @return true if a directory can be created at `path`
   *
   * If this function returns `false`, it will update the error
   * context with a message and error number.
   *
   * The function checks:
   *
   * - If a parent directory is specified, does it exist (and is it a directory)
   * - Does a non-directory already exist at `path`
   *
   * If a directory already exists at `path`, this returns `true`.
   *
   */
  API_NO_DISCARD bool is_create_directory_ok(var::StringView path) const;

  const FileSystem &remove(var::StringView path) const;
  const FileSystem &remove_directory(var::StringView path) const;

  const FileSystem &
  remove_directory(var::StringView path, IsRecursive recursive) const;

  bool directory_exists(var::StringView path) const;


  /*! \details
   *
   * This function creates a new directory. If the directory already exists,
   * no action is taken. The directory's immediate parent
   * must exist (and be a directory).
   *
   */
  const FileSystem &create_directory(
    var::StringView path,
    const Permissions &permissions = Permissions(0)) const;


  /*! \details
   *
   * This function creates a new directory. If the directory already exists,
   * no action is taken. If the immediate parent directory
   * does not exist and you pass `IsRecursive::yes` to the funtion,
   * all upstream directories are created as needed.
   *
   */
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

};

} // namespace fs

namespace printer {
class Printer;
Printer &operator<<(Printer &printer, const fs::PathContainer &a);
} // namespace printer

#endif // FSAPI_FS_FILESYSTEM_HPP
