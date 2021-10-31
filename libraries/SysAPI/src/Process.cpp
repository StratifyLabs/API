// Copyright 2020-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#if defined __link

#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#if !defined __win32
#include <sys/wait.h>
#else
#define WEXITSTATUS(x) x
#define WIFEXITED(x) x
#define WTERMSIG(x) x
#define WIFSTOPPED(x) x
#define WIFSIGNALED(x) x
#define WSTOPSIG(x) x
#define WIFCONTINUED(x) x

#endif

#include "fs/FileSystem.hpp"
#include "sys/Process.hpp"

extern "C" char **environ;

using namespace sys;

Process::Environment::Environment(char **env) : Process::Arguments("") {
  char **effective_env = (env == nullptr) ? environ : env;
  size_t i = 0;
  do {
    if (effective_env[i] != nullptr) {
      push(effective_env[i]);
      i++;
    }
  } while (effective_env[i] != nullptr);
}

Process::Environment &Process::Environment::set(
  const var::StringView name,
  const var::StringView value) {

  auto format = [](const var::StringView name, const var::StringView value) {
    return name | "=" | value;
  };

  // check to see if the entry exists
  const auto starts_with = name | "=";
  for (size_t i = 0; i < m_arguments.count(); i++) {
    char *current_value = m_arguments.at(i);
    if (var::StringView(current_value).find(starts_with) == 0) {
      replace(i, format(name, value));
      return *this;
    }
  }

  push(format(name, value));
  return *this;
}

Process::Environment &
Process::Environment::set_working_directory(const var::StringView path) {
  return set("PWD", path);
}

const char *Process::Environment::find(const var::StringView variable) const {
  const auto check = var::NameString(variable).append("=");
  for (const auto *value : variables()) {
    if (value && var::StringView(value).find(check) == 0) {
      return value + check.length();
    }
  }
  return "";
}

var::PathString Process::which(const var::StringView executable) {
  const char *pwd = getenv("PWD");
  if (pwd) {
    if (const auto path = var::StringView(pwd) / executable;
        fs::FileSystem().exists(path)) {
      return path;
    }
  }

  if (fs::FileSystem().exists(executable)) {
    return executable;
  }

  const char *path = getenv("PATH");
  if (path == nullptr) {
    return var::PathString();
  }

  const auto path_list = var::StringView(path).split(";:");
  for (const auto &entry : path_list) {
    const auto path = entry / executable;
    if (fs::FileSystem().exists(path)) {
      return path;
    }
  }

  return var::PathString();
}

u8 Process::Status::exit_status() const { return WEXITSTATUS(m_status_value); }

bool Process::Status::is_exited() const {
  return WIFEXITED(m_status_value) != 0;
}
bool Process::Status::is_terminated() const {
  return WIFSIGNALED(m_status_value) != 0;
}
int Process::Status::terminated_signal_number() const {
  return WTERMSIG(m_status_value);
}
bool Process::Status::is_stopped() const {
  return WIFSTOPPED(m_status_value) != 0;
}
int Process::Status::stopped_signal_number() const {
  return WSTOPSIG(m_status_value);
}
bool Process::Status::is_continued() const {
  return WIFCONTINUED(m_status_value) != 0;
}

Process::Process(const Arguments &arguments, const Environment &environment) {
  API_RETURN_IF_ERROR();

  if (arguments.m_arguments.count() == 0) {
    API_RETURN_ASSIGN_ERROR("arguments are empty", EINVAL);
  }

  if (var::StringView(arguments.get_value(0)).is_empty()) {
    API_RETURN_ASSIGN_ERROR("no executable was found", EINVAL);
  }

#if defined __win32
  m_process_information = new PROCESS_INFORMATION;
  *m_process_information = PROCESS_INFORMATION{};
  STARTUPINFOA startup_info = {};

  var::PathString cwd;
  _getcwd(cwd.data(), cwd.capacity());
  const var::PathString pwd = environment.find("PWD");

  int stdout_fd = dup(_fileno(stdout));

  // change stdout and stderr to specify spawned process stdout, stderr
  _dup2(m_pipe.write_file().fileno(), _fileno(stdout));
  _dup2(_fileno(stdout), _fileno(stderr));
  m_pipe.write_file() = fs::File();

  if (pwd.is_empty() == false) {
    _chdir(pwd.cstring());
  }

  // change working directory?

  m_process = HANDLE(_spawnvpe(
    P_NOWAIT,
    arguments.get_value(0),
    arguments.m_arguments.data(),
    environment.m_arguments.data()));

  // restore stdout
  _dup2(stdout_fd, _fileno(stdout));
  _close(stdout_fd);

  if (pwd.is_empty() == false) {
    _chdir(cwd.cstring());
  }

  if (m_process == nullptr) {
    m_process = INVALID_HANDLE_VALUE;
    API_RETURN_ASSIGN_ERROR("failed to spawn", EINVAL);
  }

#else
  m_pid = API_SYSTEM_CALL("fork()", fork());
  if (m_pid == 0) {

    // this will run in the child process
    Arguments args(arguments);
    Environment env(environment);

    chdir(env.find("PWD"));

    dup2(m_pipe.write_file().fileno(), STDOUT_FILENO);
    // stdout will now write to the pipe -- this fileno isn't needed anymore
    // but doesn't necessarily have to be closed
    m_pipe.write_file() = fs::File();
    // replace the current process with the one specified
    ::execve(args.m_arguments.at(0), args.m_arguments.data(), environ);
    perror("failed to launch\n");
    exit(1);
  }
#endif
}

Process::~Process() {
  // if process is NOT detached -- wait for it to complete
  wait();
}

Process &Process::wait() {
  API_RETURN_VALUE_IF_ERROR(*this);

#if defined __win32
  if (m_process == INVALID_HANDLE_VALUE || m_process == nullptr) {
    return *this;
  }

  DWORD code = 0;
  WaitForSingleObject(m_process, INFINITE);
  CloseHandle(m_process);

  m_process = INVALID_HANDLE_VALUE;
  m_status = int(code);

  return *this;

#else
  if (m_pid < 0) {
    return *this;
  }

  int status = 0;

  auto result = API_SYSTEM_CALL("waitpid()", ::waitpid(m_pid, &status, 0));
  if (result == m_pid) {
    m_pid = -1;
    m_status = status;
  }
#endif

  return *this;
}

bool Process::is_running() {
  API_RETURN_VALUE_IF_ERROR(false);
#if defined __win32
  if (m_process == INVALID_HANDLE_VALUE || m_process == nullptr) {
    API_PRINTF_TRACE_LINE();
    return false;
  }

  DWORD code = STILL_ACTIVE;
  if (GetExitCodeProcess(m_process, &code) == 0) {
    printf("error is %d\n", GetLastError());
    API_PRINTF_TRACE_LINE();
    m_process = INVALID_HANDLE_VALUE;
    return false;
  }

  if (code == STILL_ACTIVE) {
    API_PRINTF_TRACE_LINE();

    return true;
  }
  API_PRINTF_TRACE_LINE();

  m_status = int(code);
  return false;
#else
  if (m_pid < 0) {
    return false;
  }

  api::ErrorScope error_scope;
  int status = 0;
  auto result
    = API_SYSTEM_CALL("waitpid()", ::waitpid(m_pid, &status, WNOHANG));
  if (result == m_pid) {
    m_status = status;
    m_pid = -1;
    return false;
  }
#endif

  return true;
}

#endif
