// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#if defined __link
#include <sys/stat.h>
#endif

#include "fs/FileInfo.hpp"
#include "printer/Printer.hpp"
#include "var/StackString.hpp"
#include "var/String.hpp"

printer::Printer &
printer::operator<<(printer::Printer &printer, const fs::FileInfo &a) {
  var::IdString type;
  if (a.is_directory()) {
    type = "directory";
  }
  if (a.is_file()) {
    type = "file";
  }
  if (a.is_device()) {
    type = "device";
  }
  if (a.is_block_device()) {
    type = "block device";
  }
  if (a.is_character_device()) {
    type = "character device";
  }
  if (a.is_socket()) {
    type = "socket";
  }
  printer.key("type", type);
  if (a.is_file()) {
    printer.key("size", var::NumberString(a.size()).string_view());
  }
  printer.key(
    "mode",
    var::NumberString(a.permissions().permissions() & 0777, "0%o")
      .string_view());

  return printer;
}

using namespace fs;

bool FileInfo::is_directory() const {
  auto masked = static_cast<TypeFlags>(m_stat.st_mode);
  masked &= TypeFlags::mask;
  return masked == TypeFlags::directory;
}

bool FileInfo::is_file() const {
  auto masked = static_cast<TypeFlags>(m_stat.st_mode);
  masked &= TypeFlags::mask;
  return masked == TypeFlags::regular;
}

bool FileInfo::is_device() const {
  return is_block_device() || is_character_device();
}

bool FileInfo::is_block_device() const {
  auto masked = static_cast<TypeFlags>(m_stat.st_mode);
  masked &= TypeFlags::mask;
  return masked == TypeFlags::block;
}

bool FileInfo::is_character_device() const {
  auto masked = static_cast<TypeFlags>(m_stat.st_mode);
  masked &= TypeFlags::mask;
  return masked == TypeFlags::character;
}

bool FileInfo::is_socket() const {
#if defined S_IFSOCK
  auto masked = static_cast<TypeFlags>(m_stat.st_mode);
  masked &= TypeFlags::mask;
  return masked == TypeFlags::file_socket;
#else
  return false;
#endif
}

size_t FileInfo::size() const { return m_stat.st_size; }
