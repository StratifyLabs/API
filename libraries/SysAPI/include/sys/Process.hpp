// Copyright 2020-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef PROCESSAPI_CHILD_HPP
#define PROCESSAPI_CHILD_HPP

#if defined __link

#if defined __win32
#include <winsock2.h>
// don't let clang put windows.h or direct.h before winsock2
#include <direct.h>
#include <windows.h>
#endif

#include <sdk/types.h>
#include <type_traits>

#include "api/api.hpp"
#include "fs/DataFile.hpp"
#include "fs/Path.hpp"
#include "thread/Cond.hpp"
#include "thread/Mutex.hpp"
#include "thread/Thread.hpp"
#include "var/StackString.hpp"

#include "Pipe.hpp"

namespace sys {

class Process : public api::ExecutionContext {
public:
  class Status {
  public:
    u8 exit_status() const;
    bool is_exited() const;
    bool is_terminated() const;
    int terminated_signal_number() const;
    bool is_stopped() const;
    int stopped_signal_number() const;
    bool is_continued() const;

  private:
    friend Process;
    explicit Status(int status_value) : m_status_value(status_value) {}
    int m_status_value;
  };

  class Arguments : public api::ExecutionContext {
  public:
    Arguments() = default;
    explicit Arguments(const var::StringView path) {
      if (path != "") {
#if defined __win32
        push(fs::Path::name(path));
#else
        push(path);
#endif
      }
    }

    Arguments &push(const var::StringView argument) & {
      m_arguments.push_back(var::String{argument});
      return *this;
    }
    Arguments &&push(const var::StringView argument) && {
      return std::move(push(argument));
    }

    var::StringList &arguments() { return m_arguments; }
    const var::StringList &arguments() const { return m_arguments; }

  protected:
    friend Process;

    void replace(size_t offset, const var::StringView argument) {
      if (offset < m_arguments.count()) {
        m_arguments.at(offset) = var::String{argument};
      }
    }

  private:
    var::StringList m_arguments;
  };

  class Environment : private Arguments {
  public:
    explicit Environment(char **env = nullptr);
    Environment &set(const var::StringView name, const var::StringView value);
    Environment &set_working_directory(const var::StringView path);
    var::StringList &variables() { return arguments(); }
    const var::StringList &variables() const { return arguments(); }
    var::String find(const var::StringView variable) const;

  private:
    friend Process;
  };

  static var::PathString which(const var::StringView executable);

  enum class IsDetached { no, yes };

  Process() = default;
  Process(const Arguments &arguments, const Environment &environment);

  Process &wait() &;
  Process && wait() && { return std::move(wait()); }
  bool is_running();
  pid_t pid() const { return m_pid.value(); }

  Status status() { return Status(m_status); }

  var::String get_standard_output();
  var::String get_standard_error();

  var::String read_standard_output();
  var::String read_standard_error();

  const fs::DataFile &standard_output() const {
    API_ASSERT(m_standard_output != nullptr);
    return m_standard_output->data_file;
  }

  const fs::DataFile &standard_error() const {
    API_ASSERT(m_standard_error != nullptr);
    return m_standard_error->data_file;
  }

  thread::Mutex &standard_output_mutex() {
    API_ASSERT(m_standard_output != nullptr);
    return m_standard_output->mutex;
  }

  thread::Mutex &standard_error_mutex() {
    API_ASSERT(m_standard_error != nullptr);
    return m_standard_error->mutex;
  }

private:
  struct Redirect {
    thread::Thread thread;
    thread::Mutex mutex;
    Pipe pipe;
    fs::DataFile data_file;
    bool is_stop_requested = false;
    Process *self{};

    void start_thread();
    void wait_stop();
    var::String read();

#if defined __win32
    HANDLE thread_handle;
#endif
  };

  static void pid_deleter(pid_t *pid);

  using PidResource = api::SystemResource<pid_t, decltype(&pid_deleter)>;
  using RedirectPointer = api::UniquePointer<Redirect>;

  int m_status = 0;

#if defined __win32
  PROCESS_INFORMATION *m_process_information;
  HANDLE m_process = INVALID_HANDLE_VALUE;
  HANDLE m_thread = INVALID_HANDLE_VALUE;
  // using HandleResource = api::SystemResource<HANDLE, decltype(&wait_pid)>;
#endif

  PidResource m_pid;
  RedirectPointer m_standard_output;
  RedirectPointer m_standard_error;

  void update_redirect(Redirect *options);
};

} // namespace sys

namespace printer {
Printer &operator<<(Printer &printer, const sys::Process::Arguments &arguments);
Printer &operator<<(Printer &printer, const sys::Process::Environment &env);
} // namespace printer

#endif

#endif // PROCESSAPI_CHILD_HPP
