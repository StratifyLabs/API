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
public:
  class Initialize {
    API_AC(Initialize, var::StringView, name);
    API_AC(Initialize, var::StringView, version);
    API_AC(Initialize, var::StringView, git_hash);
    API_AF(Initialize, printer::Printer *, printer, nullptr);
  };

  static void initialize(const Initialize &options);
  static void finalize();

  class Scope {
  public:
    explicit Scope(const Initialize &options) { initialize(options); }
    ~Scope() { finalize(); }
  };

  static ExecuteFlags parse_execution_flags(const sys::Cli &cli);
  static u32 parse_test(const sys::Cli &cli, var::StringView name,
                        u32 test_flag);

  explicit Test(var::StringView name);
  ~Test();

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

  API_NO_DISCARD bool result() const { return m_test_result; }
  API_NO_DISCARD bool case_result() const { return m_case_result; }

  void set_case_failed() {
    m_case_result = false;
    m_test_result = false;
    m_final_result = false;
  }

  API_NO_DISCARD bool expect(const char *function, unsigned int line, bool value) {
    if (value) {
      return true;
    }

    printer().key(var::String().format("expect%d", line),
                  var::String().format("%s failed", function));

    if (is_error()) {
      printer().object("errorContext", api::ExecutionContext::error());
    }

    printer().error(var::String().format("test failed"));
    set_case_failed();
    return false;
  }

  API_NO_DISCARD static bool final_result() { return m_final_result; }

  class TimedScope {
  public:
    TimedScope(Test &test, const var::StringView name,
               const chrono::MicroTime &minimum,
               const chrono::MicroTime &maximum)
        : m_test(test), m_name(name), m_start(test.case_timer().milliseconds()),
          m_minimum(minimum.milliseconds()), m_maximum(maximum.milliseconds()) {
      m_test.printer().open_object(name);
      API_ASSERT(m_minimum < m_maximum);
    }

    ~TimedScope() {
      const auto stop = m_test.case_timer().milliseconds();
      const auto duration = stop - m_start;
      m_test.printer()
          .key("minimum (ms)", var::NumberString(m_minimum))
          .key("maximum (ms)", var::NumberString(m_maximum))
          .key("duration (ms)", var::NumberString(duration));
      if (duration < m_minimum) {
        m_test.printer().error("duration below minimum");
        m_test.set_case_failed();
      } else if (duration > m_maximum) {
        m_test.printer().error("duration above maximum");
        m_test.set_case_failed();
      }
      m_test.printer().close_object();
    }

  private:
    Test &m_test;
    var::StringView m_name;
    u32 m_start;
    u32 m_minimum;
    u32 m_maximum;
  };

protected:
  API_NO_DISCARD const chrono::ClockTimer &case_timer() const { return m_case_timer; }
  chrono::ClockTimer &case_timer() { return m_case_timer; }

  static u32 get_score(u32 microseconds);

  var::StringView name() const { return m_name.cstring(); }

  static printer::Printer &printer() { return *m_printer; }

private:
  bool m_test_result = true;
  bool m_case_result = true;
  var::DataInfo m_case_data_info;
  var::DataInfo m_test_data_info;
  chrono::ClockTimer m_case_timer;
  u32 m_test_duration_microseconds;
  var::KeyString m_name;
  Test *m_parent = nullptr;

  static var::DataInfo m_final_data_info;
  static bool m_final_result;
  static u32 m_final_duration_microseconds;
  static printer::Printer *m_printer;

  friend class Case;
  void open_case(var::StringView case_name);
  void close_case();
};

} // namespace test

#endif // TESTAPI_TEST_HPP_
