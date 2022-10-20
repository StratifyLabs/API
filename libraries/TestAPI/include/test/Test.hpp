// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef TESTAPI_TEST_HPP_
#define TESTAPI_TEST_HPP_

#include <cstdarg>
#if defined __link
#include <errno.h>
#endif

#include "chrono/ClockTime.hpp"
#include "chrono/ClockTimer.hpp"
#include "printer/Printer.hpp"
#include "sys/Cli.hpp"
#include "var/Data.hpp"
#include "var/StringView.hpp"

namespace test {

#define TEST_ASSERT_RESULT(RESULT_VALUE)                                       \
  do {                                                                         \
    if ((RESULT_VALUE) == false) {                                             \
      return false;                                                            \
    }                                                                          \
  } while (0)

#define TEST_EXPECT(RESULT_VALUE)                                              \
  PRINTER_TRACE(this->printer(), "");                                          \
  this->expect(__PRETTY_FUNCTION__, __LINE__, RESULT_VALUE)

#define TEST_ASSERT(RESULT_VALUE)                                              \
  do {                                                                         \
    PRINTER_TRACE(this->printer(), "");                                        \
    if (this->expect(__PRETTY_FUNCTION__, __LINE__, RESULT_VALUE) == false) {  \
      return false;                                                            \
    }                                                                          \
  } while (0)

#define TEST_SELF_EXPECT(RESULT_VALUE)                                         \
  PRINTER_TRACE(self->printer(), "");                                          \
  self->expect(__PRETTY_FUNCTION__, __LINE__, RESULT_VALUE)

#define TEST_SELF_ASSERT(RESULT_VALUE)                                         \
  do {                                                                         \
    PRINTER_TRACE(self->printer(), "");                                        \
    if (self->expect(__PRETTY_FUNCTION__, __LINE__, RESULT_VALUE) == false) {  \
      return false;                                                            \
    }                                                                          \
  } while (0)

struct TestFlags {
  enum class ExecuteFlags : u32 {
    null = 0,
    api /*! API Test Execution flag */ = (1 << 0),
    stress /*! Stress Test Execution flag */ = (1 << 1),
    performance /*! Performance Test Execution flag */ = (1 << 2),
    all_types = 0x7,
    all /*! Execute all test */ = static_cast<u32>(-1)
  };
};

API_OR_NAMED_FLAGS_OPERATOR(TestFlags, ExecuteFlags)

class Test : public api::ExecutionContext, public TestFlags {
  struct TestData {
    bool result = true;
    u32 duration_microseconds = {};
    var::DataInfo data_info;
  };
  static void deleter(TestData *test_data);
  api::SystemResource<TestData, decltype(&deleter)> m_test_data;

public:
  class Initialize {
    API_AC(Initialize, var::StringView, name);
    API_AC(Initialize, var::StringView, version);
    API_AC(Initialize, var::StringView, git_hash);
  };

private:
  class ScopeImplementation {
    static void deleter(void *);
    api::SystemResource<void *, decltype(&deleter)> m_deleter
      = {nullptr, &deleter};

  public:
    ScopeImplementation(const Initialize &options, printer::Printer *printer);
  };

public:
  template <class PrinterType> class Scope {
    PrinterType m_printer;
    ScopeImplementation m_scope_implementation;
  public:
    explicit Scope(const Initialize &options)
      : m_scope_implementation(options, &m_printer) {}
  };

  static ExecuteFlags parse_execution_flags(const sys::Cli &cli);
  static u32
  parse_test(const sys::Cli &cli, var::StringView name, u32 test_flag);

  explicit Test(var::StringView name);
  void execute(const sys::Cli &cli);
  void execute(ExecuteFlags execute_flags = ExecuteFlags::all) {
    if (execute_flags & ExecuteFlags::api) {
      execute_api_case();
    }
    if (execute_flags & ExecuteFlags::stress) {
      execute_stress_case();
    }
    if (execute_flags & ExecuteFlags::performance) {
      execute_performance_case();
    }
  }

  void execute_api_case();
  void execute_performance_case();
  void execute_stress_case();

  virtual bool execute_class_api_case();
  virtual bool execute_class_performance_case();
  virtual bool execute_class_stress_case();

  API_NO_DISCARD bool result() const { return m_test_data->result; }
  API_NO_DISCARD bool case_result() const { return m_case_result; }

  void set_case_failed();

  bool expect(const char *function, unsigned int line, bool value);

  API_NO_DISCARD static bool final_result();

  class TimedScope {
    struct TimedScopeData {
      Test *test;
      var::StringView name;
      u32 start;
      u32 minimum;
      u32 maximum;
    };
    static void deleter(TimedScopeData *test_scope);
    api::SystemResource<TimedScopeData, decltype(&deleter)> m_data;

  public:
    TimedScope(
      Test &test,
      var::StringView name,
      const chrono::MicroTime &minimum,
      const chrono::MicroTime &maximum);
  };

  static printer::Printer &printer();

protected:
  API_NO_DISCARD const chrono::ClockTimer &case_timer() const;
  chrono::ClockTimer &case_timer() { return m_case_timer; }
  static u32 get_score(u32 microseconds);
  var::StringView name() const { return m_name.cstring(); }

private:
  bool m_case_result = true;
  var::DataInfo m_case_data_info;
  chrono::ClockTimer m_case_timer;
  var::KeyString m_name;
  Test *m_parent = nullptr;

  friend class Case;
  void open_case(var::StringView case_name);
  void close_case();
};

} // namespace test

#endif // TESTAPI_TEST_HPP_
