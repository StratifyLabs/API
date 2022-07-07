/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.

#ifndef SAPI_SYS_MQ_HPP_
#define SAPI_SYS_MQ_HPP_

#if defined __StratifyOS__ || defined __linux

#include <cstring>
#include <fcntl.h>
#include <mqueue.h>

#include "chrono/ClockTime.hpp"
#include "fs/File.hpp"
#include "var/StringView.hpp"

namespace thread {

class Mq : public api::ExecutionContext {
public:
  enum class IsExclusive { no, yes };

  using OpenMode = fs::OpenMode;

  class Attributes {

  public:
    Attributes() = default;

    API_NO_DISCARD long flags() const { return m_attr.mq_flags; }
    API_NO_DISCARD long current_message_count() const { return m_attr.mq_curmsgs; }
    API_NO_DISCARD long maximum_message_count() const { return m_attr.mq_maxmsg; }
    API_NO_DISCARD long message_size() const { return m_attr.mq_msgsize; }

    Attributes &set_maximum_message_count(long v) {
      m_attr.mq_maxmsg = v;
      return *this;
    }

    Attributes & set_message_count(long v){
      return set_maximum_message_count(v);
    }

    Attributes &set_message_size(long v) {
      m_attr.mq_msgsize = v;
      return *this;
    }

  private:
    friend class Mq;
    struct mq_attr m_attr{};
  };

  class Info {
  public:
    Info() : m_attr{} {}
    API_NO_DISCARD OpenMode::OpenFlags flags() const {
      return OpenMode::OpenFlags(m_attr.mq_flags);
    }
    API_NO_DISCARD long o_flags() const { return m_attr.mq_flags; }
    API_NO_DISCARD long current_message_count() const { return m_attr.mq_curmsgs; }
    API_NO_DISCARD long maximum_message_count() const { return m_attr.mq_maxmsg; }
    API_NO_DISCARD long message_size() const { return m_attr.mq_msgsize; }

  private:
    friend class Mq;
    struct mq_attr m_attr;
  };

  Mq() = delete;
  Mq(const Mq &a) = delete;
  Mq &operator=(const Mq &a) = delete;

  Mq(Mq &&a)  noexcept { std::swap(m_handle, a.m_handle); }
  Mq &operator=(Mq &&a)  noexcept {
    std::swap(m_handle, a.m_handle);
    return *this;
  }

  explicit Mq(var::StringView name,
              const fs::OpenMode &open_mode = fs::OpenMode::read_write());

  // create a named Mq
  Mq(const Attributes &attributes, IsExclusive is_exclusive,
     var::StringView name,
     const OpenMode &open_mode = OpenMode::read_write(),
     fs::Permissions perms = fs::Permissions(0666));

  ~Mq();

  API_NO_DISCARD bool is_valid() const { return m_handle != -1; }

  API_NO_DISCARD Info get_info() const;
  Mq &set_flags(OpenMode open_mode);

  Mq &receive(var::View message);
  Mq &send(var::View message);

  Mq &receive_timed(var::View message,
                    const chrono::ClockTime &relative_timeout);
  Mq &send_timed(var::View message, const chrono::ClockTime &relative_timeout);

  static void unlink(const char *name);

  class File : public fs::FileAccess<File> {
  public:

    explicit File(Mq & message_queue) : m_mq(message_queue){}

    File &set_size(size_t size) {
      m_size = size;
      return *this;
    }

  private:
    mutable int m_location = 0;
    mutable size_t m_size = 0;
    Mq & m_mq;

    int interface_ioctl(int request, void *argument) const override {
      return fake_ioctl(request, argument);
    }
    int interface_lseek(int offset, int whence) const override;
    int interface_read(void *buf, int nbyte) const override;
    int interface_write(const void *buf, int nbyte) const override;
  };

private:
  friend File;
  mqd_t m_handle = -1;
  API_AF(Mq, unsigned, message_priority, 0);

  void set_attributes(const Attributes &attributes) const;
};


} // namespace thread

#endif

#endif /* SAPI_SYS_MQ_HPP_ */
