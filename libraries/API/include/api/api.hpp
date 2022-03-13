// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef API_API_HPP_
#define API_API_HPP_

#include <cerrno>
#include <climits>
#include <cstring>

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
    explicit Backtrace(const Error &context)
#if defined __link && !defined __win32
      : m_entry_count(context.m_backtrace_count),
        m_symbol_pointer(
          backtrace_symbols(context.m_backtrace_buffer, m_entry_count),
          &symbol_deleter)
#endif
    {
    }

    const char *at(size_t offset) const {
      if (offset < m_entry_count) {
        return m_symbol_pointer.get()[offset];
      }
      return nullptr;
    }

  private:
    static void symbol_deleter(char **x) { ::free(x); };
    API_RAF(Backtrace, size_t, entry_count, 0);
    std::unique_ptr<char *, decltype(&symbol_deleter)> m_symbol_pointer;
  };

  API_NO_DISCARD const char *message() const { return m_message; }
  API_NO_DISCARD int error_number() const { return m_error_number; }
  API_NO_DISCARD int line_number() const { return m_line_number; }

  API_NO_DISCARD void *signature() const { return m_signature; }

  constexpr static size_t backtrace_buffer_size() {
    return m_backtrace_buffer_size;
  }

  API_NO_DISCARD bool is_error() const { return line_number() > 0; }
  void reset() { m_line_number = 0; }
  API_NO_DISCARD bool is_guarded() const { return m_is_guarded; }
  void set_guarded(bool value = true) { m_is_guarded = value; }

private:
#if defined __link
  static constexpr size_t api_backtrace_size = 512;
#else
  static constexpr size_t api_backtrace_size = 32;
#endif

  explicit Error(void *signature) : m_signature(signature) {}
  friend class PrivateExecutionContext;
  friend class BacktraceSymbols;
  static constexpr size_t m_message_size = PATH_MAX;
  static constexpr size_t m_backtrace_buffer_size = api_backtrace_size;

  void *m_signature{};
  int m_error_number = 0;
  int m_line_number = 0;
  char m_message[m_message_size + 1]{};
  void *m_backtrace_buffer[m_backtrace_buffer_size]{};
  size_t m_backtrace_count = 0;
  bool m_is_guarded = false;

  inline void capture_backtrace() {
    if (!is_guarded()) {
#if defined __link
#if !defined __win32
      m_backtrace_count
        = backtrace(m_backtrace_buffer, m_backtrace_buffer_size);
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
  API_NO_DISCARD inline int value() const { return errno; }

  API_NO_DISCARD size_t context_count() const {
    if (m_error_list) {
      return m_error_list->size() + 1;
    }
    return 1;
  }

  Error &get_error();

  void free_context();
  void update_error_context(int result, int line, const char *message);

private:
  friend class ErrorScope;
  PrivateExecutionContext() = default;
  Error m_error = Error(&errno);
  std::vector<Error> *m_error_list = nullptr;
};

/*! \details This class is the base class for almost all classes
 * in all API frameworks.
 */
class ExecutionContext {
public:
  static int
  handle_system_call_result(int line, const char *message, int value) {
    if (value >= 0) {
      errno = value;
    } else {
      m_private_context.update_error_context(value, line, message);
    }
    return value;
  }

  template <typename T>
  static T *
  handle_system_call_null_result(int line, const char *message, T *value) {
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
  friend class ErrorScope;
  static PrivateExecutionContext m_private_context;
};

class ErrorScope {
public:
  ErrorScope() { ExecutionContext::reset_error(); }
  ErrorScope(const ErrorScope&) = delete;
  ErrorScope& operator=(const ErrorScope&) = delete;
  ~ErrorScope() {
    ExecutionContext::m_private_context.m_error = m_error;
    ExecutionContext::m_private_context.m_error.set_guarded(m_is_guarded);
    errno = m_error_number;
  }

private:
  Error m_error = Error(ExecutionContext::m_private_context.m_error);
  int m_error_number = errno;
  bool m_is_guarded = ExecutionContext::m_private_context.m_error.is_guarded();
};

using ErrorContext = ErrorScope;
using ErrorGuard = ErrorScope;

class ThreadExecutionContext {
public:
  ThreadExecutionContext(const ThreadExecutionContext &) = delete;
  ThreadExecutionContext& operator=(const ThreadExecutionContext &) = delete;
  ThreadExecutionContext(ThreadExecutionContext &&) = delete;
  ThreadExecutionContext& operator=(ThreadExecutionContext &&) = delete;
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

#define API_ASSERT(a) api::api_assert(a, __PRETTY_FUNCTION__, __LINE__)
void api_assert(bool value, const char *function, int line);

#define API_RETURN_VALUE_IF_ERROR(return_value)                                \
  do {                                                                         \
    if (api::ExecutionContext::is_error()) {                                   \
      return return_value;                                                     \
    }                                                                          \
  } while (0)

#define API_RETURN_IF_ERROR()                                                  \
  do {                                                                         \
    if (api::ExecutionContext::is_error()) {                                   \
      return;                                                                  \
    }                                                                          \
  } while (0)

#define API_SYSTEM_CALL(message_value, return_value)                           \
  api::ExecutionContext::handle_system_call_result(                            \
    __LINE__,                                                                  \
    message_value,                                                             \
    return_value)

#define API_SYSTEM_CALL_NULL(message_value, return_value)                      \
  api::ExecutionContext::handle_system_call_null_result(                       \
    __LINE__,                                                                  \
    message_value,                                                             \
    return_value)

#define API_RESET_ERROR() api::ExecutionContext::reset_error()

#define API_RETURN_VALUE_ASSIGN_ERROR(                                         \
  return_value,                                                                \
  message_value,                                                               \
  error_number_value)                                                          \
  do {                                                                         \
    errno = error_number_value;                                                \
    api::ExecutionContext::handle_system_call_result(                          \
      __LINE__,                                                                \
      message_value,                                                           \
      -1);                                                                     \
    return return_value;                                                       \
  } while (0)

#define API_RETURN_ASSIGN_ERROR(message_value, error_number_value)             \
  do {                                                                         \
    errno = error_number_value;                                                \
    api::ExecutionContext::handle_system_call_result(                          \
      __LINE__,                                                                \
      message_value,                                                           \
      -1);                                                                     \
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

#define API_SINGLETON_CUSTOM_CONSTRUCTOR(class_name)                           \
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
   using callback_t = bool (*)(void*, int, int);

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

template <typename Type> class RangeIterator {
public:
  using TransformCallback = Type (*)(const Type &, const Type &);

  RangeIterator(Type value, Type max, TransformCallback transform)
    : m_value(value), m_max(max), m_transform(transform) {}

  bool operator!=(RangeIterator const &a) const noexcept {
    return m_value != a.m_value;
  }

  Type operator*() const noexcept { return m_transform(m_value, m_max); }

  RangeIterator &operator++() {
    m_value++;
    return *this;
  }

  RangeIterator &operator--() {
    m_value--;
    return *this;
  }

private:
  Type m_value;
  Type m_max;
  TransformCallback m_transform;
};

template <typename Type = int> class Range {
public:
  static Type forward(const Type &a, const Type &) { return a; }
  static Type reverse(const Type &a, const Type &b) { return b - a - 1; }

  constexpr Range(
    const Type &start,
    const Type &finish,
    typename RangeIterator<Type>::TransformCallback transform = nullptr)
    : m_start(start < finish ? start : finish),
      m_finish(start < finish ? finish : start),
      m_transform(
        transform == nullptr ? (start < finish ? forward : reverse)
                             : transform) {}

  RangeIterator<Type> begin() const noexcept {
    return RangeIterator(m_start, m_finish, m_transform);
  }
  RangeIterator<Type> begin() noexcept {
    return RangeIterator(m_start, m_finish, m_transform);
  }

  RangeIterator<Type> end() const noexcept {
    return RangeIterator(m_finish, m_finish, m_transform);
  }
  RangeIterator<Type> end() noexcept {
    return RangeIterator(m_finish, m_finish, m_transform);
  }

  RangeIterator<Type> cbegin() const noexcept {
    return RangeIterator(m_start, m_finish, m_transform);
  }
  RangeIterator<Type> cend() const noexcept {
    return RangeIterator(m_finish, m_finish, m_transform);
  }

private:
  const Type m_start = 0;
  const Type m_finish = 0;
  typename RangeIterator<Type>::TransformCallback m_transform;
};

template <typename Type> class IndexIterator {
public:
  explicit IndexIterator(Type value) : m_value(value) {}

  bool operator!=(IndexIterator const &a) const noexcept {
    return m_value != a.m_value;
  }

  Type operator*() const noexcept { return m_value; }

  IndexIterator &operator++() {
    m_value++;
    return *this;
  }

  IndexIterator &operator--() {
    m_value--;
    return *this;
  }

private:
  Type m_value;
};

template <typename Type = int> class Index {
public:
  constexpr Index(const Type &start, const Type &finish)
    : m_start(start), m_finish(finish) {}

  constexpr explicit Index(const Type &finish)
    : m_start(Type{}), m_finish(finish) {}

  IndexIterator<Type> begin() const noexcept { return IndexIterator(m_start); }

  IndexIterator<Type> end() const noexcept { return IndexIterator(m_finish); }

  IndexIterator<Type> cbegin() const noexcept { return IndexIterator(m_start); }
  IndexIterator<Type> cend() const noexcept { return IndexIterator(m_finish); }

private:
  const Type m_start = 0;
  const Type m_finish = 0;
};

void catch_segmentation_fault();

} // namespace api

#endif // API_API_HPP_
