
#include "sys/TemporaryDirectory.hpp"
#include "chrono/ClockTime.hpp"
#include "fs/FileSystem.hpp"
#include "sys/System.hpp"

using namespace sys;

TemporaryDirectory::TemporaryDirectory(const var::StringView parent)
  : path_resource{
    (parent.is_empty() ? System::user_data_path() : parent)
    / chrono::ClockTime::get_system_time().to_unique_string(), &deleter} {
  fs::FileSystem().create_directory(path_resource.value());
  if (is_error()) {
    path_resource.set_value({});
  }
}

void TemporaryDirectory::deleter(var::PathString *path) {
  if (path->string_view()) {
    fs::FileSystem().remove_directory(*path, fs::FileSystem::IsRecursive::yes);
  }
}
