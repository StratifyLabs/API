//
// Created by Tyler Gilbert on 3/8/22.
//

#ifndef FSAPI_FS_ASSET_FILE_SYSTEM_HPP
#define FSAPI_FS_ASSET_FILE_SYSTEM_HPP

#if defined __link

#include "File.hpp"
#include "FileSystem.hpp"
#include "DataFile.hpp"

namespace fs {

class AssetFileSystem : public api::ExecutionContext {
public:
  explicit AssetFileSystem(const FileObject & source);
  PathContainer read_directory() const;

  DataFile get_file(var::StringView name) const;

private:
  static constexpr size_t filesystem_name_max = 255;

  typedef struct MCU_PACK {
    char name[filesystem_name_max + 1];
    u32 start;
    u32 size;
    u16 uid;
    u16 mode;
  } dirent_t;

  typedef struct {
    u32 count;
    const dirent_t entries[];
  } header_t;

  DataFile m_source;
  var::Vector<dirent_t> m_entry_container;

};

}

#endif

#endif // FSAPI_FS_ASSET_FILE_SYSTEM_HPP
