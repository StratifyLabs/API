// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#include <unistd.h>

#include "fs/Dir.hpp"
#include "var/StackString.hpp"

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
    return {};
  }

  return var::PathString(m_path)
    .append(m_path.string_view() ? '/' : '\0')
    .append(entry);
}

Dir::Dir(var::StringView path)
  : DirAccess<Dir>(path), m_dirp(open(path), &dir_deleter) {}

DIR *Dir::open(var::StringView path) {
  API_RETURN_VALUE_IF_ERROR(nullptr);
  var::PathString path_string(path);
  DIR *result = API_SYSTEM_CALL_NULL(
    path_string.cstring(),
    reinterpret_cast<DIR *>(::opendir(path_string.cstring())));
  if (result) {
    set_path(path_string);
  }
  return result;
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
  while (read() != nullptr) {
    count++;
  }

  seek(loc);

  return count;
}

#endif

int Dir::interface_readdir_r(struct dirent *result, struct dirent **resultp)
  const {
#if defined __linux || defined __win32
  if (const struct dirent *result_dirent = readdir(m_dirp.get());
      result_dirent) {
    *result = *result_dirent;
    if (resultp != nullptr) {
      *resultp = result;
      return 0;
    }
  }
  return -1;
#else
  return ::readdir_r(m_dirp.get(), result, resultp);
#endif
}

long Dir::interface_telldir() const { return ::telldir(m_dirp.get()); }

void Dir::interface_seekdir(size_t location) const {
  ::seekdir(m_dirp.get(), location);
}

void Dir::interface_rewinddir() const { ::rewinddir(m_dirp.get()); }

void Dir::dir_deleter(DIR *dirp) {
  if (dirp != nullptr) {
    closedir(dirp);
  }
}
