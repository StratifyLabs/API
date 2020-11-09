/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.

#if defined __link
#include <sys/stat.h>
#endif

#include "fs/FileInfo.hpp"
#include "printer/Printer.hpp"
#include "var/StackString.hpp"
#include "var/String.hpp"

printer::Printer &
printer::operator<<(printer::Printer &printer, const fs::FileInfo &a) {
  var::String type;
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

FileInfo::FileInfo() { m_stat = {0}; }

bool FileInfo::is_directory() const {
  TypeFlags masked = static_cast<TypeFlags>(m_stat.st_mode);
  masked &= TypeFlags::mask;
  return masked == TypeFlags::directory;
}

bool FileInfo::is_file() const {
  TypeFlags masked = static_cast<TypeFlags>(m_stat.st_mode);
  masked &= TypeFlags::mask;
  return masked == TypeFlags::regular;
}

bool FileInfo::is_device() const {
  return is_block_device() || is_character_device();
}

bool FileInfo::is_block_device() const {
  TypeFlags masked = static_cast<TypeFlags>(m_stat.st_mode);
  masked &= TypeFlags::mask;
  return masked == TypeFlags::block;
}

bool FileInfo::is_character_device() const {
  TypeFlags masked = static_cast<TypeFlags>(m_stat.st_mode);
  masked &= TypeFlags::mask;
  return masked == TypeFlags::character;
}

bool FileInfo::is_socket() const {
  TypeFlags masked = static_cast<TypeFlags>(m_stat.st_mode);
  masked &= TypeFlags::mask;
  return masked == TypeFlags::file_socket;
}

u32 FileInfo::size() const { return m_stat.st_size; }

