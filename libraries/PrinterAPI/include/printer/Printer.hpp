// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef PRINTER_API_PRINTER_PRINTER_HPP_
#define PRINTER_API_PRINTER_PRINTER_HPP_

#include <cstdarg>
#include <sdk/types.h>

#include "var/Data.hpp"
#include "var/String.hpp"
#include "var/StringView.hpp"
#include "var/View.hpp"

#if defined __win32
#undef ERROR
#endif

namespace api {
class PrivateExecutionContext;
}

namespace printer {

struct PrinterFlags {
  /*! \details Number printing flags. */
  enum class Flags {
    null = 0,
    hex = (1 << 0),
    type_unsigned = (1 << 1),
    type_signed = (1 << 2),
    type_char = (1 << 3),
    type_float = (1 << 25),
    width_8 = 0,
    width_16 = (1 << 4),
    width_32 = (1 << 5),
    simple_progress = (1 << 6),
    bold_keys = (1 << 7),
    bold_values = (1 << 8),
    bold_objects = (1 << 9),
    bold_arrays = (1 << 10),
    green_values = (1 << 11),
    red_values = (1 << 12),
    yellow_values = (1 << 13),
    red_errors = (1 << 14),
    yellow_warnings = (1 << 15),
    cyan_keys = (1 << 16),
    yellow_keys = (1 << 17),
    magenta_keys = (1 << 18),
    blob = (1 << 19),
    cyan_values = (1 << 20),
    red_keys = (1 << 21),
    no_progress_newline = (1 << 22),
    key_quotes = (1 << 23),
    value_quotes = (1 << 24)
  };

  enum class FormatType {
    normal = 0,
    bold = 1,
    dim = 2,
    underline = 4,
    blink = 5,
    inverted = 7,
    hidden = 8,
  };

  enum class ColorCode {
    none = 0,
    normal = 39,
    black = 30,
    red = 31,   // RED
    green = 32, // GREEN
    yellow = 33,
    blue = 34, // BLUE
    magenta = 35,
    cyan = 36, // BLUE | GREEN
    light_gray = 37,
    dark_gray = 90,
    light_red = 91,
    light_green = 92,
    light_yellow = 93,
    light_blue = 94
  };

  enum class Level { fatal, error, warning, info, message, debug, trace };
};

API_OR_NAMED_FLAGS_OPERATOR(PrinterFlags, Flags)

#define PRINTER_TRACE(printer, msg) (printer.trace(__FUNCTION__, __LINE__, msg))
#define PRINTER_TRACE_ERROR(printer, x)                                        \
  int printer_result = x;                                                      \
  if (printer_result < 0)                                                      \
  printer.print("\nError: %s():%d (%d)", __FUNCTION__, __LINE__, x, y)

class PrinterTermination {
public:
private:
};

class Printer : public api::ExecutionContext, public PrinterFlags {
public:
  Printer();
  ~Printer();

  static ColorCode color_code(var::StringView color);

  void set_format_code(u32 code);
  void clear_format_code(u32 code);
  void clear_format_code(FormatType code) {
    return clear_format_code(static_cast<u32>(code));
  }

  void set_format_code(FormatType code) {
    set_format_code(static_cast<u32>(code));
  }

  void set_color_code(u32 code);
  void clear_color_code();

  void set_color_code(ColorCode code) {
    set_color_code(static_cast<u32>(code));
  }

  Printer &operator<<(s32 a);
  Printer &operator<<(u32 a);
  Printer &operator<<(s16 a);
  Printer &operator<<(u16 a);
  Printer &operator<<(s8 a);
  Printer &operator<<(u8 a);
  Printer &operator<<(float a);
  Printer &operator<<(void *a);
  Printer &operator<<(const var::StringView a);
  Printer &operator<<(const var::View a);
  Printer &operator<<(const var::String &a);
  Printer &operator<<(const var::StringList &a);
  Printer &operator<<(const var::StringViewList &a);
  Printer &operator<<(const api::Error &error_context);
#if !defined __link
  Printer &operator<<(const var::DataInfo &a);
#endif

  Printer &set_verbose_level(Level level) {
    m_verbose_level = level;
    return *this;
  }

  Printer &set_verbose_level(var::StringView level);

  Level verbose_level() const { return m_verbose_level; }

  Printer &trace(const char *function, int line, var::StringView message);
  Printer &debug(const var::StringView a);
  Printer &message(const var::StringView a);
  Printer &info(const var::StringView a);
  Printer &warning(const var::StringView a);
  Printer &error(const var::StringView a);
  Printer &fatal(const var::StringView a);
  Printer &newline();

  Printer &error(const api::PrivateExecutionContext result, u32 line_number);

  Printer &enable_flags(Flags value) {
    m_print_flags |= value;
    return *this;
  }
  Printer &disable_flags(Flags value) {
    m_print_flags &= ~value;
    return *this;
  }

  Flags flags() const { return m_print_flags; }
  Printer &set_flags(Flags value) {
    m_print_flags = value;
    return *this;
  }

  class FlagGuard {
  public:
    FlagGuard(Printer &printer)
        : m_printer(printer), m_flags(printer.flags()) {}

    ~FlagGuard() { m_printer.set_flags(m_flags); }

  private:
    Flags m_flags;
    Printer &m_printer;
  };

  using FlagScope = FlagGuard;

  class LevelGuard {
  public:
    LevelGuard(Printer &printer)
        : m_printer(printer), m_level(printer.verbose_level()) {}

    ~LevelGuard() { m_printer.set_verbose_level(m_level); }

  private:
    Level m_level;
    Printer &m_printer;
  };

  using LevelScope = LevelGuard;

  API_NO_DISCARD const api::ProgressCallback *progress_callback() const {
    return &m_progress_callback;
  }

  static bool update_progress_callback(void *context, int progress, int total) {
    API_ASSERT(context != nullptr);
    return static_cast<Printer *>(context)->update_progress(progress, total);
  }

  bool update_progress(int progress, int total);

  Printer &set_progress_key(var::StringView progress_key) {
    m_progress_state = 0;
    m_progress_key_state = 0;
    m_progress_key = progress_key;
    return *this;
  }

  Printer &set_indent_size(u16 value) {
    m_indent_size = value;
    return *this;
  }

  u16 indent_size() const {
    return m_indent_size;
  }

  Printer &set_progress_width(u16 value) {
    m_progress_width = value;
    return *this;
  }

  API_NO_DISCARD var::StringView progress_key() const { return m_progress_key; }
  API_NO_DISCARD static char get_bitmap_pixel_character(u32 color,
                                                        u8 bits_per_pixel);
  API_NO_DISCARD static u32 get_bitmap_pixel_color(char c, u8 bits_per_pixel);

#if defined __link
  bool is_bash() const { return m_is_bash; }
  void set_bash(bool value = true) { m_is_bash = value; }
#endif

  API_NO_DISCARD Flags o_flags() const { return m_print_flags; }

  Printer &key_bool(const var::StringView key, bool value);
  Printer &key(const var::StringView key, var::StringView a);
  Printer &key(const var::StringView key, const var::String &a);

  template <class T>
  Printer &object(var::StringView key, const T &value,
                  Level level = Level::fatal) {
    print_open_object(level, key);
    *this << value;
    print_close_object();
    return *this;
  }

  template <class T>
  Printer &array(const var::StringView key, const T &value,
                 Level level = Level::fatal) {
    print_open_array(level, key);
    *this << value;
    print_close_array();
    return *this;
  }

  Printer &open_object(const var::StringView key, Level level = Level::fatal);
  Printer &close_object();
  Printer &open_array(const var::StringView key, Level level = Level::fatal);
  Printer &close_array();

  var::StringView terminal_color_code(ColorCode code);

  enum class IsNewline { no, yes };

  virtual void print_open_object(Level verbose_level, var::StringView key);
  virtual void print_close_object();

  virtual void print_open_array(Level verbose_level, var::StringView key);
  virtual void print_close_array();

  virtual void print(Level level, const var::StringView key,
                     const var::StringView value,
                     IsNewline is_newline = IsNewline::yes);

  class Object {
  public:
    Object(Printer &printer, var::StringView name, Level level = Level::info)
        : m_printer(printer) {
      printer.open_object(name, level);
    }

    ~Object() { m_printer.close_object(); }

  private:
    Printer &m_printer;
  };

  class Array {
  public:
    Array(Printer &printer, var::StringView name, Level level = Level::info)
        : m_printer(printer) {
      printer.open_array(name, level);
    }

    ~Array() { m_printer.close_array(); }

  private:
    Printer &m_printer;
  };

protected:
  template <typename T> class ContainerAccess {
  public:
    ContainerAccess(Level verbose_level, T type)
        : m_type(type), m_count(1), m_verbose_level(verbose_level) {}

    Level verbose_level() const { return m_verbose_level; }
    void set_verbose_level(Level level) { m_verbose_level = level; }

    const u32 &count() const { return m_count; }
    u32 &count() { return m_count; }

    T type() const { return m_type; }

  private:
    T m_type;
    u32 m_count;
    Level m_verbose_level;
  };

  virtual void interface_print_final(const var::StringView view);

  void write_fileno(int fd, const var::StringView view) const;

private:
#if defined __win32
  static unsigned int m_default_color;
#endif

  api::ProgressCallback m_progress_callback;
  u16 m_progress_width = 0;
  u16 m_progress_state = 0;
  u16 m_progress_key_state = 0;
  u16 m_indent;
  u16 m_indent_size = 2;
  Flags m_print_flags = Flags::null;
  var::StringView m_progress_key;
  Level m_verbose_level;

#if defined __link
  bool m_is_bash;
#endif
};

class NullPrinter : public Printer {
protected:
  void print(const char *key, const char *value) {
    MCU_UNUSED_ARGUMENT(key);
    MCU_UNUSED_ARGUMENT(value);
  }
};

} // namespace printer

#endif // PRINTER_API_PRINTER_PRINTER_HPP_
