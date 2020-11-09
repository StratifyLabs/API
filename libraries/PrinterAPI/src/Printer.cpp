/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.

#include <cstdarg>
#if defined __win32
#include <windows.h>
#endif

#include <unistd.h>

#include "var/StackString.hpp"
#include "var/String.hpp"

#include "printer/Printer.hpp"

#if defined __win32
unsigned int printer::Printer::m_default_color = static_cast<unsigned int>(-1);
#endif

using namespace printer;

Printer::Printer() {
  m_progress_callback.set_callback(Printer::update_progress_callback)
    .set_context(this);
  m_print_flags = Flags::width_8 | Flags::hex;
  m_indent = 0;
  m_progress_width = 50;
  m_progress_state = 0;
  m_verbose_level = Level::info;
  m_progress_key = "progress";
#if defined __win32
  if (m_default_color == static_cast<unsigned int>(-1)) {
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    m_default_color = info.wAttributes;
  }
#endif

#if defined __link
  m_is_bash = false;
#endif
}

void Printer::set_format_code(u32 code) {
#if defined __link
  if (is_bash()) {
    interface_print_final(var::NumberString(code, "\033[1;%dm"));
  }
#endif
}

void Printer::clear_format_code(u32 code) {
#if defined __link
  if (is_bash()) {
    interface_print_final(var::NumberString(code, "\033[1;2%dm"));
  }
#endif
}

void Printer::set_color_code(u32 code) {

#if defined __link
  if (is_bash()) {
    interface_print_final(var::NumberString(code, "\033[1;%dm"));
  }
#endif

#if defined __link && defined __win32
  WORD color = static_cast<WORD>(m_default_color);
  switch (code) {
  case ColorCode::default:
    color = static_cast<WORD>(m_default_color);
    break;
  case ColorCode::black:
    color = 0;
    break;
  case ColorCode::red:
    color = FOREGROUND_RED;
    break;
  case ColorCode::green:
    color = FOREGROUND_GREEN;
    break;
  case ColorCode::yellow:
    color = FOREGROUND_RED | FOREGROUND_GREEN;
    break;
  case ColorCode::blue:
    color = FOREGROUND_BLUE;
    break;
  case ColorCode::magenta:
    color = FOREGROUND_BLUE | FOREGROUND_RED;
    break;
  case ColorCode::cyan:
    color = FOREGROUND_BLUE | FOREGROUND_GREEN;
    break;
  case ColorCode::light_gray:
    color = FOREGROUND_INTENSITY;
    break;
  case ColorCode::dark_gray:
    color = 0;
    break;
  case ColorCode::light_red:
    color = FOREGROUND_RED | FOREGROUND_INTENSITY;
    break;
  case ColorCode::light_green:
    color = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    break;
  case ColorCode::light_yellow:
    color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    break;
  case ColorCode::light_blue:
    color = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    break;
  }
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
#endif
}

void Printer::print(
  Level verbose_level,
  var::StringView key,
  var::StringView value,
  IsNewline is_newline) {
  // default flat printer behavior
  if (verbose_level > this->verbose_level()) {
    return;
  }

  for (u32 indent = 0; indent < m_indent; indent++) {
    interface_print_final("  ");
  }

  if (key.is_null() == false) {
    if (m_print_flags & Flags::bold_keys) {
      set_format_code(FormatType::bold);
    }
    if (m_print_flags & Flags::cyan_keys) {
      set_color_code(static_cast<int>(ColorCode::cyan));
    }
    if (m_print_flags & Flags::yellow_keys) {
      set_color_code(static_cast<int>(ColorCode::yellow));
    }
    if (m_print_flags & Flags::magenta_keys) {
      set_color_code(static_cast<int>(ColorCode::magenta));
    }
    if (m_print_flags & Flags::red_keys) {
      set_color_code(static_cast<int>(ColorCode::red));
    }
    if (m_print_flags & Flags::key_quotes) {
      interface_print_final("\"");
      interface_print_final(key);
      interface_print_final("\": ");
    } else {
      interface_print_final(key);
      interface_print_final(": ");
    }
    if (m_print_flags & Flags::bold_keys) {
      clear_format_code(static_cast<int>(FormatType::bold));
    }
    if (
      m_print_flags
      & (Flags::cyan_keys | Flags::yellow_keys | Flags::magenta_keys | Flags::red_keys)) {
      clear_color_code();
    }
  }

  if (value.is_null() == false) {
    if (m_print_flags & Flags::bold_values) {
      set_format_code(static_cast<int>(FormatType::bold));
    }
    if (m_print_flags & Flags::green_values) {
      set_color_code(static_cast<int>(ColorCode::green));
    }
    if (m_print_flags & Flags::yellow_values) {
      set_color_code(static_cast<int>(ColorCode::yellow));
    }
    if (m_print_flags & Flags::red_values) {
      set_color_code(static_cast<int>(ColorCode::red));
    }
    if (m_print_flags & Flags::cyan_values) {
      set_color_code(static_cast<int>(ColorCode::cyan));
    }
    if (m_print_flags & Flags::value_quotes) {
      interface_print_final("\"");
      interface_print_final(value);
      interface_print_final("\"");
    } else {
      interface_print_final(value);
    }
    if (m_print_flags & Flags::bold_values) {
      clear_format_code(static_cast<int>(FormatType::bold));
    }
    if (
      m_print_flags
      & (Flags::green_values | Flags::yellow_values | Flags::red_values | Flags::cyan_values)) {
      clear_color_code();
    }
  }

  if (is_newline == IsNewline::yes) {
    interface_print_final("\n");
  }
}

void Printer::interface_print_final(var::StringView view) {
#if defined __link
  fwrite(view.data(), view.length(), 1, stdout);
  fflush(stdout);
#else
  ::write(stdout->_file, view.data(), view.length());
#endif
}

Printer &Printer::open_object(var::StringView key, Level level) {
  print_open_object(level, key);
  return *this;
}

Printer &Printer::close_object() {
  print_close_object();
  return *this;
}

Printer &Printer::open_array(var::StringView key, Level level) {
  print_open_array(level, key);
  return *this;
}

Printer &Printer::close_array() {
  print_close_array();
  return *this;
}

void Printer::print_open_object(Level verbose_level, var::StringView key) {
  print(verbose_level, key, "");
  m_indent++;
}

void Printer::print_close_object() {
  if (m_indent) {
    m_indent--;
  }
}

void Printer::print_open_array(
  Level verbose_level,
  var::StringView key) {
  print(verbose_level, key, "");
  m_indent++;
}

void Printer::print_close_array() {
  if (m_indent) {
    m_indent--;
  }
}

void Printer::clear_color_code() {
#if defined __link
  if (is_bash()) {
    interface_print_final("\033[0m");
  } else {
    set_color_code(ColorCode::normal);
  }
#endif
}

Printer::ColorCode Printer::color_code(var::StringView color) {
  var::String color_upper(color);
  color_upper.to_upper();
  if (color_upper == "BLACK") {
    return ColorCode::black;
  }
  if (color_upper == "RED") {
    return ColorCode::red;
  }
  if (color_upper == "GREEN") {
    return ColorCode::green;
  }
  if (color_upper == "YELLOW") {
    return ColorCode::yellow;
  }
  if (color_upper == "BLUE") {
    return ColorCode::blue;
  }
  if (color_upper == "MAGENTA") {
    return ColorCode::magenta;
  }
  if (color_upper == "CYAN") {
    return ColorCode::cyan;
  }
  if (color_upper == "LIGHT GRAY") {
    return ColorCode::light_gray;
  }
  if (color_upper == "DARK GRAY") {
    return ColorCode::dark_gray;
  }
  if (color_upper == "LIGHT RED") {
    return ColorCode::light_red;
  }
  if (color_upper == "LIGHT GREEN") {
    return ColorCode::light_green;
  }
  if (color_upper == "LIGHT YELLOW") {
    return ColorCode::light_yellow;
  }
  if (color_upper == "LIGHT BLUE") {
    return ColorCode::light_blue;
  }

  return ColorCode::normal;
}

Printer::~Printer() {}

#if 0
void Printer::vprint(const char * fmt, va_list list){
	vprintf(fmt, list);
	fflush(stdout);
}

void Printer::print(const char * fmt, ...){
	va_list list;
	va_start(list, fmt);
	vprint(fmt, list);
	va_end(list);
}
#endif

Printer &Printer::set_verbose_level(var::StringView level) {
  if (level == "debug") {
    set_verbose_level(Level::debug);
  } else if (level == "info") {
    set_verbose_level(Level::info);
  } else if (level == "message") {
    set_verbose_level(Level::message);
  } else if (level == "warning") {
    set_verbose_level(Level::warning);
  } else if (level == "error") {
    set_verbose_level(Level::error);
  } else if (level == "fatal") {
    set_verbose_level(Level::fatal);
  } else if (level == "trace") {
    set_verbose_level(Level::trace);
  }
  return *this;
}

char Printer::get_bitmap_pixel_character(u32 color, u8 bits_per_pixel) {
  if (color == 0) {
    return ' ';
  } else {
    if (bits_per_pixel == 2) {
      switch (color) {
      case 1:
        return '.';
      case 2:
        return '+';
      case 3:
        return '@';
      }
    } else if (bits_per_pixel < 8) {
      switch (color) {
      case 1:
        return '.';
      case 2:
        return ',';
      case 3:
        return '-';
      case 4:
        return '+';
      case 5:
        return '=';
      case 6:
        return '^';
      case 7:
        return 'x';
      case 8:
        return 'o';
      case 9:
        return '*';
      case 10:
        return '#';
      case 11:
        return '%';
      case 12:
        return '$';
      case 13:
        return 'O';
      case 14:
        return 'X';
      case 15:
        return '@';
      }
    } else {
      return '#';
    }
  }
  return '?';
}

u32 Printer::get_bitmap_pixel_color(char c, u8 bits_per_pixel) {

  if (bits_per_pixel == 1) {
    if (c == ' ') {
      return 0;
    }
    return 1;
  }

  if (bits_per_pixel == 2) {
    switch (c) {
    case ' ':
      return 0;
    case '.':
      return 1;
    case ',':
      return 2;
    case '-':
    default:
      return 3;
    }
  }

  if (bits_per_pixel == 4) {
    switch (c) {
    case ' ':
      return 0;
    case '.':
      return 1;
    case ',':
      return 2;
    case '-':
      return 3;
    case '+':
      return 4;
    case '=':
      return 5;
    case '^':
      return 6;
    case 'x':
      return 7;
    case 'o':
      return 8;
    case '*':
      return 9;
    case '#':
      return 10;
    case '%':
      return 11;
    case '$':
      return 12;
    case 'O':
      return 13;
    case 'X':
      return 14;
    case '@':
    default:
      return 15;
    }
  }

  return 255;
}

bool Printer::update_progress(int progress, int total) {
  const u32 width = m_progress_width;

  if (verbose_level() >= Level::info) {

    if ((m_progress_state == 0) && total) {

      // only print the key once with total == -1
      print(
        Level::info,
        m_progress_key,
        var::StringView().set_null(),
        IsNewline::no);
      if (total != -1) {
        if (m_print_flags & Flags::value_quotes) {
          interface_print_final("\"");
        }
        if ((m_print_flags & Flags::simple_progress) == 0) {
          for (u32 i = 0; i < width; i++) {
            interface_print_final(".");
          }
          for (u32 i = 0; i < width; i++) {
            interface_print_final("\b"); // backspace
          }
        }
      }
      m_progress_state++;
      fflush(stdout);
    }

    if (m_progress_state > 0) {

      if (total == api::ProgressCallback::indeterminate_progress_total()) {
        var::StringView  animation = "-\\|/";
        if ((m_print_flags & Flags::value_quotes) && (m_progress_state == 1)) {
          interface_print_final("\"");
        }
        m_progress_state++;

        if ((m_print_flags & Flags::simple_progress) == 0) {
          var::NumberString output;
          output.format(
            "%c" F32U,
            animation.at(m_progress_state % animation.length()),
            progress);
          interface_print_final(output.cstring());
          for (const auto c : output.string_view()) {
            interface_print_final("\b"); // backspace
          }
        } else {
          interface_print_final(var::NumberString(m_progress_state - 1));
        }

      } else {

        while (
          (total != 0)
          && (m_progress_state <= (progress * width + total / 2) / total)) {
          interface_print_final("#");
          m_progress_state++;
          fflush(stdout);
        }

        if ((progress >= total) || (total == 0)) {
          m_progress_state = 0;
        }
      }
    }
    if (total == 0) {
      if ((m_print_flags & Flags::no_progress_newline) == false) {
        interface_print_final("\n");
      }
      if (m_print_flags & Flags::value_quotes) {
        interface_print_final("\"");
      }
    }
  }

  return false;
}

Printer &Printer::key(var::StringView key, const var::String &a) {
  print(Level::info, key, a.cstring());
  return *this;
}

Printer &Printer::key_bool(var::StringView key, bool a) {
  print(Level::info, key, a ? "true" : "false");
  return *this;
}

Printer &Printer::key(var::StringView key, var::StringView a) {
  print(Level::info, key, a);
  return *this;
}

Printer &Printer::debug(var::StringView a) {
  print(Level::debug, "debug", a);
  return *this;
}

Printer &Printer::info(var::StringView a) {
  print(Level::info, "info", a);
  return *this;
}

Printer &Printer::message(var::StringView a) {
  print(Level::message, "message", a);
  return *this;
}

Printer &Printer::warning(var::StringView a) {
  if (flags() & Flags::yellow_warnings) {
    set_color_code(ColorCode::yellow);
  }
  print(Level::warning, "warning", a);
  if (flags() & Flags::yellow_warnings) {
    clear_color_code();
  }
  return *this;
}


Printer &Printer::error(var::StringView a) {
  if (flags() & Flags::red_errors) {
    set_color_code(ColorCode::red);
  }
  print(Level::error, "error", a);
  if (flags() & Flags::red_errors) {
    clear_color_code();
  }
  return *this;
}

Printer &Printer::fatal(var::StringView a) {
  if (flags() & Flags::red_errors) {
    set_color_code(ColorCode::red);
  }
  print(Level::fatal, "fatal", a);
  if (flags() & Flags::red_errors) {
    clear_color_code();
  }
  return *this;
}

Printer &
Printer::trace(const char *function, int line, var::StringView message) {

  if (verbose_level() == Level::trace) {
    const var::String s = var::String().format(
      ">> trace %s:%d %s\n",
      function,
      line,
      var::String(message).cstring());
    interface_print_final(s);
  }
  return *this;
}

Printer &Printer::operator<<(var::View a) {
  const Flags o_flags = flags();
  const s8 *ptrs8 = a.to_const_s8();
  const s16 *ptrs16 = a.to_const_s16();
  const s32 *ptrs32 = a.to_const_s32();
  const u8 *ptru8 = a.to_const_u8();
  const u16 *ptru16 = a.to_const_u16();
  const u32 *ptru32 = a.to_const_u32();

  int s;
  if (o_flags & Flags::width_32) {
    s = a.size() / 4;
  } else if (o_flags & Flags::width_16) {
    s = a.size() / 2;
  } else if (o_flags & Flags::blob) {
    s = (a.size() + 15) / 16;
  } else {
    s = a.size();
  }

  int i;
  u32 bytes_printed = 0;
  var::String data_string;

  for (i = 0; i < s; i++) {
    if (o_flags & Flags::hex) {
      if (o_flags & Flags::width_32) {
        data_string += var::String().format(F32X, ptru32[i]);
      } else if (o_flags & Flags::width_16) {
        data_string += var::String().format("%X", ptru16[i]);
      } else if (o_flags & Flags::blob) {
        for (u32 j = 0; j < 16; j++) {
          data_string += var::String().format("%02X ", ptru8[i * 16 + j]);
          if (j < 15) {
            data_string += " ";
          }
          bytes_printed++;
          if (bytes_printed == a.size()) {
            break;
          }
        }
      } else {
        data_string += var::String().format("%X", ptru8[i]);
      }
      data_string += " ";
    }
    if (o_flags & Flags::type_unsigned) {
      if (o_flags & Flags::width_32) {
        data_string += var::String().format(F32U, ptru32[i]);
      } else if (o_flags & Flags::width_16) {
        data_string += var::String().format("%u", ptru16[i]);
      } else if (o_flags & Flags::blob) {
        for (u32 j = 0; j < 16; j++) {
          data_string += var::String().format("%u", ptru8[i * 16 + j]);
          if (j < 15) {
            data_string += " ";
          }
        }
      } else {
        data_string += var::String().format("%u", ptru8[i]);
      }
      data_string += " ";
    }
    if (o_flags & Flags::type_signed) {
      if (o_flags & Flags::width_32) {
        data_string += var::String().format(F32D, ptrs32[i]);
      } else if (o_flags & Flags::width_16) {
        data_string += var::String().format("%d", ptrs16[i]);
      } else if (o_flags & Flags::blob) {
        for (u32 j = 0; j < 16; j++) {
          data_string += var::String().format("%d", ptru8[i * 16 + j]);
          if (j < 15) {
            data_string += " ";
          }
        }
      } else {
        data_string += var::String().format("%d", ptrs8[i]);
      }
      data_string += " ";
    }
    if (o_flags & Flags::type_char) {
      if (ptru8[i] == '\n') {
        data_string += (" \\n");
      } else if (ptru8[i] == '\r') {
        data_string += (" \\r");
      } else if (ptru8[i] == 0) {
        data_string += (" null");
      } else if (ptru8[i] < 128) {
        data_string += var::String().format(" %c", ptru8[i]);
      }
    }

    print(
      verbose_level(),
      var::String().format("[%04d]", i).cstring(),
      data_string.cstring());
    data_string.clear();
  }

  return *this;
}

// to use the demangler, the symbol needs to parse the line and pull out the
// mangled symbol
#define USE_DEMANGLER 0

Printer &Printer::operator<<(const api::Error &error_context) {
  key(
    "lineNumber",
    var::NumberString(error_context.line_number()).string_view());
  key(
    "errorNumber",
    var::NumberString(error_context.error_number()).string_view());
  key("message", var::StringView(error_context.message()));

  api::Error::Backtrace backtrace(error_context);

  Printer::Object po(*this, "backtrace");
  const char *symbol;
  size_t offset = 0;
#if USE_DEMANGLER
  api::Demangler demangler;
#endif

  do {
    symbol = backtrace.at(offset);
#if USE_DEMANGLER
    symbol = demangler.demangle(symbol);
#endif

    if (symbol != nullptr) {
      key(var::NumberString(offset), var::StringView(symbol));
    }

    offset++;
  } while (symbol != nullptr);

  return *this;
}

Printer &Printer::operator<<(var::StringView a) {
  interface_print_final(a);
  return *this;
}

Printer &Printer::operator<<(const var::String &a) {
  interface_print_final(a.cstring());
  return *this;
}

Printer &Printer::operator<<(const var::StringList &a) {
  for (u32 i = 0; i < a.count(); i++) {
    key(var::NumberString(i), a.at(i));
  }
  return *this;
}

Printer &Printer::operator<<(const var::StringViewList &a) {
  for (u32 i = 0; i < a.count(); i++) {
    key(var::NumberString(i), a.at(i));
  }
  return *this;
}
