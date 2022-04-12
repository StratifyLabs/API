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
    Arguments(const Arguments &arguments) { copy(arguments); }

    Arguments &operator=(const Arguments &arguments) {
      copy(arguments);
      return *this;
    }

    Arguments(Arguments &&) = default;
    Arguments &operator=(Arguments &&) = default;

    explicit Arguments(const var::StringView path) : m_path(path) {
      m_arguments.push_back(nullptr);
      if (path != "") {
#if defined __win32
        push(fs::Path::name(path));
#else
        push(path);
#endif
      }
    }

    ~Arguments() {
      for (auto *value : m_arguments) {
        if (value) {
          free(value);
        }
      }
    }

    Arguments &push(const var::StringView argument) {
      auto *value = create(argument);
      API_ASSERT(m_arguments.count());
      m_arguments.back() = value;
      m_arguments.push_back(nullptr);
      return *this;
    }

    char *get_value(size_t offset) {
      if (offset < m_arguments.count()) {
        return m_arguments.at(offset);
      }
      return nullptr;
    }

    const char *get_value(size_t offset) const {
      if (offset < m_arguments.count()) {
        return m_arguments.at(offset);
      }
      return nullptr;
    }

    var::Vector<char *> &arguments() { return m_arguments; }

    const var::Vector<char *> &arguments() const { return m_arguments; }

  protected:
    friend Process;

    void replace(size_t offset, const var::StringView argument) {
      free(m_arguments.at(offset));
      m_arguments.at(offset) = create(argument);
    }

  private:
    var::Vector<char *> m_arguments;
    API_RAC(Arguments, var::PathString, path);
    void copy(const Arguments &arguments) {
      m_path = arguments.path();
      m_arguments.push_back(nullptr);
      for (const auto *value : arguments.m_arguments) {
        value &&push(value).is_success();
      }
    }

    char *create(const var::StringView argument) {
      const auto length = argument.length();
      char *value = reinterpret_cast<char *>(malloc(length + 1));
      API_ASSERT(value != nullptr);
      var::View(value, length).copy(var::View(argument.data(), length));
      value[length] = 0;
      return value;
    }
  };

  class Environment : private Arguments {
  public:
    explicit Environment(char **env = nullptr);

    Environment &set(const var::StringView name, const var::StringView value);
    Environment &set_working_directory(const var::StringView path);

    var::Vector<char *> &variables() { return arguments(); }

    const var::Vector<char *> &variables() const { return arguments(); }

    const char *find(const var::StringView variable) const;

  private:
    friend Process;
  };

  static var::PathString which(const var::StringView executable);

  enum class IsDetached { no, yes };

  Process() = default;
  Process(const Arguments &arguments, const Environment &environment);

  Process &wait();
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
    static constexpr auto stop_sequence
      = ";askdryqwepibafgo;aisu;drapoasdf1023498yafgbcnvn,zxn.lk;d[pfsda]][asd["
        "p]{}}{AKPGJFojd;skfjgns[]{}asdkf77983124ba;"
        "iasdkjbflaskjdhflasidugajsbga;sokfguaspoiduyfgaskldjfbas;"
        "iasdkjbflaskjdhflasidugajsbga;sokfguaspoiduyfgaskldjfbas;"
        "iasdkjbflaskjdhflasidugajsbga;sokfguaspoiduyfgaskldjfbas;"
        "dfupuiy2ipu3y4aslkdjnflajg";
    thread::Thread thread;
    thread::Mutex mutex;
    Pipe pipe;
    fs::DataFile data_file;
    volatile bool is_stop_requested = false;
    Process *self;

    void start_thread();
    void wait_stop();
    var::String read();

#if defined __win32
    HANDLE thread_handle;
#endif
  };

  static void pid_deleter(pid_t *pid);

  using PidResource = api::SystemResource<pid_t, decltype(&pid_deleter)>;
  using RedirectPointer = std::unique_ptr<Redirect>;

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

  static void *update_redirect_thread_function(void *args);
  void update_redirect(Redirect *options);
};

} // namespace sys

namespace printer {
Printer &operator<<(Printer &printer, const sys::Process::Arguments &arguments);
Printer &operator<<(Printer &printer, const sys::Process::Environment &env);
} // namespace printer

#endif

#endif // PROCESSAPI_CHILD_HPP
