// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef API_API_HPP_
#define API_API_HPP_

#include <cstring>
#include <errno.h>
#include <limits.h>

#include <vector>

#include "macros.hpp"

#if defined __link
#if !defined __win32
#include <execinfo.h>
#endif
#else
extern "C" int sos_trace_stack(u32 count);
#endif

namespace api {

class ApiInfo {
public:
  static const char *version();
  static const char *git_hash();

  static constexpr u32 malloc_start_chunk_size() {
    return API_MINIMUM_CHUNK_SIZE;
  }

  static constexpr u32 malloc_chunk_size() { return API_MALLOC_CHUNK_SIZE; }
};

#if defined __link
template <typename A, const A *initial_value> class Api {
#else
extern "C" const void *kernel_request_api(u32 request);
template <typename A, u32 request> class Api {
#endif
public:
  Api() { initialize(); }

  bool is_valid() {
    initialize();
    return m_api != nullptr;
  }

  Api &operator=(const A *value) {
    m_api = value;
    return *this;
  }

  const A *operator->() const { return m_api; }
  const A *api() const { return m_api; }

private:
  void initialize() {
    if (m_api == nullptr) {
#if defined __link
      m_api = initial_value;
#else
      m_api = (const A *)kernel_request_api(request);
#endif
    }
  }
  const A *m_api = nullptr;
};

class Error {
public:
  class Backtrace {
  public:
    Backtrace(const Error &context) {
#if defined __link
#if !defined __win32
      m_entry_count = context.m_backtrace_count;
      m_symbol_pointer =
          backtrace_symbols(context.m_backtrace_buffer, m_entry_count);
#endif
#else

#endif
    }

    const char *at(size_t offset) {
      if (offset < m_entry_count) {
        return m_symbol_pointer[offset];
      }
      return nullptr;
    }

    ~Backtrace() {
      if (m_symbol_pointer != nullptr) {
        ::free(m_symbol_pointer);
      }
    }

  private:
    char **m_symbol_pointer;
    API_RAF(Backtrace, size_t, entry_count, 0);
  };

  const char *message() const { return m_message; }
  int error_number() const { return m_error_number; }
  int line_number() const { return m_line_number; }

  void *signature() const { return m_signature; }

  constexpr static size_t backtrace_buffer_size() {
    return m_backtrace_buffer_size;
  }

  bool is_error() const { return line_number() > 0; }
  void reset() { m_line_number = 0; }
  bool is_guarded() const { return m_is_guarded; }
  void set_guarded(bool value = true) { m_is_guarded = value; }

private:
  Error(void *signature) : m_signature(signature) {}
  friend class PrivateExecutionContext;
  friend class BacktraceSymbols;
  static constexpr size_t m_message_size = PATH_MAX;
  static constexpr size_t m_backtrace_buffer_size =
#if defined __link
      512
#else
      32
#endif
      ;

  void *m_signature;
  int m_error_number = 0;
  int m_line_number = 0;
  char m_message[m_message_size + 1];
  void *m_backtrace_buffer[m_backtrace_buffer_size];
  size_t m_backtrace_count = 0;
  bool m_is_guarded = false;

  inline void capture_backtrace() {
    if (!is_guarded()) {
#if defined __link
#if !defined __win32
      m_backtrace_count =
          backtrace(m_backtrace_buffer, m_backtrace_buffer_size);
#endif
#else
      sos_trace_stack(32);
#endif
    }
  }
};

class PrivateExecutionContext {
protected:
  friend class ExecutionContext;
  inline bool is_error() const { return value() < 0; }
  inline bool is_success() const { return value() >= 0; }
  inline int value() const { return errno; }

  size_t context_count() const {
    if (m_error_list) {
      return m_error_list->size() + 1;
    }
    return 1;
  }

  Error &get_error();

  void free_context();
  void update_error_context(int result, int line, const char *message);

private:
  friend class ErrorGuard;
  PrivateExecutionContext() : m_error(&(errno)) {}
  Error m_error;
  std::vector<Error> *m_error_list = nullptr;
};

class ExecutionContext {
public:
  static int handle_system_call_result(int line, const char *message,
                                       int value) {
    if (value >= 0) {
      errno = value;
    } else {
      m_private_context.update_error_context(value, line, message);
    }
    return value;
  }

  template <typename T>
  static T *handle_system_call_null_result(int line, const char *message,
                                           T *value) {
    if (value == nullptr) {
      m_private_context.update_error_context(-1, line, message);
    }
    return value;
  }

  static Error &error() { return m_private_context.get_error(); }
  static void free_context() { return m_private_context.free_context(); }
  static void exit_fatal(const char *message);

  static inline size_t context_count() {
    return m_private_context.context_count();
  }
  static inline void reset_error() {
    errno = 0;
    error().reset();
  }
  static inline bool is_error() { return m_private_context.is_error(); }
  static inline bool is_success() { return m_private_context.is_success(); }
  static inline int return_value() { return m_private_context.value(); }

private:
  friend class ErrorGuard;
  static PrivateExecutionContext m_private_context;
};

class ErrorGuard {
public:
  ErrorGuard()
      : m_error(ExecutionContext::m_private_context.m_error),
        m_error_number(errno) {
    m_is_guarded = ExecutionContext::m_private_context.m_error.is_guarded();
    ExecutionContext::reset_error();
  }
  ~ErrorGuard() {
    ExecutionContext::m_private_context.m_error = m_error;
    ExecutionContext::m_private_context.m_error.set_guarded(m_is_guarded);
    errno = m_error_number;
  }

private:
  Error m_error;
  int m_error_number;
  bool m_is_guarded;
};

using ErrorContext = ErrorGuard;
using ErrorScope = ErrorGuard;

class ThreadExecutionContext {
public:
  ~ThreadExecutionContext() { ExecutionContext::free_context(); }
};

class Demangler {
public:
  Demangler();
  ~Demangler();

  Demangler(const Demangler &) = delete;
  Demangler &operator=(const Demangler &) = delete;

  Demangler(Demangler &&) = default;
  Demangler &operator=(Demangler &&) = default;

  const char *demangle(const char *input);

private:
  API_RAF(Demangler, int, status, 0);
  API_RAF(Demangler, size_t, length, 2048);
  char *m_buffer = nullptr;
  char *m_last = nullptr;
};

#define API_THREAD_EXECUTION_CONTEXT()                                         \
  api::ThreadExecutionContext api_thread_execution_context;

#define API_ASSERT(a) api::api_assert(a, __PRETTY_FUNCTION__, __LINE__);
void api_assert(bool value, const char *function, int line);

#define API_RETURN_VALUE_IF_ERROR(return_value)                                \
  if (api::ExecutionContext::is_error()) {                                     \
    return return_value;                                                       \
  }

#define API_RETURN_IF_ERROR()                                                  \
  if (api::ExecutionContext::is_error()) {                                     \
    return;                                                                    \
  }

#define API_SYSTEM_CALL(message_value, return_value)                           \
  api::ExecutionContext::handle_system_call_result(__LINE__, message_value,    \
                                                   return_value)

#define API_SYSTEM_CALL_NULL(message_value, return_value)                      \
  api::ExecutionContext::handle_system_call_null_result(                       \
      __LINE__, message_value, return_value)

#define API_RESET_ERROR() api::ExecutionContext::reset_error()

#define API_RETURN_VALUE_ASSIGN_ERROR(return_value, message_value,             \
                                      error_number_value)                      \
  do {                                                                         \
    errno = error_number_value;                                                \
    api::ExecutionContext::handle_system_call_result(__LINE__, message_value,  \
                                                     -1);                      \
    return return_value;                                                       \
  } while (0)

#define API_RETURN_ASSIGN_ERROR(message_value, error_number_value)             \
  do {                                                                         \
    errno = error_number_value;                                                \
    api::ExecutionContext::handle_system_call_result(__LINE__, message_value,  \
                                                     -1);                      \
    return;                                                                    \
  } while (0)

#define API_SINGLETON(class_name)                                              \
private:                                                                       \
  class_name() = default;                                                      \
                                                                               \
public:                                                                        \
  static class_name &instance() {                                              \
    static class_name m_instance;                                              \
    return m_instance;                                                         \
  }                                                                            \
  class_name(const class_name &) = delete;                                     \
  class_name &operator=(const class_name &) = delete;                          \
  class_name(class_name &&) = delete;                                          \
  class_name &operator=(class_name &&) = delete

/*! \brief ProgressCallback Class
 * \details The ProgressCallback class is used
 * by various methods to allow the application
 * to update the progress of an operation.
 *
 * ```
 * #include <sys.hpp>
 * #include <inet.hpp>
 * Printer p;
 *
 * p.set_progress_key("downloading");
 * HttpClient http_client;
 * DataFile data_file(File::APPEND);
 *
 * //download file to data_file and print the progress using #'s
 * http_client.get("http://some.url/file", data_file, p.progress_callback());
 * ```
 *
 */
class ProgressCallback {
public:
  /*! \details Defines the callback function prototype.
   *
   * The function has three arguments.  The first
   * is the context() member of this object. The first
   * integer is the current progress value and the second
   * is the total progress value.
   *
   * If the total (third argument) is zero, the operation is either complete
   * or aborted. If total is set to -1, the progress should be
   * shown as indeterminate.
   *
   */
  typedef bool (*callback_t)(void *, int, int);

  /*! \details Constructs an empty object. */
  ProgressCallback();

  static int indeterminate_progress_total() { return -1; }

  /*! \details Executes the callback if it is valid.
   *
   * This method is called within operations in order
   * to execute the provided callback.
   *
   * @param value The value of the progress of the operation
   * @param total The total possible progress for the operation
   * @return true to abort the operation or false to continue as normal
   *
   */
  bool update(int value, int total) const;

  static int update_function(const void *context, int value, int total);

private:
  API_AF(ProgressCallback, callback_t, callback, nullptr);
  API_AF(ProgressCallback, void *, context, nullptr);
};

} // namespace api

#endif // API_API_HPP_
