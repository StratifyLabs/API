
#if defined __link

#include <unistd.h>

#include "sys/Pipe.hpp"

using namespace sys;

Pipe::Pipe()
{
  API_RETURN_IF_ERROR();
  int fd[2];
#if defined __win32

#else
  API_SYSTEM_CALL("pipe()", pipe(fd));
#endif
  API_RETURN_IF_ERROR();

  m_read_file = fs::File().set_fileno(fd[0]).move();
  m_write_file= fs::File().set_fileno(fd[1]).move();
}

#endif
