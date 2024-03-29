// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#if defined __win32
#include <windows.h>
#endif

#include <unistd.h>

#include "var/StackString.hpp"

#include "printer/Printer.hpp"

#if defined __win32
unsigned int printer::Printer::m_default_color = static_cast<unsigned int>(-1);
#endif

using namespace printer;
using namespace var;

Printer::Printer()
  : m_progress_callback(
    [&](int value, int total) { return update_progress(value, total); }) {
#if defined __win32
  if (m_default_color == static_cast<unsigned int>(-1)) {
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    m_default_color = info.wAttributes;
  }
#endif
}

void Printer::set_format_code(u32 code) {
#if defined __link
  if (is_bash()) {
    interface_print_final(NumberString(code, "\033[1;%dm"));
  }
#endif
}

void Printer::clear_format_code(u32 code) {
#if defined __link
  if (is_bash()) {
    interface_print_final(NumberString(code, "\033[1;2%dm"));
  }
#endif
}

void Printer::set_color_code(u32 code) {

#if defined __link
  if (is_bash()) {
    interface_print_final(NumberString(code, "\033[1;%dm"));
  }
#endif

#if defined __link && defined __win32
  WORD color = static_cast<WORD>(m_default_color);
  switch (static_cast<ColorCode>(code)) {
  case ColorCode::none:
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
  const StringView key,
  const StringView value,
  IsNewline is_newline) {
  // default flat printer behavior
  if (verbose_level > this->verbose_level()) {
    return;
  }

  for (u32 indent = 0; indent < m_indent * m_indent_size; indent++) {
    interface_print_final(" ");
  }

  auto print_escaped = [&](StringView value) {
    for (const auto character : value) {
      const auto print_value = [&]() {
        if (character == '"') {
          return StringView{"\\\""};
        }
        if (character == '\b') {
          return StringView{"\\b"};
        }
        if (character == '\f') {
          return StringView{"\\f"};
        }
        if (character == '\n') {
          return StringView{"\\n"};
        }
        if (character == '\r') {
          return StringView{"\\r"};
        }
        if (character == '\t') {
          return StringView{"\\t"};
        }
        if (character == '\\') {
          return StringView{"\\\\"};
        }

        return StringView{&character, 1};
      }();
      interface_print_final(print_value);
    }
  };

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
      print_escaped(key);
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
      print_escaped(value);
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

void Printer::interface_print_final(const StringView view) {
#if defined __link
  fwrite(view.data(), view.length(), 1, stdout);
  fflush(stdout);
#else
  write_fileno(stdout->_file, view);
#endif
}

void Printer::write_fileno(int fd, const StringView view) const {
  const auto *begin = view.data();
  const auto length = view.length();
  auto sent = size_t{};
  auto result = ssize_t{};
  api::ErrorScope error_scope;
  do {
    const auto page_size = view.length() - sent;
    result = ::write(fd, begin + sent, page_size);
    if (result > 0) {
      sent += result;
    }
  } while ((sent < length) && (result > 0));
}

Printer &Printer::open_object(const StringView key, Level level) {
  print_open_object(level, key);
  return *this;
}

Printer &Printer::close_object() {
  print_close_object();
  return *this;
}

Printer &Printer::open_array(const StringView key, Level level) {
  print_open_array(level, key);
  return *this;
}

Printer &Printer::close_array() {
  print_close_array();
  return *this;
}

void Printer::print_open_object(Level verbose_level, StringView key) {
  print(verbose_level, key, "", IsNewline::yes);
  m_indent++;
}

void Printer::print_close_object() {
  if (m_indent) {
    m_indent--;
  }
}

void Printer::print_open_array(Level verbose_level, StringView key) {
  print(verbose_level, key, "", IsNewline::yes);
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

Printer::ColorCode Printer::color_code(const StringView color) {
  IdString color_upper(color);
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

Printer &Printer::set_verbose_level(const StringView level) {
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

auto Printer::update_progress(int progress, int total)
  -> api::ProgressCallback::IsAbort {
  const auto width = m_progress_width;

  if (verbose_level() >= Level::info) {

    if ((m_progress_state == 0) && total) {

      // only print the key once with total == -1
      const NumberString key
        = m_progress_key_state == 0
            ? NumberString(m_progress_key)
            : NumberString(m_progress_key)
                .append(NumberString(m_progress_key_state, "-%d"));
      print(Level::info, key, StringView().set_null(), IsNewline::no);

      m_progress_key_state++;

      if (total != api::ProgressCallback::indeterminate_progress_total()) {
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
        const StringView animation = "-\\|/";
        if ((m_print_flags & Flags::value_quotes) && (m_progress_state == 1)) {
          interface_print_final("\"");
        }
        m_progress_state++;

        if ((m_print_flags & Flags::simple_progress) == 0) {
          NumberString output;
          output.format(
            "%c" F32U,
            animation.at(m_progress_state % animation.length()),
            progress);
          interface_print_final(output);
          for (const auto c : output.string_view()) {
            MCU_UNUSED_ARGUMENT(c);
            interface_print_final("\b"); // backspace
          }
        } else {
          interface_print_final("~");
        }

      } else {

        const auto target = [&]() {
          const auto is_overflow = total && (INT_MAX / width < total);
          if( is_overflow ){
            //printf("overflow %d/%d!!!\n", progress, total);
          }
          const auto scaled_progress
            = is_overflow ? progress / width : progress;
          const auto scaled_total = is_overflow ? total / width : total;
          return scaled_total
                   ? (scaled_progress * width + scaled_total / 2) / scaled_total
                   : 0;
        }();

        while ((total != 0) && (m_progress_state <= target)) {
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
      if (m_print_flags & Flags::value_quotes) {
        interface_print_final("\"");
      }
      if ((m_print_flags & Flags::no_progress_newline) == false) {
        interface_print_final("\n");
      }
    }
  }

  return api::ProgressCallback::IsAbort::no;
}

Printer &Printer::key(const StringView key, const String &a) {
  print(Level::info, key, a.cstring(), IsNewline::yes);
  return *this;
}

Printer &Printer::key_bool(const StringView key, bool a) {
  print(Level::info, key, a ? "true" : "false", IsNewline::yes);
  return *this;
}

Printer &Printer::key(const StringView key, StringView a) {
  print(Level::info, key, a, IsNewline::yes);
  return *this;
}

Printer &Printer::newline() {
  interface_print_final("\n");
  return *this;
}

Printer &Printer::debug(const StringView a) {
  print(Level::debug, "debug", a, IsNewline::yes);
  return *this;
}

Printer &Printer::info(const StringView a) {
  print(Level::info, "info", a, IsNewline::yes);
  return *this;
}

Printer &Printer::message(const StringView a) {
  print(Level::message, "message", a, IsNewline::yes);
  return *this;
}

Printer &Printer::warning(const StringView a) {
  if (flags() & Flags::yellow_warnings) {
    set_color_code(ColorCode::yellow);
  }
  print(Level::warning, "warning", a, IsNewline::yes);
  if (flags() & Flags::yellow_warnings) {
    clear_color_code();
  }
  return *this;
}

Printer &Printer::error(const StringView a) {
  if (flags() & Flags::red_errors) {
    set_color_code(ColorCode::red);
  }
  print(Level::error, "error", a, IsNewline::yes);
  if (flags() & Flags::red_errors) {
    clear_color_code();
  }
  return *this;
}

Printer &Printer::fatal(const StringView a) {
  if (flags() & Flags::red_errors) {
    set_color_code(ColorCode::red);
  }
  print(Level::fatal, "fatal", a, IsNewline::yes);
  if (flags() & Flags::red_errors) {
    clear_color_code();
  }
  return *this;
}

Printer &Printer::trace(const char *function, int line, StringView message) {
  if (verbose_level() == Level::trace) {
    interface_print_final(">> trace ");
    interface_print_final(function);
    interface_print_final(NumberString(line, ":%d "));
    interface_print_final(message);
    interface_print_final("\n");
  }
  return *this;
}

#if !defined __link
Printer &Printer::operator<<(const DataInfo &a) {
  return key("arena", NumberString(a.arena()))
    .key("freeSize", NumberString(a.free_size()))
    .key("usedSize", NumberString(a.used_size()))
    .key("freeBlockCount", NumberString(a.free_block_count()));
}
#endif

Printer &Printer::operator<<(const View a) {
  const auto o_flags = flags();

  const auto count = [a, o_flags]() {
    const auto size = a.size();
    if (o_flags & Flags::width_32) {
      return size / 4;
    } else if (o_flags & Flags::width_16) {
      return size / 2;
    } else if (o_flags & Flags::blob) {
      return (size + 15) / 16;
    }
    return size;
  }();

  const auto *ptru8 = a.to_const_u8();
  const auto *ptru32 = a.to_const_u32();
  const auto *ptru16 = a.to_const_u16();
  auto bytes_printed = 0;

  for (int i = 0; i < count; i++) {
    GeneralString data_string;
    if (o_flags & Flags::hex) {
      if (o_flags & Flags::width_32) {
        data_string = NumberString().format(F32X, ptru32[i]).string_view();
      } else if (o_flags & Flags::width_16) {
        data_string = NumberString().format("%X", ptru16[i]).string_view();
      } else if (o_flags & Flags::blob) {
        for (u32 j = 0; j < 16; j++) {
          if (i * 16 + j < a.size()) {
            data_string |= NumberString().format("%02X", ptru8[i * 16 + j]);
          } else {
            data_string |= "__";
          }
          if (j < 15) {
            data_string |= " ";
          }
          bytes_printed++;
        }
      } else {
        data_string |= NumberString(ptru8[i], "%X");
      }
      data_string |= " ";
    } else if (o_flags & Flags::type_unsigned) {
      if (o_flags & Flags::width_32) {
        data_string = NumberString().format(F32U, ptru32[i]).string_view();
      } else if (o_flags & Flags::width_16) {
        data_string = NumberString().format("%u", ptru16[i]).string_view();
      } else if (o_flags & Flags::blob) {
        for (u32 j = 0; j < 16; j++) {
          if (i * 16 + j < a.size()) {
            data_string |= NumberString().format("%u", ptru8[i * 16 + j]);
          } else {
            data_string |= "___";
          }
          if (j < 15) {
            data_string |= " ";
          }
        }
      } else {
        data_string = NumberString().format("%u", ptru8[i]).string_view();
      }
      data_string |= " ";
    } else if (o_flags & Flags::type_char) {
      if (ptru8[i] == '\n') {
        data_string = " \\n";
      } else if (ptru8[i] == '\r') {
        data_string = " \\r";
      } else if (ptru8[i] == 0) {
        data_string = " null";
      } else if (ptru8[i] < 128) {
        data_string = NumberString().format(" %c", ptru8[i]).string_view();
      }
    } else if (o_flags & Flags::type_float) {
      const auto *ptrfloat = a.to_const_float();
      data_string = NumberString().format("%0.3f", ptrfloat[i]).string_view();
    } else {
      // default is signed values
      if (o_flags & Flags::width_32) {
        const auto *ptrs32 = a.to_const_s32();
        data_string = NumberString().format(F32D, ptrs32[i]).string_view();
      } else if (o_flags & Flags::width_16) {
        const auto *ptrs16 = a.to_const_s16();
        data_string = NumberString().format("%d", ptrs16[i]).string_view();
      } else if (o_flags & Flags::blob) {
        for (u32 j = 0; j < 16; j++) {
          if (i * 16 + j < a.size()) {
            data_string
              |= NumberString().format("%d", ptru8[i * 16 + j]).string_view();
          } else {
            data_string |= "__";
          }
          if (j < 15) {
            data_string |= " ";
          }
        }
      } else {
        const auto *ptrs8 = a.to_const_s8();
        data_string = NumberString().format("%d", ptrs8[i]).string_view();
      }
    }

    print(
      verbose_level(),
      NumberString(i, "[%04d]"),
      data_string,
      IsNewline::yes);
  }

  return *this;
}

// to use the demangler, the symbol needs to parse the line and pull out the
// mangled symbol
#define USE_DEMANGLER 0

Printer &Printer::operator<<(const api::Error &error_context) {
  key("lineNumber", NumberString(error_context.line_number()).string_view());
  key(
    "returnValue",
    NumberString(api::ExecutionContext::return_value()).string_view());
  key("errorNumber", NumberString(error_context.error_number()).string_view());
  key("message", StringView(error_context.message()));
#if defined __link

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
      key(NumberString(offset), StringView(symbol));
    }

    offset++;
  } while (symbol != nullptr);
#endif

  return *this;
}

Printer &Printer::operator<<(const StringView a) {
  interface_print_final(a);
  return *this;
}

Printer &Printer::operator<<(const String &a) {
  interface_print_final(a.cstring());
  return *this;
}

Printer &Printer::operator<<(const StringList &a) {
  for (u32 i = 0; i < a.count(); i++) {
    key(NumberString(i), a.at(i));
  }
  return *this;
}

Printer &Printer::operator<<(const StringViewList &a) {
  for (u32 i = 0; i < a.count(); i++) {
    key(NumberString(i), a.at(i));
  }
  return *this;
}
Printer &Printer::enable_flags(PrinterFlags::Flags value) {
  m_print_flags |= value;
  return *this;
}
Printer &Printer::disable_flags(PrinterFlags::Flags value) {
  m_print_flags &= ~value;
  return *this;
}
Printer &Printer::set_flags(PrinterFlags::Flags value) {
  m_print_flags = value;
  return *this;
}
