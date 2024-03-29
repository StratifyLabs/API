﻿
#include <cstdio>

#include "fs.hpp"
#include "sys/System.hpp"
#include "sys/TemporaryDirectory.hpp"
#include "test/Test.hpp"
#include "var/Base64.hpp"

using namespace printer;
using namespace var;
using namespace sys;

#if defined __link
#define HOME_FOLDER "."
#else
#define HOME_FOLDER "/home"
#endif

class UnitTest : public test::Test {

public:
  using FS = FileSystem;
  using F = File;
  using D = Dir;
  using DF = fs::DataFile;

  explicit UnitTest(var::StringView name) : test::Test(name) {}

  bool execute_class_api_case() override {

    TEST_ASSERT_RESULT(file_api_case());
    TEST_ASSERT_RESULT(file_system_api_case());
    TEST_ASSERT_RESULT(dir_api_case());
    TEST_ASSERT_RESULT(fileinfo_api_case());
    TEST_ASSERT_RESULT(view_file_api_case());
    TEST_ASSERT_RESULT(data_file_api_case());
    TEST_ASSERT_RESULT(transformer_api_case());

    return true;
  }

  bool transformer_api_case() {
    Printer::Object po(printer(), __FUNCTION__);
    static constexpr auto test_string_list = {
      "The fox ran through the hollow",
      "This is another string",
      "1234",
      "0",
      "0123456789012345678901234567890123456789012345678901234567890123456789"
      "0123456789",
      ""};
    for (const auto &test_string : test_string_list) {
      printer().key("testing", test_string);
      const auto encoded_data = Base64().encode(test_string);
      TemporaryDirectory temporary_directory;

      const auto base64_path = temporary_directory.path() / "base64.txt";
      File(File::IsOverwrite::yes, base64_path)
        .write(ViewFile(test_string), Base64Encoder());

      {
        const auto contents = DataFile(File(base64_path));
        TEST_ASSERT(View(contents.data()) == View(encoded_data));
      }
      {
        auto contents = DataFile();
        contents.write(File(base64_path), Base64Decoder());
        TEST_ASSERT(View(contents.data()) == View(test_string));
      }
    }

    return true;
  }

  bool data_file_api_case() {
    Printer::Object po(printer(), __FUNCTION__);
    const StringView contents
      = "0123456789012345678901234567890123456789012345678901234567890123456789"
        "0123456789";

    TEST_ASSERT(DataFile().write(contents).return_value() == contents.length());

    {
      DataFile df(OpenMode::read_write());
      df.seek(0).data().resize(contents.length());
      Data buffer(contents.length() + 4);

      TEST_ASSERT(df.read(buffer).return_value() == contents.length());
      df.seek(0);
      buffer.resize(7);
      while (df.read(buffer).return_value() > 0) {
        int result = return_value();
        printer().key(
          "read",
          NumberString().format("%d of %d", result, df.size()));
      }
    }

    printer().key("complete", __FUNCTION__);
    return true;
  }

  bool view_file_api_case() {
    Printer::Object po(printer(), __FUNCTION__);

    const StringView contents
      = "0123456789012345678901234567890123456789012345678901234567890123456789"
        "0123456789";

    u32 value;

    TEST_ASSERT(
      ViewFile(View(value)).write(contents).return_value() == sizeof(u32));

    printer().key("complete", __FUNCTION__);
    return true;
  }

  bool fileinfo_api_case() {
    printer::Printer::Object po(printer(), "fileinfo");
    var::PathString temp_path;
    {
      TemporaryDirectory td(HOME_FOLDER);
      printer().key("tempPath", td.path());
      TEST_ASSERT(FS().directory_exists(td.path()));

      const StringView new_test_contents = "new test file";

      temp_path = td.path();
      TEST_ASSERT(F(F::IsOverwrite::yes,
                    td.path() + "/test.txt",
                    OpenMode::read_write(),
                    Permissions(0664))
                    .write(new_test_contents)
                    .is_success());

      TEST_ASSERT(FS().get_info(td.path()).is_directory());
      TEST_ASSERT(FS().get_info(td.path()).is_file() == false);
      TEST_ASSERT(FS().get_info(td.path()).is_device() == false);
      TEST_ASSERT(FS().get_info(td.path()).is_block_device() == false);
      TEST_ASSERT(FS().get_info(td.path()).is_character_device() == false);
      TEST_ASSERT(FS().get_info(td.path()).is_socket() == false);
      TEST_ASSERT(FS().get_info(td.path()).is_device() == false);

      FileInfo file_info = FS().get_info(td.path() + "/test.txt");
      TEST_ASSERT(file_info.is_directory() == false);

#if !defined __win32 && !defined __StratifyOS__
      TEST_ASSERT(file_info.permissions().is_owner_execute() == false);
      TEST_ASSERT(file_info.permissions().is_owner_read() == true);
      TEST_ASSERT(file_info.permissions().is_owner_write() == true);

      TEST_ASSERT(file_info.permissions().is_public_execute() == false);
      TEST_ASSERT(file_info.permissions().is_public_read() == true);
      TEST_ASSERT(file_info.permissions().is_public_write() == false);
#endif

      printer().object("file", file_info);

      TEST_ASSERT(
        FS().get_info(td.path() + "/test.txt").size()
        == new_test_contents.length());
    }

    TEST_ASSERT(FS().directory_exists(temp_path) == false);

    TEST_ASSERT(is_success());
    printer().key("complete", __FUNCTION__);
    return true;
  }

  bool dir_api_case() {
    Printer::Object po(printer(), __FUNCTION__);

    FS().remove_directory(HOME_FOLDER "/tmp", FS::IsRecursive::yes);
    reset_error();
    FS().remove_directory(HOME_FOLDER "/tmp2", FS::IsRecursive::yes);
    reset_error();

    TEST_ASSERT(FS().create_directory(HOME_FOLDER "/tmp").is_success());
    TEST_ASSERT(F(F::IsOverwrite::yes, HOME_FOLDER "/tmp/test0.txt")
                  .write("test0\n")
                  .is_success());
    TEST_ASSERT(F(F::IsOverwrite::yes, HOME_FOLDER "/tmp/test1.txt")
                  .write("test1\n")
                  .is_success());
    TEST_ASSERT(F(F::IsOverwrite::yes, HOME_FOLDER "/tmp/test2.txt")
                  .write("test2\n")
                  .is_success());
    TEST_ASSERT(FS().create_directory(HOME_FOLDER "/tmp2").is_success());
    TEST_ASSERT(F(F::IsOverwrite::yes, HOME_FOLDER "/tmp2/test0.txt")
                  .write("test0\n")
                  .is_success());
    TEST_ASSERT(F(F::IsOverwrite::yes, HOME_FOLDER "/tmp2/filesystem.txt")
                  .write("test1\n")
                  .is_success());
    TEST_ASSERT(F(F::IsOverwrite::yes, HOME_FOLDER "/tmp2/test2.txt")
                  .write("test2\n")
                  .is_success());

    TEST_ASSERT(D(HOME_FOLDER "/tmp").is_success());

    {
      // check that the compiler can move Dir
      const auto d = [] { return D(HOME_FOLDER "/tmp"); }();
      d.read();
    }

    {
      Vector<var::PathString> dir_list
        = FS().read_directory(HOME_FOLDER "/tmp");
      printer().object("list", dir_list);
      TEST_ASSERT(dir_list.count() == 3);
    }

    {
      D d(HOME_FOLDER "/tmp");
      auto count = 0;
      var::PathString e;
      while ((e = d.get_entry()).string_view() && count < 10) {
        printer().key("tell", NumberString(d.tell()));
        printer().key(NumberString(count), e);
        ++count;
      }
#if defined __link
      // add two for . and ..
      TEST_ASSERT(count == 5);
#if !defined __win32
      TEST_EXPECT(d.tell() == (count - 1));
#endif
#else
      TEST_ASSERT(count == 3);
#endif
#if !defined __win32
      TEST_EXPECT(d.seek(0).is_success());
      TEST_ASSERT(d.rewind().is_success());
      // const auto entry = d.get_entry();
#if defined __link
      // TEST_ASSERT(d.get_entry() == "tmp/.");
#endif

      TEST_ASSERT(d.rewind().is_success());
      if (!System().is_macosx()) {
        printer().key("tell", NumberString(d.tell()).string_view());
        TEST_ASSERT(d.tell() == 0);
      }
#endif
    }

    {
      TEST_ASSERT(is_success());
      TEST_ASSERT(FS().directory_exists(HOME_FOLDER "/tmp"));
      PRINTER_TRACE(printer(), "read directory " HOME_FOLDER "/tmp");
      const auto list
        = FS().read_directory(HOME_FOLDER "/tmp", FS::IsRecursive::yes);
      TEST_ASSERT(is_success());
      printer().object("tmpFiles", list);

      TEST_ASSERT(list.find("test0.txt") == "test0.txt");
      TEST_ASSERT(list.find("test1.txt") == "test1.txt");
      TEST_ASSERT(list.find("test2.txt") == "test2.txt");
    }

    {
      Printer::Object tmp2_object(printer(), "readDirectory");
      TEST_ASSERT(FS().directory_exists(HOME_FOLDER "/tmp2"));
      const auto list = FS().read_directory(
        HOME_FOLDER "/tmp2",
        FS::IsRecursive::yes,
        [](StringView entry) {
          return FS::IsExclude(entry.find("filesystem") != StringView::npos);
        });
      TEST_ASSERT(list.find("test0.txt") == "test0.txt");
      TEST_ASSERT(list.find("filesystem.txt") == "");
      TEST_ASSERT(list.find("test2.txt") == "test2.txt");
    }

    {
      PathList list
        = FS().read_directory(HOME_FOLDER "/tmp", FS::IsRecursive::no);
      printer().object("files", list);
      TEST_ASSERT(
        list.find(var::PathString("test0.txt"))
        == var::PathString("test0.txt"));
      TEST_ASSERT(
        list.find(var::PathString("test1.txt"))
        == var::PathString("test1.txt"));
      TEST_ASSERT(
        list.find(var::PathString("test2.txt"))
        == var::PathString("test2.txt"));
    }

    TEST_ASSERT(FS()
                  .remove_directory(HOME_FOLDER "/tmp", FS::IsRecursive::yes)
                  .remove_directory(HOME_FOLDER "/tmp2", FS::IsRecursive::yes)
                  .is_success());

    printer().key("complete", __FUNCTION__);
    return true;
  }

  bool file_system_api_case() {
    Printer::Object fs_po(printer(), __FUNCTION__);

    {
      printer::Printer::Object po(printer(), "create/remove directories");

      constexpr const char *file_name = HOME_FOLDER "/filessytem.txt";
      const StringView dir_name = HOME_FOLDER "/tmpdir";
      const StringView dir_name_recursive = HOME_FOLDER "/tmpdir/tmp/dir";
      const StringView file_name2 = HOME_FOLDER "/filessytem2.txt";

      // cleanup
      reset_error();
      FS().remove_directory(
        HOME_FOLDER "/tmpdir/tmp/dir",
        FS::IsRecursive::yes);
      reset_error();
      FS().remove_directory(HOME_FOLDER "/tmpdir/tmp", FS::IsRecursive::yes);
      reset_error();
      FS().remove_directory(HOME_FOLDER "/tmpdir", FS::IsRecursive::yes);
      reset_error();

      TEST_ASSERT(is_success());

      TEST_ASSERT(F(F::IsOverwrite::yes, file_name)
                    .write("Filesystem file")
                    .is_success());

      TEST_ASSERT(FS().exists(file_name));

      TEST_ASSERT(FS().exists("does_not_exist") == false);

      // not exists should not affect the error context
      TEST_ASSERT(!FS().exists(file_name2) && is_success());

      TEST_ASSERT(FS().remove(file_name).is_success());
      TEST_ASSERT(!FS().exists(file_name) && is_success());

      TEST_ASSERT(
        F(F::IsOverwrite::yes, file_name).write(file_name2).is_success());

      TEST_ASSERT(FS().get_info(file_name).size() == file_name2.length());

      TEST_ASSERT(FS().create_directory(dir_name).is_success());
      TEST_ASSERT(FS().remove_directory(dir_name).is_success());

      TEST_ASSERT(
        FS().create_directory(dir_name, FS::IsRecursive::no).is_success());

      TEST_ASSERT(FS().directory_exists(dir_name));

      reset_error();
      TEST_ASSERT(FS().remove_directory(dir_name).is_success());

      TEST_ASSERT(FS().create_directory(dir_name_recursive).is_error());

      TEST_ASSERT(dir_name_recursive == error().message());
      TEST_ASSERT(error().message() == dir_name_recursive);

      reset_error();

      TEST_ASSERT(FS()
                    .create_directory(dir_name_recursive, FS::IsRecursive::yes)
                    .is_success());

      TEST_ASSERT(F(F::IsOverwrite::yes, dir_name_recursive + "/tmp.txt")
                    .write("Hello")
                    .is_success);

      TEST_ASSERT(
        DF()
          .write(F(dir_name_recursive + "/tmp.txt", OpenMode::read_only()))
          .data()
          .add_null_terminator()
        == StringView("Hello"));

      TEST_ASSERT(F(F::IsOverwrite::yes,
                    fs::Path::parent_directory(dir_name_recursive) + "/tmp.txt")
                    .write("Hello2")
                    .is_success);

      TEST_ASSERT(
        DF()
          .write(
            F(fs::Path::parent_directory(dir_name_recursive) + "/tmp.txt",
              OpenMode::read_only()))
          .data()
          .add_null_terminator()
        == StringView("Hello2"));

      TEST_ASSERT(
        F(F::IsOverwrite::yes,
          fs::Path::parent_directory(dir_name_recursive, 2) + "/tmp.txt")
          .write("Hello3")
          .is_success);

      TEST_ASSERT(
        DF()
          .write(
            F(fs::Path::parent_directory(dir_name_recursive, 2) + "/tmp.txt",
              OpenMode::read_only()))
          .data()
          .add_null_terminator()
        == StringView("Hello3"));

      TEST_ASSERT(FS().exists(dir_name_recursive) == true);

      TEST_ASSERT(
        FS().exists(fs::Path::parent_directory(dir_name_recursive)) == true);

      TEST_ASSERT(
        FS().exists(fs::Path::parent_directory(dir_name_recursive, 2)) == true);

      TEST_ASSERT(
        FS().remove_directory(dir_name, FS::IsRecursive::yes).is_success());

      TEST_ASSERT(
        FS().remove_directory(dir_name, FS::IsRecursive::yes).is_error());

      TEST_ASSERT(error().message() == dir_name);

      reset_error();
    }

    {
      printer::Printer::Object po(printer(), "directory permissions");
      Permissions permissions = FS().get_info(HOME_FOLDER).permissions();
      const StringView dir_name = HOME_FOLDER "/permdir";

      FS().remove_directory(dir_name);
      reset_error();

      TEST_ASSERT(FS().create_directory(dir_name).is_success());
      TEST_ASSERT(FS().get_info(dir_name).permissions() == permissions);
      TEST_ASSERT(FS().remove_directory(dir_name).is_success());
    }

    {
      printer::Printer::Object po(printer(), "utils");
      const StringView old_name = HOME_FOLDER "/old.txt";
      const StringView new_name = HOME_FOLDER "/new.txt";

      // ensure a clean slate
      FS().remove(old_name);
      reset_error();

      FS().remove(new_name);
      reset_error();

      F(F::IsOverwrite::yes, old_name).write("Hello");

      TEST_ASSERT(FS().exists(old_name));
      TEST_ASSERT(
        FS()
          .rename(FS::Rename().set_source(old_name).set_destination(new_name))
          .is_success());
      TEST_ASSERT(FS().exists(new_name));
      TEST_ASSERT(!FS().exists(old_name));

      TEST_ASSERT(
        DF()
          .write(F(new_name, OpenMode::read_only()))
          .data()
          .add_null_terminator()
        == StringView("Hello"));
    }

    printer().key("complete", __FUNCTION__);
    return true;
  }

  bool file_api_case() {
    Printer::Object file_po(printer(), __FUNCTION__);
    constexpr const char *file_name = HOME_FOLDER "/tmp.txt";

    const std::array<StringView, 5> test_strings = {
      "Testing String 0\n",
      "-Testing String 1-\n",
      "Testing String 2\n",
      "Testing String 3\n",
      "Testing String 4\n"};

    reset_error();

    {
      constexpr const char *file1_name = HOME_FOLDER "/verify1.txt";
      constexpr const char *file2_name = HOME_FOLDER "/verify2.txt";

      F(F::IsOverwrite::yes, file1_name).write(test_strings.at(0));
      F(F::IsOverwrite::yes, file2_name).write(test_strings.at(1));
      DataFile data1_file = DataFile().write(test_strings.at(0)).move();
      DataFile data2_file = DataFile().write(test_strings.at(1)).move();

      TEST_ASSERT(F(file1_name).verify(data1_file.seek(0)));
      TEST_ASSERT(F(file2_name).verify(data2_file.seek(0)));
      TEST_ASSERT(F(file1_name).verify(F(file1_name)));
      TEST_ASSERT(F(file1_name).verify(F(file2_name)) == false);
      TEST_ASSERT(F(file1_name).verify(data2_file.seek(0)) == false);
      TEST_ASSERT(F(file2_name).verify(data1_file.seek(0)) == false);
      TEST_ASSERT(data1_file.seek(0).verify(data2_file.seek(0)) == false);
      TEST_ASSERT(data1_file.seek(0).verify(data1_file.seek(0)));
      printer().set_progress_key("verify");
      TEST_ASSERT(
        F(file1_name)
          .verify(
            data1_file.seek(0),
            F::Verify().set_progress_callback(printer().progress_callback())));

      FS().remove(file1_name).remove(file2_name);
    }

    DataFile f;

    for (const auto &value : test_strings) {
      f.write(value);
    }

    printer().key("size", NumberString(f.size()));
    printer().object("contents", View(f.data()));
    printer().key("line", f.get_line().string_view());

    TEST_ASSERT(f.seek(0).get_line() == test_strings.at(0));
    TEST_ASSERT(f.get_line() == test_strings.at(1));
    TEST_ASSERT(f.get_line() == test_strings.at(2));
    TEST_ASSERT(f.get_line() == test_strings.at(3));
    TEST_ASSERT(f.get_line() == test_strings.at(4));

    TEST_ASSERT(
      F(F::IsOverwrite::yes, file_name).write(test_strings.at(0)).is_success());

    TEST_ASSERT(
      F(F::IsOverwrite::no, file_name).write(test_strings.at(0)).is_error());

    TEST_ASSERT(var::StringView(error().message()) == file_name);

    reset_error();

    TEST_ASSERT(
      String(DF().write(F(file_name, OpenMode::read_only())).data())
      == test_strings.at(0));

    TEST_ASSERT(return_value() == StringView(test_strings.at(0)).length());

    TEST_ASSERT(F(F::IsOverwrite::yes, file_name)
                  .write(test_strings.at(0))
                  .write(test_strings.at(1))
                  .write(test_strings.at(2))
                  .write(test_strings.at(3))
                  .write(test_strings.at(4))
                  .is_success());

    TEST_ASSERT(
      F(HOME_FOLDER "/does_not_exist.txt", OpenMode::read_only()).is_error());
    TEST_ASSERT(F(file_name, OpenMode::read_only()).is_error());

    reset_error();
    TEST_ASSERT(F(file_name, OpenMode::read_only()).is_success());

    {
      F tmp(file_name, OpenMode::read_write());

      TEST_ASSERT(FS().get_info(tmp).is_file());

      TEST_ASSERT(
        DataFile()
          .reserve(256)
          .write(tmp, F::Write().set_terminator('\n'))
          .data()
          .add_null_terminator()
        == test_strings.at(0));

      TEST_ASSERT(
        DataFile()
          .reserve(256)
          .write(tmp, F::Write().set_terminator('\n'))
          .data()
          .add_null_terminator()
        == test_strings.at(1));

      TEST_ASSERT(
        DataFile()
          .reserve(256)
          .write(tmp, F::Write().set_terminator('\n'))
          .data()
          .add_null_terminator()
        == test_strings.at(2));

      TEST_ASSERT(
        DataFile()
          .reserve(256)
          .write(tmp, F::Write().set_terminator('\n'))
          .data()
          .add_null_terminator()
        == test_strings.at(3));

      TEST_ASSERT(
        DataFile()
          .reserve(256)
          .write(tmp, F::Write().set_terminator('\n'))
          .data()
          .add_null_terminator()
        == test_strings.at(4));

      TEST_ASSERT(
        DataFile()
          .reserve(256)
          .write(
            tmp.seek(var::StringView(test_strings.at(0)).length()),
            F::Write().set_terminator('\n'))
          .data()
          .add_null_terminator()
        == test_strings.at(1));
    }

    {
      Printer::Object po(printer(), "lambdaFile");
      Data lambda_file_data;
      printer().key("fileData", NumberString(&lambda_file_data, "%p"));
      auto lambda_file
        = LambdaFile()
            .set_read_callback(
              [&lambda_file_data](int location, var::View view) -> int {
                View data_at_location
                  = View(lambda_file_data).pop_front(location);
                const size_t size = data_at_location.size() > view.size()
                                      ? view.size()
                                      : data_at_location.size();
                view.copy(View(lambda_file_data).pop_front(location));
                return size;
              })
            .set_write_callback(
              [&lambda_file_data](int location, const var::View view) -> int {
                lambda_file_data.append(view);
                return view.size();
              })
            .move();

      const StringView hello = "hello";
      DataFile incoming;
      TEST_ASSERT(lambda_file.write(hello).is_success());

      TEST_ASSERT(incoming.write(lambda_file.seek(0)).is_success());
      PRINTER_TRACE(printer(), "");
      printer().key(
        "incoming",
        StringView(View(incoming.data()).to_const_char(), incoming.size()));
      TEST_ASSERT(incoming.size() == hello.length());
      TEST_ASSERT(lambda_file.size() == hello.length());

      TEST_ASSERT(incoming.data().add_null_terminator() == hello);
      TEST_ASSERT(lambda_file_data.add_null_terminator() == hello);
    }

    {
      auto ref_object = Printer::Object(printer(), "refQualified");
      auto file
        = F(F::IsOverwrite::yes, "fileTest.txt").write("Hello.txt").seek(0);
    }

    {
      class SelfFile : public FileMemberAccess<SelfFile, File> {
      public:
        SelfFile(File::IsOverwrite is_overwrite, var::StringView name)
          : FileMemberAccess(is_overwrite, name) {}
        SelfFile(var::StringView name)
          : FileMemberAccess(name) {}
      };

      {
        auto self_file
          = SelfFile(File::IsOverwrite::yes, "Testing.txt").write("Hello ");
        self_file.write("World");

        const auto read_self = SelfFile("Testing.txt");
        auto self_data = DataFile().write(read_self.file());
        API_ASSERT(
          self_data.data().add_null_terminator() == StringView{"Hello World"});
      }
    }
    printer().key("complete", __FUNCTION__);
    return true;
  }

private:
};
