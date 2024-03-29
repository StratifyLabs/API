// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef API_API_MACROS_HPP_
#define API_API_MACROS_HPP_

#include <sdk/types.h>
#if defined __win32

#if !defined NAME_MAX
#define NAME_MAX 256
#endif

#if !defined PATH_MAX
#define PATH_MAX 1024
#endif

#endif

#define API_DEPRECATED(message) [[deprecated(message)]]
#define API_DEPRECATED_NO_REPLACEMENT [[deprecated]]
#define API_MAYBE_UNUSED [[maybe_unused]]
#define API_NO_DISCARD [[nodiscard]]
#define API_NO_RETURN [[noreturn]]
#define API_FALLTHROUGH [[fallthrough]]

#define API_ACCESS_BOOL(c, v, iv)                                              \
public:                                                                        \
  bool is_##v() const { return m_is_##v; }                                     \
  c &set_##v(bool value = true) {                                              \
    m_is_##v = value;                                                          \
    return *this;                                                              \
  }                                                                            \
                                                                               \
private:                                                                       \
  bool m_is_##v = iv

#define API_AB(c, v, iv) API_ACCESS_BOOL(c, v, iv)

#define API_READ_ACCESS_BOOL(c, v, iv)                                         \
public:                                                                        \
  bool is_##v() const { return m_is_##v; }                                     \
                                                                               \
private:                                                                       \
  bool m_is_##v = iv

#define API_RAB(c, v, iv) API_READ_ACCESS_BOOL(c, v, iv)

#define API_ACCESS_FUNDAMENTAL(c, t, v, iv)                                    \
public:                                                                        \
  t v() const { return m_##v; }                                                \
  c &set_##v(t value) & {                                                      \
    m_##v = value;                                                             \
    return *this;                                                              \
  }                                                                            \
  c &&set_##v(t value) && {                                                    \
    m_##v = value;                                                             \
    return std::move(*this);                                                   \
  }                                                                            \
                                                                               \
private:                                                                       \
  t m_##v = iv

#define API_AF(c, t, v, iv) API_ACCESS_FUNDAMENTAL(c, t, v, iv)

#define API_PUBLIC_MEMBER(CLASS, TYPE, NAME, INITIAL_VALUE)                    \
  CLASS &set_##NAME(TYPE value_parameter) & {                                  \
    NAME = value_parameter;                                                    \
    return *this;                                                              \
  }                                                                            \
  CLASS &&set_##NAME(TYPE value_parameter) && {                                \
    return std::move(set_##NAME(value_parameter));                             \
  }                                                                            \
  TYPE NAME = INITIAL_VALUE

#define API_PUBLIC_MEMBER_AZ(NAME, CLASS, TYPE, INITIAL_VALUE)                 \
  CLASS &set_##NAME(TYPE value_parameter) & {                                  \
    NAME = value_parameter;                                                    \
    return *this;                                                              \
  }                                                                            \
  CLASS &&set_##NAME(TYPE value_parameter) && {                                \
    return std::move(set_##NAME(value_parameter));                             \
  }                                                                            \
  TYPE NAME = INITIAL_VALUE

#define API_PMAZ(NAME, CLASS, TYPE, INITIAL_VALUE)                             \
  API_PUBLIC_MEMBER_AZ(NAME, CLASS, TYPE, INITIAL_VALUE)

#define API_PUBLIC_BOOL(CLASS, NAME, INITIAL_VALUE)                            \
  CLASS &set_##NAME(bool value_parameter = true) & {                           \
    is_##NAME = value_parameter;                                               \
    return *this;                                                              \
  }                                                                            \
  CLASS &&set_##NAME(bool value_parameter = true) && {                         \
    return std::move(set_##NAME(value_parameter));                             \
  }                                                                            \
  bool is_##NAME = INITIAL_VALUE

#define API_ACCESS_MEMBER_FUNDAMENTAL(c, t, p, v)                              \
public:                                                                        \
  t v() const { return m_##p.v; }                                              \
  c &set_##v(t value) {                                                        \
    m_##p.v = value;                                                           \
    return *this;                                                              \
  }

#define API_AMF(c, t, p, v) API_ACCESS_MEMBER_FUNDAMENTAL(c, t, p, v)

#define API_READ_ACCESS_MEMBER_FUNDAMENTAL(c, t, p, v)                         \
public:                                                                        \
  API_NO_DISCARD t v() const { return m_##p.v; }

#define API_RAMF(c, t, p, v) API_READ_ACCESS_MEMBER_FUNDAMENTAL(c, t, p, v)

#define API_ACCESS_MEMBER_FUNDAMENTAL_WITH_ALIAS(c, t, p, a, v)                \
public:                                                                        \
  API_NO_DISCARD t a() const { return m_##p.v; }                               \
  c &set_##a(t value) & {                                                      \
    m_##p.v = value;                                                           \
    return *this;                                                              \
  }                                                                            \
  c &&set_##a(t value) && { return std::move(set_##a(value)); }

#define API_AMFWA(c, t, p, a, v)                                               \
  API_ACCESS_MEMBER_FUNDAMENTAL_WITH_ALIAS(c, t, p, a, v)

#define API_ACCESS_MEMBER_COMPOUND(c, t, p, v)                                 \
public:                                                                        \
  API_NO_DISCARD const t &v() const { return m_##p.v; }                        \
  c &set_##v(const t &value) & {                                               \
    m_##p.v = value;                                                           \
    return *this;                                                              \
  }                                                                            \
  c &&set_##v(const t &value) && { return std::move(set_##v(value)); }

#define API_AMC(c, t, p, v) API_ACCESS_MEMBER_COMPOUND(c, t, p, v)

#define API_READ_ACCESS_FUNDAMENTAL(c, t, v, iv)                               \
public:                                                                        \
  API_NO_DISCARD t v() const { return m_##v; }                                 \
                                                                               \
private:                                                                       \
  t m_##v = iv

#define API_RAF(c, t, v, iv) API_READ_ACCESS_FUNDAMENTAL(c, t, v, iv)

#define API_ACCESS_COMPOUND(c, t, v)                                           \
public:                                                                        \
  API_NO_DISCARD const t &v() const { return m_##v; }                          \
  t &v() { return m_##v; }                                                     \
  c &set_##v(const t &value) & {                                               \
    m_##v = value;                                                             \
    return *this;                                                              \
  }                                                                            \
  c &&set_##v(const t &value) && { return std::move(set_##v(value)); }         \
                                                                               \
private:                                                                       \
  t m_##v

#define API_AC(c, t, v) API_ACCESS_COMPOUND(c, t, v)

#define API_ACCESS_STRING(PARENT_VALUE, VALUE_NAME)                            \
public:                                                                        \
  API_NO_DISCARD var::StringView VALUE_NAME() const {                          \
    return m_##VALUE_NAME.string_view();                                       \
  }                                                                            \
  PARENT_VALUE &set_##VALUE_NAME(const var::StringView value) & {              \
    m_##VALUE_NAME = value.to_string();                                        \
    return *this;                                                              \
  }                                                                            \
  PARENT_VALUE &&set_##VALUE_NAME(const var::StringView value) && {            \
    return std::move(set_##VALUE_NAME(value));                                 \
  }                                                                            \
                                                                               \
private:                                                                       \
  var::String m_##VALUE_NAME

#define API_AS(PARENT_VALUE, VALUE_NAME)                                       \
  API_ACCESS_STRING(PARENT_VALUE, VALUE_NAME)

#define API_READ_ACCESS_COMPOUND(c, t, v)                                      \
public:                                                                        \
  API_NO_DISCARD const t &v() const { return m_##v; }                          \
                                                                               \
private:                                                                       \
  t m_##v

#define API_RAC(c, t, v) API_READ_ACCESS_COMPOUND(c, t, v)

#define API_ACCESS_DERIVED_COMPOUND(c, d, t, v)                                \
  d &set_##v(const t &value) & {                                               \
    c::set_##v(value);                                                         \
    return static_cast<d &>(*this);                                            \
  }                                                                            \
  d &&set_##v(const t &value) && { return std::move(set_##v(value)); }

#define API_ADC(c, d, t, v) API_ACCESS_DERIVED_COMPOUND(c, d, t, v)

#define API_ACCESS_DERIVED_FUNDAMETAL(c, d, t, v)                              \
  d &set_##v(t value) & {                                                      \
    c::set_##v(value);                                                         \
    return static_cast<d &>(*this);                                            \
  }                                                                            \
  d &&set_##v(t value) && { return std::move(set_##v(value)); }

#define API_ADF(c, d, t, v) API_ACCESS_DERIVED_FUNDAMETAL(c, d, t, v)

#define API_ACCESS_DERIVED_BOOL(c, d, v)                                       \
  d &set_##v(bool value = true) & {                                            \
    c::set_##v(value);                                                         \
    return static_cast<d &>(*this);                                            \
  }                                                                            \
  d &&set_##v(bool value = true) && { return std::move(set_##v(value)); }

#define API_ADB(c, d, v) API_ACCESS_DERIVED_BOOL(c, d, v)

#define API_OR_ENUM_CLASS(TYPE)                                                \
  inline TYPE operator|(const TYPE a, const TYPE b) {                          \
    return static_cast<TYPE>(static_cast<u32>(a) | static_cast<u32>(b));       \
  }                                                                            \
  inline bool operator&(const TYPE a, const TYPE b) {                          \
    return (static_cast<u32>(a) & static_cast<u32>(b)) != 0;                   \
  }                                                                            \
  inline TYPE operator~(const TYPE a) {                                        \
    return static_cast<TYPE>(~(static_cast<u32>(a)));                          \
  }                                                                            \
  inline TYPE &operator|=(TYPE &a, const TYPE b) { return a = a | b; }         \
  inline TYPE &operator&=(TYPE &a, const TYPE b) {                             \
    return a = static_cast<TYPE>(static_cast<u32>(a) & static_cast<u32>(b));   \
  }

#define API_OR_NAMED_FLAGS_OPERATOR(TYPE, FLAG_NAME)                           \
  inline TYPE::FLAG_NAME operator|(                                            \
    const TYPE::FLAG_NAME a,                                                   \
    const TYPE::FLAG_NAME b) {                                                 \
    return static_cast<TYPE::FLAG_NAME>(                                       \
      static_cast<u32>(a) | static_cast<u32>(b));                              \
  }                                                                            \
  inline bool operator&(const TYPE::FLAG_NAME a, const TYPE::FLAG_NAME b) {    \
    return (static_cast<u32>(a) & static_cast<u32>(b)) != 0;                   \
  }                                                                            \
  inline TYPE::FLAG_NAME operator~(const TYPE::FLAG_NAME a) {                  \
    return static_cast<TYPE::FLAG_NAME>(~(static_cast<u32>(a)));               \
  }                                                                            \
  inline TYPE::FLAG_NAME &operator|=(                                          \
    TYPE::FLAG_NAME &a,                                                        \
    const TYPE::FLAG_NAME b) {                                                 \
    return a = a | b;                                                          \
  }                                                                            \
  inline TYPE::FLAG_NAME &operator&=(                                          \
    TYPE::FLAG_NAME &a,                                                        \
    const TYPE::FLAG_NAME b) {                                                 \
    return a = static_cast<TYPE::FLAG_NAME>(                                   \
             static_cast<u32>(a) & static_cast<u32>(b));                       \
  }

#define API_OR_FLAGS_OPERATOR(TYPE) API_OR_NAMED_FLAGS_OPERATOR(TYPE, flags)

#define API_ENUM_LOOP_OPERATOR(TYPE)                                           \
  TYPE &operator++(TYPE &a) {                                                  \
    a = TYPE(static_cast<std::underlying_type<TYPE>::type>(a) + 1);            \
    return a;                                                                  \
  }

#if defined __link
#include <string>
#define API_MINIMUM_CHUNK_SIZE 1024
#define API_MALLOC_CHUNK_SIZE 1024
#else
#include <sos/arch.h>
// this doesn't have to match the chunk size of the target
#define API_MALLOC_CHUNK_SIZE 32
#define API_MINIMUM_CHUNK_SIZE (128 - 12)
#endif

#define API_CONST_CAST_SELF(type_value, function_value, ...)                   \
  const_cast<type_value &>(                                                    \
    const_cast<const type_value *>(this)->function_value(__VA_ARGS__))

#define API_CONST_CAST(type_value, function_value, ...)                        \
  const_cast<const type_value *>(this)->function_value(__VA_ARGS__);

#define API_WRITE_ACCESS_COMPOUND_ALIAS(PARENT, DERIVED, TYPE, NAME)           \
  DERIVED &set_##NAME(const TYPE &a) {                                         \
    return static_cast<DERIVED &>(PARENT::set_##NAME(a));                      \
  }

#define API_WRITE_ACCESS_FUNDAMENTAL_ALIAS(PARENT, DERIVED, TYPE, NAME)        \
  DERIVED &set_##NAME(TYPE a) {                                                \
    return static_cast<DERIVED &>(PARENT::set_##NAME(a));                      \
  }

#define API_PRINTF_TRACE_LINE()                                                \
  printf(                                                                      \
    "%s():%d error? %d\n",                                                     \
    __FUNCTION__,                                                              \
    __LINE__,                                                                  \
    api::ExecutionContext::is_error())

#endif // API_API_MACROS_HPP_
