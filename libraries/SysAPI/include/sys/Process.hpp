// Copyright 2020-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef PROCESSAPI_CHILD_HPP
#define PROCESSAPI_CHILD_HPP

#if defined __link

#if defined __win32
#include <winsock2.h>
#include <windows.h>
#include <direct.h>
#endif

#include <sdk/types.h>
#include <type_traits>

#include "api/api.hpp"
#include "var/StackString.hpp"
#include "fs/Path.hpp"
#include "fs/DataFile.hpp"

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
    var::Vector<char *> m_arguments;

    void replace(size_t offset, const var::StringView argument) {
      free(m_arguments.at(offset));
      m_arguments.at(offset) = create(argument);
    }

  private:
    API_RAC(Arguments,var::PathString,path);
    void copy(const Arguments &arguments) {
      m_path = arguments.path();
      m_arguments.push_back(nullptr);
      for (auto *value : arguments.m_arguments) {
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
  Process(const Process &) = delete;
  Process &operator=(const Process &) = delete;
  Process(Process &&a) { swap(a); }
  Process &operator=(Process &&a) {
    swap(a);
    return *this;
  }
  ~Process();

  Process &read_output();
  Process &wait();
  bool is_running();

  Status status() { return Status(m_status); }

  var::String get_standard_output();
  var::String get_standard_error();

  const fs::DataFile & standard_output() const {
    return m_standard_output;
  }

  const fs::DataFile & standard_error() const {
    return m_standard_error;
  }


private:
  pid_t m_pid = -1;
  int m_status = 0;

  fs::DataFile m_standard_output;
  fs::DataFile m_standard_error;


#if defined __win32
  PROCESS_INFORMATION *m_process_information;
  HANDLE m_process;
#else
  Pipe m_pipe_output;
  Pipe m_pipe_error;
#endif

  void swap(Process &a) {
    std::swap(m_pid, a.m_pid);
    std::swap(m_status, a.m_status);
#if defined __win32

#else
    std::swap(m_pipe_output, a.m_pipe_output);
    std::swap(m_pipe_error, a.m_pipe_error);
#endif
  }
};

} // namespace sys


namespace printer {
Printer & operator << (Printer & printer, const sys::Process::Arguments & arguments);
Printer & operator << (Printer & printer, const sys::Process::Environment & env);
}

#endif

#endif // PROCESSAPI_CHILD_HPP
