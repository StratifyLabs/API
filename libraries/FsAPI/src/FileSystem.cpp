// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#include <sys/stat.h>

#include "fs/Dir.hpp"
#include "printer/Printer.hpp"
#include "var/Tokenizer.hpp"

#include "fs/FileSystem.hpp"
#include "fs/Path.hpp"

printer::Printer &
printer::operator<<(printer::Printer &printer, const fs::PathContainer &a) {
  size_t i = 0;
  for (const auto &item : a) {
    printer.key(var::NumberString(i++), item.string_view());
  }
  return printer;
}

using namespace fs;

const FileSystem &FileSystem::remove(var::StringView path) const {
  API_RETURN_VALUE_IF_ERROR(*this);
  const var::PathString path_string(path);
  API_SYSTEM_CALL(
    path_string.cstring(),
    interface_unlink(path_string.cstring()));
  return *this;
}

const FileSystem &FileSystem::touch(var::StringView path) const {
  API_RETURN_VALUE_IF_ERROR(*this);
  char c;
  API_SYSTEM_CALL(
    "",
    File(path, OpenMode::read_write())
      .read(var::View(c))
      .seek(0)
      .write(var::View(c))
      .return_value());
  return *this;
}

const FileSystem &FileSystem::rename(const Rename &options) const {
  API_RETURN_VALUE_IF_ERROR(*this);
  const var::PathString source_string(options.source());
  const var::PathString dest_string(options.destination());
  API_SYSTEM_CALL(
    source_string.cstring(),
    interface_rename(source_string.cstring(), dest_string.cstring()));
  return *this;
}

bool FileSystem::exists(var::StringView path) const {
  API_RETURN_VALUE_IF_ERROR(false);
  const auto info = get_info(path);
  bool result = info.is_valid() && is_success();
  reset_error();
  return result;
}

bool FileSystem::is_create_file_ok(
  var::StringView path,
  IsOverwrite is_overwrite) const {

  const auto parent = Path::parent_directory(path);
  if (parent) {
    if (exists(parent)) {
      if (!get_info(parent).is_directory()) {
        API_RETURN_VALUE_ASSIGN_ERROR(
          false,
          "Parent exists but is not a directory",
          EEXIST);
      }
    } else {
      API_RETURN_VALUE_ASSIGN_ERROR(
        false,
        "Parent directory does not exist",
        EINVAL);
    }
  }

  if (exists(path)) {
    if (is_overwrite == IsOverwrite::no) {
      API_RETURN_VALUE_ASSIGN_ERROR(
        false,
        "Cannot overwrite existing file",
        EEXIST);
    } else if (!get_info(path).is_file()) {
      API_RETURN_VALUE_ASSIGN_ERROR(
        false,
        "Cannot overwrite destination (not a file)",
        EEXIST);
    }
  }

  return true;
}

bool FileSystem::is_create_directory_ok(var::StringView path) const {

  const auto parent = Path::parent_directory(path);
  if (!parent.is_empty()) {
    if (exists(parent)) {
      if (!get_info(parent).is_directory()) {
        API_RETURN_VALUE_ASSIGN_ERROR(
          false,
          "Parent exists but is not a directory",
          EEXIST);
      }
    } else {
      API_RETURN_VALUE_ASSIGN_ERROR(
        false,
        "Parent directory does not exist",
        EINVAL);
    }
  }

  if (exists(path) && !get_info(path).is_directory()) {
    API_RETURN_VALUE_ASSIGN_ERROR(
      false,
      "Cannot create directory (conflict with existing file)",
      EINVAL);
  }

  return true;
}

FileInfo FileSystem::get_info(var::StringView path) const {
  API_RETURN_VALUE_IF_ERROR(FileInfo());
  const var::PathString path_string(path);
  struct stat stat {};
  API_SYSTEM_CALL(
    path_string.cstring(),
    interface_stat(path_string.cstring(), &stat));
  return FileInfo(stat);
}

FileInfo FileSystem::get_info(const File &file) const {
  API_RETURN_VALUE_IF_ERROR(FileInfo());
  struct stat stat {};
  API_SYSTEM_CALL("", interface_fstat(file.fileno(), &stat));
  return FileInfo(stat);
}

const FileSystem &FileSystem::remove_directory(
  var::StringView path,
  IsRecursive recursive) const {

  if (recursive == IsRecursive::yes) {
    Dir d(path);

    const char *entry;
    while ((entry = d.read()) != nullptr) {
      const auto entry_path = path / entry;
      FileInfo info = get_info(entry_path);
      if (info.is_directory()) {
        if (const var::StringView entry_view(entry);
            entry_view != "." && entry_view != ".."
            && remove_directory(entry_path, recursive).is_error()) {
          return *this;
        }

      } else if (remove(entry_path).is_error()) {
        return *this;
      }
    }
  }

  remove_directory(path);
  return *this;
}

const FileSystem &FileSystem::remove_directory(var::StringView path) const {
  API_RETURN_VALUE_IF_ERROR(*this);
  const var::PathString path_string(path);
  API_SYSTEM_CALL(
    path_string.cstring(),
    interface_rmdir(path_string.cstring()));
  return *this;
}

size_t FileSystem::get_entry_count(
  const var::StringView path,
  IsRecursive is_recursive) const {
  Dir directory(path);
  auto result = size_t{};
  const char *entry;
  while ((entry = directory.read()) != nullptr) {
    const var::StringView entry_view = entry;
    if (entry_view != "." && entry_view != "..") {
      ++result;
      if (is_recursive == IsRecursive::yes) {
        const auto entry_path = path / entry;
        const auto info = get_info(entry_path);
        if (info.is_directory()) {
          result += get_entry_count(entry_path, IsRecursive::yes);
        }
      }
    }
  }
  return result;
}

PathList FileSystem::read_directory(
  const var::StringView path,
  IsRecursive is_recursive,
  ExcludeCallback exclude,
  void *context) const {
  PathList result;
  bool is_the_end = false;

  result.reserve(get_entry_count(path, is_recursive));

  Dir directory(path);
  do {
    const char *entry_result = directory.read();
    const var::PathString entry = (entry_result != nullptr)
                                    ? var::PathString(entry_result)
                                    : var::PathString();

    if (entry.is_empty()) {
      is_the_end = true;
    }

    if (
      (exclude == nullptr
       || (exclude(entry.string_view(), context) == IsExclude::no))
      && !entry.is_empty() && (entry.string_view() != ".")
      && (entry.string_view() != "..")) {

      if (is_recursive == IsRecursive::yes) {

        if (const var::PathString entry_path
            = var::PathString(directory.path()) / entry.string_view();
            get_info(entry_path).is_directory()) {
          const auto intermediate_result
            = read_directory(entry_path, is_recursive, exclude, context);

          for (const auto &intermediate_entry : intermediate_result) {
            result.push_back(entry / intermediate_entry);
          }
        } else {
          result.push_back(entry);
        }
      } else {
        result.push_back(entry);
      }
    }

  } while (!is_the_end);

  return result;
}

bool FileSystem::directory_exists(var::StringView path) const {
  API_RETURN_VALUE_IF_ERROR(false);
  bool result = Dir(path).is_success();
  reset_error();
  return result;
}

Permissions FileSystem::get_permissions(var::StringView path) const {
  const var::StringView parent = fs::Path::parent_directory(path);
  if (parent.is_empty()) {
    return get_info(".").permissions();
  }

  return get_info(parent).permissions();
}

const FileSystem &FileSystem::create_directory(
  var::StringView path,
  const Permissions &permissions) const {

  if (directory_exists(path)) {
    return *this;
  }

  const Permissions use_permissions
    = permissions.permissions() == 0 ? get_permissions(path) : permissions;

  const var::PathString path_string(path);
  API_SYSTEM_CALL(
    path_string.cstring(),
    interface_mkdir(path_string.cstring(), use_permissions.permissions()));
  return *this;
}

const FileSystem &FileSystem::create_directory(
  var::StringView path,
  IsRecursive is_recursive,
  const Permissions &permissions) const {

  if (is_recursive == IsRecursive::no) {
    return create_directory(path, permissions);
  }

  var::Tokenizer path_tokens
    = var::Tokenizer(path, var::Tokenizer::Construct().set_delimiters("/"));
  // tokenizer will strip the first / and create an empty token
  var::PathString base_path = (path && path.front() == '/') ? "/" : "";
  for (const auto path_component : path_tokens.list()) {
    if (path_component) {
      base_path &= path_component;
      if (
        !directory_exists(base_path)
        && create_directory(base_path, permissions).is_error()) {
        return *this;
      }
      base_path &= "/";
    }
  }

  return *this;
}

#if !defined __link
Access FileSystem::access(var::StringView path) {
  API_RETURN_VALUE_IF_ERROR(Access());
  const var::PathString path_string(path);
  Access result;
  API_SYSTEM_CALL(
    path_string.cstring(),
    ::access(path_string.cstring(), static_cast<int>(result.o_access())));
  return result;
}
#endif

int FileSystem::interface_mkdir(const char *path, int mode) const {
  return ::mkdir(
    path
#if !defined __win32
    ,
    mode
#endif
  );
}

int FileSystem::interface_rmdir(const char *path) const {
  return ::rmdir(path);
}

int FileSystem::interface_unlink(const char *path) const {
  return ::unlink(path);
}

int FileSystem::interface_stat(const char *path, struct stat *stat) const {
  return ::stat(path, stat);
}

int FileSystem::interface_fstat(int fd, struct stat *stat) const {
  return ::fstat(fd, stat);
}

int FileSystem::interface_rename(const char *old_name, const char *new_name)
  const {
  int result = ::rename(old_name, new_name);
  return result;
}
