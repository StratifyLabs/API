#ifndef PROCESSAPI_PIPE_HPP
#define PROCESSAPI_PIPE_HPP

#if defined __link

#include "fs/File.hpp"

namespace sys {

class Pipe : public api::ExecutionContext {
public:
  Pipe();
  Pipe(const Pipe &) = delete;
  Pipe &operator=(const Pipe &) = delete;
  Pipe(Pipe &&) = default;
  Pipe &operator=(Pipe &&) = default;

  fs::File &read_file() { return m_read_file; }
  const fs::File &read_file() const { return m_read_file; }

  fs::File &write_file() { return m_write_file; }
  const fs::File &write_file() const { return m_write_file; }

  static void make_fifo(var::StringView path, fs::Permissions permissions = fs::Permissions());

private:
  fs::File m_read_file;
  fs::File m_write_file;
};

} // namespace sys

#endif

#endif // PROCESSAPI_PIPE_HPP
