// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#include "test/Test.hpp"
#include "printer/Printer.hpp"
#include "sys/System.hpp"
#include "test/Case.hpp"

using namespace var;
using namespace test;
using namespace printer;

namespace {
unsigned final_duration_microseconds = {};
bool is_final_result = true;
DataInfo final_data_info = {};
Printer * test_printer = nullptr;
} // namespace

Test::ScopeImplementation::ScopeImplementation(
  const Test::Initialize &options,
  printer::Printer *printer_instance) {
  test_printer = printer_instance;

  final_duration_microseconds = 0;

  {
    Printer::Object pg(printer(), "system");
    printer().key("operatingSystem", sys::System::operating_system_name());
    printer().key("processor", sys::System::processor());
  }

  {
    Printer::Object pg(printer(), "test");
    printer().key("name", options.name());
    printer().key("version", options.version());
    printer().key("gitHash", options.git_hash());
    printer().key("apiVersion", var::StringView(api::ApiInfo::version()));
    printer().key("apiGitHash", var::StringView(api::ApiInfo::git_hash()));
  }

  final_data_info = var::DataInfo();
}

void Test::ScopeImplementation::deleter(void *) {
  Printer::Object pg(printer(), "finalResult");
  printer().key_bool("result", is_final_result);
  printer().key(
    "finalResult",
    is_final_result ? StringView("___finalResultPass___")
                    : StringView("___finalResultFail___"));
  printer().key(
    "microseconds",
    NumberString(final_duration_microseconds).string_view());
  printer().key_bool("memoryLeak", final_data_info == var::DataInfo());
  printer().key(
    "score",
    NumberString(get_score(final_duration_microseconds)).string_view());
}

Printer &Test::printer() {
  return *test_printer;
}


Test::Test(var::StringView name) : m_name(name) {
  API_ASSERT(test_printer);
  printer().open_object(name);
}


void Test::deleter(Test::TestData *test_data) {
  Printer::Object pg(printer(), "testResult");
  printer().key_bool("result", test_data->result);
  printer().key(
    "score",
    NumberString(get_score(test_data->duration_microseconds)));
  printer().key(
    "microseconds",
    NumberString(test_data->duration_microseconds));
  printer().key_bool(
    "memoryLeak",
    test_data->data_info == var::DataInfo());
  printer().close_object();
  final_duration_microseconds += test_data->duration_microseconds;
}

u32 Test::get_score(u32 microseconds) {
  constexpr u32 baseline_microseconds = 1000000000UL;
  if (microseconds == 0) {
    microseconds = 1;
  }
  return baseline_microseconds / microseconds;
}

void Test::execute(const sys::Cli &cli) {
  ExecuteFlags o_flags = ExecuteFlags::null;

  if (cli.get_option("api") == "true") {
    o_flags |= ExecuteFlags::api;
  }
  if (cli.get_option("stress") == "true") {
    o_flags |= ExecuteFlags::stress;
  }
  if (cli.get_option("performance") == "true") {
    o_flags |= ExecuteFlags::performance;
  }

  if (cli.get_option("all") == "true") {
    o_flags |= ExecuteFlags::all;
  }

  if (o_flags == ExecuteFlags::null) {
    o_flags = ExecuteFlags::api;
  }

  execute(o_flags);
}

void Test::open_case(var::StringView case_name) {
  printer().open_object(case_name);
  m_case_result = true;
  m_case_data_info = DataInfo();
  m_case_timer.restart();
}

void Test::close_case() {
  m_case_timer.stop();
  {
    printer::Printer::Object po(printer(), "caseResult");
    m_test_data->duration_microseconds += m_case_timer.micro_time().microseconds();
    printer()
      .key_bool("result", m_case_result)
      .key(
        "score",
        NumberString(get_score(m_case_timer.micro_time().microseconds()))
          .string_view())
      .key(
        "microseconds",
        NumberString(m_case_timer.micro_time().microseconds()).string_view())
      .key_bool("memoryLeak", m_case_data_info == var::DataInfo());
  }
  printer().close_object();
  m_case_result = true;
}


Test::ExecuteFlags Test::parse_execution_flags(const sys::Cli &cli) {
  ExecuteFlags o_execute_flags = ExecuteFlags::null;

  bool is_all = false;

  if (
    cli.get_option(
      "all",
      "execute all tests and types (if no type "
      "(api|stress|performance|additional) is specified")
    == "true") {
    is_all = true;
  }

  if (
    cli.get_option(
      "allTypes",
      "execute all test types (api|stress|performance|additional)")
    == "true") {
    o_execute_flags |= ExecuteFlags::all_types;
  }

  if (cli.get_option("api", "execute api tests") == "true") {
    o_execute_flags |= ExecuteFlags::api;
  }

  if (cli.get_option("performance", "execute performance tests") == "true") {
    o_execute_flags |= ExecuteFlags::performance;
  }

  if (cli.get_option("stress", "execute stress test") == "true") {
    o_execute_flags |= ExecuteFlags::stress;
  }

  if (is_all) {
    if (o_execute_flags == ExecuteFlags::null) {
      o_execute_flags = ExecuteFlags::all;
    } else {
      o_execute_flags |= ~(ExecuteFlags::all_types);
    }
  }

  return o_execute_flags;
}

u32 Test::parse_test(const sys::Cli &cli, var::StringView name, u32 test_flag) {

  const var::GeneralString help = "Execute the " | name | " test suite";
  if (cli.get_option(name, help) == "true") {
    return test_flag;
  }

  return 0;
}


void Test::execute_api_case() {
  Case cg(this, "api");
  execute_class_api_case();
}

void Test::execute_performance_case() {
  Case cg(this, "performance");
  execute_class_performance_case();
}

void Test::execute_stress_case() {
  Case cg(this, "stress");
  execute_class_stress_case();
}

bool Test::execute_class_api_case() {
  printer().key("api", "no test");
  return true;
}

bool Test::execute_class_performance_case() {
  printer().key("performance", "no test");
  return true;
}

bool Test::execute_class_stress_case() {
  printer().key("stress", "no test");
  return true;
}
void Test::set_case_failed() {
  m_case_result = false;
  m_test_data->result = false;
  is_final_result = false;
}

bool Test::final_result() { return is_final_result; }
bool Test::expect(const char *function, unsigned int line, bool value) {
  if (value) {
    return true;
  }

  printer().key(
    var::String().format("expect%d", line),
    var::String().format("%s failed", function));

  if (is_error()) {
    printer().object("errorContext", api::ExecutionContext::error());
  }

  printer().error(var::String().format("test failed"));
  set_case_failed();
  return false;
}
const chrono::ClockTimer &Test::case_timer() const {
  return m_case_timer;
}

void Test::TimedScope::deleter(Test::TimedScope::TimedScopeData *test_scope) {
  const auto stop = test_scope->test->case_timer().milliseconds();
  const auto duration = stop - test_scope->start;
  printer()
    .key("minimum (ms)", var::NumberString(test_scope->minimum))
    .key("maximum (ms)", var::NumberString(test_scope->maximum))
    .key("duration (ms)", var::NumberString(duration));
  if (duration < test_scope->minimum) {
    printer().error("duration below minimum");
    test_scope->test->set_case_failed();
  } else if (duration > test_scope->maximum) {
    printer().error("duration above maximum");
    test_scope->test->set_case_failed();
  }
  printer().close_object();
}

Test::TimedScope::TimedScope(
  Test &test,
  const var::StringView name,
  const chrono::MicroTime &minimum,
  const chrono::MicroTime &maximum)
  : m_data(
    {.test = &test,
     .name = name,
     .start = test.case_timer().milliseconds(),
     .minimum = minimum.milliseconds(),
     .maximum = maximum.milliseconds()},
    &deleter) {
  printer().open_object(name);
  API_ASSERT(minimum < maximum);
}
