//
// Created by Tyler Gilbert on 3/8/22.
//

#if defined __link

#include "fs/AssetFileSystem.hpp"

using namespace fs;
using namespace var;

AssetFileSystem::AssetFileSystem(const FileObject &source) {
  File::LocationScope ls(source);
  m_source.write(source.seek(0));
  u32 count = 0;
  m_source.seek(0).read(View(count));
  m_entry_container.reserve(count);
  for (auto i : api::Index(count)) {
    dirent_t entry;
    m_source.read(View(entry));
    m_entry_container.push_back(entry);
  }
}

PathContainer AssetFileSystem::read_directory() const {
  PathContainer result;
  result.reserve(m_entry_container.count());
  for (const auto &entry : m_entry_container) {
    result.push_back(entry.name);
  }
  return result;
}

DataFile AssetFileSystem::get_file(var::StringView name) const {
  for (const auto &entry : m_entry_container) {
    if (entry.name == name) {
      DataFile result;
      result.write(
        m_source.seek(entry.start),
        File::Write().set_size(entry.size)).seek(0);
      return result;
    }
  }
  return DataFile();
}

#endif