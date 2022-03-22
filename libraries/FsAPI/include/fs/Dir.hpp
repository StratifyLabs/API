// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef SAPI_FS_DIR_HPP_
#define SAPI_FS_DIR_HPP_

#ifdef __link
#if defined __win32
#include <winsock2.h>
// keep this space so the formatter doesn't put windows.h before winsock2.h
#include <windows.h>
#if !defined FALSE
#define FALSE 0
#endif
#if !defined TRUE
#define TRUE 1
#endif
#include <dirent.h>
#undef ERROR
#else
#include <dirent.h>
#endif

#else
#include <dirent.h>
#endif
#include <functional>

#include "var/StackString.hpp"
#include "var/Vector.hpp"

#include "File.hpp"
#include "FileInfo.hpp"

namespace fs {

class DirObject : public api::ExecutionContext {
public:
  enum class IsRecursive { no, yes };

  DirObject() = default;
  virtual ~DirObject() = default;

  static var::PathString filter_hidden(const var::PathString &entry) {
    if (!entry.is_empty() && entry.string_view().front() == '.') {
      return {};
    }
    return entry;
  }

  const char *read() const;
  API_NO_DISCARD var::PathString get_entry() const;
  API_NO_DISCARD const char *entry_name() const { return m_entry.d_name; }
  API_NO_DISCARD ssize_t ino() const { return m_entry.d_ino; }
  API_NO_DISCARD int count() const;

  inline long tell() const {
    API_RETURN_VALUE_IF_ERROR(-1);
    return interface_telldir();
  }

  const var::PathString &path() const { return m_path; }

protected:
  void set_path(const var::StringView path) { m_path = path; }
  virtual int interface_readdir_r(dirent *result, dirent **resultp) const = 0;

  virtual long interface_telldir() const = 0;
  virtual void interface_seekdir(size_t location) const = 0;
  virtual void interface_rewinddir() const = 0;

private:
  mutable struct dirent m_entry = {};
  var::PathString m_path;
};

template <class Derived> class DirAccess : public DirObject {
public:
  const Derived &rewind() const {
    API_RETURN_VALUE_IF_ERROR(static_cast<const Derived &>(*this));
    interface_rewinddir();
    return static_cast<const Derived &>(*this);
  }

  Derived &rewind() {
    API_RETURN_VALUE_IF_ERROR(static_cast<Derived &>(*this));
    interface_rewinddir();
    return static_cast<Derived &>(*this);
  }

  const Derived &seek(size_t location) const {
    API_RETURN_VALUE_IF_ERROR(static_cast<const Derived &>(*this));
    interface_seekdir(location);
    return static_cast<const Derived &>(*this);
  }

  Derived &seek(size_t location) {
    API_RETURN_VALUE_IF_ERROR(static_cast<Derived &>(*this));
    interface_seekdir(location);
    return static_cast<Derived &>(*this);
  }
};


/*! \details
 *
 * This class is a wrapper for POSIX directory
 * access functions opendir(), readdir(), closedir().
 *
 */
class Dir : public DirAccess<Dir> {
public:
  explicit Dir(var::StringView path);

  bool is_open() const { return m_dirp != nullptr; }
  int count() const;

protected:
  int interface_readdir_r(dirent *result, dirent **resultp) const override;
  long interface_telldir() const override;
  void interface_seekdir(size_t location) const override;
  void interface_rewinddir() const override;

private:
  static void dir_deleter(DIR *dirp);
  std::unique_ptr<DIR, decltype(&dir_deleter)> m_dirp;

  DIR *open(var::StringView path);
};

} // namespace fs

#endif /* SAPI_FS_DIR_HPP_ */
