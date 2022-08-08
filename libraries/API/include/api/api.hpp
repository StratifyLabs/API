// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef API_API_HPP_
#define API_API_HPP_

#include <cerrno>
#include <climits>
#include <cstring>

#include <memory>
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

template <class Type, class Deleter = std::default_delete<Type>>
using UniquePointer = std::unique_ptr<Type, Deleter>;

/*! \details
 *
 * This class contains basic functions to access information
 * about the Api build.
 *
 */
class ApiInfo {
public:
  /*! \details Gets the version as a c-style string. The version
   * uses semantic version format.
   *
   * @return `<major>.<minor>.<patch>`
   */
  static const char *version();

  /*! \details Gets the git hash as a c-style string.
   *
   * This can be useful when debugging development builds
   *
   */
  static const char *git_hash();

  /*! \details Gets the initial size of a malloc chunck.
   *
   * This function is really only useful when using Stratify OS.
   * It lets you optimize some buffers to malloc boundaries.
   *
   */
  static constexpr u32 malloc_start_chunk_size() {
    return API_MINIMUM_CHUNK_SIZE;
  }

  /*! \details Gets the standard size of a malloc chunk.
   *
   * This function is really only useful when using Stratify OS.
   * It lets you optimize some buffers to malloc boundaries.
   *
   */
  static constexpr u32 malloc_chunk_size() { return API_MALLOC_CHUNK_SIZE; }
};

/*! \details
 *
 * This class is used for creating abstractions to C libraries.
 *
 * It is primarily useful when creating shared libraries on
 * Stratify OS. For desktop builds, it just uses a function
 * table for 3rd party libraries. This repo doesn't use
 * any 3rd party libraries. Check out
 * [JsonAPI](https://github.com/StratifyLabs/JsonAPI) or
 * [InetAPI](https://github.com/StratifyLabs/InetAPI).
 * for more examples
 *
 * @tparam FunctionTable The c-style function table
 * @tparam initial_value The initial value to assign to the table. In
 * StratifyOS, you use a kernel request to get the pointer to the function
 * table.
 *
 */
#if defined __link
template <typename FunctionTable, const FunctionTable *initial_value>
class Api {
#else
extern "C" const void *kernel_request_api(u32 request);
template <typename FunctionTable, u32 request> class Api {
#endif
public:
  Api() { initialize(); }

  /*! \details Checks to see if the API is valid and available.
   *
   * @return `true` if the API is available.
   */
  bool is_valid() { return m_api != nullptr; }

  Api &operator=(const FunctionTable *value) {
    m_api = value;
    return *this;
  }

  const FunctionTable *operator->() const { return m_api; }
  const FunctionTable *api() const { return m_api; }

private:
  void initialize() {
    if (m_api == nullptr) {
#if defined __link
      m_api = initial_value;
#else
      m_api = (const FunctionTable *)kernel_request_api(request);
#endif
    }
  }
  const FunctionTable *m_api = nullptr;
};

/*! \details
 * This class contains the thread-local error object.
 *
 * The API framework is designed to keep track of errors
 * on a thread-by-thread basis. If the thread has an error,
 * the API framework will not call any code that affects
 * the error context.
 *
 * For example:
 *
 * ```cpp
 * #include <fs.hpp>
 *
 * File file("does_not_exist.txt");
 * file.write("Hello");
 * ```
 *
 * In the snippet above, the code will try to open `does_not_exist.txt`. It will
 * fail and set the threads error context. `file.write()` will not attempt
 * to write to the file because the thread has an error. The first error
 * encountered is preserved until it is cleared.
 *
 * This approach allows you to chain together complex operations and then
 * precisely debug the error. This code copies a file:
 *
 * ```cpp
 * #include <fs.hpp>
 * File(File::IsOverwrite::yes,
 * "new_file.txt").write(File("probably_exists.txt")); if(
 * api::ExecutionContext::is_error() ){
 *   //at this point, the first error is preserved and shown
 *   printf("Error: %s\n", error().message());
 * }
 * ```
 *
 *
 */
class Error {
public:
  /*! \details
   *
   * This class stores a symbol backtrace whenever an error happens.
   *
   * The backtrace is only available on systems that support the
   * `backtrace_symbols()` function.
   *
   */
  class Backtrace {
  public:
    explicit Backtrace(const Error &context)
#if defined __link && !defined __win32
      : m_entry_count(context.m_backtrace_count),
        m_symbol_pointer(
          backtrace_symbols(context.m_backtrace_buffer, m_entry_count),
          &symbol_deleter)
#else
      : m_symbol_pointer(nullptr, &symbol_deleter)
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
    UniquePointer<char *, decltype(&symbol_deleter)> m_symbol_pointer;
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

class ThreadExecutionContext {
public:
  ThreadExecutionContext(const ThreadExecutionContext &) = delete;
  ThreadExecutionContext &operator=(const ThreadExecutionContext &) = delete;
  ThreadExecutionContext(ThreadExecutionContext &&) = delete;
  ThreadExecutionContext &operator=(ThreadExecutionContext &&) = delete;
  ~ThreadExecutionContext() { ExecutionContext::free_context(); }
};

class Demangler {
public:
  const char *demangle(const char *input);

private:
  static constexpr size_t buffer_size = 2048;
  API_RAF(Demangler, int, status, 0);
  size_t m_length = buffer_size;
  UniquePointer<char> m_last;
  UniquePointer<char> m_buffer;
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
  using callback_t = bool (*)(void *, int, int);

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

/*! \sa Range */
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

/*! \details
 *
 * This class is used to create range based loops from integer types.
 *
 * @tparam Type The integer type to use.
 *
 * For example:
 *
 * ```cpp
 *
 * for(int i=5; i < 10; ++i){}
 *
 * //becomes
 * for(auto i: api::Range(5,10)){}
 * ```
 *
 * Using range based loops is less error prone than tradition `for` loops
 * and the compiler can deduce the type. For example:
 *
 * ```cpp
 * const u16 first = 100;
 * const u16 last = 200;
 *
 * for(auto i: api::Range(first,last)){}
 *
 * ```
 *
 */
template <typename Type> class Range {
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

/*! \sa Index */
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

/*! \details
 *
 *
 * This class is used to create range based loops from zero to some value.
 *
 * @tparam Type The integer type to use. This is usually deduced automatically
 * by the compiler and does not need to be specified.
 *
 * For example:
 *
 * ```cpp
 *
 * for(int i=0; i < 10; ++i){}
 * //becomes:
 * for(auto i: api::Index(10)){}
 *
 * //tell the compiler what number type to user
 * for(auto i: api::Index<size_t>(10)){}
 * ```
 *
 * Using range based loops is less error prone than tradition `for` loops
 * and the compiler can deduce the type. For example:
 *
 * ```cpp
 * u16 last = 200;
 *
 * for(auto i: api::Index(last)){}
 *
 * const auto size = File("file.txt").size();
 * for(auto i: api::Index(size)){}
 * ```
 *
 */
template <typename Type> class Index {
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

/*! \details
 *
 * This class is used to manage system resources. It implements the rule of 5
 * and holds an arbitrary data member that is custom-deleted upon destruction.
 *
 * For example, a file descriptor (`int`) can be wrapped in a SystemResource.
 * The SystemResource will close the file when the destructor is called.
 *
 * @tparam Type Type of the member (e.g., pthread_mutex_t, sem_t, int)
 * @tparam Deleter The function to call when the destructor is called.
 *
 * \sa File
 */
template <typename Type, typename Deleter> class SystemResource {
public:
  SystemResource(const Type &invalid_value = {}) : m_value(invalid_value) {}
  SystemResource(const Type &initial_value, const Deleter &deleter)
    : m_value(initial_value), m_deleter(deleter) {}

  SystemResource(const SystemResource &) = delete;
  SystemResource &operator=(const SystemResource &) = delete;

  SystemResource(SystemResource &&a) noexcept { swap(a); }
  SystemResource &operator=(SystemResource &&a) noexcept {
    swap(a);
    return *this;
  }

  ~SystemResource() {
    if (m_deleter) {
      m_deleter(&m_value);
    }
  };

  SystemResource &set_value(const Type &value) {
    m_value = value;
    return *this;
  }
  const Type &value() const { return m_value; }

  Type *pointer_to_value() { return &m_value; }

  const Type *pointer_to_value() const { return &m_value; }

private:
  Type m_value = {};
  Deleter m_deleter = nullptr;

  void swap(SystemResource &a) {
    std::swap(m_value, a.m_value);
    std::swap(m_deleter, a.m_deleter);
  }
};

/*! \details
 *
 * This class saves a copy of the error context on the stack and sets the
 * current `Error` to a fresh value (no error). Upon
 * destruction, the original error scope is restored.
 *
 * This is helpful in two situations,
 *
 * 1. You know an error might happen
 * 2. An error may have happened, but you want to execute code in an error-free
 * context.
 *
 * For example:
 *
 * ```cpp
 *
 *   File new_file(File::IsOverwrite::yes, "new_file.txt");
 *  {
 *    api::ErrorScope error_scope;
 *    File maybe_file("maybe_exists.txt");
 *    if( file.is_success() ){
 *      new_file.write(file);
 *    }
 *  }
 *  //if maybe_exists.txt was opened, it's contents were copied to new_file
 *  //either way, the context is error free
 *  new_file.write("Hello World\n");
 * ```
 *
 */
class ErrorScope {
  struct Context {
    Error error = ExecutionContext::m_private_context.get_error();
    int error_number = errno;
  };

  static void deleter(Context * context){
    ExecutionContext::m_private_context.get_error() = context->error;
    errno = context->error_number;
  }
  using ErrorResource = SystemResource<Context, decltype(&deleter)>;
  ErrorResource m_error_resource;

public:
  ErrorScope() : m_error_resource({}, &deleter) { ExecutionContext::reset_error(); }
};

/*! \cond */
using ErrorContext = ErrorScope;
using ErrorGuard = ErrorScope;
/*! \endcond */

/*! \details
 *
 * This function will setup the system to trace an error
 * associated with a segmentation fault.
 *
 * You can call it at the beginning of main to debug segmentation
 * faults.
 *
 */
void catch_segmentation_fault();

} // namespace api

#endif // API_API_HPP_
