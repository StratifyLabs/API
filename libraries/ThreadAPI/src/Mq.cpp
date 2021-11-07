// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#if !defined __link

#include <mqueue.h>

#include "chrono.hpp"
#include "thread/Mq.hpp"

using namespace thread;

Mq::Mq(const Attributes &attributes, IsExclusive is_exclusive,
       var::StringView name, const OpenMode& open_mode,
       fs::Permissions perms) {
  API_RETURN_IF_ERROR();
  int o_flags = int(open_mode.o_flags()) | O_CREAT |
                (is_exclusive == IsExclusive::yes ? O_EXCL : 0);

  API_SYSTEM_CALL("", m_handle = mq_open(var::NameString(name).cstring(), o_flags,
                              perms.permissions(), &attributes.m_attr));
}

Mq::Mq(const var::StringView name, const fs::OpenMode &open_mode) {
  API_RETURN_IF_ERROR();
  API_SYSTEM_CALL(
      "", m_handle = mq_open(var::NameString(name).cstring(), int(open_mode.o_flags())));
}

Mq::~Mq(){
  if( m_handle != -1 ){
    mq_close(m_handle);
  }
}

Mq::Info Mq::get_info() const {
  API_RETURN_VALUE_IF_ERROR(Info());
  Info result;
  API_SYSTEM_CALL("", mq_getattr(m_handle, &result.m_attr));
  return result;
}

Mq& Mq::set_flags(fs::OpenMode open_mode){
  Attributes attributes;
  attributes.m_attr.mq_flags = int(open_mode.o_flags());
  set_attributes(attributes);
  return *this;
}

void Mq::set_attributes(const Attributes &attributes){
  API_RETURN_IF_ERROR();
  API_SYSTEM_CALL("", mq_setattr(m_handle, &attributes.m_attr, nullptr));
}

Mq &Mq::receive(var::View message) {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL("", mq_receive(m_handle, message.to_char(), message.size(),
                                 &m_message_priority));
  return *this;
}

Mq &Mq::send(var::View message) {
  API_RETURN_VALUE_IF_ERROR(*this);
  API_SYSTEM_CALL("", mq_send(m_handle, message.to_char(), message.size(),
                                 m_message_priority));
  return *this;
}

Mq &Mq::receive_timed(var::View message, const chrono::ClockTime & relative_timeout){
  API_RETURN_VALUE_IF_ERROR(*this);
  auto calc_time = chrono::ClockTime::get_system_time() + relative_timeout;
  API_SYSTEM_CALL("", mq_timedreceive(m_handle, message.to_char(), message.size(),
                              &m_message_priority, calc_time.timespec()));
  return *this;
}

Mq &Mq::send_timed(var::View message, const chrono::ClockTime & relative_timeout){
  API_RETURN_VALUE_IF_ERROR(*this);
  auto calc_time = chrono::ClockTime::get_system_time() + relative_timeout;
  API_SYSTEM_CALL("", mq_timedsend(m_handle, message.to_char(), message.size(),
                                   m_message_priority, calc_time.timespec()));
  return *this;
}

void Mq::unlink(const char *name){
  API_RETURN_IF_ERROR();
  API_SYSTEM_CALL("", mq_unlink(name));
}

int Mq::File::interface_read(void *buf, int nbyte) const {
  return mq_receive(m_mq.m_handle, reinterpret_cast<char*>(buf), nbyte, nullptr);
}

int Mq::File::interface_write(const void *buf, int nbyte) const {
  return mq_send(m_mq.m_handle, reinterpret_cast<const char*>(buf), nbyte, 0);
}

int Mq::File::interface_lseek(int offset, int whence) const {
  fake_seek(m_location, m_size, offset, whence);
  return m_location;
}

#else

int thread_api_mq_unused = 0;

#endif

