// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md
#ifndef SOSAPI_SYSTEM_HPP
#define SOSAPI_SYSTEM_HPP

#include <sdk/types.h>

#include "var/StringView.hpp"

namespace sys {

class System {
public:
  API_NO_DISCARD static var::StringView operating_system_name();
  API_NO_DISCARD static var::StringView processor();
  API_NO_DISCARD static bool is_processor_i386();
  API_NO_DISCARD static bool is_processor_x86_64();
  API_NO_DISCARD static bool is_processor_arm32();
  API_NO_DISCARD static bool is_processor_arm64();
  API_NO_DISCARD static bool is_windows();
  API_NO_DISCARD static bool is_macosx();
  API_NO_DISCARD static bool is_linux();
  API_NO_DISCARD static bool is_stratify_os();
  API_NO_DISCARD static var::StringView user_data_path();
};

} // namespace sys

#endif // SOSAPI_SYSTEM_HPP
