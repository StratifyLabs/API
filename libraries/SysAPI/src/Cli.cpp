// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#include "var/StackString.hpp"
#include "var/Tokenizer.hpp"

#include "printer/Printer.hpp"
#include "sys/Cli.hpp"

printer::Printer &
printer::operator<<(printer::Printer &printer, const sys::Cli &a) {
  for (size_t i = 0; i < a.count(); i++) {
    printer.key(var::NumberString(i, "[%d]"), a.at(i));
  }
  return printer;
}

using namespace var;
using namespace sys;

Cli::Cli(int argc, char *argv[]) {
  if (argc < 0) {
    argc = 0;
  }
  m_argc = argc;
  m_argv = argv;
}

const Cli &Cli::handle_version(const HandleVersion &options) const {
#if !defined __link
  if (!get_option("--version").is_empty()) {
    var::GeneralString output = var::GeneralString()
                                  .append(get_name())
                                  .append("version: ")
                                  .append(options.version())
                                  .append(" by ")
                                  .append(options.publisher());

    printf("%s\n", output.cstring());
    exit(0);
  }
#endif
  return *this;
}

var::GeneralString Cli::to_general_string() const {
  GeneralString result;
  for (u32 i = 1; i < count(); i++) {
    result |= at(i);
    if (i < count() - 1) {
      result |= " ";
    }
  }
  return result;
}

StringView Cli::at(u16 value) const {
  return (value < m_argc) ? StringView(m_argv[value]) : var::StringView();
}

var::StringView Cli::get_option(StringView name, StringView help) const {
  u32 args;

  if (!help.is_empty()) {
    m_help_list.push_back(name & ":" & help);
  }

  for (args = 1; args < count(); args++) {
    StringView arg = m_argv[args];

    if (arg.find("--") == 0 && arg.length() >= 3) {
      const Tokenizer tokens(
        arg.pop_front(2),
        Tokenizer::Construct()
          .set_delimeters("=")
          .set_ignore_between("")
          .set_maximum_delimeter_count(1));

      if (tokens.count() > 0) {
        if (tokens.at(0) == name) {
          if (tokens.count() > 1) {
            return tokens.at(1);
          } else {
            return {"true"};
          }
        }
      }
    }
  }
  return {};
}

var::StringView Cli::get_name() const {
  if (m_argc > 0) {
    StringView result = m_argv[0];
    size_t slash_position = result.reverse_find('/');
    if (slash_position != StringView::npos) {
      result.pop_front(slash_position + 1);
    }

    return result;
  }
  return {};
}

var::StringView Cli::get_path() const {
  if (m_argc > 0) {
    return m_argv[0];
  }
  return {};
}

const Cli &Cli::show_help(const ShowHelp &options) const {
  printer::Printer simple_printer;
  auto *printer
    = options.printer() == nullptr ? &simple_printer : options.printer();
  if (!options.publisher().is_empty()) {
    printer->key("publisher", options.publisher());
  }

  if (!options.version().is_empty()) {
    printer->key("version", options.version());
  }

  printer::Printer::Object po(*printer, get_name() | " options");

  for (const auto &help_item : m_help_list) {
    const auto part_container = var::Tokenizer(
      help_item,
      var::Tokenizer::Construct().set_maximum_delimeter_count(1).set_delimeters(":"));
    if( part_container.count() > 1 ){
      printer->key(part_container.at(0), part_container.at(1));
    }
  }
  return *this;
}

const Cli &Cli::show_version(const ShowVersion &options) const {
  printer::Printer simple_printer;
  auto *printer
    = options.printer() == nullptr ? &simple_printer : options.printer();

  printer->key("name", get_name());

  if (!options.publisher().is_empty()) {
    printer->key("publisher", options.publisher());
  }

  if (!options.version().is_empty()) {
    printer->key("version", options.version());
  }

  return *this;
}
