// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef PRINTER_API_PRINTER_MARKDOWNPRINTER_HPP_
#define PRINTER_API_PRINTER_MARKDOWNPRINTER_HPP_

#include "var/String.hpp"
#include "var/StringView.hpp"
#include "var/Vector.hpp"

#include "Printer.hpp"

namespace printer {

class MarkdownPrinter : public Printer {
public:
  MarkdownPrinter();

  enum class Directive {
    no_directive,
    emphasis_bold,
    emphasis_italic,
    emphasis_underline,
    emphasis_strikethrough,
    suppress_newline,
    insert_newline
  };

  enum class ListType { unordered, ordered };

  // emoji: https://www.webfx.com/tools/emoji-cheat-sheet/

  using Printer::operator<<;
  MarkdownPrinter &operator<<(Directive directive);

  MarkdownPrinter &horizontal_line();

  MarkdownPrinter &
  open_object(const var::StringView key, Level level = Level::fatal) {
    open_header(key, level);
    return open_list(ListType::unordered, level);
  }

  MarkdownPrinter &close_object() {
    close_list();
    return close_header();
  }

  MarkdownPrinter &close() {
    close_list();
    return close_header();
  }

  MarkdownPrinter &
  open_array(const var::StringView key, Level level = Level::fatal) {
    open_header(key, level);
    return open_list(ListType::ordered, level);
  }

  MarkdownPrinter &close_array() {
    close_list();
    return close_header();
  }

  // increase header level -- can be nested
  MarkdownPrinter &
  open_header(const var::StringView key, Level level = Level::info);
  MarkdownPrinter &close_header();

  MarkdownPrinter &open_paragraph(Level level = Level::info);

  MarkdownPrinter &close_paragraph();

  // increase list level -- can be nested
  MarkdownPrinter &
  open_list(ListType type = ListType::unordered, Level level = Level::info);

  MarkdownPrinter &close_list();

  // cannot be nested
  MarkdownPrinter &open_code(
    var::StringView language = "",
    // unique id value
    Level level = Level::info);
  MarkdownPrinter &close_code();

  MarkdownPrinter &open_blockquote(Level level = Level::info);

  MarkdownPrinter &close_blockquote();

  MarkdownPrinter &
  open_table(const var::StringList &header, Level level = Level::info);

  MarkdownPrinter &append_table_row(const var::StringList &row);
  MarkdownPrinter &close_table();

  MarkdownPrinter &open_pretty_table(const var::StringList &header);

  MarkdownPrinter &append_pretty_table_row(const var::StringList &row);
  MarkdownPrinter &close_pretty_table(Level level = Level::info);

  API_NO_DISCARD bool is_pretty_table_valid() const {
    return m_pretty_table.count() && m_pretty_table.front().count();
  }

  API_NO_DISCARD const var::Vector<var::Vector<var::String>> &
  pretty_table() const {
    return m_pretty_table;
  }

  MarkdownPrinter &hyperlink(var::StringView text, var::StringView link);
  MarkdownPrinter &image(var::StringView text, var::StringView link);

  class Header {
  public:
    Header(
      MarkdownPrinter &printer,
      var::StringView header,
      Level level = Level::info)
      : m_printer(printer) {
      printer.open_header(header, level);
    }

    Header(const Header &) = delete;
    Header &operator=(const Header &) = delete;
    Header(Header &&) = delete;
    Header &operator=(Header &&) = delete;

    ~Header() { m_printer.close_header(); }

  private:
    MarkdownPrinter &m_printer;
  };

  class Code {
  public:
    Code(
      MarkdownPrinter &printer,
      var::StringView language,
      Level level = Level::info)
      : m_printer(printer) {
      printer.open_code(language, level);
    }

    Code(const Code &) = delete;
    Code &operator=(const Code &) = delete;
    Code(Code &&) = delete;
    Code &operator=(Code &&) = delete;

    ~Code() { m_printer.close_code(); }

  private:
    MarkdownPrinter &m_printer;
  };

  class BlockQuote {
  public:
    explicit BlockQuote(MarkdownPrinter &printer, Level level = Level::info)
      : m_printer(printer) {
      m_printer.open_blockquote(level);
    }

    BlockQuote(const BlockQuote &) = delete;
    BlockQuote &operator=(const BlockQuote &) = delete;
    BlockQuote(BlockQuote &&) = delete;
    BlockQuote &operator=(BlockQuote &&) = delete;

    ~BlockQuote() { m_printer.close_blockquote(); }

  private:
    MarkdownPrinter &m_printer;
  };

  class Paragraph {
  public:
    explicit Paragraph(MarkdownPrinter &printer, Level level = Level::info)
      : m_printer(printer) {
      m_printer.open_paragraph(level);
    }

    Paragraph(const Paragraph &) = delete;
    Paragraph &operator=(const Paragraph &) = delete;
    Paragraph(Paragraph &&) = delete;
    Paragraph &operator=(Paragraph &&) = delete;

    ~Paragraph() { m_printer.close_paragraph(); }

  private:
    MarkdownPrinter &m_printer;
  };

  class List {
  public:
    List(MarkdownPrinter &printer, ListType type, Level level = Level::info)
      : m_printer(printer) {
      printer.open_list(type, level);
    }

    List(const List &) = delete;
    List &operator=(const List &) = delete;
    List(List &&) = delete;
    List &operator=(List &&) = delete;

    ~List() { m_printer.close_list(); }

  private:
    MarkdownPrinter &m_printer;
  };

  class PrettyTable {
  public:
    PrettyTable(
      MarkdownPrinter &printer,
      const var::StringList &header,
      Level level = Level::info)
      : m_printer(&printer) {
      printer.open_pretty_table(header);
    }

    PrettyTable(const PrettyTable &) = delete;
    PrettyTable &operator=(const PrettyTable &) = delete;
    PrettyTable(PrettyTable &&) = delete;
    PrettyTable &operator=(PrettyTable &&) = delete;

    ~PrettyTable() { m_printer->close_pretty_table(); }

  private:
    MarkdownPrinter *m_printer;
  };

#if 0
	using Printer::debug;
	using Printer::message;
	using Printer::info;
	using Printer::warning;
	using Printer::error;
	using Printer::fatal;

	Printer & debug(const char * fmt, ...);
	Printer & message(const char * fmt, ...);
	Printer & info(const char * fmt, ...);
	Printer & warning(const char * fmt, ...);
	Printer & error(const char * fmt, ...);
	Printer & fatal(const char * fmt, ...);
#endif

private:
  enum class ContainerType {
    top,
    code,
    header,
    paragraph,
    ordered_list,
    unordered_list,
    blockquote,
  };

  using Container = ContainerAccess<ContainerType>;
  var::Vector<Container> m_container_list;
  bool m_is_last_close = false;
  Directive m_directive = Directive::no_directive;
  var::Vector<var::Vector<var::String>> m_pretty_table;

  var::Vector<Container> &container_list() { return m_container_list; }
  API_NO_DISCARD const var::Vector<Container> &container_list() const {
    return m_container_list;
  }

  // re-implemented virtual functions from Printer
  void print_open_object(Level level, var::StringView key) override;
  void print_close_object() override;
  void print(
    Level level,
    var::StringView key,
    var::StringView value,
    IsNewline is_newline) override;

  Container &container() { return m_container_list.back(); }

  API_NO_DISCARD const Container &container() const {
    return m_container_list.back();
  }

  bool pop_container(ContainerType type) {
    bool has_type = false;
    for (const auto &c : m_container_list) {
      if (c.type() == type) {
        has_type = true;
      }
    }

    if (!has_type) {
      return false;
    }

    while (container().type() != type) {
      m_container_list.pop_back();
    }

    m_container_list.pop_back();
    return true;
  }

  API_NO_DISCARD u16 calculate_nesting() const {
    u16 nesting = 0;
    ContainerType type = container().type();
    for (auto const &c : m_container_list) {
      if (c.type() == type) {
        nesting++;
      }
    }
    return nesting;
  }

  bool close_type(ContainerType type);
};

} // namespace printer

#endif // PRINTER_API_PRINTER_MARKDOWNPRINTER_HPP_
