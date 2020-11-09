/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
#include "api/api.hpp"
// #include "var/String.hpp"

#if defined __link
#include <cxxabi.h>
#endif

#include <pthread.h>

#include <cstdio>
#include <cstring>

#define ERROR_CODE_CASE(c)                                                     \
  case c:                                                                      \
    return MCU_STRINGIFY(c)

using namespace api;

const char *ApiInfo::version() {
  return MCU_STRINGIFY(__PROJECT_VERSION_MAJOR) "." MCU_STRINGIFY(
    __PROJECT_VERSION_MINOR) "." MCU_STRINGIFY(__PROJECT_VERSION_PATCH);
}

const char *ApiInfo::git_hash() { return SOS_GIT_HASH; }

void api::api_assert(bool value, const char *function, int line) {
  if (!value) {
    printf("assertion %s():%d\n", function, line);
#if defined __link && !defined __win32
    void *array[200];
    size_t size;
    size = backtrace(array, 200);
    backtrace_symbols_fd(array, size, stderr->_file);
#endif
    ::abort();
  }
}

PrivateExecutionContext ExecutionContext::m_private_context;

Error &PrivateExecutionContext::get_error() {
  if (&(errno) == m_error.m_signature) {
    return m_error;
  }

  if (m_error_list == nullptr) {
    m_error_list = new std::vector<Error>();
    API_ASSERT(m_error_list != nullptr);
  }

  for (Error &error : *m_error_list) {
    if (error.m_signature == &(errno)) {
      return error;
    }

    if (error.m_signature == nullptr) {
      error.m_signature = &(errno);
      return error;
    }
  }

  m_error_list->push_back(Error(&(errno)));
  return m_error_list->back();
}

void PrivateExecutionContext::free_context() {
  API_ASSERT(&(errno) != m_error.m_signature);
  if (m_error_list == nullptr) {
    // context is only created if thread has an error
    return;
  }

  for (Error &error : *m_error_list) {
    if (error.m_signature == &(errno)) {
      error.m_signature = nullptr;
      return;
    }
  }
}

void PrivateExecutionContext::update_error_context(
  int result,
  int line,
  const char *message) {
  Error &error = get_error();
  strncpy(error.m_message, message, Error::m_message_size);
  error.m_line_number = line;
  error.m_error_number = errno; // positive value set by system
  error.capture_backtrace();
  errno = result; // mark the context as an error state
}

#define RESULT_ERROR_CODE_CASE(c)                                              \
  case ErrorCode::c:                                                           \
    return MCU_STRINGIFY(c)

void ExecutionContext::exit_fatal(const char *message) {
  printf("fatal error: %s\n", message);
  exit(1);
}

ProgressCallback::ProgressCallback() {}

bool ProgressCallback::update(int value, int total) const {
  if (m_callback) {
    return m_callback(context(), value, total);
  }
  // do not abort the operation
  return false;
}

int ProgressCallback::update_function(
  const void *context,
  int value,
  int total) {
  if (context == nullptr) {
    return 0;
  }
  return ((ProgressCallback *)context)->update(value, total);
}

Demangler::Demangler() { m_buffer = static_cast<char *>(malloc(m_length)); }
Demangler::~Demangler() {
  printf("Free buffer %d\n", 2048);
  if (m_buffer && length() == 2048) {
    free(m_buffer);
  }
  if (m_last) {
    free(m_last);
  }
}

const char *Demangler::demangle(const char *input) {
  if (m_last != nullptr) {
    free(m_last);
  }

#if defined __link
  m_last = abi::__cxa_demangle(input, m_buffer, &m_length, &m_status);
#endif
  return m_last;
}
