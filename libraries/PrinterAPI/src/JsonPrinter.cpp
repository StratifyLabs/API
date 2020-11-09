/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
#include "printer/JsonPrinter.hpp"

using namespace printer;

JsonPrinter::JsonPrinter() {
  container_list().push_back(Container(Level::fatal, ContainerType::array));
  enable_flags(
    Flags::no_progress_newline | Flags::key_quotes | Flags::value_quotes);
}

bool JsonPrinter::is_level_filtered() const {
  for (auto const &c : container_list()) {
    if (c.verbose_level() > verbose_level()) {
      return true;
    }
  }
  return false;
}

void JsonPrinter::print(
  Level level,
  var::StringView key,
  var::StringView value,
  IsNewline is_newline) {

  if (level > verbose_level()) {
    return;
  }

  if (is_level_filtered()) {
    return;
  }

  insert_comma();

  if (container().type() == ContainerType::array) {
    key = var::StringView().set_null();
  }

  Printer::print(level, key, value, IsNewline::no);
}

void JsonPrinter::print_open_object(Level level, var::StringView key) {

  if (verbose_level() >= level && !is_level_filtered()) {
    insert_comma();
    if (container().type() == ContainerType::object) {
      const var::String string_key = "\"" + key + "\":{";
      interface_print_final(string_key.cstring());
    } else {
      interface_print_final("{");
    }
  }

  container_list().push_back(Container(level, ContainerType::object));
}

void JsonPrinter::print_open_array(Level level, var::StringView key) {
  if (verbose_level() >= level && !is_level_filtered()) {
    insert_comma();
    if (container().type() == ContainerType::object) {
      const var::String string_key = "\"" + key + "\":[";
      interface_print_final(string_key.cstring());
    } else {
      interface_print_final("[");
    }
  }
  container_list().push_back(Container(level, ContainerType::array));
}

void JsonPrinter::print_close_object() {
  if (container_list().count() > 1) {
    if (
      verbose_level() >= container().verbose_level() && !is_level_filtered()) {
      if (container().type() == ContainerType::array) {
        interface_print_final("]");
      } else if (container().type() == ContainerType::object) {
        interface_print_final("}");
      }
    }
    container_list().pop_back();
  }
}

void JsonPrinter::insert_comma() {
  if (container().count() > 1) {
    interface_print_final(",");
  }
  container().count() = container().count() + 1;
}
