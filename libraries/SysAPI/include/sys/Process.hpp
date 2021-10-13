// Copyright 2020-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef PROCESSAPI_CHILD_HPP
#define PROCESSAPI_CHILD_HPP

#if defined __link

#include <sdk/types.h>
#include <type_traits>

#include "api/api.hpp"
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

    explicit Arguments(const var::StringView path) {
      m_arguments.push_back(nullptr);
      if (path != "") {
        push(path);
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

  protected:
    friend Process;
    var::Vector<char *> m_arguments;

    void replace(size_t offset, const var::StringView argument) {
      free(m_arguments.at(offset));
      m_arguments.at(offset) = create(argument);
    }

  private:
    void copy(const Arguments &arguments) {
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

  const Pipe &pipe() const { return m_pipe; }

  Process &wait();
  bool is_running();

  Status status() { return Status(m_status); }

private:
  Pipe m_pipe;
  pid_t m_pid = -1;
  int m_status = 0;

  void swap(Process &a) {
    std::swap(m_pid, a.m_pid);
    std::swap(m_status, a.m_status);
    m_pipe = std::move(a.m_pipe);
  }
};

} // namespace sys

#endif

#endif // PROCESSAPI_CHILD_HPP