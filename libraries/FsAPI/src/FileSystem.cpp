
#include <sys/stat.h>

#include "chrono/ClockTime.hpp"
#include "fs/Dir.hpp"
#include "printer/Printer.hpp"
#include "sys/System.hpp"
#include "var/StackString.hpp"
#include "var/Tokenizer.hpp"

#include "fs/FileSystem.hpp"
#include "fs/Path.hpp"
#include "local.h"

printer::Printer &
printer::operator<<(printer::Printer &printer, const fs::PathList &a) {
  size_t i = 0;
  for (const auto &item : a) {
    printer.key(var::NumberString(i++), item.string_view());
  }
  return printer;
}

using namespace fs;

FileSystem::FileSystem() {}

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
  bool result = File(path, OpenMode::read_only()).is_success();
  reset_error();
  return result;
}

FileInfo FileSystem::get_info(var::StringView path) const {
  API_RETURN_VALUE_IF_ERROR(FileInfo());
  const var::PathString path_string(path);
  struct stat stat = {0};
  API_SYSTEM_CALL(
    path_string.cstring(),
    interface_stat(path_string.cstring(), &stat));
  return FileInfo(stat);
}

FileInfo FileSystem::get_info(const File &file) const {
  API_RETURN_VALUE_IF_ERROR(FileInfo());
  struct stat stat = {0};
  API_SYSTEM_CALL("", interface_fstat(file.fileno(), &stat));
  return FileInfo(stat);
}

const FileSystem &FileSystem::remove_directory(
  var::StringView path,
  IsRecursive recursive) const {

  if (recursive == IsRecursive::yes) {
    Dir d(path);

    var::String entry;
    while ((entry = d.read()).is_empty() == false) {
      var::String entry_path = path + "/" + entry;
      FileInfo info = get_info(entry_path);
      if (info.is_directory()) {
        if (entry != "." && entry != "..") {
          if (remove_directory(entry_path, recursive).is_error()) {
            return *this;
          }
        }

      } else {
        if (remove(entry_path).is_error()) {
          return *this;
        }
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

PathList FileSystem::read_directory(
  const var::StringView path,
  IsRecursive is_recursive,
  bool (*exclude)(var::StringView entry)) const {
  PathList result;
  bool is_the_end = false;

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
      (exclude == nullptr || !exclude(entry.string_view())) && !entry.is_empty()
      && (entry.string_view() != ".") && (entry.string_view() != "..")) {

      if (is_recursive == IsRecursive::yes) {

        const var::PathString entry_path
          = var::PathString(directory.path()) / entry.string_view();
        FileInfo info = get_info(entry_path.cstring());

        if (info.is_directory()) {
          PathList intermediate_result
            = read_directory(entry_path, is_recursive, exclude);

          for (const auto &intermediate_entry : intermediate_result) {
            const var::PathString intermediate_path
              = var::PathString(entry_path) / intermediate_entry;

            result.push_back(intermediate_path);
          }
        } else {
          result.push_back(entry_path);
        }
      } else {
        result.push_back(entry);
      }
    }
  } while (!is_the_end);

  return std::move(result);
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
    = var::Tokenizer(path, var::Tokenizer::Construct().set_delimeters("/"));
  var::String base_path;

  // tokenizer will strip the first / and create an empty token
  if (path.length() && path.front() == '/') {
    base_path += "/";
  }

  for (u32 i = 0; i < path_tokens.count(); i++) {
    if (path_tokens.at(i).is_empty() == false) {
      base_path += path_tokens.at(i);
      if (create_directory(base_path.cstring(), permissions)
            .is_error()) {
        return *this;
      }
      base_path += "/";
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
  return ::mkdir(path, mode);
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
  return ::rename(old_name, new_name);
}

TemporaryDirectory::TemporaryDirectory(var::StringView parent)
  : m_path(
    var::PathString()
      .append(
        parent.is_empty() ? (
          var::PathString(sys::System::user_data_path()).append("/").cstring())
                          : "")
      .append(chrono::ClockTime::get_unique_string().cstring())) {
  FileSystem().create_directory(m_path);
  if (is_error()) {
    m_path.clear();
  }
}

TemporaryDirectory::~TemporaryDirectory() {
  if (m_path.is_empty() == false) {
    FileSystem().remove_directory(m_path, FileSystem::IsRecursive::yes);
  }
}
