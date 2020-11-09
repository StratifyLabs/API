/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.

#include "var/StackString.hpp"
#include "var/Tokenizer.hpp"

#include "printer/Printer.hpp"
#include "sys/Cli.hpp"

printer::Printer &
printer::operator<<(printer::Printer &printer, const sys::Cli &a) {
#if 0
  printer.print_open_object(printer.verbose_level(), a.name().cstring());
  {
    printer.key("publisher", a.publisher());
    printer.print_open_object(printer.verbose_level(), "arguments");
    {
      for (u32 i = 0; i < a.count(); i++) {
        printer.key(0, "%s", a.at(i).cstring());
      }
      printer.print_close_object();
    }
    printer.print_close_object();
  }
#endif
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
  if (get_option("--version").is_empty() == false) {
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

var::String Cli::to_string() const {
  String result;
  for (u32 i = 1; i < count(); i++) {
    result += at(i);
    if (i < count() - 1) {
      result += " ";
    }
  }
  return result;
}

StringView Cli::at(u16 value) const {
  return (value < m_argc) ? StringView(m_argv[value]) : var::StringView();
}

var::StringView Cli::get_option(StringView name, StringView help) const {
  u32 args;

  if (help.is_empty() == false) {
    m_help_list.push_back(name + ": " + help);
  }

  for (args = 1; args < count(); args++) {
    StringView arg = m_argv[args];

    if (arg.find("--") == 0 && arg.length() >= 5) {
      const Tokenizer tokens(
        arg.pop_front(2),
        Tokenizer::Construct()
          .set_delimeters("=")
          .set_ignore_between("")
          .set_maximum_delimeter_count(1));

      if (tokens.count() > 0) {
        if (is_case_senstive() && (tokens.at(0) == name)) {
          if (tokens.count() > 1) {
            return tokens.at(1);
          } else {
            return var::StringView("true");
          }
        } else if (String(name).to_upper() == String(tokens.at(0)).to_upper()) {
          if (tokens.count() > 1) {
            return tokens.at(1);
          } else {
            return var::StringView("true");
          }
        }
      }
    }
  }
  return StringView();
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
  return var::StringView();
}

var::StringView Cli::get_path() const {
  if (m_argc > 0) {
    return m_argv[0];
  }
  return var::StringView();
}

Cli &Cli::show_help(const ShowHelp &options) {
  printf("%s options:\n", var::String(get_name()).cstring());
  for (u32 i = 0; i < m_help_list.count(); i++) {
    printf("- %s\n", m_help_list.at(i).cstring());
  }
  return *this;
}
