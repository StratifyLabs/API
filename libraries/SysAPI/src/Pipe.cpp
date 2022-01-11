
#if defined __link

#include <unistd.h>

#include "sys/Pipe.hpp"

#if defined __win32

#include <windows.h>

#define posix_pipe(x) _pipe(x, 4096, _O_NOINHERIT | _O_BINARY)
#else
#define posix_pipe(x) pipe(x)
#define posix_fcntl(x, y, z) fcntl(x, y, z)
#define POSIX_F_SETFL F_SETFL
#define POSIX_F_GETFL F_GETFL
#define POSIX_O_NONBLOCK O_NONBLOCK
#endif

using namespace sys;

Pipe::Pipe() {
  int fd[2];
  API_SYSTEM_CALL("pipe()", posix_pipe(fd));
  m_read_file = fs::File().set_fileno(fd[0]).move();
  m_write_file = fs::File().set_fileno(fd[1]).move();

#if defined __win32 || 1

#else
  fcntl(
    m_read_file.fileno(),
    F_SETFL,
    fcntl(m_read_file.fileno(), F_GETFL, 0) | O_NONBLOCK);
#endif
}

#endif
