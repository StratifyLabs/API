/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
#ifndef PRINTER_API_PRINTER_YAMLPRINTER_HPP_
#define PRINTER_API_PRINTER_YAMLPRINTER_HPP_

#include "Printer.hpp"
#include "var/Vector.hpp"

namespace printer {

class YamlPrinter : public Printer {
public:
  YamlPrinter();

  static PrinterTermination close() { return PrinterTermination(); }

  using Printer::operator<<;

  YamlPrinter &operator<<(const PrinterTermination &printer_termination) {
    close_object();
    return *this;
  }

  YamlPrinter &set_top_verbose_level(Level level) {
    container_list().front().set_verbose_level(level);
    return *this;
  }

private:
  enum class ContainerType { array, object };

  using Container = ContainerAccess<ContainerType>;
  var::Vector<Container> m_container_list;
  var::Vector<Container> &container_list() { return m_container_list; }
  const var::Vector<Container> &container_list() const {
    return m_container_list;
  }

  // re-implemented virtual functions from Printer
  void print_open_object(Level level, var::StringView key) override;
  void print_close_object() override;
  void print_open_array(Level level, var::StringView key) override;
  void print_close_array() override { return print_close_object(); }
  void print(
    Level level,
    var::StringView key,
    var::StringView value,
    IsNewline is_newline = IsNewline::yes) override;

  Container &container() { return m_container_list.back(); }

  const Container &container() const { return m_container_list.back(); }
};

} // namespace printer

#endif // PRINTER_API_PRINTER_YAMLPRINTER_HPP_
