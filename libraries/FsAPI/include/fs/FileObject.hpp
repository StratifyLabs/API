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

  const FileObject &read(void *buf, int size) const;
  FileObject &read(void *buf, int size) {
    return API_CONST_CAST_SELF(FileObject, read, buf, size);
  }

  const FileObject &read(var::View view) const {
    return read(view.to_void(), int(view.size()));
  }

  FileObject &read(var::View view) {
    return read(view.to_void(), int(view.size()));
  }

  const FileObject &write(const void *buf, int size) const;
  FileObject &write(const void *buf, int size) {
    return API_CONST_CAST_SELF(FileObject, write, buf, size);
  }

  const FileObject &write(var::View view) const {
    return write(view.to_const_void(), int(view.size()));
  }

  FileObject &write(var::View view) {
    return write(view.to_const_void(), int(view.size()));
  }

  class Write {
  public:
    Write()
      : m_location(-1), m_page_size(FSAPI_LINK_DEFAULT_PAGE_SIZE),
        m_size(static_cast<size_t>(-1)) {}

  private:
    API_ACCESS_FUNDAMENTAL(Write, int, location, -1);
    API_ACCESS_FUNDAMENTAL(Write, u32, page_size, FSAPI_LINK_DEFAULT_PAGE_SIZE);
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
      : m_resource({&object, object.location()}) {}
  };

  using LocationGuard = LocationScope;

  FileObject &
  write(const FileObject &source_file, const Write &options = Write()) {
    return API_CONST_CAST_SELF(FileObject, write, source_file, options);
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

  var::GeneralString gets(char term = '\n') const;

  template <class StringType> StringType get_line(char term = '\n') const {
    StringType result;
    const auto file_location = location();
    read(var::View(result.data(), result.capacity()));
    size_t offset = 0;
    for (auto c : var::StringView(result)) {
      if (c == term) {
        const auto new_length = offset + 1;
        seek(file_location + new_length);
        result.truncate(new_length);
        return result;
      }
      ++offset;
    }
    return result;
  }

  class Ioctl {
    API_ACCESS_FUNDAMENTAL(Ioctl, int, request, 0);
    API_ACCESS_FUNDAMENTAL(Ioctl, void *, argument, nullptr);
  };

  const FileObject &ioctl(int request, void *arg) const;
  FileObject &ioctl(int request, void *arg) {
    return API_CONST_CAST_SELF(FileObject, ioctl, request, arg);
  }

  const FileObject &ioctl(int request) const { return ioctl(request, nullptr); }
  FileObject &ioctl(int request) { return ioctl(request, nullptr); }

  const FileObject &ioctl(const Ioctl &options) const {
    return ioctl(options.request(), options.argument());
  }

  FileObject &ioctl(const Ioctl &options) {
    return ioctl(options.request(), options.argument());
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

  static int fake_ioctl(int request, void *argument) {
    MCU_UNUSED_ARGUMENT(request);
    MCU_UNUSED_ARGUMENT(argument);
    errno = ENOTSUP;
    return -1;
  }

private:
  constexpr static size_t m_gets_buffer_size = 128;
};

template <class Derived> class FileAccess : public FileObject {
public:
  const Derived &read(void *buf, size_t size) const {
    return static_cast<const Derived &>(FileObject::read(buf, size));
  }

  Derived &read(void *buf, size_t size) {
    return static_cast<Derived &>(FileObject::read(buf, size));
  }

  const Derived &read(var::View view) const {
    return static_cast<const Derived &>(FileObject::read(view));
  }

  Derived &read(var::View view) {
    return static_cast<Derived &>(FileObject::read(view));
  }

  const Derived &write(const void *buf, size_t size) const {
    return static_cast<const Derived &>(FileObject::write(buf, size));
  }

  Derived &write(const void *buf, size_t size) {
    return static_cast<Derived &>(FileObject::write(buf, size));
  }

  const Derived &write(var::View view) const {
    return static_cast<const Derived &>(FileObject::write(view));
  }

  Derived &write(var::View view) {
    return static_cast<Derived &>(FileObject::write(view));
  }

  const Derived &sync() const {
    return static_cast<const Derived &>(FileObject::sync());
  }

  Derived &sync() { return static_cast<Derived &>(FileObject::sync()); }

  const Derived &
  write(const FileObject &source_file, const Write &options = Write()) const {
    return static_cast<const Derived &>(
      FileObject::write(source_file, options));
  }

  Derived &
  write(const FileObject &source_file, const Write &options = Write()) {
    return static_cast<Derived &>(FileObject::write(source_file, options));
  }

  const Derived &write(
    const FileObject &source_file,
    const var::Transformer &transformer,
    const Write &options = Write()) const {
    return static_cast<const Derived &>(
      FileObject::write(source_file, transformer, options));
  }

  Derived &write(
    const FileObject &source_file,
    const var::Transformer &transformer,
    const Write &options = Write()) {
    return static_cast<Derived &>(
      FileObject::write(source_file, transformer, options));
  }

  const Derived &seek(int location, Whence whence = Whence::set) const {
    return static_cast<const Derived &>(FileObject::seek(location, whence));
  }

  Derived &seek(int location, Whence whence = Whence::set) {
    return static_cast<Derived &>(FileObject::seek(location, whence));
  }

  const Derived &ioctl(int request, void *arg) const {
    return static_cast<const Derived &>(FileObject::ioctl(request, arg));
  }

  Derived &ioctl(int request, void *arg) {
    return static_cast<Derived &>(FileObject::ioctl(request, arg));
  }

  const Derived &ioctl(const Ioctl &options) const {
    return static_cast<const Derived &>(FileObject::ioctl(options));
  }

  Derived &ioctl(const Ioctl &options) {
    return static_cast<Derived &>(FileObject::ioctl(options));
  }

  Derived &&move() { return std::move(static_cast<Derived &>(*this)); }

protected:
  FileAccess<Derived>() = default;

private:
};

template <class Derived> class FileMemberAccess {
public:
  using Whence = fs::FileObject::Whence;
  using Write = fs::FileObject::Write;
  using Ioctl = fs::FileObject::Ioctl;

  FileMemberAccess(const fs::FileObject &file)
    : m_file_member_reference_access(file) {}

  // FileMemberAccess(const FileMemberAccess & a) = default;
  // FileMemberAccess& operator =(const FileMemberAccess & a) = default;

  const Derived &read(void *buf, size_t size) const {
    m_file_member_reference_access.read(buf, int(size));
    return static_cast<const Derived &>(*this);
  }
  Derived &read(void *buf, size_t size) {
    m_file_member_reference_access.read(buf, int(size));
    return static_cast<Derived &>(*this);
  }
  const Derived &read(var::View view) const {
    m_file_member_reference_access.read(view);
    return static_cast<const Derived &>(*this);
  }
  Derived &read(var::View view) {
    m_file_member_reference_access.read(view);
    return static_cast<Derived &>(*this);
  }
  const Derived &write(const void *buf, size_t size) const {
    m_file_member_reference_access.write(buf, size);
    return static_cast<const Derived &>(*this);
  }
  Derived &write(const void *buf, size_t size) {
    m_file_member_reference_access.write(buf, size);
    return static_cast<Derived &>(*this);
  }
  const Derived &write(var::View view) const {
    m_file_member_reference_access.write(view);
    return static_cast<const Derived &>(*this);
  }
  Derived &write(var::View view) {
    m_file_member_reference_access.write(view);
    return static_cast<Derived &>(*this);
  }
  const Derived &write(
    const fs::FileObject &source_file,
    const Write &options = Write()) const {
    m_file_member_reference_access.write(source_file, options);
    return static_cast<const Derived &>(*this);
  }
  Derived &
  write(const fs::FileObject &source_file, const Write &options = Write()) {
    m_file_member_reference_access.write(source_file, options);
    return static_cast<Derived &>(*this);
  }
  const Derived &write(
    const fs::FileObject &source_file,
    const var::Transformer &transformer,
    const Write &options = Write()) const {
    m_file_member_reference_access.write(source_file, transformer, options);
    return static_cast<const Derived &>(*this);
  }
  Derived &write(
    const fs::FileObject &source_file,
    const var::Transformer &transformer,
    const Write &options = Write()) {
    m_file_member_reference_access.write(source_file, transformer, options);
    return static_cast<Derived &>(*this);
  }
  const Derived &seek(int location, Whence whence = Whence::set) const {
    m_file_member_reference_access.seek(location, whence);
    return static_cast<const Derived &>(*this);
  }
  Derived &seek(int location, Whence whence = Whence::set) {
    m_file_member_reference_access.seek(location, whence);
    return static_cast<Derived &>(*this);
  }
  const Derived &ioctl(int request, void *arg) const {
    m_file_member_reference_access.ioctl(request, arg);
    return static_cast<const Derived &>(*this);
  }
  Derived &ioctl(int request, void *arg) {
    m_file_member_reference_access.ioctl(request, arg);
    return static_cast<Derived &>(*this);
  }
  const Derived &ioctl(const Ioctl &options) const {
    m_file_member_reference_access.ioctl(options);
    return static_cast<const Derived &>(*this);
  }
  Derived &ioctl(const Ioctl &options) {
    m_file_member_reference_access.ioctl(options);
    return static_cast<Derived &>(*this);
  }

private:
  const fs::FileObject &m_file_member_reference_access;
};

} // namespace fs

#endif /* FS_API_FS_FILE_HPP_ */
