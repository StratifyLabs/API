// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef FSAPI_PATH_HPP
#define FSAPI_PATH_HPP

#include "var/StringView.hpp"

namespace fs {

class Path {
public:
  API_NO_DISCARD static var::StringView suffix(var::StringView path);
  API_NO_DISCARD static var::StringView name(var::StringView path);
  API_NO_DISCARD static var::StringView
  parent_directory(var::StringView path, size_t depth = 1);
  API_NO_DISCARD static var::StringView base_name(var::StringView path);
  API_NO_DISCARD static var::StringView no_suffix(var::StringView path);
  API_NO_DISCARD static bool is_hidden(var::StringView path);

private:
  var::StringView m_path;
};
} // namespace fs

#endif // FSAPI_PATH_HPP
