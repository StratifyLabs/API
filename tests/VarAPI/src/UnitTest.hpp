
#include <cstdio>

#include "api/api.hpp"
#include "chrono.hpp"
#include "fs.hpp"
#include "printer.hpp"
#include "sys.hpp"
#include "test/Test.hpp"
#include "var.hpp"

using S = var::String;
using SV = var::StringView;
using D = var::Data;
using V = var::View;
using T = var::Tokenizer;

using B64 = var::Base64;

class UnitTest : public test::Test {
public:
  UnitTest(var::StringView name) : test::Test(name) {}

  bool execute_class_api_case() {
    if (!string_api_case()) {
      return false;
    }

    if (!string_view_api_case()) {
      return false;
    }

    if (!stack_string_api_case()) {
      return false;
    }

    if (!base64_api_case()) {
      return false;
    }

    if (!tokenizer_api_case()) {
      return false;
    }

    if (!view_api_case()) {
      return false;
    }

    if (!data_api_case()) {
      return false;
    }

    if (!vector_api_case()) {
      return false;
    }

    return true;
  }

  bool vector_api_case() {
    {
      Vector<StringView> list
        = Vector<StringView>().push_back("hello").push_back("world");

      TEST_ASSERT(list.find("hello", StringView()) == "hello");
      TEST_ASSERT(list.find("world", "") == "world");
      TEST_ASSERT(list.find("test", "") == "");
      TEST_ASSERT(list.find("go", "notempty") == "notempty");
    }

    return true;
  }

  bool stack_string_api_case() {

    {
      const char s0[] = "012345678901234567890123456789123456789";
      KeyString s(s0);
      PRINTER_TRACE(printer(), KeyString().format("length: %d", s.length()));
      TEST_ASSERT(strlen(s.cstring()) == sizeof(s0) - 1);
      TEST_ASSERT(strlen(KeyString(s0).cstring()) == sizeof(s0) - 1);

      TEST_ASSERT(KeyString("test") == "test");
      TEST_ASSERT(NumberString("test") == "test");
      TEST_ASSERT(GeneralString("test") == "test");
    }

    return true;
  }

  bool data_api_case() {

    printer().key("mininumSize", NumberString(Data::minimum_capacity()));
    printer().key("blockSize", NumberString(Data::minimum_capacity()));

    const Array<u32, 4> value_list(
      std::array<u32, 4>({0x11223344, 0x22334411, 0x33441122, 0x44332211}));

    Data data_list = Data().copy(View(value_list));

    TEST_ASSERT(View(data_list) == View(value_list));
    data_list.append(View(value_list));

    TEST_ASSERT(data_list.size() == View(value_list).size() * 2);

    String s = data_list.to_string();

    Data copy_list = Data::from_string(s);

    TEST_ASSERT(copy_list == data_list);

    const char a = 'a';
    copy_list.append(View(a));
    TEST_ASSERT(copy_list.size() == data_list.size() + 1);
    TEST_ASSERT(copy_list != data_list);

    return true;
  }

  bool view_api_case() {

    TEST_EXPECT(V().to_const_char() == nullptr);

    char buffer[32];

    View view_buffer(buffer);
    TEST_ASSERT(view_buffer.size() == sizeof(buffer));
    TEST_ASSERT(view_buffer.to_char() == buffer);
    TEST_ASSERT(view_buffer.is_read_only() == false);

    const char test[] = "test1234567890\n";
    View view_test(test);
    printer().key("view test size", NumberString(view_test.size()).string_view());
    printer().key("test size", NumberString(sizeof(test)).string_view());
    TEST_ASSERT(view_test.size() == sizeof(test) - 1);
    TEST_ASSERT(view_test.to_char() == nullptr);
    TEST_ASSERT(view_test.to_const_char() == test);
    TEST_ASSERT(view_test.is_read_only() == true);

    u32 value_u32 = 0x12345678;
    TEST_ASSERT(View(value_u32).size() == sizeof(value_u32));
    TEST_ASSERT(View(value_u32).to<u32>() == &value_u32);
    TEST_ASSERT(View(value_u32).is_read_only() == false);

    printer().key("value", View(value_u32).to_string());
    TEST_ASSERT(View(value_u32).to_string() == "78563412");

    {
      struct test_struct {
        u8 a;
        u8 b;
        u8 c;
        u8 d;
        u32 x;
        u32 y;
      };

      struct test_struct t;
      struct test_struct t0;
      View(t).fill<u8>(0xaa);
      View(t0).fill<u8>(0xbb);

      TEST_ASSERT(t.d == 0xaa);
      TEST_ASSERT(t.x == 0xaaaaaaaa);
      TEST_ASSERT(t.y == 0xaaaaaaaa);
      TEST_ASSERT(t0.y == 0xbbbbbbbb);

      TEST_ASSERT(View(t) != View(t0));
      View(t0).fill<u8>(0xaa);
      TEST_ASSERT(View(t) == View(t0));
    }

    {
      u32 first = 0x11223344;
      u32 second = 0;
      u16 third;
      TEST_ASSERT(View(second).size() == sizeof(second));
      View(second).copy(View(first));
      TEST_ASSERT(first == second);
      TEST_ASSERT(first == 0x11223344);
      View(third).copy(View(first));
      TEST_ASSERT(third == 0x3344);
    }

    {
      const Array<u32, 4> value_list(
        std::array<u32, 4>({0x11223344, 0x22334411, 0x33441122, 0x44332211}));

      u32 buffer[4];

      TEST_ASSERT(View(value_list).size() == value_list.count() * sizeof(u32));
      TEST_ASSERT(View(value_list).is_read_only());
      TEST_ASSERT(View(buffer).copy(View(value_list)).is_success());
      TEST_ASSERT(View(buffer) == View(value_list));

      TEST_ASSERT(View(buffer).pop_front(4).size() == sizeof(u32) * 3);
      TEST_ASSERT(View(buffer).pop_back(4).size() == sizeof(u32) * 3);
      TEST_ASSERT(View(buffer).pop_front(4).at<u32>(0) == 0x22334411);
    }

    return true;
  }

  bool tokenizer_api_case() {

    {
      T t("0,1,2", T::Construct().set_delimeters(","));
      TEST_EXPECT(t.count() == 3);
      TEST_EXPECT(t.at(0) == "0");
      TEST_EXPECT(t.at(1) == "1");
      TEST_EXPECT(t.at(2) == "2");
    }

    {
      T t(
        "0,'1,2'",
        T::Construct().set_delimeters(",").set_ignore_between("'"));
      TEST_ASSERT(t.count() == 2);
      TEST_EXPECT(t.at(0) == "0");
      TEST_EXPECT(t.at(1) == "'1,2'");
    }

    {
      T t(
        "0,\"1,2\"",
        T::Construct().set_delimeters(",").set_ignore_between("\""));
      TEST_ASSERT(t.count() == 2);
      TEST_EXPECT(t.at(0) == "0");
      TEST_EXPECT(t.at(1) == "\"1,2\"");
    }

    {
      T t(
        "0,1,2,3,4,5",
        T::Construct().set_delimeters(",").set_maximum_delimeter_count(2));
      TEST_EXPECT(t.count() == 3);
      TEST_EXPECT(t.at(0) == "0");
      TEST_EXPECT(t.at(1) == "1");
      TEST_EXPECT(t.at(2) == "2,3,4,5");
    }

    {
      T t(
        "0,'1,2,3',4,5",
        T::Construct()
          .set_delimeters(",")
          .set_maximum_delimeter_count(2)
          .set_ignore_between("'"));
      TEST_EXPECT(t.count() == 3);
      TEST_EXPECT(t.at(0) == "0");
      TEST_EXPECT(t.at(1) == "'1,2,3'");
      TEST_EXPECT(t.at(2) == "4,5");
    }

    {
      T t("0,1,,,2", T::Construct().set_delimeters(","));
      TEST_EXPECT(t.count() == 5);
      TEST_EXPECT(t.at(0) == "0");
      TEST_EXPECT(t.at(1) == "1");
      TEST_EXPECT(t.at(2) == "");
      TEST_EXPECT(t.at(3) == "");
      TEST_EXPECT(t.at(4) == "2");
    }

    {
      T t(
        "0,1,Testing'123'Testing,2",
        T::Construct().set_delimeters(",").set_ignore_between("'"));
      TEST_EXPECT(t.count() == 4);
      TEST_EXPECT(t.at(0) == "0");
      TEST_EXPECT(t.at(1) == "1");
      TEST_EXPECT(t.at(2) == "Testing'123'Testing");
      TEST_EXPECT(t.at(3) == "2");
    }

    {
      T t(
        "'0,1',Testing'123'Testing,2",
        T::Construct().set_delimeters(",").set_ignore_between("'"));
      TEST_EXPECT(t.count() == 3);
      TEST_EXPECT(t.at(0) == "'0,1'");
      TEST_EXPECT(t.at(1) == "Testing'123'Testing");
      TEST_EXPECT(t.at(2) == "2");
    }

    {
      T token("0,1,4,5,7,2,3", T::Construct().set_delimeters(","));
      TEST_ASSERT(token.count() == 7);
      TEST_ASSERT(token.at(0) == "0");
      TEST_ASSERT(token.at(6) == "3");
      TEST_ASSERT(token.at(7) == "");
      TEST_ASSERT(token.at(8) == "");
      TEST_ASSERT(token.at(100) == "");

      TEST_ASSERT(
        token.sort(T::SortBy::ascending).join(";") == "0;1;2;3;4;5;7");

      TEST_ASSERT(
        token.sort(T::SortBy::descending).join(".") == "7.5.4.3.2.1.0");
    }

    return true;
  }

  bool base64_api_case() {

    bool (*encode_test)(const char *, const char *)
      = [](const char *input, const char *output) {
          return (Base64().encode(SV(input)) == S(output));
        };

    printer().key("1", Base64().encode(StringView("1")));
    printer().key(".", Base64().encode(StringView(".")));
    printer().key("123.", Base64().encode(StringView("123.")));
    printer().key("ks).", Base64().encode(StringView("ks).")));

    TEST_EXPECT(encode_test("1", "MQ=="));
    TEST_ASSERT(encode_test(".", "Lg=="));
    TEST_EXPECT(encode_test("ab", "YWI="));
    TEST_EXPECT(encode_test("234", "MjM0"));
    TEST_EXPECT(encode_test("5678", "NTY3OA=="));
    TEST_EXPECT(encode_test("9abcd", "OWFiY2Q="));
    TEST_EXPECT(encode_test("efghij", "ZWZnaGlq"));
    TEST_EXPECT(encode_test("KLMNOPQ", "S0xNTk9QUQ=="));
    TEST_EXPECT(encode_test("rstuvwxy", "cnN0dXZ3eHk="));

    bool (*decode_test)(StringView, StringView)
      = [](StringView output, StringView input) {
          return (V(Base64().decode(input)) == V(output));
        };

    TEST_EXPECT(decode_test("1", "MQ=="));
    TEST_EXPECT(decode_test("ab", "YWI="));
    TEST_EXPECT(decode_test("234", "MjM0"));
    TEST_EXPECT(decode_test("5678", "NTY3OA=="));
    TEST_EXPECT(decode_test("9abcd", "OWFiY2Q="));
    TEST_EXPECT(decode_test("efghij", "ZWZnaGlq"));
    TEST_EXPECT(decode_test("KLMNOPQ", "S0xNTk9QUQ=="));
    TEST_EXPECT(decode_test("rstuvwxy", "cnN0dXZ3eHk="));

    const StringView test_input
      = "In computer science, Base64 is a group of binary-to-text encoding "
        "schemes that represent binary data in an ASCII string format by "
        "translating it into a radix-64 representation. The term Base64 "
        "originates from a specific MIME content transfer encoding. Each "
        "Base64 digit represents exactly 6 bits of data. Three 8-bit bytes "
        "(i.e., a total of 24 bits) can therefore be represented by four 6-bit "
        "Base64 digits. Common to all binary-to-text encoding schemes, Base64 "
        "is designed to carry data stored in binary formats across channels "
        "that only reliably support text content. Base64 is particularly "
        "prevalent on the World Wide Web[1] where its uses include the ability "
        "to embed image files or other binary assets inside textual assets "
        "such as HTML and CSS files.[2] Base64 is also widely used for sending "
        "e-mail attachments. This is required because SMTP in its original "
        "form was designed to transport 7 bit ASCII characters only. This "
        "encoding causes an overhead of 33–36% (33% by the encoding itself, up "
        "to 3% more by the inserted line breaks).";

    const StringView test_output
      = "SW4gY29tcHV0ZXIgc2NpZW5jZSwgQmFzZTY0IGlzIGEgZ3JvdXAgb2YgYmluYXJ5LXRvLX"
        "RleHQgZW5jb2Rpbmcgc2NoZW1lcyB0aGF0IHJlcHJlc2VudCBiaW5hcnkgZGF0YSBpbiBh"
        "biBBU0NJSSBzdHJpbmcgZm9ybWF0IGJ5IHRyYW5zbGF0aW5nIGl0IGludG8gYSByYWRpeC"
        "02NCByZXByZXNlbnRhdGlvbi4gVGhlIHRlcm0gQmFzZTY0IG9yaWdpbmF0ZXMgZnJvbSBh"
        "IHNwZWNpZmljIE1JTUUgY29udGVudCB0cmFuc2ZlciBlbmNvZGluZy4gRWFjaCBCYXNlNj"
        "QgZGlnaXQgcmVwcmVzZW50cyBleGFjdGx5IDYgYml0cyBvZiBkYXRhLiBUaHJlZSA4LWJp"
        "dCBieXRlcyAoaS5lLiwgYSB0b3RhbCBvZiAyNCBiaXRzKSBjYW4gdGhlcmVmb3JlIGJlIH"
        "JlcHJlc2VudGVkIGJ5IGZvdXIgNi1iaXQgQmFzZTY0IGRpZ2l0cy4gQ29tbW9uIHRvIGFs"
        "bCBiaW5hcnktdG8tdGV4dCBlbmNvZGluZyBzY2hlbWVzLCBCYXNlNjQgaXMgZGVzaWduZW"
        "QgdG8gY2FycnkgZGF0YSBzdG9yZWQgaW4gYmluYXJ5IGZvcm1hdHMgYWNyb3NzIGNoYW5u"
        "ZWxzIHRoYXQgb25seSByZWxpYWJseSBzdXBwb3J0IHRleHQgY29udGVudC4gQmFzZTY0IG"
        "lzIHBhcnRpY3VsYXJseSBwcmV2YWxlbnQgb24gdGhlIFdvcmxkIFdpZGUgV2ViWzFdIHdo"
        "ZXJlIGl0cyB1c2VzIGluY2x1ZGUgdGhlIGFiaWxpdHkgdG8gZW1iZWQgaW1hZ2UgZmlsZX"
        "Mgb3Igb3RoZXIgYmluYXJ5IGFzc2V0cyBpbnNpZGUgdGV4dHVhbCBhc3NldHMgc3VjaCBh"
        "cyBIVE1MIGFuZCBDU1MgZmlsZXMuWzJdIEJhc2U2NCBpcyBhbHNvIHdpZGVseSB1c2VkIG"
        "ZvciBzZW5kaW5nIGUtbWFpbCBhdHRhY2htZW50cy4gVGhpcyBpcyByZXF1aXJlZCBiZWNh"
        "dXNlIFNNVFAgaW4gaXRzIG9yaWdpbmFsIGZvcm0gd2FzIGRlc2lnbmVkIHRvIHRyYW5zcG"
        "9ydCA3IGJpdCBBU0NJSSBjaGFyYWN0ZXJzIG9ubHkuIFRoaXMgZW5jb2RpbmcgY2F1c2Vz"
        "IGFuIG92ZXJoZWFkIG9mIDMz4oCTMzYlICgzMyUgYnkgdGhlIGVuY29kaW5nIGl0c2VsZi"
        "wgdXAgdG8gMyUgbW9yZSBieSB0aGUgaW5zZXJ0ZWQgbGluZSBicmVha3MpLg==";

    // TEST_EXPECT(encode_test(test_input, test_output));
    TEST_EXPECT(decode_test(test_input, test_output));

    {

      TEST_ASSERT(
        DataFile()
          .write(
            ViewFile(V(test_output)),
            Base64Decoder(),
            DataFile::Write().set_page_size(32))
          .data()
          .add_null_terminator()
        == test_input);

      TEST_ASSERT(
        DataFile()
          .write(
            ViewFile(V(test_output)),
            Base64Decoder(),
            DataFile::Write().set_page_size(10))
          .data()
          .add_null_terminator()
        == test_input);

      TEST_ASSERT(
        DataFile()
          .write(
            ViewFile(V(test_output)),
            Base64Decoder(),
            DataFile::Write().set_page_size(20))
          .data()
          .add_null_terminator()
        == test_input);

      TEST_ASSERT(
        DataFile()
          .write(
            ViewFile(V(test_output)),
            Base64Decoder(),
            DataFile::Write().set_page_size(30))
          .data()
          .add_null_terminator()
        == test_input);

      TEST_ASSERT(
        DataFile()
          .write(
            ViewFile(V(test_output)),
            Base64Decoder(),
            DataFile::Write().set_page_size(40))
          .data()
          .add_null_terminator()
        == test_input);

      DataFile df;
      df.write(
        ViewFile(V(test_input)),
        Base64Encoder(),
        DataFile::Write().set_page_size(12));

      TEST_ASSERT(
        DataFile()
          .write(
            ViewFile(V(test_input)),
            Base64Encoder(),
            DataFile::Write().set_page_size(12))
          .data()
          .add_null_terminator()
        == test_output);

      TEST_ASSERT(
        DataFile()
          .write(
            ViewFile(V(test_input)),
            Base64Encoder(),
            DataFile::Write().set_page_size(30))
          .data()
          .add_null_terminator()
        == test_output);

      TEST_ASSERT(
        DataFile()
          .write(
            ViewFile(V(test_input)),
            Base64Encoder(),
            DataFile::Write().set_page_size(50))
          .data()
          .add_null_terminator()
        == test_output);

      TEST_ASSERT(
        DataFile()
          .write(
            ViewFile(V(test_input)),
            Base64Encoder(),
            DataFile::Write().set_page_size(60))
          .data()
          .add_null_terminator()
        == test_output);
    }

    return true;
  }

  bool string_view_api_case() {
    Printer::Object po(printer(), "StringView");
    {
      SV sv;
      TEST_EXPECT(sv.is_empty());
      TEST_EXPECT(!sv.is_null());
      TEST_EXPECT(sv.data() != nullptr);
    }

    {
      SV sv("");
      TEST_EXPECT(sv.is_empty());
      TEST_EXPECT(!sv.is_null());
      TEST_EXPECT(sv.data() != nullptr);
    }

    {
      SV sv("testing");
      TEST_EXPECT(!sv.is_empty());
      TEST_EXPECT(!sv.is_null());
      TEST_EXPECT(sv.is_null_terminated());
      TEST_EXPECT(sv.data() != nullptr);
      TEST_EXPECT(sv.data()[1] == 'e');
      TEST_EXPECT(sv == "testing");
      TEST_EXPECT(!(sv != "testing"));
      TEST_EXPECT(sv.front() == 't');
      TEST_EXPECT(sv.back() == 'g');
      TEST_EXPECT(sv.at(0) == 't');
      TEST_EXPECT(sv.at(1) == 'e');
      TEST_EXPECT(sv.at(2) == 's');
      TEST_EXPECT(sv.at(3) == 't');
      TEST_EXPECT(sv.at(4) == 'i');
      TEST_EXPECT(sv.at(5) == 'n');
      TEST_EXPECT(sv.at(6) == 'g');
      TEST_EXPECT(sv.length() == (sizeof("testing") - 1));

      TEST_EXPECT(sv.get_substring_at_position(2) == "sting");
      TEST_EXPECT(sv.get_substring_with_length(4) == "test");
      TEST_EXPECT(
        sv.get_substring_with_length(4).is_null_terminated() == false);

      {
        const StringView s0("test0");
        TEST_ASSERT(
          s0.get_substring(SV::GetSubstring().set_position(0).set_length(2))
          == "te");

        TEST_ASSERT(
          s0(SV::GetSubstring().set_position(0).set_length(2)) == "te");

        TEST_ASSERT(s0.get_substring_at_position(2) == "st0");
        TEST_ASSERT(s0.get_substring_at_position(100) == "");
        TEST_ASSERT(s0.get_substring_with_length(0) == "");
        TEST_ASSERT(s0.get_substring_with_length(0) == StringView());
        TEST_ASSERT(s0.get_substring_with_length(100) == "test0");
      }

      TEST_EXPECT(sv.find('e') == 1);
      TEST_EXPECT(sv.find('x') == SV::npos);
      TEST_EXPECT(sv.reverse_find('e') == 1);
      TEST_EXPECT(sv.reverse_find('x') == SV::npos);

      TEST_EXPECT(sv.find("e") == 1);
      TEST_EXPECT(sv.find("x") == SV::npos);
      TEST_EXPECT(sv.reverse_find("e") == 1);
      TEST_EXPECT(sv.reverse_find("x") == SV::npos);
      TEST_EXPECT(sv.find_first_of("abcde") == 1);
      TEST_EXPECT(sv.find_first_of("wxyz") == SV::npos);
      TEST_EXPECT(sv.find_first_not_of("abcde") == 0);
      TEST_EXPECT(sv.find_first_not_of("test") == 4);

#if RUN_NOT_PASSING
      TEST_EXPECT(sv.find_last_of("rst") == 3);
      TEST_EXPECT(sv.find_last_not_of("in") == 6);
#endif

      TEST_EXPECT(
        sv.get_substring(SV::GetSubstring().set_position(2).set_length(3))
        == "sti");

      size_t i = 0;
      for (auto c : sv) {
        TEST_EXPECT(c == sv.at(i++));
      }

      TEST_EXPECT(sv.to_long() == 0);

      TEST_EXPECT(sv.pop_front(4) == "ing");
    }

    {
      SV sv("105");
      TEST_EXPECT(sv.to_long() == 105);
      TEST_EXPECT(sv.to_unsigned_long() == 105);
      TEST_EXPECT(sv.to_long(SV::Base::decimal) == 105);
      TEST_EXPECT(sv.to_unsigned_long(SV::Base::decimal) == 105);
    }

    {
      SV sv("-500");
      TEST_EXPECT(sv.to_long() == -500);
    }

    {
      SV sv("0.456");
      TEST_EXPECT(sv.to_float() == 0.456f);
    }

    {
      SV sv("1E6");
      TEST_EXPECT(sv.to_float() == 1E6f);
    }

    {
      SV sv("123E-3");
      TEST_EXPECT(sv.to_float() == 123E-3f);
    }

    {
      SV sv("0666");
      TEST_EXPECT(sv.to_long(SV::Base::octal) == 0666);
      TEST_EXPECT(sv.to_unsigned_long(SV::Base::octal) == 0666);
    }

    {
      SV sv("abcd");
      TEST_EXPECT(sv.to_long(SV::Base::hexadecimal) == 0xabcd);
      TEST_EXPECT(sv.to_unsigned_long(SV::Base::hexadecimal) == 0xabcd);
    }

    {
      SV sv;
      TEST_EXPECT(sv.is_empty());
      TEST_EXPECT(!sv.is_null());
      sv.set_null();
      TEST_EXPECT(sv.is_empty());
      TEST_EXPECT(sv.is_null());
      TEST_EXPECT(SV().set_null().is_null());
    }

    {
      SV test("testing");
      SV test2("testing");
      SV test3("test");
      TEST_ASSERT(test == test2);
      TEST_ASSERT(test != test3);
      TEST_ASSERT(test.at(0) == 't');
      TEST_ASSERT(test.at(1) == 'e');
      TEST_ASSERT(test.at(2) == 's');
      TEST_ASSERT(test.at(3) == 't');
    }

    {
      TEST_ASSERT(StringView(NumberString(10)) == "10");
      TEST_ASSERT(StringView(NumberString(100)) == "100");
      TEST_ASSERT(StringView(NumberString(50UL)) == "50");
      TEST_ASSERT(StringView(NumberString(-50)) == "-50");
      TEST_ASSERT(StringView(NumberString(1.2f)) == "1.200000");
      TEST_ASSERT(StringView(NumberString(-1.2f)) == "-1.200000");
      TEST_ASSERT(StringView(NumberString(-1.2f, "%0.2f")) == "-1.20");
    }

    {
      StringViewList list = StringView("1,2,3,4").split(",");
      TEST_ASSERT(list.count() == 4);
    }

    return true;
  }

  bool string_api_case() {
    {
      S s("construct");
      TEST_EXPECT(s == "construct");
    }

    {
      const String value("3");
      TEST_EXPECT(SV("1") + String("2") == String("12"));
      TEST_EXPECT("1" + String("2") == String("12"));
      TEST_EXPECT(value == "3");
      TEST_EXPECT(SV("1") + value == String("13"));
    }

    {
      char buffer[8];
      View(buffer).fill('a');
      TEST_EXPECT(String(View(buffer)) == "aaaaaaaa");

      Data data_buffer(api::ApiInfo::malloc_chunk_size() * 2);

      View(data_buffer).fill('b');

      TEST_EXPECT(var::String().format("%c.%c", buffer[0], buffer[1]) == "a.a");
      TEST_EXPECT(
        var::String().format("%s", String(View(data_buffer)).cstring())
        == String(View(data_buffer)));
    }
    {
      S s("1,2,3,4,5");
      TEST_ASSERT(s.erase(S::Erase().set_length(1)) == ",2,3,4,5");
      TEST_ASSERT(
        s.erase(S::Erase().set_position(1).set_length(1)) == ",,3,4,5");
      S all("all");
      TEST_ASSERT(all.erase(S::Erase().set_length(500)).is_empty());
    }

    {
      S s("testing,1,2,3,4");
      TEST_ASSERT(
        s.replace(S::Replace().set_old_string(",").set_new_string(";"))
        == "testing;1;2;3;4");
    }

    {
      S s("testing,1,2,3,4");
      TEST_ASSERT(
        s.replace(
          S::Replace().set_old_string(",").set_new_string(";").set_count(1))
        == "testing;1,2,3,4");
    }

    {
      S s("testing,1,2,3,4");
      TEST_ASSERT(
        s.replace(
          S::Replace().set_old_string(",").set_new_string(";").set_position(8))
        == "testing,1;2;3;4");
    }

    {
      S s("testing,1,2,3,4");
      TEST_ASSERT(
        s.replace(S::Replace()
                    .set_old_string(",")
                    .set_new_string(";")
                    .set_position(8)
                    .set_count(2))
        == "testing,1;2;3,4");
    }

    {
      S s("testing,1,2,3,4");
      TEST_ASSERT(s.erase("testing") == ",1,2,3,4");
      TEST_ASSERT(s.erase("2,3") == ",1,,4");
      TEST_ASSERT(s.erase("5") == ",1,,4");
    }

    {
      S s("testing");
      TEST_ASSERT(String(s).to_upper() == "TESTING");
      TEST_ASSERT(String(s).to_upper().to_lower() == s);
    }

    {
      S s("1,2,3,4,5,6,7");
      TEST_ASSERT(s.count(",") == 6);
      TEST_ASSERT(s.count("1") == 1);
      TEST_ASSERT(s.count("1,2") == 1);
      TEST_ASSERT(s.count("A") == 0);
    }

    {
      const String s0("test0");
      S s = S("test");
      TEST_ASSERT(s == "test");
      TEST_ASSERT((s = s0) == "test0");
    }

    {
      const String less("abcd");
      const String greater("efgh");
      const String greater_equal("efgh");
      TEST_ASSERT(less < greater);
      TEST_ASSERT(less <= greater);
      TEST_ASSERT(greater > less);
      TEST_ASSERT(greater >= less);
      TEST_ASSERT(!(less > greater));
      TEST_ASSERT(!(greater < less));
      TEST_ASSERT(greater <= greater_equal);
      TEST_ASSERT(greater >= greater_equal);
    }

    {
      StringViewList string_view_list = {"test", "test1", "test2"};
      StringList string_list = string_view_list.convert(StringView::get_string);
      for (u32 i = 0; i < string_view_list.count(); i++) {
        TEST_ASSERT(string_list.at(i) == string_view_list.at(i));
      }
    }

    TEST_ASSERT(String().is_empty());

    return true;
  }

private:
  const void *m_original_context = nullptr;
};
