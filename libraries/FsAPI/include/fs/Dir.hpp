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

  DirObject(const DirObject &dir) = delete;
  DirObject &operator=(const DirObject &dir) = delete;

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
    API_RETURN_VALUE_IF_ERROR(static_cast<const Derived &>(*this));
    interface_rewinddir();
    return static_cast<const Derived &>(*this);
  }

  Derived &rewind() {
    return API_CONST_CAST_SELF(Derived, rewind);
  }

  const Derived &seek(size_t location) const {
    API_RETURN_VALUE_IF_ERROR(static_cast<const Derived &>(*this));
    interface_seekdir(location);
    return static_cast<const Derived &>(*this);
  }

  Derived &seek(size_t location) {
    return API_CONST_CAST_SELF(Derived, seek, location);
  }
};

class Dir : public DirAccess<Dir> {
public:
  explicit Dir(var::StringView path);
  Dir(const Dir &dir) = delete;
  Dir &operator=(const Dir &dir) = delete;

  Dir(Dir &&dir) noexcept { std::swap(m_dirp, dir.m_dirp); }
  Dir &operator=(Dir &&dir) noexcept {
    std::swap(m_dirp, dir.m_dirp);
    return *this;
  }

  ~Dir() override;

  bool is_open() const { return m_dirp != nullptr; }
  int count() const;

protected:
  Dir &open(var::StringView path);
  Dir &close();

  int interface_readdir_r(dirent *result, dirent **resultp) const override;
  int interface_telldir() const override;
  void interface_seekdir(size_t location) const override;
  void interface_rewinddir() const override;

private:
  DIR *m_dirp = nullptr;
  static DIR *internal_opendir(const char *path);
};

} // namespace fs

#endif /* SAPI_FS_DIR_HPP_ */
