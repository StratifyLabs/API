// Copyright 2020-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#if defined __link

#include <cstdlib>
#include <unistd.h>

#include "printer/Printer.hpp"

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

namespace printer {
Printer &
operator<<(Printer &printer, const sys::Process::Arguments &arguments) {
  size_t count = 0;
  for (const auto &arg : arguments.arguments()) {
    if (arg != nullptr) {
      printer.key(var::NumberString(count, "[%04d]"), arg);
      ++count;
    }
  }
  return printer;
}

Printer &operator<<(Printer &printer, const sys::Process::Environment &env) {
  for (const auto &variable : env.variables()) {
    if (variable != nullptr) {
      const auto value_list = var::StringView(variable).split("=");
      if (value_list.count() > 1) {
        printer.key(value_list.at(0), value_list.at(1));
      }
    }
  }
  return printer;
}

} // namespace printer

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
    if (current_value != nullptr) {
      if (var::StringView(current_value).find(starts_with) == 0) {
        replace(i, format(name, value));
        return *this;
      }
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
    return {};
  }

  const auto path_list = var::StringView(path).split(";:");
  for (const auto &entry : path_list) {
    const auto entry_path = entry / executable;
    if (fs::FileSystem().exists(entry_path)) {
      return entry_path;
    }
  }

  return {};
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
  STARTUPINFOA startup_info{};

  var::PathString cwd;
  _getcwd(cwd.data(), cwd.capacity());
  const var::PathString pwd = environment.find("PWD");

  int stdout_fd = dup(_fileno(stdout));
  int stderr_fd = dup(_fileno(stderr));

  // change stdout and stderr to specify spawned process stdout, stderr
  _dup2(m_standard_output.pipe.write_file().fileno(), _fileno(stdout));
  _dup2(m_standard_error.pipe.write_file().fileno(), _fileno(stderr));

  m_standard_output.pipe.write_file() = fs::File();
  m_standard_error.pipe.write_file() = fs::File();

  if (pwd.is_empty() == false) {
    _chdir(pwd.cstring());
  }

  m_process = HANDLE(_spawnvpe(
    P_NOWAIT,
    arguments.path().cstring(),
    arguments.m_arguments.data(),
    environment.m_arguments.data()));

  // restore stdout
  _dup2(stdout_fd, _fileno(stdout));
  _close(stdout_fd);

  // restore stderr
  _dup2(stderr_fd, _fileno(stderr));
  _close(stderr_fd);

  if (pwd.is_empty() == false) {
    _chdir(cwd.cstring());
  }

  if (m_process == nullptr || m_process == INVALID_HANDLE_VALUE) {
    printf("Last error %d\n", GetLastError());
    m_process = INVALID_HANDLE_VALUE;
    API_RETURN_ASSIGN_ERROR("failed to spawn", errno);
  }

#else

  const auto pwd = environment.find("PWD");
  if (fs::FileSystem().directory_exists(pwd) == false) {
    API_RETURN_ASSIGN_ERROR(
      ("cannot change dir to `" | var::StringView(pwd)) | "`",
      errno);
  }

  m_pid = API_SYSTEM_CALL("fork()", fork());
  if (m_pid == 0) {

    // this will run in the child process
    Arguments args(arguments);

    if (chdir(environment.find("PWD")) < 0) {
      API_RETURN_ASSIGN_ERROR("failed to chdir to PWD", errno);
    }

    dup2(m_standard_output.pipe.write_file().fileno(), STDOUT_FILENO);
    // stdout will now write to the pipe -- this fileno isn't needed anymore
    // but doesn't necessarily have to be closed
    m_standard_output.pipe.write_file() = fs::File();

    dup2(m_standard_error.pipe.write_file().fileno(), STDERR_FILENO);
    // stderr will now write to the pipe -- this fileno isn't needed anymore
    // but doesn't necessarily have to be closed
    m_standard_error.pipe.write_file() = fs::File();

    // replace the current process with the one specified
    ::execve(args.path(), args.m_arguments.data(), environ);
    perror("failed to launch\n");
    exit(1);
  }
#endif

  if (m_pid > 0) {
    m_standard_output_redirect_options
      = {.redirect = &m_standard_output, .self = this};
    m_standard_error_redirect_options
      = {.redirect = &m_standard_error, .self = this};

    m_standard_output.start_thread(&m_standard_output_redirect_options);
    m_standard_error.start_thread(&m_standard_error_redirect_options);
  }
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
    m_standard_error.wait_stop();
    m_standard_output.wait_stop();
  }
#endif

  return *this;
}

bool Process::is_running() {
  API_RETURN_VALUE_IF_ERROR(false);
#if defined __win32
  if (m_process == INVALID_HANDLE_VALUE || m_process == nullptr) {
    return false;
  }

  DWORD code = STILL_ACTIVE;
  if (GetExitCodeProcess(m_process, &code) == 0) {
    m_process = INVALID_HANDLE_VALUE;
    return false;
  }

  if (code == STILL_ACTIVE) {
    return true;
  }

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

    m_standard_error.wait_stop();
    m_standard_output.wait_stop();
    return false;
  }
#endif

  return true;
}

var::String Process::get_standard_output() {
  thread::Mutex::Scope mutex_scope(m_standard_output.mutex);
  return var::String(var::StringView(
    reinterpret_cast<const char *>(
      m_standard_output.data_file.data().data_u8()),
    m_standard_output.data_file.data().size()));
}

var::String Process::get_standard_error() {
  thread::Mutex::Scope mutex_scope(m_standard_error.mutex);
  return var::String(var::StringView(
    reinterpret_cast<const char *>(m_standard_error.data_file.data().data_u8()),
    m_standard_error.data_file.data().size()));
}

var::String Process::read_standard_output() { return m_standard_output.read(); }

var::String Process::read_standard_error() { return m_standard_error.read(); }

void Process::update_redirect(const RedirectOptions *options) {
  // reads the pipe in a thread
  var::Array<char, 2048> buffer;
  auto &data_file = options->redirect->data_file;
  auto &pipe = options->redirect->pipe;
  auto &mutex = options->redirect->mutex;
  data_file.seek(0, fs::File::Whence::end);

  do {
    api::ErrorScope error_scope;
    const auto bytes_read = pipe.read_file().read(buffer).return_value();
    {
      thread::Mutex::Scope mutex_scope(mutex);
      if (bytes_read > 0) {
        // data file is write append, we want to preserve
        // the file location for reading the data file
        fs::File::LocationScope location_scope(data_file);
        data_file.write(var::View(buffer.data(), bytes_read));
      }
    }
  } while (1);
}

void *Process::update_redirect_thread_function(void *args) {
  const auto options = reinterpret_cast<const RedirectOptions *>(args);
  options->self->update_redirect(options);
  return nullptr;
}

void Process::Redirect::start_thread(Process::RedirectOptions *options) {
  thread = thread::Thread(
    thread::Thread::Attributes().set_joinable(),
    options,
    update_redirect_thread_function);
}

var::String Process::Redirect::read() {
  thread::Mutex::Scope ms(mutex);
  var::Array<char, 1024> buffer;
  var::String result;
  int bytes_read = 0;
  do {
    api::ErrorScope error_scope;
    bytes_read = data_file.read(var::View(buffer.data(), buffer.count() - 1))
                   .return_value();
    if (bytes_read > 0) {
      buffer.at(bytes_read) = 0;
      result += buffer.data();
    }
  } while (bytes_read > 0);
  return result;
}

void Process::Redirect::wait_stop() {
  thread::Mutex::Scope ms(mutex);
  thread.cancel().join();
}

#endif
