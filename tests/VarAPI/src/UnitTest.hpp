
#include <cstdio>

#include "api/api.hpp"
#include "chrono.hpp"
#include "fs.hpp"
#include "printer.hpp"
#include "sys.hpp"
#include "test/Test.hpp"
#include "var.hpp"

#include "var/MagicEnum.hpp"

#if defined __link
#define BIG_BUFFER_SIZE 10 * 1024 * 1024
#else
#define BIG_BUFFER_SIZE 1024
#endif

using S = var::String;
using SV = var::StringView;
using D = var::Data;
using V = var::View;
using T = var::Tokenizer;

using B64 = var::Base64;

class UnitTest : public test::Test {

  template <typename Container>
  bool container_test(void (*initialize)(Container &container) = nullptr) {
    {
      Container data;
      if (initialize) {
        initialize(data);
      }
      data.populate_by_incrementing(1);
      const auto sum = data.accumulate(0);
      printer().key("sum", NumberString(sum));
      u32 sum2 = 0;
      for (const auto value : data) {
        sum2 += value;
      }
      printer().key("sum2", NumberString(sum2));
      TEST_ASSERT(sum == sum2);
      for (auto i : api::Index(data.count())) {
        TEST_ASSERT(data.at(i) == i + 1);
      }
      printer().key("minimum", NumberString(data.get_minimum()));
      printer().key("maximum", NumberString(data.get_maximum()));
      TEST_EXPECT(data.get_minimum() == 1);
      TEST_EXPECT(data.get_maximum() == data.count());
    }

    {
      Container data;
      if (initialize) {
        initialize(data);
      }
      data.fill(4);
      for (const auto &value : data) {
        TEST_ASSERT(value == 4);
      }
      for (auto i : api::Index(data.count())) {
        TEST_ASSERT(data.at(i) == 4);
      }
    }

    {
      Container data0;
      if (initialize) {
        initialize(data0);
      }
      Container data1;
      if (initialize) {
        initialize(data1);
      }
      data0.populate_by_incrementing(0);
      data1.populate_by_incrementing(0);
      for (const auto &value : data0) {
        printer().key("data0", NumberString(value));
      }
      for (const auto &value : data0) {
        printer().key("data1", NumberString(value));
      }
      const auto is_equal_true = data0 == data1;
      const auto is_not_equal_false = data0 != data1;
      printer().key_bool("== (true?)", is_equal_true);
      printer().key_bool("!= (false?)", is_not_equal_false);
      TEST_ASSERT(is_equal_true);
      TEST_ASSERT(!(is_not_equal_false));
      data0.populate_by_incrementing(5);
      for (const auto &value : data0) {
        printer().key("data0", NumberString(value));
      }
      const auto is_equal_false = data0 == data1;
      const auto is_not_equal_true = data0 != data1;
      printer().key_bool("== (false?)", is_equal_false);
      printer().key_bool("!= (true?)", is_not_equal_true);
      TEST_ASSERT(!(is_equal_false));
      TEST_ASSERT(is_not_equal_true);
    }

    return true;
  }

public:
  UnitTest(var::StringView name) : test::Test(name) {}

  bool execute_class_api_case() {

    TEST_ASSERT_RESULT(set_api_case());
    TEST_ASSERT_RESULT(magic_enum_api_case());
    TEST_ASSERT_RESULT(array_api_case());
    TEST_ASSERT_RESULT(vector_api_case());
    TEST_ASSERT_RESULT(string_api_case());
    TEST_ASSERT_RESULT(string_view_api_case());
    TEST_ASSERT_RESULT(stack_string_api_case());
    TEST_ASSERT_RESULT(base64_api_case());
    TEST_ASSERT_RESULT(tokenizer_api_case());
    TEST_ASSERT_RESULT(view_api_case());
    TEST_ASSERT_RESULT(data_api_case());
    return true;
  }

  bool set_api_case() {

    {
      OrderedSet<int> set;
      set.insert(7)
        .insert(0)
        .insert(3)
        .insert(2)
        .insert(6)
        .insert(4)
        .insert(5)
        .insert(1);

      int check_value{};
      for (const auto value : set) {
        TEST_ASSERT(value == check_value);
        ++check_value;
      }
    }

    {
      UnorderedSet<int> set;
      set.insert(7)
        .insert(0)
        .insert(3)
        .insert(2)
        .insert(6)
        .insert(4)
        .insert(5)
        .insert(1);

      TEST_ASSERT(set.lookup(0) != set.end());
      TEST_ASSERT(set.lookup(1) != set.end());
      TEST_ASSERT(set.lookup(2) != set.end());
      TEST_ASSERT(set.lookup(3) != set.end());
      TEST_ASSERT(set.lookup(4) != set.end());
      TEST_ASSERT(set.lookup(5) != set.end());
      TEST_ASSERT(set.lookup(6) != set.end());
      TEST_ASSERT(set.lookup(7) != set.end());
      TEST_ASSERT(set.lookup(8) == set.end());
    }

    {
      UnorderedMultiset<int> set;
      set.insert(7)
        .insert(0)
        .insert(3)
        .insert(2)
        .insert(6)
        .insert(4)
        .insert(5)
        .insert(1);
    }

    return true;
  }

  bool magic_enum_api_case() {
    enum class X { x0, x1, x2, x3, x4, x5 };
    using MagicX = MagicEnum<X>;
    Printer::Object object(printer(), "magicEnumApiCase");

    TEST_ASSERT(MagicX::to_string_view(X::x0).is_null_terminated());
    TEST_ASSERT(MagicX::to_string_view(X::x1).is_null_terminated());
    TEST_ASSERT(MagicX::to_string_view(X::x2).is_null_terminated());
    TEST_ASSERT(MagicX::to_string_view(X::x3).is_null_terminated());
    TEST_ASSERT(MagicX::to_string_view(X::x4).is_null_terminated());
    TEST_ASSERT(MagicX::to_string_view(X::x5).is_null_terminated());

    TEST_ASSERT(MagicX::to_string_view(X::x0) == "x0");
    TEST_ASSERT(MagicX::to_string_view(X::x1) == "x1");
    TEST_ASSERT(MagicX::to_string_view(X::x2) == "x2");
    TEST_ASSERT(MagicX::to_string_view(X::x3) == "x3");
    TEST_ASSERT(MagicX::to_string_view(X::x4) == "x4");
    TEST_ASSERT(MagicX::to_string_view(X::x5) == "x5");

    TEST_ASSERT(MagicX::from_cstring("x0").value() == X::x0);
    TEST_ASSERT(MagicX::from_cstring("x1").value() == X::x1);
    TEST_ASSERT(MagicX::from_cstring("x2").value() == X::x2);
    TEST_ASSERT(MagicX::from_cstring("x3").value() == X::x3);
    TEST_ASSERT(MagicX::from_cstring("x4").value() == X::x4);
    TEST_ASSERT(MagicX::from_cstring("x5").value() == X::x5);
    TEST_ASSERT(!MagicX::from_cstring("x6").has_value());

    TEST_ASSERT(MagicX::from_string("x0").value() == X::x0);
    TEST_ASSERT(MagicX::from_string("x1").value() == X::x1);
    TEST_ASSERT(MagicX::from_string("x2").value() == X::x2);
    TEST_ASSERT(MagicX::from_string("x3").value() == X::x3);
    TEST_ASSERT(MagicX::from_string("x4").value() == X::x4);
    TEST_ASSERT(MagicX::from_string("x5").value() == X::x5);
    TEST_ASSERT(!MagicX::from_string("x6").has_value());

    int count = 0;
    for (const auto value : MagicX::list()) {
      const auto sv = MagicX::to_string_view(value);
      printer().key(NumberString(count), sv);
      ++count;
    }

    return true;
  }

  bool array_api_case() {
    Printer::Object array_object(printer(), "arrayApiCase");
    {
      using Container = Array<int, 4>;
      TEST_ASSERT(container_test<Container>());
    }

    return true;
  }

  bool vector_api_case() {
    Printer::Object array_object(printer(), "vectorApiCase");

    {
      auto list
        = Vector<StringView>().reserve(2).push_back("hello").push_back("world");

      TEST_ASSERT(list.find("hello") == "hello");
      TEST_ASSERT(list.find("world") == "world");
      TEST_ASSERT(list.find("test") == "");
      TEST_ASSERT(list.find("go") != "go");
      TEST_ASSERT(list.find("go") != "notempty");
      TEST_ASSERT(list.emplace_back("go") == "go");
    }

    {
      using Container = Vector<int>;
      TEST_ASSERT(container_test<Container>([](Container &a) { a.resize(4); }));
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

    String s = data_list.view().to_string<String>();
    GeneralString gs = data_list.view().to_string<GeneralString>();

    Data copy_list = Data::from_string(s);

    TEST_ASSERT(copy_list == data_list);

    const char a = 'a';
    copy_list.append(View(a));
    TEST_ASSERT(copy_list.size() == data_list.size() + 1);
    TEST_ASSERT(copy_list != data_list);

    return true;
  }

  bool view_api_case() {
    Printer::Object po(printer(), "View");

    TEST_EXPECT(V().to_const_char() == nullptr);

    char buffer[32];

    View view_buffer(buffer);
    TEST_ASSERT(view_buffer.size() == sizeof(buffer));
    TEST_ASSERT(view_buffer.to_char() == buffer);

    const char test[] = "test1234567890\n";
    View view_test(test);
    printer().key(
      "view test size",
      NumberString(view_test.size()).string_view());
    printer().key("test size", NumberString(sizeof(test)).string_view());
    TEST_ASSERT(view_test.size() == sizeof(test) - 1);
    TEST_ASSERT(view_test.to_char() == test);
    TEST_ASSERT(view_test.to_const_char() == test);

    u32 value_u32 = 0x12345678;
    TEST_ASSERT(View(value_u32).size() == sizeof(value_u32));
    TEST_ASSERT(View(value_u32).to<u32>() == &value_u32);

    printer().key("value", View(value_u32).to_string<String>());
    TEST_ASSERT(View(value_u32).to_string<NumberString>() == "78563412");

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

      Data source(BIG_BUFFER_SIZE);
      Data dest(BIG_BUFFER_SIZE);
      TEST_ASSERT(View(source).size() == BIG_BUFFER_SIZE);
      TEST_ASSERT(View(source).size() == BIG_BUFFER_SIZE);
      View(source).fill(0);
      View(dest).fill<u32>(0xaaaa5555);
      {
        ClockTimer ct(ClockTimer::IsRunning::yes);
        PerformanceScope ps("memcpyCharBuffer", ct, printer());
        memcpy(dest.data(), source.data(), BIG_BUFFER_SIZE);
      }
      TEST_ASSERT(View(source) == View(dest));
      View(dest).fill<u32>(0xaaaa5555);
      TEST_ASSERT(View(source) != View(dest));
      {
        ClockTimer ct(ClockTimer::IsRunning::yes);
        PerformanceScope ps("viewCopy", ct, printer());
        View(dest).copy(View(source));
      }
      {
        ClockTimer ct(ClockTimer::IsRunning::yes);
        PerformanceScope ps("viewCompare", ct, printer());
        TEST_ASSERT(View(source) == View(dest));
      }
      {
        ClockTimer ct(ClockTimer::IsRunning::yes);
        PerformanceScope ps("fill8", ct, printer());
        View(dest).fill<u8>(0x00);
      }
      TEST_ASSERT(View(source) == View(dest));
      {
        ClockTimer ct(ClockTimer::IsRunning::yes);
        PerformanceScope ps("fill16", ct, printer());
        View(dest).fill<u16>(0x00);
      }
      TEST_ASSERT(View(source) == View(dest));
      {
        ClockTimer ct(ClockTimer::IsRunning::yes);
        PerformanceScope ps("fill32", ct, printer());
        View(dest).fill<u32>(0x00);
      }
      TEST_ASSERT(View(source) == View(dest));
      {
        ClockTimer ct(ClockTimer::IsRunning::yes);
        PerformanceScope ps("fill64", ct, printer());
        View(dest).fill<u64>(0x00);
      }
      TEST_ASSERT(View(source) == View(dest));
    }

    {
      const Array<u32, 4> value_list(
        std::array<u32, 4>({0x11223344, 0x22334411, 0x33441122, 0x44332211}));

      u32 buffer[4];

      TEST_ASSERT(View(value_list).size() == value_list.count() * sizeof(u32));
      TEST_ASSERT(View(buffer).copy(View(value_list)).is_success());
      TEST_ASSERT(View(buffer) == View(value_list));

      TEST_ASSERT(View(buffer).pop_front(4).size() == sizeof(u32) * 3);
      TEST_ASSERT(View(buffer).pop_back(4).size() == sizeof(u32) * 3);
      TEST_ASSERT(View(buffer).pop_front(4).at<u32>(0) == 0x22334411);
    }

    {
      const Array<u32, 4> value_list = std::array<u32, 4>{0, 1, 2, 3};

      {
        View view(value_list);
        while (view.pop_back().size() > 0) {
          ;
        }
      }

      {
        View view(value_list);
        while (view.pop_front().size() > 0) {
          ;
        }
      }
    }

    printer().key("complete", __FUNCTION__);
    return true;
  }

  bool tokenizer_api_case() {
    Printer::Object po(printer(), "Tokenizer");

    {
      T t("0,1,2", T::Construct().set_delimiters(","));
      TEST_EXPECT(t.count() == 3);
      TEST_EXPECT(t.at(0) == "0");
      TEST_EXPECT(t.at(1) == "1");
      TEST_EXPECT(t.at(2) == "2");
    }

    {
      T t(
        "0,'1,2'",
        T::Construct().set_delimiters(",").set_ignore_between("'"));
      TEST_ASSERT(t.count() == 2);
      TEST_EXPECT(t.at(0) == "0");
      TEST_EXPECT(t.at(1) == "'1,2'");
    }

    {
      T t(
        "0,\"1,2\"",
        T::Construct().set_delimiters(",").set_ignore_between("\""));
      TEST_ASSERT(t.count() == 2);
      TEST_ASSERT(t.at(0) == "0");
      TEST_ASSERT(t.at(1) == "\"1,2\"");
    }

    {
      T t(
        "0,1,2,3,4,5",
        T::Construct().set_delimiters(",").set_maximum_delimiter_count(2));
      TEST_ASSERT(t.count() == 3);
      TEST_ASSERT(t.at(0) == "0");
      TEST_ASSERT(t.at(1) == "1");
      TEST_ASSERT(t.at(2) == "2,3,4,5");
    }

    {
      T t(
        "0,'1,2,3',4,5",
        T::Construct()
          .set_delimiters(",")
          .set_maximum_delimiter_count(2)
          .set_ignore_between("'"));
      TEST_ASSERT(t.count() == 3);
      TEST_ASSERT(t.at(0) == "0");
      printf("value: %s\n", String{t.at(1)}.cstring());
      TEST_ASSERT(t.at(1) == "'1,2,3'");
      TEST_ASSERT(t.at(2) == "4,5");
    }
    {
      T t(
        "0,{1,2,3},4,5",
        T::Construct()
          .set_delimiters(",")
          .set_maximum_delimiter_count(2)
          .set_ignore_between("{"));
      TEST_ASSERT(t.count() == 3);
      TEST_ASSERT(t.at(0) == "0");
      TEST_ASSERT(t.at(1) == "{1,2,3}");
      TEST_ASSERT(t.at(2) == "4,5");
    }
    {
      T t(
        "0,(1,2,3),4,5",
        T::Construct()
          .set_delimiters(",")
          .set_maximum_delimiter_count(2)
          .set_ignore_between("("));
      TEST_ASSERT(t.count() == 3);
      TEST_ASSERT(t.at(0) == "0");
      TEST_ASSERT(t.at(1) == "(1,2,3)");
      TEST_ASSERT(t.at(2) == "4,5");
    }

    {
      T t(
        "0,[1,2,3],4,5",
        T::Construct()
          .set_delimiters(",")
          .set_maximum_delimiter_count(2)
          .set_ignore_between("["));
      TEST_ASSERT(t.count() == 3);
      TEST_ASSERT(t.at(0) == "0");
      TEST_ASSERT(t.at(1) == "[1,2,3]");
      TEST_ASSERT(t.at(2) == "4,5");
    }

    {
      T t(
        "0,[1,[2],3],[4,[5]]",
        T::Construct()
          .set_delimiters(",")
          .set_maximum_delimiter_count(2)
          .set_ignore_between("["));
      TEST_ASSERT(t.count() == 3);
      TEST_ASSERT(t.at(0) == "0");
      TEST_ASSERT(t.at(1) == "[1,[2],3]");
      TEST_ASSERT(t.at(2) == "[4,[5]]");
    }

    {
      T t(
        "1,{2,5},{{3,10,12}},${test ${this ${that 1,2,3}}",
        T::Construct().set_delimiters(",").set_ignore_between("{"));
      TEST_ASSERT(t.count() == 4);
      TEST_ASSERT(t.at(0) == "1");
      TEST_ASSERT(t.at(1) == "{2,5}");
      TEST_ASSERT(t.at(2) == "{{3,10,12}}");
      TEST_ASSERT(t.at(3) == "${test ${this ${that 1,2,3}}");
    }

    {
      auto t = T(
        "0,<1,(2),3>,4,<<5>>",
        T::Construct()
          .set_delimiters(",")
          .set_maximum_delimiter_count(2)
          .set_ignore_between("<"));
      TEST_ASSERT(t.count() == 3);
      TEST_ASSERT(t.at(0) == "0");
      TEST_ASSERT(t.at(1) == "<1,(2),3>");
      TEST_ASSERT(t.at(2) == "4,<<5>>");
    }

    {
      T t("0,1,,,2", T::Construct().set_delimiters(","));
      TEST_ASSERT(t.count() == 5);
      TEST_ASSERT(t.at(0) == "0");
      TEST_ASSERT(t.at(1) == "1");
      TEST_ASSERT(t.at(2) == "");
      TEST_ASSERT(t.at(3) == "");
      TEST_ASSERT(t.at(4) == "2");
    }

    {
      T t(
        "0,1,Testing'123'Testing,2",
        T::Construct().set_delimiters(",").set_ignore_between("'"));
      TEST_ASSERT(t.count() == 4);
      TEST_ASSERT(t.at(0) == "0");
      TEST_ASSERT(t.at(1) == "1");
      TEST_ASSERT(t.at(2) == "Testing'123'Testing");
      TEST_ASSERT(t.at(3) == "2");
    }

    {
      T t(
        "'0,1',Testing'123'Testing,2",
        T::Construct().set_delimiters(",").set_ignore_between("'"));
      TEST_ASSERT(t.count() == 3);
      TEST_ASSERT(t.at(0) == "'0,1'");
      TEST_ASSERT(t.at(1) == "Testing'123'Testing");
      TEST_ASSERT(t.at(2) == "2");
    }

    {
      T t(
        "mkdir /home/test && ninja build",
        T::Construct().set_delimiters("&&").set_delimiter_type(
          Tokenizer::DelimiterType::string));
      TEST_ASSERT(t.count() == 2);
      TEST_ASSERT(t.at(0) == "mkdir /home/test ");
      TEST_ASSERT(t.at(1) == " ninja build");
    }

    {
      T t(
        "mkdir /home/test' && 'ninja build",
        T::Construct()
          .set_delimiters("&&")
          .set_delimiter_type(Tokenizer::DelimiterType::string)
          .set_ignore_between("'"));
      TEST_ASSERT(t.count() == 1);
      TEST_ASSERT(t.at(0) == "mkdir /home/test' && 'ninja build");
    }

    {
      T t(
        "mkdir '/home/test' && \"ninja build\"",
        T::Construct()
          .set_delimiters("&&")
          .set_delimiter_type(Tokenizer::DelimiterType::string)
          .set_ignore_between("'"));
      TEST_ASSERT(t.count() == 2);
      TEST_ASSERT(t.at(0) == "mkdir '/home/test' ");
      TEST_ASSERT(t.at(1) == " \"ninja build\"");
    }

    {
      T token("0,1,4,5,7,2,3", T::Construct().set_delimiters(","));
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

    printer().key("complete", __FUNCTION__);
    return true;
  }

  bool base64_api_case() {
    Printer::Object po(printer(), "Base64");

    auto encode_test = [](const char *input, const char *output) {
      return (Base64().encode(SV(input)) == S(output));
    };

    TEST_ASSERT(encode_test("1", "MQ=="));
    TEST_ASSERT(encode_test(".", "Lg=="));
    TEST_ASSERT(encode_test("ab", "YWI="));
    TEST_ASSERT(encode_test("234", "MjM0"));
    TEST_ASSERT(encode_test("5678", "NTY3OA=="));
    TEST_ASSERT(encode_test("9abcd", "OWFiY2Q="));
    TEST_ASSERT(encode_test("efghij", "ZWZnaGlq"));
    TEST_ASSERT(encode_test("KLMNOPQ", "S0xNTk9QUQ=="));
    TEST_ASSERT(encode_test("rstuvwxy", "cnN0dXZ3eHk="));

    auto decode_test = [](StringView output, StringView input) {
      return (V(Base64().decode(input)) == V(output));
    };

    TEST_ASSERT(decode_test("1", "MQ=="));
    TEST_ASSERT(decode_test("ab", "YWI="));
    TEST_ASSERT(decode_test("234", "MjM0"));
    TEST_ASSERT(decode_test("5678", "NTY3OA=="));
    TEST_ASSERT(decode_test("9abcd", "OWFiY2Q="));
    TEST_ASSERT(decode_test("efghij", "ZWZnaGlq"));
    TEST_ASSERT(decode_test("KLMNOPQ", "S0xNTk9QUQ=="));
    TEST_ASSERT(decode_test("rstuvwxy", "cnN0dXZ3eHk="));

    auto valid_test = [](StringView input) { return Base64().is_valid(input); };

    TEST_EXPECT(valid_test("MQ=="));
    TEST_EXPECT(valid_test("YWI="));
    TEST_EXPECT(valid_test("MjM0"));
    TEST_EXPECT(valid_test("NTY3OA=="));
    TEST_EXPECT(valid_test("OWFiY2Q="));
    TEST_EXPECT(valid_test("ZWZnaGlq"));
    TEST_EXPECT(valid_test("S0xNTk9QUQ=="));
    TEST_EXPECT(valid_test("cnN0dXZ3eHk="));
    TEST_EXPECT(valid_test("cnN0dXZ3eHk="));

    TEST_EXPECT(!valid_test("(Q=="));
    TEST_EXPECT(!valid_test("Q=="));
    TEST_EXPECT(!valid_test("ABQ=="));
    TEST_EXPECT(!valid_test("YI=)"));
    TEST_EXPECT(!valid_test("YWI==="));
    TEST_EXPECT(!valid_test("cnN0dX|Z3H="));

    static constexpr StringView test_input
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

    static constexpr StringView test_output
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

    TEST_ASSERT(Base64().is_valid(test_output));

    // TEST_EXPECT(encode_test(test_input, test_output));
    TEST_EXPECT(decode_test(test_input, test_output));

    {
      printer().key("transform", "decoder0");
      TEST_ASSERT(
        DataFile()
          .write(
            ViewFile(V(test_output)),
            Base64Decoder(),
            DataFile::Write().set_page_size(32))
          .data()
          .add_null_terminator()
        == test_input);

      printer().key("transform", "decoder1");
      TEST_ASSERT(
        DataFile()
          .write(
            ViewFile(V(test_output)),
            Base64Decoder(),
            DataFile::Write().set_page_size(10))
          .data()
          .add_null_terminator()
        == test_input);

      printer().key("transform", "decoder2");
      TEST_ASSERT(
        DataFile()
          .write(
            ViewFile(V(test_output)),
            Base64Decoder(),
            DataFile::Write().set_page_size(20))
          .data()
          .add_null_terminator()
        == test_input);

      printer().key("transform", "decoder3");
      TEST_ASSERT(
        DataFile()
          .write(
            ViewFile(V(test_output)),
            Base64Decoder(),
            DataFile::Write().set_page_size(30))
          .data()
          .add_null_terminator()
        == test_input);

      printer().key("transform", "decoder4");
      TEST_ASSERT(
        DataFile()
          .write(
            ViewFile(V(test_output)),
            Base64Decoder(),
            DataFile::Write().set_page_size(40))
          .data()
          .add_null_terminator()
        == test_input);

      printer().key("transform", "encoder0");
      DataFile df;
      df.write(
        ViewFile(V(test_input)),
        Base64Encoder(),
        DataFile::Write().set_page_size(12));

      printer().key("transform", "encoder1");
      TEST_ASSERT(
        DataFile()
          .write(
            ViewFile(V(test_input)),
            Base64Encoder(),
            DataFile::Write().set_page_size(12))
          .data()
          .add_null_terminator()
        == test_output);

      printer().key("transform", "encoder2");
      TEST_ASSERT(
        DataFile()
          .write(
            ViewFile(V(test_input)),
            Base64Encoder(),
            DataFile::Write().set_page_size(30))
          .data()
          .add_null_terminator()
        == test_output);

      printer().key("transform", "encoder3");
      TEST_ASSERT(
        DataFile()
          .write(
            ViewFile(V(test_input)),
            Base64Encoder(),
            DataFile::Write().set_page_size(50))
          .data()
          .add_null_terminator()
        == test_output);

      printer().key("transform", "encoder4");
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

    printer().key("complete", __FUNCTION__);
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
      Printer::Object get_encapsulated_object(printer(), "getEncapsulated");
      SV sv("${test ${wildcard 1,${this}}}");
      const auto encapsulated = sv.get_encapsulated("${");
      printer().key("encapsulated", encapsulated);
      TEST_ASSERT(encapsulated == "test ${wildcard 1,${this}}");
      const auto encapsulated2 = encapsulated.get_encapsulated("${");
      printer().key("encapsulated2", encapsulated2);
      TEST_ASSERT(encapsulated2 == "wildcard 1,${this}");
      const auto encapsulated3 = encapsulated2.get_encapsulated("${");
      printer().key("encapsulated3", encapsulated3);
      TEST_ASSERT(encapsulated3 == "this");
    }

    {
      Printer::Object pop_encapsulated_object(printer(), "popEncapsulated");
      SV sv("${test1}${test2}${test3}");
      const auto pop_encapsulated1 = sv.pop_encapsulated("${");
      printer().key("pop_encapsulated1", pop_encapsulated1);
      TEST_ASSERT(pop_encapsulated1 == "${test2}${test3}");
      const auto pop_encapsulated2
        = StringView{pop_encapsulated1}.pop_encapsulated("${");
      printer().key("pop_encapsulated2", pop_encapsulated2);
      TEST_ASSERT(pop_encapsulated2 == "${test3}");
      const auto pop_encapsulated3
        = StringView{pop_encapsulated2}.pop_encapsulated("${");
      printer().key("pop_encapsulated3", pop_encapsulated3);
      TEST_ASSERT(!pop_encapsulated3);
    }

    {
      SV sv("testing");
      TEST_ASSERT(!sv.is_empty());
      TEST_ASSERT(bool{sv});
      TEST_ASSERT(!sv.is_null());
      TEST_ASSERT(sv.is_null_terminated());
      TEST_ASSERT(sv.data() != nullptr);
      TEST_ASSERT(sv.data()[1] == 'e');
      TEST_ASSERT(sv == "testing");
      TEST_ASSERT(!(sv != "testing"));
      TEST_ASSERT(sv.front() == 't');
      TEST_ASSERT(sv.back() == 'g');
      TEST_ASSERT(sv.at(0) == 't');
      TEST_ASSERT(sv.at(1) == 'e');
      TEST_ASSERT(sv.at(2) == 's');
      TEST_ASSERT(sv.at(3) == 't');
      TEST_ASSERT(sv.at(4) == 'i');
      TEST_ASSERT(sv.at(5) == 'n');
      TEST_ASSERT(sv.at(6) == 'g');
      TEST_ASSERT(sv.length() == (sizeof("testing") - 1));

      TEST_ASSERT(sv.get_substring_at_position(2) == "sting");
      TEST_ASSERT(sv.get_substring_with_length(4) == "test");
      TEST_ASSERT(
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
        TEST_ASSERT(s0.contains("test"));
        TEST_ASSERT(!s0.contains("ti"));
        TEST_ASSERT(s0.contains("st"));
        TEST_ASSERT(!s0.contains_any_of("abcdf"));
        TEST_ASSERT(s0.contains_any_of("abcdef"));
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

      TEST_ASSERT(sv.find_last_of("rst") == 3);
      TEST_ASSERT(sv.find_last_not_of("in") == 6);

      TEST_EXPECT(
        sv.get_substring(SV::GetSubstring().set_position(2).set_length(3))
        == "sti");

      size_t i = 0;
      for (auto c : sv) {
        TEST_EXPECT(c == sv.at(i++));
      }

      {
        static constexpr StringView sv = "\t This is a test";
        TEST_ASSERT(sv.find_first_not_of(StringView::whitespace()) == 2);
        TEST_ASSERT(
          StringView{sv}.strip_leading_whitespace() == "This is a test");
      }

      {
        static constexpr StringView sv = "This is a test   \t\t";
        TEST_ASSERT(sv.find_last_not_of(StringView::whitespace()) == 13);
        TEST_ASSERT(
          StringView{sv}.strip_trailing_whitespace() == "This is a test");
      }

      {
        static constexpr StringView sv = "     \t This is a test   \t\t";
        TEST_ASSERT(
          StringView{sv}.strip_leading_whitespace().strip_trailing_whitespace()
          == "This is a test");
      }

      TEST_EXPECT(sv.to_long() == 0);

      TEST_EXPECT(
        StringView("0x08000000").to_unsigned_long(SV::Base::auto_)
        == 0x08000000);
      TEST_EXPECT(
        StringView("8000000").to_unsigned_long(SV::Base::auto_) == 8000000);
      TEST_EXPECT(StringView("0777").to_unsigned_long(SV::Base::auto_) == 0777);

      TEST_EXPECT(sv.pop_front(4) == "ing");

      const auto value = StringView{"This is a test"};
      TEST_EXPECT(StringView{value}.pop_front(5).pop_back(5) == "is a");
      TEST_EXPECT(StringView{value}.pop_front(5).truncate(4) == "is a");
      TEST_EXPECT(StringView{value}.truncate(4) == "This");
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
      const auto value = StringView{"Hello World"};
      TEST_ASSERT(value.starts_with("Hello"));
      TEST_ASSERT(value.ends_with("World"));
      TEST_ASSERT(!value.starts_with("hello"));
      TEST_ASSERT(!value.ends_with("hello"));
    }

    {
      const auto list = StringView("1,2,3,4").split(",");
      TEST_ASSERT(list.count() == 4);
    }

    printer().key("complete", __FUNCTION__);
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
      Printer::Object replace_characters(printer(), "replaceCharacters");
      auto s
        = S("   testing, 1, 2, \t3, \t\t4")(S::Replace()
                                              .set_old_string(SV::whitespace())
                                              .set_new_string("")
                                              .set_character_wise(true));
      printer().key("replaced", s);
      TEST_ASSERT(s == "testing,1,2,3,4");
    }

    {
      Printer::Object replace_characters(printer(), "removeWhitespace");
      auto s = std::move(S("   testing, 1, 2, \t3, \t\t4").remove_whitespace());
      printer().key("replaced", s);
      TEST_ASSERT(s == "testing,1,2,3,4");
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
      StringList string_list = string_view_list.convert(StringView::to_string);
      for (u32 i = 0; i < string_view_list.count(); i++) {
        TEST_ASSERT(string_list.at(i) == string_view_list.at(i));
      }
    }

    TEST_ASSERT(String().is_empty());

    printer().key("complete", __FUNCTION__);
    return true;
  }

private:
  const void *m_original_context = nullptr;
};
