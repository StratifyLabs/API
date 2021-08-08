/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.

#ifndef SAPI_SYS_MQ_HPP_
#define SAPI_SYS_MQ_HPP_

#ifndef __link

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
    Attributes() : m_attr{} {}

    long flags() const { return m_attr.mq_flags; }
    long current_message_count() const { return m_attr.mq_curmsgs; }
    long maximum_message_count() const { return m_attr.mq_maxmsg; }
    long message_size() const { return m_attr.mq_msgsize; }

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
    struct mq_attr m_attr;
  };

  class Info {
  public:
    Info() : m_attr{} {}
    OpenMode::OpenFlags flags() const {
      return OpenMode::OpenFlags(m_attr.mq_flags);
    }
    long o_flags() const { return m_attr.mq_flags; }
    long current_message_count() const { return m_attr.mq_curmsgs; }
    long maximum_message_count() const { return m_attr.mq_maxmsg; }
    long message_size() const { return m_attr.mq_msgsize; }

  private:
    friend class Mq;
    struct mq_attr m_attr;
  };

  Mq() = delete;
  Mq(const Mq &a) = delete;
  Mq &operator=(const Mq &a) = delete;

  Mq(Mq &&a) { std::swap(m_handle, a.m_handle); }
  Mq &operator=(Mq &&a) {
    std::swap(m_handle, a.m_handle);
    return *this;
  }

  explicit Mq(const var::StringView name,
              const fs::OpenMode &open_mode = fs::OpenMode::read_write());

  // create a named Mq
  Mq(const Attributes &attributes, IsExclusive is_exclusive,
     var::StringView name,
     const OpenMode &open_mode = OpenMode::read_write(),
     fs::Permissions perms = fs::Permissions(0666));

  ~Mq();

  bool is_valid() const { return m_handle != -1; }

  Info get_info() const;
  Mq &set_flags(OpenMode open_mode);

  Mq &receive(var::View message);
  Mq &send(var::View message);

  Mq &receive_timed(var::View message,
                    const chrono::ClockTime &relative_timeout);
  Mq &send_timed(var::View message, const chrono::ClockTime &relative_timeout);

  static void unlink(const char *name);

private:
  mqd_t m_handle;
  API_AF(Mq, unsigned, message_priority, 0);

  void set_attributes(const Attributes &attributes);
};

} // namespace thread

#endif

#endif /* SAPI_SYS_MQ_HPP_ */
