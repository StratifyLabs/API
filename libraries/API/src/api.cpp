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

#define ERROR_CODE_CASE(c)                                                     \
  case c:                                                                      \
    return MCU_STRINGIFY(c)

using namespace api;

const char *ApiInfo::version() {
  return MCU_STRINGIFY(__PROJECT_VERSION_MAJOR) "." MCU_STRINGIFY(
    __PROJECT_VERSION_MINOR) "." MCU_STRINGIFY(__PROJECT_VERSION_PATCH);
}

const char *ApiInfo::git_hash() { return CMSDK_GIT_HASH; }

void api::api_assert(bool value, const char *function, int line) {
  if (!value) {
    printf("assertion %s():%d\n", function, line);
#if defined __link && !defined __win32
    std::array<void*,200> array = {};
    size_t size;
    size = backtrace(array.data(), array.size());
    backtrace_symbols_fd(array.data(), size, fileno(stderr));
#endif
#if defined __link
    fflush(stdout);
#endif
    ::abort();
  }
}

PrivateExecutionContext ExecutionContext::m_private_context;

static void error_mutex_handler(int do_lock){
  static pthread_mutex_t mutex = {};
  static bool is_initialized = false;
  if( !is_initialized ){
    is_initialized = true;
    pthread_mutex_init(&mutex, nullptr);
  }
  if( do_lock > 0 ){
    pthread_mutex_lock(&mutex);
  } else if ( do_lock < 0 ){
    pthread_mutex_unlock(&mutex);
  }
}

Error &PrivateExecutionContext::get_error() {
  if (&(errno) == m_error.m_signature) {
    return m_error;
  }
  error_mutex_handler(1);
  if (m_error_list == nullptr) {
    m_error_list = new std::vector<Error>();
    API_ASSERT(m_error_list != nullptr);
  }

  for (Error &error : *m_error_list) {
    if (error.m_signature == &(errno)) {
      error_mutex_handler(-1);
      return error;
    }

    if (error.m_signature == nullptr) {
      error.m_signature = &(errno);
      error_mutex_handler(-1);
      return error;
    }
  }

  m_error_list->emplace_back(Error(&(errno)));
  auto & result =  m_error_list->back();
  error_mutex_handler(-1);
  return result;
}

void PrivateExecutionContext::free_context() {
  API_ASSERT(&(errno) != m_error.m_signature);
  if (m_error_list == nullptr) {
    // context is only created if thread has an error
    return;
  }

  error_mutex_handler(1);
  for (Error &error : *m_error_list) {
    if (error.m_signature == &(errno)) {
      error.m_signature = nullptr;
      error_mutex_handler(-1);
      return;
    }
  }
  error_mutex_handler(-1);
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

ProgressCallback::ProgressCallback() = default;

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
  return reinterpret_cast<const ProgressCallback*>(context)->update(value, total);
}


const char *Demangler::demangle(const char *input) {
#if defined __link
  m_buffer.reset(static_cast<char*>(malloc(m_length)));
  m_last.reset(abi::__cxa_demangle(input, m_buffer.get(), &m_length, &m_status));
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
