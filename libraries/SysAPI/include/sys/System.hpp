// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md
#ifndef SOSAPI_SYSTEM_HPP
#define SOSAPI_SYSTEM_HPP

#include <sdk/types.h>

#include "var/StringView.hpp"

namespace sys {

class System
{
public:
  static var::StringView operating_system_name();
  static var::StringView processor();
  static bool is_processor_i386();
  static bool is_processor_x86_64();
  static bool is_processor_arm32();
  static bool is_processor_arm64();
  static bool is_windows();
  static bool is_macosx();
  static bool is_linux();
  static bool is_stratify_os();
  static var::StringView user_data_path();
};

} // namespace sys

#endif // SOSAPI_SYSTEM_HPP
