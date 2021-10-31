
#include "sys/TemporaryDirectory.hpp"
#include "chrono/ClockTime.hpp"
#include "fs/FileSystem.hpp"
#include "sys/System.hpp"

using namespace sys;

TemporaryDirectory::TemporaryDirectory(const var::StringView parent)
  : m_path(
    (parent.is_empty() ? System::user_data_path() : parent)
    / chrono::ClockTime::get_system_time().to_unique_string()) {
  fs::FileSystem().create_directory(m_path);
  if (is_error()) {
    m_path.clear();
  }
}

TemporaryDirectory::~TemporaryDirectory() {
  if (!m_path.is_empty()) {
    fs::FileSystem().remove_directory(m_path, fs::FileSystem::IsRecursive::yes);
  }
}
