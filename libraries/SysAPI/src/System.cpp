// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#include "sys/System.hpp"
#include "var/StackString.hpp"

using namespace sys;

var::StringView System::operating_system_name() {
#if defined __link
#if defined __macosx
  return "macosx";
#elif defined __win32
  return "windows";
#elif defined __linux
  return "linux";
#else
  return "unknown";
#endif
#else
  return "stratifyos";
#endif
}

var::StringView System::processor() {
#if defined __processor_i386 || defined __processor_x86
  return "i386";
#elif defined __processor_x86_64 || defined __processor_AMD64
  return "x86_64";
#elif defined __processor_arm || defined __processor_armv7l
  return "arm32";
#elif defined __processor_aarch64
  return "arm64";
#else
#if defined __StratifyOS__
#if defined __v7m
  return "v7m";
#endif
#if defined __v7em
  return "v7em";
#endif
#if defined __v7em_f4sh
  return "v7em_f4sh";
#endif
#if defined __v7em_f5dh
  return "v7em_f5dh";
#endif
#if defined __v7em_f5sh
  return "v7em_f5sh";
#endif
#endif
  return "unknown";
#endif
}

bool System::is_windows() {
  return var::StringView(operating_system_name()) == "windows";
}

bool System::is_macosx() {
  return var::StringView(operating_system_name()) == "macosx";
}

bool System::is_linux() {
  return var::StringView(operating_system_name()) == "linux";
}

bool System::is_stratify_os() {
  return var::StringView(operating_system_name()) == "stratifyos";
}

bool System::is_processor_i386() {
  return var::StringView(processor()) == "i386";
}
bool System::is_processor_x86_64() {
  return var::StringView(processor()) == "x86_64";
}
bool System::is_processor_arm32() {
  return var::StringView(processor()) == "arm32";
}
bool System::is_processor_arm64() {
  return var::StringView(processor()) == "arm64";
}

var::StringView System::user_data_path() {
#if defined __link
  static var::PathString result;
  var::PathString path;
  if (is_windows()) {
    path = getenv("LocalAppData");
    result = path;
  }

  if (is_macosx()) {
    // read env home variable
    path = getenv("HOME");
    result = path / "Library/Application Support";
  }

  if (is_linux()) {
    path = getenv("HOME");
    result = path / ".StratifyLabs";
  }

  return result.cstring();
#else
  return "/home";
#endif
}

void System::launch_browser(var::StringView url){
#if defined __link
  var::String command = var::String(is_macosx() ? "open" : "start") + " " + url;
  system(command.cstring());
#endif
}

const char * System::get_executable_suffix(){
#if defined __link
  return is_windows() ? ".exe" : "";
#else
  return "";
#endif
}

