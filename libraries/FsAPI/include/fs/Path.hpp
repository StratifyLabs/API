#ifndef FSAPI_PATH_HPP
#define FSAPI_PATH_HPP

#include "var/StringView.hpp"

namespace fs {

class Path {
public:
  static var::StringView suffix(const var::StringView path);
  static var::StringView name(const var::StringView path);
  static var::StringView
  parent_directory(const var::StringView path, size_t depth = 1);
  static var::StringView base_name(const var::StringView path);
  static var::StringView no_suffix(const var::StringView path);

  static bool is_hidden(const var::StringView path);

private:
  var::StringView m_path;
};
} // namespace fs

#endif // FSAPI_PATH_HPP
