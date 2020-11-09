/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
// Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc

#include <sys/stat.h>
#include <unistd.h>

#include "fs/Dir.hpp"
#include "fs/File.hpp"
#include "var/StackString.hpp"
#include "var/Tokenizer.hpp"

#include "fs/FileSystem.hpp"
#include "local.h"

using namespace fs;

const char *DirObject::read() const {
  API_RETURN_VALUE_IF_ERROR(nullptr);
  struct dirent *dirent_result = nullptr;
  int result;
  result = interface_readdir_r(&m_entry, &dirent_result);
  if (dirent_result == nullptr) {
    return nullptr;
  }
  return m_entry.d_name;
}

var::PathString DirObject::get_entry() const {
  const char *entry = read();

  if (entry == nullptr) {
    return var::PathString();
  }

  return var::PathString(m_path)
    .append((m_path.is_empty() == false) ? "/" : "")
    .append(entry);
}

Dir::Dir(var::StringView path) { open(path); }

Dir::~Dir() { close(); }

Dir &Dir::open(var::StringView path) {
  API_RETURN_VALUE_IF_ERROR(*this);
  const var::PathString path_string(path);
  m_dirp = API_SYSTEM_CALL_NULL(
    path_string.cstring(),
    interface_opendir(path_string.cstring()));
  if (m_dirp) {
    set_path(path_string);
  }
  return *this;
}

#if !defined __link
int Dir::count() const {
  API_RETURN_VALUE_IF_ERROR(-1);
  long loc;
  int count;

  if (!is_open()) {
    API_RETURN_VALUE_ASSIGN_ERROR(-1, "", EBADF);
  }

#if defined __link

#else
  loc = tell();
#endif

#if defined __link

#else
  rewind();
#endif

  count = 0;
  while (read() != 0) {
    count++;
  }

  seek(loc);

  return count;
}

#endif

Dir &Dir::close() {
  API_RETURN_VALUE_IF_ERROR(*this);
  if (m_dirp) {
    API_SYSTEM_CALL(path().cstring(), ::closedir(m_dirp));
  }

  set_path("");
  return *this;
}

DIR *Dir::interface_opendir(const char *path) const {
  return reinterpret_cast<DIR *>(::opendir(path));
}

int Dir::interface_readdir_r(
  struct dirent *result,
  struct dirent **resultp) const {
  return ::readdir_r(m_dirp, result, resultp);
}

int Dir::interface_closedir() const { return ::closedir(m_dirp); }

int Dir::interface_telldir() const { return ::telldir(m_dirp); }

void Dir::interface_seekdir(size_t location) const {
  ::seekdir(m_dirp, location);
}

void Dir::interface_rewinddir() const { ::rewinddir(m_dirp); }
