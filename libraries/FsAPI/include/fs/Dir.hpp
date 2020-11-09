/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.

#ifndef SAPI_FS_DIR_HPP_
#define SAPI_FS_DIR_HPP_

#ifdef __link
#if defined __win32
#include <windows.h>
#include <winsock2.h>
#if !defined FALSE
#define FALSE 0
#endif
#if !defined TRUE
#define TRUE 1
#endif
#include "dirent_windows.h"
#undef ERROR
#else
#include <dirent.h>
#endif

#include <sos/link.h>

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

  DirObject() {}

  DirObject(const DirObject &dir) = delete;
  DirObject &operator=(const DirObject &dir) = delete;
  DirObject(DirObject &&dir) = default;
  DirObject &operator=(DirObject &&dir) = default;

  static const var::String filter_hidden(const var::String &entry) {
    if (!entry.is_empty() && entry.front() == '.') {
      return var::String();
    }
    return entry;
  }

  class Copy {
    API_AC(Copy, var::StringView, source_path);
    API_AC(Copy, var::StringView, destination_path);
#if defined __link
    API_AF(Copy, link_transport_mdriver_t *, source_driver, nullptr);
    API_AF(Copy, link_transport_mdriver_t *, destination_driver, nullptr);
#endif
  };

  const char *read() const;
  var::PathString get_entry() const;
  const char *entry_name() const { return m_entry.d_name; }
  int ino() { return m_entry.d_ino; }
  int count() const;

  const DirObject &rewind() const {
    API_RETURN_VALUE_IF_ERROR(*this);
    interface_rewinddir();
    return *this;
  }

  DirObject &rewind() { return API_CONST_CAST_SELF(DirObject, rewind); }

  const DirObject &seek(size_t location) const {
    API_RETURN_VALUE_IF_ERROR(*this);
    interface_seekdir(location);
    return *this;
  }

  DirObject &seek(size_t location) {
    return API_CONST_CAST_SELF(DirObject, seek, location);
  }

  inline long tell() const {
    API_RETURN_VALUE_IF_ERROR(-1);
    return interface_telldir();
  }

  const var::PathString &path() const { return m_path; }

protected:
  void set_path(const var::StringView path) { m_path = path; }
  virtual int interface_readdir_r(dirent *result, dirent **resultp) const = 0;

  virtual int interface_closedir() const = 0;
  virtual int interface_telldir() const = 0;
  virtual void interface_seekdir(size_t location) const = 0;
  virtual void interface_rewinddir() const = 0;

private:
  mutable struct dirent m_entry = {0};
  var::PathString m_path;
};

template <class Derived> class DirAccess : public DirObject {
public:
  const Derived &rewind() const {
    return static_cast<const Derived &>(DirObject::rewind());
  }

  Derived &rewind() { return static_cast<Derived &>(DirObject::rewind()); }

  const Derived &seek(size_t location) const {
    return static_cast<const Derived &>(DirObject::seek(location));
  }

  Derived &seek(size_t location) {
    return static_cast<Derived &>(DirObject::seek(location));
  }
};

class Dir : public DirAccess<Dir> {
public:
  Dir(var::StringView path);
  Dir(const Dir &dir) = delete;
  Dir &operator=(const Dir &dir) = delete;
  Dir(Dir &&dir) { std::swap(m_dirp, dir.m_dirp); }
  Dir &operator=(Dir &&dir) {
    std::swap(m_dirp, dir.m_dirp);
    return *this;
  }
  ~Dir();
  bool is_open() const { return m_dirp != nullptr; }
  int count() const;

protected:
  Dir &open(var::StringView path);
  Dir &close();

  virtual int interface_readdir_r(dirent *result, dirent **resultp) const;
  virtual int interface_closedir() const;
  virtual int interface_telldir() const;
  virtual void interface_seekdir(size_t location) const;
  virtual void interface_rewinddir() const;

private:
  DIR *m_dirp = nullptr;
  DIR *interface_opendir(const char *path) const;
};

} // namespace fs

#endif /* SAPI_FS_DIR_HPP_ */
