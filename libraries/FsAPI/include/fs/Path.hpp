// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef FSAPI_PATH_HPP
#define FSAPI_PATH_HPP

#include "var/StringView.hpp"

namespace fs {

/*! \details
 *
 * This class contains functions that are useful for parsing
 * file paths. The class does not store any data. You pass
 * it a var::StringView and it returns a var::StringView.
 *
 * For example:
 *
 * ```cpp
 * #include <fs.hpp>
 * #include <var.hpp>
 *
 * const auto path = PathString("/Users/parent_directory/base_name.suffix");
 *
 * if( Path::name(path) == "base_name.suffix" ){
 *   printf("Yep\n");
 * }
 *
 *
 * ```
 *
 */

class Path {
  Path() = default;
public:
  API_NO_DISCARD static var::StringView suffix(var::StringView path);
  API_NO_DISCARD static var::StringView name(var::StringView path);
  API_NO_DISCARD static var::StringView
  parent_directory(var::StringView path, size_t depth = 1);
  API_NO_DISCARD static var::StringView base_name(var::StringView path);
  API_NO_DISCARD static var::StringView no_suffix(var::StringView path);

  /*! \details
   *
   * This checks to see if name or any parent directory in the path
   * starts with `.` followed by a valid file/directory name.
   *
   * @param path The path to consider
   * @return true the entity specified by `path` is hidden.
   *
   */
  API_NO_DISCARD static bool is_hidden(var::StringView path);
};
} // namespace fs

#endif // FSAPI_PATH_HPP
