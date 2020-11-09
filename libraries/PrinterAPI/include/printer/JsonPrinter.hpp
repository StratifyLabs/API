/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
#ifndef PRINTER_API_PRINTER_JSONPRINTER_HPP_
#define PRINTER_API_PRINTER_JSONPRINTER_HPP_

#include "var/Vector.hpp"

#include "Printer.hpp"

namespace printer {

class JsonPrinter : public Printer {
public:
  JsonPrinter();

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

  void insert_comma();

  bool is_level_filtered() const;
};

} // namespace printer

#endif // PRINTER_API_PRINTER_JSONPRINTER_HPP_
