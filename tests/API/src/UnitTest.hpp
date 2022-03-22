
#include <cstdio>

#include "api/api.hpp"
#include "chrono.hpp"
#include "printer.hpp"
#include "sys.hpp"
#include "test/Test.hpp"
#include "thread.hpp"
#include "var.hpp"

class UnitTest : public test::Test {
public:
  UnitTest(var::StringView name) : test::Test(name) {}

  bool execute_class_api_case() {
    TEST_ASSERT_RESULT(markdown_printer_test());
    TEST_ASSERT_RESULT(api_case());
    return true;
  }

  bool markdown_printer_test() {
    MarkdownPrinter md;
    {
      MarkdownPrinter::Header h(md, "Header");

      {
        MarkdownPrinter::Code c(md, "c++");
        md << StringView("int main(int argc, char * argv[]){");
        md << MarkdownPrinter::Directive::insert_newline;
        md << StringView("  printf(\"HelloWorld\\n\")");
        md << MarkdownPrinter::Directive::insert_newline;
        md << StringView("  return 0;");
        md << MarkdownPrinter::Directive::insert_newline;
        md << StringView("}");
        md << MarkdownPrinter::Directive::insert_newline;
      }
    }

    return true;
  }

  bool api_case() {

    TEST_ASSERT(error().signature() == static_cast<const void *>(&(errno)));

    {
      api::ErrorScope error_scope;
      errno = EINVAL;
      const int line_error = __LINE__ + 1;
      API_SYSTEM_CALL("message", -1);
      printer().object("error", error());

      TEST_ASSERT(error().error_number() == EINVAL);
      TEST_ASSERT(error().line_number() == line_error);
      TEST_ASSERT(StringView(error().message()) == "message");
      TEST_ASSERT(return_value() < 0);
      API_RESET_ERROR();
    }

    TEST_ASSERT(return_value() == 0);
    TEST_ASSERT(context_count() == 1);

    printer().key("signature", String().format("%p", error().signature()));

    void *thread_error_signature;
    // create a thread and make sure it's error context is independent
    Thread t(
      Thread::Attributes().set_detach_state(Thread::DetachState::joinable),
      Thread::Construct().set_argument(this).set_function(
        [](void *args) -> void * {
          Test *self = reinterpret_cast<Test *>(args);
          self->printer().key(
            "threadSignature",
            String().format("%p", error().signature()));
          const int line_error = __LINE__ + 1;
          API_SYSTEM_CALL("threadmessage", -1);

          TEST_SELF_EXPECT(error().line_number() == line_error);
          TEST_SELF_EXPECT(StringView(error().message()) == "threadmessage");

          return error().signature();
        }));
    t.join(&thread_error_signature);

    printer().key("signature", String().format("%p", error().signature()));
    printer().key(
      "thread signature",
      String().format("%p", thread_error_signature));

    TEST_ASSERT(context_count() == 2);

    auto print_progress = [this]() {
      {
        Printer::Object po(printer(), "progress");

        printer().set_progress_key("progressing");
        for (u32 i = 0; i < 50; i++) {
          wait(5_milliseconds);
          printer().progress_callback()->update(i + 1, 50);
        }
        printer().progress_callback()->update(0, 0);
      }

      {
        Printer::Object po(printer(), "spin");
        printer().set_progress_key("spinning");
        for (u32 i = 0; i < 10; i++) {
          wait(10_milliseconds);
          printer().progress_callback()->update(
            i + 1,
            api::ProgressCallback::indeterminate_progress_total());
        }
        printer().progress_callback()->update(0, 0);
      }
    };

    print_progress();
    printer().enable_flags(Printer::Flags::simple_progress);
    print_progress();
    printer().disable_flags(Printer::Flags::simple_progress);
    print_progress();

    TEST_ASSERT(is_success());

    {
      const u16 last = 200;
      int value = 0;
      for(auto i: api::Index(last)) {
        TEST_ASSERT(sizeof(i) == sizeof(u16));
        value+=i;
      }
      printer().key("indexValueU16", NumberString(value));
    }

    {
      const size_t last = 200;
      int value = 0;
      for(auto i: api::Index(last)) {
        TEST_ASSERT(sizeof(i) == sizeof(size_t));
        value+=i;
      }
      printer().key("indexValueSize", NumberString(value));
    }

    {
      const u16 first = 50;
      const u16 last = 200;
      int value = 0;
      for(auto i: api::Range(first, last)) {
        TEST_ASSERT(sizeof(i) == sizeof(u16));
        value+=i;
      }
      printer().key("rangeValueU16", NumberString(value));
    }

    {
      const size_t first = 50;
      const size_t last = 200;
      int value = 0;
      for(auto i: api::Range(first,last)) {
        TEST_ASSERT(sizeof(i) == sizeof(size_t));
        value+=i;
      }
      printer().key("rangeValueSize", NumberString(value));
    }

    return true;
  }

private:
  const void *m_original_context = nullptr;
};
