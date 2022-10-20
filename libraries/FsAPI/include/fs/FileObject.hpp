// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef FS_API_FS_FILE_OBJECT_HPP_
#define FS_API_FS_FILE_OBJECT_HPP_

#include "api/api.hpp"

#include "FileInfo.hpp"
#include "chrono/MicroTime.hpp"
#include "var/Base64.hpp"

#include "var/String.hpp"

namespace fs {

/*! \details
 *
 * This class is a pure virtual base class
 * for managing file-like objects.
 *
 * The API framework can treat almost anything like a file
 * using this class. This makes it easy to read and write
 * all kinds of data structures.
 *
 * For example, a DataFile treats memory allocated on
 * the heap as a file like object. So you can easily read the contents
 * of a file from disk into memory.
 *
 * ```cpp
 * #include <fs.hpp>
 * #include <var.hpp>
 *
 * DataFile data_file(File("load_me.txt"));
 * const auto line = data_file.gets<String>();
 * ```
 *
 */
class FileObject : public api::ExecutionContext, public FileInfoFlags {
public:
  enum class IsOverwrite { no, yes };
  enum class IsNull { yes };

  enum class Whence { set = SEEK_SET, current = SEEK_CUR, end = SEEK_END };

  FileObject() = default;
  virtual ~FileObject() = default;

  API_NO_DISCARD size_t size() const;
  API_NO_DISCARD ssize_t size_signed() const {
    return static_cast<ssize_t>(size());
  }

  API_NO_DISCARD int location() const;

  const FileObject &read(var::View view) const;
  FileObject &read(var::View view) {
    return API_CONST_CAST_SELF(FileObject, read, view);
  }

  const FileObject &write(var::View view) const;
  FileObject &write(var::View view) {
    return API_CONST_CAST_SELF(FileObject, write, view);
  }

  class Write {
  public:
    Write()
      : m_location(-1), m_page_size(FSAPI_LINK_DEFAULT_PAGE_SIZE),
        m_size(static_cast<size_t>(-1)) {}

  private:
    API_ACCESS_FUNDAMENTAL(Write, int, location, -1);
    API_ACCESS_FUNDAMENTAL(
      Write,
      size_t,
      page_size,
      FSAPI_LINK_DEFAULT_PAGE_SIZE);
    API_ACCESS_FUNDAMENTAL(Write, size_t, size, static_cast<size_t>(-1));
    API_ACCESS_FUNDAMENTAL(Write, char, terminator, 0);
    API_ACCESS_FUNDAMENTAL(Write, chrono::MicroTime, timeout, 0_microseconds);
    API_ACCESS_FUNDAMENTAL(
      Write,
      chrono::MicroTime,
      retry_delay,
      10_milliseconds);
    API_ACCESS_FUNDAMENTAL(
      Write,
      const var::Transformer *,
      transformer,
      nullptr);
    API_ACCESS_FUNDAMENTAL(
      Write,
      const api::ProgressCallback *,
      progress_callback,
      nullptr);
  };

  const FileObject &
  write(const FileObject &source_file, const Write &options = Write()) const;

  class Verify {
  public:
    Verify()
      : m_page_size(FSAPI_LINK_DEFAULT_PAGE_SIZE),
        m_size(static_cast<size_t>(-1)) {}

  private:
    API_ACCESS_FUNDAMENTAL(
      Verify,
      u32,
      page_size,
      FSAPI_LINK_DEFAULT_PAGE_SIZE);
    API_ACCESS_FUNDAMENTAL(Verify, size_t, size, static_cast<size_t>(-1));
    API_ACCESS_FUNDAMENTAL(
      Verify,
      const api::ProgressCallback *,
      progress_callback,
      nullptr);
  };

  bool
  verify(const FileObject &source_file, const Verify &options = Verify()) const;

  class LocationScope {
    struct Context {
      const FileObject *file_object;
      int location;
    };
    static void deleter(Context *context) {
      context->file_object->seek(context->location);
    }
    using Resource = api::SystemResource<Context, decltype(&deleter)>;
    Resource m_resource;

  public:
    explicit LocationScope(const FileObject &object)
      : m_resource({&object, object.location()}, &deleter) {}
  };

  using LocationGuard = LocationScope;

  FileObject &
  write(const FileObject &source_file, const Write &options = Write()) {
    return API_CONST_CAST_SELF(FileObject, write, source_file, options);
  }

  template <typename Type = void>
  const FileObject &ioctl(int request, Type *args = nullptr) const {
    ioctl_implementation(request, static_cast<void *>(args));
    return *this;
  }

  template <typename Type> FileObject &ioctl(int request, Type *args) {
    return API_CONST_CAST_SELF(FileObject, ioctl, request, args);
  }

  const FileObject &write(
    const FileObject &source_file,
    const var::Transformer &transformer,
    const Write &options = Write()) const {
    return write(source_file, Write(options).set_transformer(&transformer));
  }

  FileObject &write(
    const FileObject &source_file,
    const var::Transformer &transformer,
    const Write &options = Write()) {
    return API_CONST_CAST_SELF(
      FileObject,
      write,
      source_file,
      transformer,
      options);
  }

  const FileObject &seek(int location, Whence whence = Whence::set) const;
  FileObject &seek(int location, Whence whence = Whence::set) {
    return API_CONST_CAST_SELF(FileObject, seek, location, whence);
  }

  /*! \details Does a character size read until `terminal_character` is found`
   *
   */
  template <class StringType = var::GeneralString>
  StringType get_line(char terminal_character = '\n') const {
    StringType result;
    return StringType{get_line_implementation(
      terminal_character,
      result.data(),
      result.capacity())};
  }

  /*! \details Reads in a line from a file.
   *
   * The entire `StringType` is read from the file. The file then
   * seeks back to the original location.
   *
   * Don't use this with sockets: use get_line().
   *
   * Use this when reading large text files. It performs
   * much faster then `get_line()` but requires seekable
   * files.
   *
   */
  template <class StringType = var::GeneralString>
  StringType read_line(char term = '\n') const {
    StringType result;
    return StringType{
      read_line_implementation(term, result.data(), result.capacity())};
  }

  const FileObject &sync() const;
  FileObject &sync() { return API_CONST_CAST_SELF(FileObject, sync); }

protected:
  virtual int interface_lseek(int offset, int whence) const = 0;
  virtual int interface_read(void *buf, int nbyte) const = 0;
  virtual int interface_write(const void *buf, int nbyte) const = 0;
  virtual int interface_ioctl(int request, void *argument) const = 0;
  virtual int interface_fsync() const { return 0; }
  static void fake_seek(int &location, size_t size, int offset, int whence);
  static int fake_ioctl(int, void *) {
    errno = ENOTSUP;
    return -1;
  }

private:
  const FileObject &ioctl_implementation(int request, void *arg) const;
  auto get_line_implementation(char term, char *buffer, size_t size) const
    -> var::StringView;
  auto read_line_implementation(char term, char *buffer, size_t size) const
    -> var::StringView;
};

template <class Derived> class FileAccess : public FileObject {
public:
#define FSAPI_FUNCTION_GROUP(QUAL)                                             \
  auto QUAL read(var::View view) QUAL {                                        \
    FileObject::read(view);                                                    \
    return static_cast<Derived QUAL>(*this);                                   \
  }
  FSAPI_FUNCTION_GROUP(const &)
  FSAPI_FUNCTION_GROUP(&)
  FSAPI_FUNCTION_GROUP(&&)
#undef FSAPI_FUNCTION_GROUP
#define FSAPI_FUNCTION_GROUP(QUAL)                                             \
  auto QUAL write(var::View view) QUAL {                                       \
    FileObject::write(view);                                                   \
    return static_cast<Derived QUAL>(*this);                                   \
  }
  FSAPI_FUNCTION_GROUP(const &)
  FSAPI_FUNCTION_GROUP(&)
  FSAPI_FUNCTION_GROUP(&&)
#undef FSAPI_FUNCTION_GROUP
#define FSAPI_FUNCTION_GROUP(QUAL)                                             \
  auto QUAL sync() QUAL {                                                      \
    FileObject::sync();                                                        \
    return static_cast<Derived QUAL>(*this);                                   \
  }
  FSAPI_FUNCTION_GROUP(const &)
  FSAPI_FUNCTION_GROUP(&)
  FSAPI_FUNCTION_GROUP(&&)
#undef FSAPI_FUNCTION_GROUP
#define FSAPI_FUNCTION_GROUP(QUAL)                                             \
  auto QUAL write(                                                             \
    const FileObject &source_file,                                             \
    const Write &options = Write()) QUAL {                                     \
    FileObject::write(source_file, options);                                   \
    return static_cast<Derived QUAL>(*this);                                   \
  }
  FSAPI_FUNCTION_GROUP(const &)
  FSAPI_FUNCTION_GROUP(&)
  FSAPI_FUNCTION_GROUP(&&)
#undef FSAPI_FUNCTION_GROUP

#define FSAPI_FUNCTION_GROUP(QUAL)                                             \
  auto QUAL write(                                                             \
    const FileObject &source_file,                                             \
    const var::Transformer &transformer,                                       \
    const Write &options = Write()) QUAL {                                     \
    FileObject::write(source_file, transformer, options);                      \
    return static_cast<Derived QUAL>(*this);                                   \
  }
  FSAPI_FUNCTION_GROUP(const &)
  FSAPI_FUNCTION_GROUP(&)
  FSAPI_FUNCTION_GROUP(&&)
#undef FSAPI_FUNCTION_GROUP

#define FSAPI_FUNCTION_GROUP(QUAL)                                             \
  auto QUAL seek(int location, Whence whence = Whence::set) QUAL {             \
    FileObject::seek(location, whence);                                        \
    return static_cast<Derived QUAL>(*this);                                   \
  }
  FSAPI_FUNCTION_GROUP(const &)
  FSAPI_FUNCTION_GROUP(&)
  FSAPI_FUNCTION_GROUP(&&)
#undef FSAPI_FUNCTION_GROUP

#define FSAPI_FUNCTION_GROUP(QUAL)                                             \
  template <typename Type> auto QUAL ioctl(int request, Type *arg) QUAL {      \
    FileObject::ioctl(request, arg);                                           \
    return static_cast<Derived QUAL>(*this);                                   \
  }
  FSAPI_FUNCTION_GROUP(const &)
  FSAPI_FUNCTION_GROUP(&)
  FSAPI_FUNCTION_GROUP(&&)
#undef FSAPI_FUNCTION_GROUP

#define FSAPI_FUNCTION_GROUP(QUAL)                                             \
  auto QUAL ioctl(int request) QUAL {                                          \
    FileObject::ioctl<void>(request, static_cast<void *>(nullptr));            \
    return static_cast<Derived QUAL>(*this);                                   \
  }
  FSAPI_FUNCTION_GROUP(const &)
  FSAPI_FUNCTION_GROUP(&)
  FSAPI_FUNCTION_GROUP(&&)
#undef FSAPI_FUNCTION_GROUP

  Derived &&move() { return std::move(static_cast<Derived &>(*this)); }

protected:
  FileAccess<Derived>() = default;

private:
};

template <class Derived> class FileMemberAccess {
public:
  using Whence = fs::FileObject::Whence;
  using Write = fs::FileObject::Write;

  FileMemberAccess(const fs::FileObject &file)
    : m_file_member_reference_access{&file} {}

  // a move should not copy or swap anything
  // The member pointer should always point to the
  // derived owner's internal m_file
  FileMemberAccess(FileMemberAccess &&) {}
  FileMemberAccess &operator=(FileMemberAccess &&) { return *this; }

  FileMemberAccess(const FileMemberAccess &) = delete;
  FileMemberAccess &operator=(const FileMemberAccess &) = delete;

#define FSAPI_FUNCTION_GROUP(QUAL)                                             \
  auto QUAL read(var::View view) QUAL {                                        \
    m_file_member_reference_access->read(view);                                \
    return static_cast<Derived QUAL>(*this);                                   \
  }
  FSAPI_FUNCTION_GROUP(const &)
  FSAPI_FUNCTION_GROUP(&)
  FSAPI_FUNCTION_GROUP(&&)
#undef FSAPI_FUNCTION_GROUP
#define FSAPI_FUNCTION_GROUP(QUAL)                                             \
  auto QUAL write(var::View view) QUAL {                                       \
    m_file_member_reference_access->write(view);                               \
    return static_cast<Derived QUAL>(*this);                                   \
  }
  FSAPI_FUNCTION_GROUP(const &)
  FSAPI_FUNCTION_GROUP(&)
  FSAPI_FUNCTION_GROUP(&&)
#undef FSAPI_FUNCTION_GROUP
#define FSAPI_FUNCTION_GROUP(QUAL)                                             \
  auto QUAL write(                                                             \
    const fs::FileObject &source_file,                                         \
    const Write &options = Write()) QUAL {                                     \
    m_file_member_reference_access->write(source_file, options);               \
    return static_cast<Derived QUAL>(*this);                                   \
  }
  FSAPI_FUNCTION_GROUP(const &)
  FSAPI_FUNCTION_GROUP(&)
  FSAPI_FUNCTION_GROUP(&&)
#undef FSAPI_FUNCTION_GROUP
#define FSAPI_FUNCTION_GROUP(QUAL)                                             \
  auto QUAL write(                                                             \
    const fs::FileObject &source_file,                                         \
    const var::Transformer &transformer,                                       \
    const Write &options = Write()) QUAL {                                     \
    m_file_member_reference_access->write(source_file, transformer, options);  \
    return static_cast<Derived QUAL>(*this);                                   \
  }
  FSAPI_FUNCTION_GROUP(const &)
  FSAPI_FUNCTION_GROUP(&)
  FSAPI_FUNCTION_GROUP(&&)
#undef FSAPI_FUNCTION_GROUP
#define FSAPI_FUNCTION_GROUP(QUAL)                                             \
  auto QUAL seek(int location, Whence whence = Whence::set) QUAL {             \
    m_file_member_reference_access->seek(location, whence);                    \
    return static_cast<Derived QUAL>(*this);                                   \
  }
  FSAPI_FUNCTION_GROUP(const &)
  FSAPI_FUNCTION_GROUP(&)
  FSAPI_FUNCTION_GROUP(&&)
#undef FSAPI_FUNCTION_GROUP

#define FSAPI_FUNCTION_GROUP(QUAL)                                             \
  template <typename Type> auto QUAL ioctl(int request, Type *arg) QUAL {      \
    m_file_member_reference_access->ioctl(request, arg);                       \
    return static_cast<Derived QUAL>(*this);                                   \
  }
  FSAPI_FUNCTION_GROUP(const &)
  FSAPI_FUNCTION_GROUP(&)
  FSAPI_FUNCTION_GROUP(&&)
#undef FSAPI_FUNCTION_GROUP

#define FSAPI_FUNCTION_GROUP(QUAL)                                             \
  auto QUAL ioctl(int request) QUAL {                                          \
    m_file_member_reference_access->ioctl<void>(                               \
      request,                                                                 \
      static_cast<void *>(nullptr));                                           \
    return static_cast<Derived QUAL>(*this);                                   \
  }
  FSAPI_FUNCTION_GROUP(const &)
  FSAPI_FUNCTION_GROUP(&)
  FSAPI_FUNCTION_GROUP(&&)
#undef FSAPI_FUNCTION_GROUP

private:
  // This should not be moved during move operations
  // the file it points to will move the fd from the temporary
  // to the new location and this will point to the new location
  const fs::FileObject *m_file_member_reference_access = nullptr;
}; // namespace fs

} // namespace fs

#endif /* FS_API_FS_FILE_HPP_ */
