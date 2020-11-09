/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.

#ifndef PRINTER_API_PRINTER_HPP_
#define PRINTER_API_PRINTER_HPP_

/*! \brief System Access (POSIX wrappers)
 * \details The sys namespace includes classes for
 * accessing the system.
 *
 */
namespace printer {}

#include "printer/Printer.hpp"

#include "printer/JsonPrinter.hpp"
#include "printer/MarkdownPrinter.hpp"
#include "printer/YamlPrinter.hpp"

using namespace printer;

#endif /* PRINTER_API_PRINTER_HPP_ */
