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
  auto count = size_t{};
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
using namespace var;
using namespace thread;

namespace {
constexpr auto stop_sequence = StringView{
  ";askdryqwepibafgo;aisu;drapoasdf1023498yafgbcnvn,zxn.lk;d[pfsda]][asd["
  "p]{}}{AKPGJFojd;skfjgns[]{}asdkf77983124ba;"
  "iasdkjbflaskjdhflasidugajsbga;sokfguaspoiduyfgaskldjfbas;"
  "iasdkjbflaskjdhflasidugajsbga;sokfguaspoiduyfgaskldjfbas;"
  "iasdkjbflaskjdhflasidugajsbga;sokfguaspoiduyfgaskldjfbas;"
  "dfupuiy2ipu3y4aslkdjnflajg"};

auto create_cstring_list_from_strings(StringList &list) {
  auto result = Vector<char *>().reserve(list.count());
  for (const auto &item : list) {
    result.push_back(const_cast<char*>(item.cstring()));
  }
  return result;
}

} // namespace

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

  auto format = [](const StringView name, const StringView value) {
    return name | "=" | value;
  };

  // check to see if the entry exists
  const auto starts_with = name | "=";
  for (auto i = size_t{}; i < m_arguments.count(); ++i) {
    const auto current_value = m_arguments.at(i);
    if (current_value != nullptr) {
      if (StringView{current_value}.find(starts_with) == 0) {
        replace(i, format(name, value));
        return *this;
      }
    }
  }

  push(format(name, value));
  return *this;
}

Process::Environment &
Process::Environment::set_working_directory(const StringView path) {
  return set("PWD", path);
}

var::String Process::Environment::find(const StringView variable) const {
  const auto check = NameString(variable).append("=");
  for (const auto &value : variables()) {
    if (value.string_view().starts_with(check)) {
      return String{value.string_view().pop_front(check.length())};
    }
  }
  return {};
}

PathString Process::which(const StringView executable) {
  const char *pwd = getenv("PWD");
  if (pwd) {
    if (const auto path = StringView(pwd) / executable;
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

  const auto path_list = StringView(path).split(";:");
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

Process::Process(const Arguments &arguments, const Environment &environment)
  : m_pid(-1, &pid_deleter), m_standard_output(new Redirect()),
    m_standard_error(new Redirect()) {
  API_RETURN_IF_ERROR();

  if (arguments.m_arguments.count() == 0) {
    API_RETURN_ASSIGN_ERROR("arguments are empty", EINVAL);
  }

  if (arguments.arguments().front().string_view().is_empty()) {
    API_RETURN_ASSIGN_ERROR("no executable was found", EINVAL);
  }

  bool is_process_launched = false;

#if defined __win32
  m_process_information = new PROCESS_INFORMATION;
  *m_process_information = PROCESS_INFORMATION{};

  PathString cwd;
  _getcwd(cwd.data(), cwd.capacity());
  const auto pwd = environment.find("PWD");

  if (pwd.is_empty() == false) {
    _chdir(pwd.cstring());
  }

  struct PipeHandles {
    HANDLE read;
    HANDLE write;
  };

  auto update_pipe = [](Pipe &pipe) {
    PipeHandles handles;

    SECURITY_ATTRIBUTES sa_attributes{
      .nLength = sizeof(SECURITY_ATTRIBUTES),
      .bInheritHandle = true};

    const auto create_result
      = CreatePipe(&handles.read, &handles.write, &sa_attributes, 0);
    API_ASSERT(create_result);

    const auto set_result
      = SetHandleInformation(handles.read, HANDLE_FLAG_INHERIT, 0);
    API_ASSERT(set_result);

    pipe.write_file() = fs::File();
    pipe.read_file() = fs::File();

    pipe.write_file().set_fileno(_open_osfhandle(intptr_t(handles.write), 0));
    pipe.read_file().set_fileno(_open_osfhandle(intptr_t(handles.read), 0));
    return handles;
  };

  const auto output_pipe = update_pipe(m_standard_output->pipe);
  const auto error_pipe = update_pipe(m_standard_error->pipe);

  STARTUPINFO startup_info{
    .cb = sizeof(STARTUPINFO),
    .dwFlags = STARTF_USESTDHANDLES,
    .hStdOutput = output_pipe.write,
    .hStdError = error_pipe.write};

  PROCESS_INFORMATION process_info{};
  auto path = String{};
  for (const auto &arg : arguments.arguments()) {
    path += arg + " ";
  }
  path.pop_back();

  fflush(stdout);
  const auto create_result = CreateProcessA(
    NULL,             // No module name (use command line)
    path.data(),      // Command line
    NULL,             // Process handle not inheritable
    NULL,             // Thread handle not inheritable
    TRUE,             // Set handle inheritance to FALSE
    CREATE_NO_WINDOW, // creation flags
    NULL,             // Use parent's environment block
    NULL,             // Use parent's starting directory
    &startup_info,    // Pointer to STARTUPINFO structure
    &process_info);   // Pointer to PROCESS_INFORMATION structure

  if (create_result) {
    m_process = process_info.hProcess;
    m_thread = process_info.hThread;
  }

  if (pwd.is_empty() == false) {
    _chdir(cwd.cstring());
  }

  is_process_launched = true;
#else

  const auto pwd = environment.find("PWD");
  if (fs::FileSystem().directory_exists(pwd) == false) {
    API_RETURN_ASSIGN_ERROR(
      ("cannot change dir to `" | StringView(pwd)) | "`",
      errno);
  }

  const auto fork_result = API_SYSTEM_CALL("fork()", fork());
  if (fork_result == 0) {

    // this will run in the child process
    Arguments args(arguments);

    if (chdir(environment.find("PWD").cstring()) < 0) {
      API_RETURN_ASSIGN_ERROR("failed to chdir to PWD", errno);
    }

    dup2(m_standard_output->pipe.write_file().fileno(), STDOUT_FILENO);
    // stdout will now write to the pipe -- this fileno isn't needed anymore
    // but doesn't necessarily have to be closed
    m_standard_output->pipe.write_file() = fs::File();

    dup2(m_standard_error->pipe.write_file().fileno(), STDERR_FILENO);
    // stderr will now write to the pipe -- this fileno isn't needed anymore
    // but doesn't necessarily have to be closed
    m_standard_error->pipe.write_file() = fs::File();

    // delete m_standard_output;
    // delete m_standard_error;

    // replace the current process with the one specified
    ::execve(
      args.arguments().front().cstring(),
      create_cstring_list_from_strings(args.m_arguments).data(),
      environ);
    perror("failed to launch\n");
    exit(1);
  } else {
    m_pid = PidResource(fork_result, &pid_deleter);
  }

  is_process_launched = (m_pid.value() > 0);
#endif

  if (is_process_launched) {
    m_standard_output->self = this;
    m_standard_error->self = this;
    m_standard_output->start_thread();
    m_standard_error->start_thread();
  } else {
    m_standard_output = {};
    m_standard_error = {};
  }
}

void Process::pid_deleter(pid_t *pid) {
  // caller MUST wait for pid -- can't let it be destroyed when not equal to -1
  API_ASSERT((*pid == -1));
}

Process &Process::wait() & {
  API_RETURN_VALUE_IF_ERROR(*this);

#if defined __win32
  if (m_process == INVALID_HANDLE_VALUE || m_process == nullptr) {
    return *this;
  }

  DWORD code = 0;
  WaitForSingleObject(m_process, INFINITE);
  CloseHandle(m_process);
  CloseHandle(m_thread);

  m_process = INVALID_HANDLE_VALUE;
  m_status = int(code);
  m_standard_error->wait_stop();
  m_standard_output->wait_stop();

  return *this;
#else
  if (m_pid.value() < 0) {
    return *this;
  }

  int status = 0;

  auto result
    = API_SYSTEM_CALL("waitpid()", ::waitpid(m_pid.value(), &status, 0));
  if (result == m_pid.value()) {
    m_pid.set_value(-1);
    m_status = status;
    m_standard_error->wait_stop();
    m_standard_output->wait_stop();
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

  CloseHandle(m_process);
  CloseHandle(m_thread);
  m_pid.set_value(-1);
  m_status = int(code);
  m_standard_error->wait_stop();
  m_standard_output->wait_stop();
  return false;
#else
  if (m_pid.value() < 0) {
    return false;
  }

  api::ErrorScope error_scope;
  int status = 0;
  auto result
    = API_SYSTEM_CALL("waitpid()", ::waitpid(m_pid.value(), &status, WNOHANG));
  if (result == m_pid.value()) {
    m_status = status;
    m_pid.set_value(-1);
    m_standard_error->wait_stop();
    m_standard_output->wait_stop();
    return false;
  }
#endif

  return true;
}

String Process::get_standard_output() {
  thread::Mutex::Scope mutex_scope(m_standard_output->mutex);
  return String(StringView(
    reinterpret_cast<const char *>(
      m_standard_output->data_file.data().data_u8()),
    m_standard_output->data_file.data().size()));
}

String Process::get_standard_error() {
  thread::Mutex::Scope mutex_scope(m_standard_error->mutex);
  return String(StringView(
    reinterpret_cast<const char *>(
      m_standard_error->data_file.data().data_u8()),
    m_standard_error->data_file.data().size()));
}

String Process::read_standard_output() {
  API_ASSERT(m_standard_output != nullptr);
  return m_standard_output->read();
}

String Process::read_standard_error() {
  API_ASSERT(m_standard_error != nullptr);
  return m_standard_error->read();
}

void Process::update_redirect(Redirect *redirect) {
  // reads the pipe in a thread
  API_ASSERT(redirect != nullptr);

#if defined __win32
  redirect->thread_handle = GetCurrentThread();
#endif
  Array<char, 2048> buffer;
  auto &data_file = redirect->data_file;
  auto &pipe = redirect->pipe;
  auto &mutex = redirect->mutex;
  thread::Mutex::Scope(mutex, [&]() {
    data_file.seek(0, fs::File::Whence::end);
  });
  for (bool is_stop_requested = false; !is_stop_requested;) {
    {
      api::ErrorScope error_scope;
      const auto bytes_read = pipe.read_file().read(buffer).return_value();
      if (bytes_read > 0) {
        auto incoming_string = StringView{buffer.data(), size_t(bytes_read)};
        const auto stop_position = incoming_string.find(stop_sequence);
        if (stop_position != StringView::npos) {
          incoming_string.truncate(stop_position);
        }
        thread::Mutex::Scope(mutex, [&]() {
          // data file is write append, we want to preserve
          // the file location for reading the data file
          auto location_scope = fs::File::LocationScope(data_file);
          data_file.write(incoming_string);
        });
      }
    }

    thread::Mutex::Scope(mutex, [&]() {
      is_stop_requested = redirect->is_stop_requested;
    });
  }
}

void Process::Redirect::start_thread() {
  thread = thread::Thread(
    thread::Thread::Attributes().set_stack_size(512 * 1024).set_joinable(),
    [this]() -> void * {
      self->update_redirect(this);
      return nullptr;
    });
}

String Process::Redirect::read() {
  auto mutex_scope = thread::Mutex::Scope(mutex);
  Array<char, 1024> buffer;
  String result;
  for (int bytes_read = 1; bytes_read > 0;) {
    api::ErrorScope error_scope;
    bytes_read
      = data_file.read(View(buffer.data(), buffer.count() - 1)).return_value();
    if (bytes_read > 0) {
      buffer.at(bytes_read) = 0;
      result += buffer.data();
    }
  }
  return result;
}

void Process::Redirect::wait_stop() {
  Mutex::Scope(mutex, [&]() { is_stop_requested = true; });
  pipe.write_file().write(stop_sequence);
  if (thread.is_joinable()) {
    thread.join();
  }
}

#endif
