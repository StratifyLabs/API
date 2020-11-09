#include <cstring>
#include <string>

#include "sys/System.hpp"
#include "var/String.hpp"

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
  static var::String result;
  result.clear();
  var::String path;
  if (is_windows()) {
    path = getenv("LocalAppData");
    result = path;
  }

  if (is_macosx()) {
    // read env home variable
    path = getenv("HOME");
    result = path + "/Library/Application Support";
  }

  if (is_linux()) {
    path = getenv("HOME");
    result = path + "/.StratifyAPI";
  }

  return result.cstring();
#else
  return "/home";
#endif
}
