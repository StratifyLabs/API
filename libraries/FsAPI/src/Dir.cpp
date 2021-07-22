// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#include <sys/stat.h>
#include <unistd.h>

#include "fs/Dir.hpp"
#include "fs/File.hpp"
#include "var/StackString.hpp"

#include "fs/FileSystem.hpp"
#include "local.h"

using namespace fs;

const char *DirObject::read() const {
  API_RETURN_VALUE_IF_ERROR(nullptr);
  struct dirent *dirent_result = nullptr;
  interface_readdir_r(&m_entry, &dirent_result);
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
  var::PathString path_string(path);
  m_dirp = API_SYSTEM_CALL_NULL(path_string.cstring(),
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
    API_RETURN_VALUE_ASSIGN_ERROR(-1, "directory is not open", EBADF);
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

int Dir::interface_readdir_r(struct dirent *result,
                             struct dirent **resultp) const {
#if defined __link
  struct dirent *result_dirent = readdir(m_dirp);
  if (result_dirent) {
    memcpy(result, result_dirent, sizeof(struct dirent));
    if (resultp != nullptr) {
      *resultp = result;
      return 0;
    }
  }
  return -1;
#else
  return ::readdir_r(m_dirp, result, resultp);
#endif
}

int Dir::interface_telldir() const { return ::telldir(m_dirp); }

void Dir::interface_seekdir(size_t location) const {
  ::seekdir(m_dirp, location);
}

void Dir::interface_rewinddir() const { ::rewinddir(m_dirp); }
