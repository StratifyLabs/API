// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#include <cstring>

#include "chrono/ClockTimer.hpp"
#include "fs/FileObject.hpp"
#include "var/StackString.hpp"

using namespace fs;

size_t FileObject::size() const {
  // get current cursor
  API_RETURN_VALUE_IF_ERROR(0);
  const int loc = location();
  seek(0, Whence::end);
  const auto seek_size = static_cast<size_t>(location());
  seek(loc, Whence::set);
  API_RETURN_VALUE_IF_ERROR(0);
  return seek_size;
}

const FileObject &FileObject::read(var::View view) const {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL("", interface_read(view.data(), view.size()));
  return *this;
}

const FileObject &FileObject::write(var::View view) const {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL("", interface_write(view.data(), view.size()));
  return *this;
}

const FileObject &FileObject::seek(int location, Whence whence) const {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL("", interface_lseek(location, static_cast<int>(whence)));
  return *this;
}

const FileObject &FileObject::sync() const {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL("", interface_fsync());
  return *this;
}

int FileObject::location() const {
  return seek(0, Whence::current).return_value();
}

const FileObject &
FileObject::ioctl_implementation(int request, void *argument) const {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL("", interface_ioctl(request, argument));
  return *this;
}

const FileObject &
FileObject::write(const FileObject &source_file, const Write &options) const {
  API_RETURN_VALUE_IF_ERROR(*this);

  if (options.location() != -1) {
    seek(options.location(), Whence::set);
  }

  const size_t file_size = (options.size() == static_cast<size_t>(-1))
                             ? (source_file.size() - source_file.location())
                             : options.size();

  if (file_size == 0) {
    if (options.progress_callback()) {
      options.progress_callback()->update(0, 100);
      options.progress_callback()->update(100, 100);
      options.progress_callback()->update(0, 0);
    }
    return *this;
  }

  chrono::ClockTimer clock_timer;

  const size_t effective_page_size
    = options.page_size() ? options.page_size() : FSAPI_LINK_DEFAULT_PAGE_SIZE;

  const size_t page_size_with_boundary
    = (options.transformer() == nullptr)
        ? effective_page_size
        : (
          (effective_page_size / options.transformer()->page_size_boundary())
          * options.transformer()->page_size_boundary());

  const size_t read_buffer_size
    = options.terminator() != '\0' ? 1 : page_size_with_boundary;

  u8 file_read_buffer[read_buffer_size];
  size_t size_processed = 0;

  clock_timer.start();
  do {
    const size_t remaining_size = file_size - size_processed;
    const size_t page_size
      = (remaining_size < read_buffer_size) ? remaining_size : read_buffer_size;

    file_read_buffer[0] = 0;

    if (const int bytes_read
        = source_file.read(var::View(file_read_buffer, page_size))
            .return_value();
        bytes_read > 0) {
      if (options.transformer()) {
        const size_t transform_size
          = options.transformer()->get_output_size(page_size);
        u8 file_write_buffer[transform_size];
        const int bytes_to_write = options.transformer()->transform(
          var::Transformer::Transform()
            .set_input(var::View(file_read_buffer, page_size))
            .set_output(var::View(file_write_buffer, transform_size)));

        write(var::View(file_write_buffer, bytes_to_write));
      } else {
        write(var::View(file_read_buffer, bytes_read));
        if (return_value() != bytes_read) {
          if (options.progress_callback()) {
            options.progress_callback()->update(0, 0);
          }
          API_RETURN_VALUE_ASSIGN_ERROR(*this, "bad page size", EINVAL);
        }
      }

      if (is_error()) {
        return *this;
      }

      size_processed += static_cast<size_t>(bytes_read);
      if (
        options.terminator() != 0
        && static_cast<char>(file_read_buffer[0]) == options.terminator()) {
        break;
      }

    } else {
      // are we on a timeout?
      if (options.timeout() > 0_microseconds) {
        if (clock_timer.micro_time() > options.timeout()) {
          break;
        }

        if (bytes_read < 0) {
          reset_error();
        }

        chrono::wait(options.retry_delay());
      }
    }

    if (
      options.progress_callback()
      && options.progress_callback()->update(
           int(size_processed),
           int(file_size))
           == api::ProgressCallback::IsAbort::yes) {
      options.progress_callback()->update(0, 0);
      API_SYSTEM_CALL("aborted", size_processed);
      return *this;
    }

  } while ((source_file.return_value() > 0) && (file_size > size_processed));

  // this will terminate the progress operation
  if (options.progress_callback()) {
    options.progress_callback()->update(0, 0);
  }

  if ((source_file.is_error()) && (size_processed == 0)) {
    API_SYSTEM_CALL("", -1);
  } else {
    API_SYSTEM_CALL("", size_processed);
  }

  return *this;
}

bool FileObject::verify(const FileObject &source_file, const Verify &options)
  const {
  API_RETURN_VALUE_IF_ERROR(false);

  size_t size_processed = 0;

  if (this == &source_file) {
    if (options.progress_callback()) {
      options.progress_callback()->update(0, 0);
    }
    return true;
  }

  const size_t verify_size
    = options.size() != static_cast<size_t>(-1) ? options.size() : size();

  if (options.progress_callback()) {
    options.progress_callback()->update(0, static_cast<int>(verify_size));
  }

  char source_file_buffer[options.page_size()];
  char this_file_buffer[options.page_size()];

  do {
    const size_t remaining = verify_size - size_processed;
    const size_t current_page_size
      = (remaining > options.page_size()) ? options.page_size() : remaining;

    var::View source_file_view(source_file_buffer, current_page_size);
    var::View this_file_view(this_file_buffer, current_page_size);

    const int source_result = source_file.read(source_file_view).return_value();

    if (const int this_result = read(this_file_view).return_value();
        source_result != this_result) {
      if (options.progress_callback()) {
        options.progress_callback()->update(0, 0);
      }
      return false;
    }

    if (source_file_view != this_file_view) {
      if (options.progress_callback()) {
        options.progress_callback()->update(0, 0);
      }
      return false;
    }

    size_processed += current_page_size;

    if (
      options.progress_callback()
      && options.progress_callback()->update(
           int(size_processed),
           int(verify_size))
           == api::ProgressCallback::IsAbort::yes) {
      options.progress_callback()->update(0, 0);
      API_SYSTEM_CALL("aborted", size_processed);
      return false;
    }

  } while (size_processed < verify_size);

  if (options.progress_callback()) {
    options.progress_callback()->update(0, 0);
  }

  return true;
}

void FileObject::fake_seek(
  int &location,
  const size_t size,
  int offset,
  int whence) {
  switch (static_cast<Whence>(whence)) {
  case Whence::current:
    location += offset;
    break;
  case Whence::end:
    location = static_cast<int>(size);
    break;
  case Whence::set:
    location = offset;
    break;
  }

  if (location > static_cast<int>(size)) {
    location = static_cast<int>(size);
  } else if (location < 0) {
    location = 0;
  }
}

auto FileObject::read_line_implementation(char term, char *buffer, size_t size)
  const -> var::StringView {
  const auto file_location = location();
  const auto bytes_read = read(var::View(buffer, size)).return_value();
  auto result = bytes_read > 0 ? var::StringView{buffer, size_t(bytes_read)}
                               : var::StringView{};
  auto offset = size_t{};
  for (auto c : result) {
    if (c == term) {
      const auto new_length = offset + 1;
      seek(file_location + new_length);
      result.truncate(new_length);
      return result;
    }
    ++offset;
  }
  return result;
}

auto FileObject::get_line_implementation(char term, char *buffer, size_t size)
  const -> var::StringView {
  auto c = '\0';
  auto bytes_received = size_t{};
  while ((c != term) && is_success()) {
    if (read(var::View(c)).return_value() == 1) {
      buffer[bytes_received] = c;
      ++bytes_received;
      if (bytes_received == size) {
        c = term;
      }
    } else {
      c = term;
    }
  }

  return var::StringView{buffer, bytes_received};
}
