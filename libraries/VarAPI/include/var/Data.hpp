/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.

#ifndef VAR_API_DATA_HPP_
#define VAR_API_DATA_HPP_

#include <cstdio>
#include <cstring>
#include <type_traits>
#include <vector>

#include "View.hpp"

#if !defined __link
#include <malloc.h>
#endif

namespace var {

class StringView;

class DataInfo {
public:
#if !defined __link
  DataInfo() : m_info{mallinfo()} {}
  API_NO_DISCARD u32 arena() const { return m_info.arena; }
  API_NO_DISCARD u32 free_block_count() const { return m_info.ordblks; }
  API_NO_DISCARD u32 free_size() const { return m_info.fordblks; }
  API_NO_DISCARD u32 used_size() const { return m_info.uordblks; }
#else
  DataInfo() = default;
  u32 arena() const { return 0; }
  u32 free_block_count() const { return 0; }
  u32 free_size() const { return 0; }
  u32 used_size() const { return 0; }
#endif

  bool operator==(const DataInfo &a) const {
    return used_size() == a.used_size();
  }

private:
#if !defined __link
  struct mallinfo m_info {};
#endif
};

class Data : public api::ExecutionContext {
public:
  Data() = default;

  explicit Data(std::initializer_list<u8> il) : m_data(il) {}
  explicit Data(size_t size);

  API_NO_DISCARD static Data from_string(var::StringView value);
  API_NO_DISCARD static u32 minimum_capacity();
  API_NO_DISCARD static u32 block_size();

  const char *add_null_terminator();

  API_NO_DISCARD u32 capacity() const { return m_data.capacity(); }
  Data &resize(size_t size) &;
  Data &&resize(size_t size) && { return std::move(resize(size)); }
  Data &free() &;
  Data &&free() && { return std::move(free()); }

  class Copy {
  public:
    Copy() : m_destination_position(0), m_size(static_cast<size_t>(-1)) {}

  private:
    API_AF(Copy, size_t, destination_position, 0);
    API_AF(Copy, size_t, size, -1);
  };

  Data &copy(View a, const Copy &options = Copy()) &;
  Data &&copy(View a, const Copy &options = Copy()) && {
    return std::move(copy(a, options));
  }
  Data &append(View view) &;
  Data &&append(View view) && { return std::move(append(view)); }

  class Erase {
    API_AF(Erase, size_t, position, 0);
    API_AF(Erase, size_t, size, 0);
  };

  Data &erase(const Erase &options) &;
  Data &&erase(const Erase &options) && { return std::move(erase(options)); }
  inline Data &operator()(const Erase &options) { return erase(options); }

#if !defined __link
  static void reclaim_heap_space() { ::free((void *)1); }
#else
  static void reclaim_heap_space() {
    // this is only implemented on StratifyOS
  }
#endif

  Data &reserve(size_t size) &;
  Data && reserve(size_t size) && {
    return std::move(reserve(size));
  }

  bool operator==(const var::Data &data) const { return data.m_data == m_data; }
  bool operator!=(const var::Data &data) const { return data.m_data != m_data; }
  bool operator>(const var::Data &data) const { return data.m_data > m_data; }
  bool operator<(const var::Data &data) const { return data.m_data < m_data; }

  API_NO_DISCARD void *data() { return static_cast<void *>(m_data.data()); }
  API_NO_DISCARD const void *data() const {
    return static_cast<const void *>(m_data.data());
  }
  API_NO_DISCARD u8 *data_u8() { return (m_data.data()); }
  API_NO_DISCARD const u8 *data_u8() const { return (m_data.data()); }

  API_NO_DISCARD View view() { return {*this}; }
  API_NO_DISCARD View view() const { return {*this}; }

  API_NO_DISCARD size_t size() const { return m_data.size(); }
  API_NO_DISCARD ssize_t size_signed() const {
    return static_cast<ssize_t>(m_data.size());
  }

  API_NO_DISCARD StringView string_view() const;

private:
  std::vector<u8> m_data;
};

} // namespace var

#if USE_PRINTER
namespace sys {
class Printer;
#if !defined __link
Printer &operator<<(printer::Printer &printer, const var::DataInfo &a);
#endif
} // namespace sys
#endif

#endif /* VAR_API_DATA_HPP_ */
