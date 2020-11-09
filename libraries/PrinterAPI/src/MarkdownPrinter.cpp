/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
#include "printer/MarkdownPrinter.hpp"

using namespace var;
using namespace printer;

MarkdownPrinter::MarkdownPrinter() {
  m_is_last_close = false;
  container_list().push_back(Container(Level::info, ContainerType::top));
  m_directive = Directive::no_directive;
}

void MarkdownPrinter::print_open_object(Level level, const StringView key) {
  if (level <= verbose_level()) {
    this->key(key, "");
  }
  open_list(ListType::unordered, level);
}

void MarkdownPrinter::print_close_object() { close_list(); }

void MarkdownPrinter::print(
  Level level,
  var::StringView key,
  var::StringView value,
  IsNewline is_newline) {

  if (level > verbose_level()) {
    return;
  }

  for (auto const &c : container_list()) {
    if (c.verbose_level() > verbose_level()) {
      return;
    }
  }

  var::String content;

  if (key.is_null() == false) {
    content += String(key) + ": ";
  }
  if (value.is_null() == false) {
    content += value;
  }

  var::String prefix;
  var::String marker;

  bool is_suppress_newline = false;
  bool is_print_newline = false;

  if ((m_directive == Directive::suppress_newline) || value.is_null()) {
    m_directive = Directive::no_directive;
    is_suppress_newline = true;
  }

  bool is_first_list = true;
  for (auto const &c : container_list()) {
    // if any parent prohibits printing -- don't print
    if (c.verbose_level() > verbose_level()) {
      return;
    }
    switch (c.type()) {
    case ContainerType::top:
      break;
    case ContainerType::paragraph:
      prefix = "";
      marker = "";
      break;
    case ContainerType::header:
      prefix = "";
      marker = "";
      is_print_newline = true;
      break;
    case ContainerType::blockquote:
      prefix += ">";
      marker = " ";
      is_print_newline = true;
      break;
    case ContainerType::code:
      prefix += "";
      marker = "";
      break;
    case ContainerType::ordered_list:
      if (is_first_list) {
        is_first_list = false;
      } else {
        prefix += "   ";
      }
      marker = var::String().format("%d. ", container().count()++);
      is_print_newline = true;
      break;
    case ContainerType::unordered_list:
      if (is_first_list) {
        is_first_list = false;
      } else {
        prefix += "   ";
      }
      marker = "- ";
      is_print_newline = true;
      break;
    }
  }

#if 0
	//check for line wrapping
	if( (container().type() != ContainerType::code) &&
		 (container().type() != ContainerType::yaml_array) &&
		 (container().type() != ContainerType::yaml_object) ){

		size_t newline_position = content.find("\n");
		if( newline_position != var::String::npos ){
			m_line_length += newline_position;
		} else {
			m_line_length += 0;
		}

		if( m_line_length > m_wrap_length ){
			size_t space_position = content.reverse_find(
						" ",
						var::String::Position());


			if( space_position != var::String::npos ){
				content.at(space_position) = "\n";
			} else {
				content.insert("\n", var::String::Position(space_position));
			}

		}
	}
#endif

  if (
    (container().type() == ContainerType::blockquote)
    || (container().type() == ContainerType::paragraph)) {
    if (content.back() == '.') {
      content += " ";
    }
  }

  // print the decoration
  interface_print_final((prefix + marker).cstring());

  // print the key/value pair
  Printer::print(
    level,
    key,
    value,
    (is_print_newline && !is_suppress_newline) ? IsNewline::yes : IsNewline::no);
}

bool MarkdownPrinter::close_type(ContainerType type) {
  if (container().type() == type) {
    Level level = container().verbose_level();
    container_list().pop_back();
    if (!m_is_last_close && (level <= verbose_level())) {
      m_is_last_close = true;
      // print_final("\n");
      return true;
    }
  }
  return false;
}

MarkdownPrinter &MarkdownPrinter::horizontal_line() {
  print(
    verbose_level(),
    StringView().set_null(),
    "-------------------------------\n");
  return *this;
}

MarkdownPrinter &MarkdownPrinter::hyperlink(
  var::StringView text,
  var::StringView link) {

  var::String output = var::String("[") + text + "](" + link + ")";
  print(
    this->verbose_level(),
    StringView().set_null(),
    output.string_view(),
    IsNewline::no);
  return *this;
}

MarkdownPrinter &MarkdownPrinter::image(
  var::StringView text,
  var::StringView link) {
  var::String output = var::String("![") + text + "](" + link + ")";
  print(
    this->verbose_level(),
    StringView().set_null(),
    output.string_view(),
    IsNewline::no);
  return *this;
}

MarkdownPrinter &
MarkdownPrinter::open_header(var::StringView header, Level level) {
  m_is_last_close = false;
  container_list().push_back(Container(level, ContainerType::header));

  var::String header_output;
  for (u32 i = 0; i < calculate_nesting(); i++) {
    header_output += "#";
  }
  header_output += " " + header;

  print(level, StringView().set_null(), header_output.string_view());
  return *this;
}

MarkdownPrinter &MarkdownPrinter::close_header() {
  close_type(ContainerType::header);
  return *this;
}

// increase list level -- can be nested
MarkdownPrinter &MarkdownPrinter::open_list(ListType type, Level level) {
  const ContainerType c_type = (type == ListType::ordered)
                                 ? ContainerType::ordered_list
                                 : ContainerType::unordered_list;
  m_is_last_close = false;
  container_list().push_back(Container(level, c_type));
  return *this;
}
MarkdownPrinter &MarkdownPrinter::close_list() {
  if (container().type() == ContainerType::ordered_list) {
    close_type(ContainerType::ordered_list);
  } else {
    close_type(ContainerType::unordered_list);
  }
  return *this;
}

// cannot be nested
MarkdownPrinter &MarkdownPrinter::open_code(
  var::StringView language,
  // unique id value
  Level level) {
  m_is_last_close = false;
  container_list().push_back(Container(level, ContainerType::code));
  print(
    level,
    StringView().set_null(),
    (var::String() + "```" + language).string_view());
  return *this;
}
MarkdownPrinter &MarkdownPrinter::close_code() {
  if (container().type() == ContainerType::code) {
    Level level = container().verbose_level();
    container_list().pop_back();

    for (auto const &c : container_list()) {
      if (c.verbose_level() > verbose_level()) {
        return *this;
      }
    }

    if (level <= verbose_level()) {
      interface_print_final("```\n");
    }
  }
  return *this;
}

MarkdownPrinter &MarkdownPrinter::open_blockquote(Level level) {
  container_list().push_back(Container(level, ContainerType::blockquote));
  m_is_last_close = false;
  // print("\n");
  return *this;
}

MarkdownPrinter &MarkdownPrinter::close_blockquote() {

  bool is_blockquote = false;
  while (container().type() == ContainerType::blockquote) {
    container_list().pop_back();
    is_blockquote = true;
  }
  if (is_blockquote) {
    if (!m_is_last_close) {
      m_is_last_close = true;
      // print("\n");
    }
  }
  return *this;
}

MarkdownPrinter &MarkdownPrinter::open_paragraph(Level level) {
  m_is_last_close = false;
  container_list().push_back(Container(level, ContainerType::paragraph));
  return *this;
}

MarkdownPrinter &MarkdownPrinter::close_paragraph() {
  if (close_type(ContainerType::paragraph)) {
    interface_print_final("\n"); // paragraphs need an extra break
  }
  return *this;
}

MarkdownPrinter &
MarkdownPrinter::open_table(const var::StringList &header, Level level) {
  m_is_last_close = false;
  return *this;
}

MarkdownPrinter &MarkdownPrinter::append_table_row(const var::StringList &row) {
  return *this;
}

MarkdownPrinter &MarkdownPrinter::close_table() { return *this; }

MarkdownPrinter &MarkdownPrinter::operator<<(Directive directive) {
  if (directive == Directive::insert_newline) {
    if (container().verbose_level() <= verbose_level()) {
      interface_print_final("\n");
    }
  } else {
    m_directive = directive;
  }
  return *this;
}

MarkdownPrinter &
MarkdownPrinter::open_pretty_table(const var::StringList &header) {
  m_pretty_table.clear();
  if (header.count() == 0) {
    return *this;
  }
  m_pretty_table.push_back(header);
  return *this;
}

MarkdownPrinter &
MarkdownPrinter::append_pretty_table_row(const var::StringList &row) {
  if (m_pretty_table.count() == 0) {
    return *this;
  }

  m_pretty_table.push_back(row);

  // ensure the new row is the same size as the first row
  if (m_pretty_table.count() > 1) {
    if (row.count() != m_pretty_table.front().count()) {
      m_pretty_table.back().resize(m_pretty_table.front().count());
    }
  }
  return *this;
}

MarkdownPrinter &MarkdownPrinter::close_pretty_table(Level level) {
  // markdown table
  var::Vector<u32> column_widths;
  for (const auto &row : m_pretty_table) {
    if (column_widths.count() < row.count()) {
      column_widths.resize(row.count());
    }
    for (u32 i = 0; i < row.count(); i++) {
      if (row.at(i).length() > column_widths.at(i)) {
        column_widths.at(i) = row.at(i).length();
      }
    }
  }

  open_paragraph(level);
  for (u32 row = 0; row < m_pretty_table.count(); row++) {
    if (row == 1) {
      *this << MarkdownPrinter::Directive::suppress_newline;
      *this << var::StringView("|");
      for (auto const &value : column_widths) {
        *this << MarkdownPrinter::Directive::suppress_newline;
        *this << (var::String("-") * (value + 2)) + "|";
      }
      *this << MarkdownPrinter::Directive::insert_newline;
    }

    *this << MarkdownPrinter::Directive::suppress_newline;
    *this << var::StringView("|");
    for (u32 column = 0; column < m_pretty_table.at(row).count(); column++) {
      var::StringView cell = m_pretty_table.at(row).at(column).cstring();
      u32 value = column_widths.at(column);
      *this << MarkdownPrinter::Directive::suppress_newline;
      *this
        << (var::String(" ") + cell
            + (var::String(" ") * (value + 1 - cell.length())) + "|");
    }
    *this << MarkdownPrinter::Directive::insert_newline;
  }
  close_paragraph();
  return *this;
}

#if 0
Printer & MarkdownPrinter::debug(const char * fmt, ...){
	if( verbose_level() >= level_debug ){
		va_list list;
		va_start(list, fmt);
		print_final(
					(var::String(">>>> ") +
					var::String().vformat(fmt, list) +
					"\n").cstring()
					);
		va_end(list);
	}
	return *this;
}

Printer & MarkdownPrinter::message(const char * fmt, ...){
	if( verbose_level() >= level_message ){
		va_list list;
		va_start(list, fmt);
		print_final(
					(var::String("> ") +
					var::String().vformat(fmt, list) +
					"\n").cstring()
					);
		va_end(list);
	}
	return *this;
}

Printer & MarkdownPrinter::info(const char * fmt, ...){
	va_list list;
	va_start(list, fmt);
	print(Level::info, "info", var::String().vformat(fmt, list).cstring());
	va_end(list);
	return *this;
}

Printer & MarkdownPrinter::warning(const char * fmt, ...){
	va_list list;
	va_start(list, fmt);
	print(level_warning, "warning", var::String().vformat(fmt, list).cstring());
	va_end(list);
	return *this;
}

Printer & MarkdownPrinter::error(const char * fmt, ...){
	va_list list;
	va_start(list, fmt);
	print(level_error, "error", var::String().vformat(fmt, list).cstring());
	va_end(list);
	return *this;
}

Printer & MarkdownPrinter::fatal(const char * fmt, ...){
	va_list list;
	va_start(list, fmt);
	print(level_fatal, "fatal", var::String().vformat(fmt, list).cstring());
	va_end(list);
	return *this;
}

#endif
