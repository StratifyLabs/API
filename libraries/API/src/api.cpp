// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#include <array>

#include "api/api.hpp"

#if defined __link
#include <cxxabi.h>
#include <pthread.h>
#include <signal.h>
#endif

#include <cstdio>
#include <cstring>

using namespace api;

namespace {
enum class DoLock { unlock, lock };

pthread_mutex_t error_pthread_mutex = {};
bool error_mutex_is_initialized = false;

void error_mutex_handler(DoLock do_lock) {
  if (!error_mutex_is_initialized) {
    error_mutex_is_initialized = true;
    pthread_mutex_init(&error_pthread_mutex, nullptr);
  }
  if (do_lock == DoLock::lock) {
    pthread_mutex_lock(&error_pthread_mutex);
  } else {
    pthread_mutex_unlock(&error_pthread_mutex);
  }
}

class PrivateExecutionContext {
public:
  PrivateExecutionContext() = default;

  friend class ExecutionContext;
  bool is_error() const { return value() < 0; }
  bool is_success() const { return value() >= 0; }
  API_NO_DISCARD inline int value() const { return errno; }

  API_NO_DISCARD size_t context_count() const {
    if (m_error_list) {
      return m_error_list->size() + 1;
    }
    return 1;
  }

  Error &get_error() {
    if (&(errno) == m_error.signature()) {
      return m_error;
    }
    error_mutex_handler(DoLock::lock);
    if (m_error_list == nullptr) {
      m_error_list = new std::vector<Error>();
      API_ASSERT(m_error_list != nullptr);
    }

    for (Error &error : *m_error_list) {
      if (error.signature() == &(errno)) {
        error_mutex_handler(DoLock::unlock);
        return error;
      }

      if (error.signature() == nullptr) {
        error.update_signature(&errno);
        error_mutex_handler(DoLock::unlock);
        return error;
      }
    }

    m_error_list->emplace_back(Error(&(errno)));
    auto &result = m_error_list->back();
    error_mutex_handler(DoLock::unlock);
    return result;
  }

  void free_context(void *signature) {
    // this is only called in a created thread and should never match the
    // default thread that starts when the process starts
    API_ASSERT(signature != m_error.signature());

    if ((m_error_list == nullptr) || (signature == nullptr)) {
      // context is only created if thread has an error
      return;
    }

    error_mutex_handler(DoLock::lock);
    for (Error &error : *m_error_list) {
      if (error.signature() == signature) {
        error.nullify();
        error_mutex_handler(DoLock::unlock);
        return;
      }
    }
    error_mutex_handler(DoLock::unlock);
  }

  void update_error_context(int result, int line, const char *message) {
    get_error().update_error_context(result, line, message);
  }

private:
  friend class api::ErrorScope;
  Error m_error = Error(&errno);
  std::vector<Error> *m_error_list = nullptr;
};

PrivateExecutionContext private_context;

} // namespace

const char *ApiInfo::version() {
  return MCU_STRINGIFY(__PROJECT_VERSION_MAJOR) "." MCU_STRINGIFY(
    __PROJECT_VERSION_MINOR) "." MCU_STRINGIFY(__PROJECT_VERSION_PATCH);
}

const char *ApiInfo::git_hash() { return CMSDK_GIT_HASH; }

void api::api_assert(bool value, const char *function, int line) {
  if (!value) {
    printf("assertion %s():%d\n", function, line);
#if defined __link && !defined __win32
    std::array<void *, 200> array = {};
    const auto size = backtrace(array.data(), array.size());
    backtrace_symbols_fd(array.data(), size, fileno(stderr));
#endif
#if defined __link
    fflush(stdout);
#endif
    ::abort();
  }
}

#define RESULT_ERROR_CODE_CASE(c)                                              \
  case ErrorCode::c:                                                           \
    return MCU_STRINGIFY(c)

void ExecutionContext::exit_fatal(const char *message) {
  printf("fatal error: %s\n", message);
  exit(1);
}
int ExecutionContext::handle_system_call_result(
  int line,
  const char *message,
  int value) {
  if (value >= 0) {
    errno = value;
  } else {
    private_context.update_error_context(value, line, message);
  }
  return value;
}

auto ExecutionContext::error() -> Error & {
  return private_context.get_error();
}

void ExecutionContext::free_context(void *signature) {
  return private_context.free_context(signature);
}

size_t ExecutionContext::context_count() {
  return private_context.context_count();
}

void ExecutionContext::reset_error() {
  errno = 0;
  error().reset();
}
bool ExecutionContext::is_error() { return private_context.is_error(); }
bool ExecutionContext::is_success() { return private_context.is_success(); }
int ExecutionContext::return_value() { return private_context.value(); }

ProgressCallback::ProgressCallback(Callback callback)
  : m_callback(std::move(callback)) {}

auto ProgressCallback::update(int value, int total) const -> IsAbort {
  if (m_callback) {
    return m_callback(value, total);
  }
  // do not abort the operation
  return IsAbort::no;
}

int ProgressCallback::update_function(
  const void *context,
  int value,
  int total) {
  const auto *progress_callback
    = reinterpret_cast<const ProgressCallback *>(context);
  const auto result = progress_callback->update(value, total);
  return result == IsAbort::yes;
}

const char *Demangler::demangle(const char *input) {
#if defined __link
  m_buffer.reset(static_cast<char *>(malloc(m_length)));
  m_last.reset(
    abi::__cxa_demangle(input, m_buffer.get(), &m_length, &m_status));
#endif
  return m_last.get();
}

#if defined __link
void signal_segmentation_fault(int) {
  static int count = 0;
  if (count == 0) {
    API_ASSERT(false);
    count++;
  }
}

#endif

void api::catch_segmentation_fault() {
#if defined __link
  signal(11, signal_segmentation_fault);
#endif
}

void ErrorScope::deleter(ErrorScope::Context *context) {
  private_context.get_error() = context->error;
  errno = context->error_number;
}

ErrorScope::ErrorScope() : m_error_resource({}, &deleter) {
  ExecutionContext::reset_error();
}

void Error::update_error_context(int result, int line, const char *message) {
  strncpy(m_message, message, Error::m_message_size);
  m_line_number = line;
  m_error_number = errno; // positive value set by system
  capture_backtrace();
  errno = result; // mark the context as an error state
}
