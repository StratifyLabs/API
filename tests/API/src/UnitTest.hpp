
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

    errno = EINVAL;
    const int line_error = __LINE__ + 1;
    API_SYSTEM_CALL("message", -1);

    printer().object("error", error());

    TEST_ASSERT(error().error_number() == EINVAL);
    TEST_ASSERT(error().line_number() == line_error);
    TEST_ASSERT(StringView(error().message()) == "message");
    TEST_ASSERT(return_value() < 0);
    API_RESET_ERROR();

    TEST_ASSERT(return_value() == 0);
    TEST_ASSERT(context_count() == 1);

    printer().key("signature", String().format("%p", error().signature()));

    void *thread_error_signature;
    // create a thread and make sure it's error context is independent
    Thread t(
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
        }),
      Thread::Attributes().set_detach_state(Thread::DetachState::joinable));
    t.join(&thread_error_signature);

    printer().key("signature", String().format("%p", error().signature()));
    printer().key(
      "thread signature",
      String().format("%p", thread_error_signature));

    printer().key("message", StringView(error().message()));
    TEST_ASSERT(StringView(error().message()) == "message");
    TEST_ASSERT(context_count() == 2);

    auto print_progress = [this]() {
      {
        Printer::Object po(printer(), "progress");

        printer().set_progress_key("progressing");
        for (u32 i = 0; i < 50; i++) {
          wait(25_milliseconds);
          printer().progress_callback()->update(i + 1, 50);
        }
        printer().progress_callback()->update(0, 0);
      }

      {
        Printer::Object po(printer(), "spin");
        printer().set_progress_key("spinning");
        for (u32 i = 0; i < 10; i++) {
          wait(50_milliseconds);
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

    return true;
  }

private:
  const void *m_original_context = nullptr;
};
