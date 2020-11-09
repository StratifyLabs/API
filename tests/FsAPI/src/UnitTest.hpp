
#include <cstdio>

#include "api/api.hpp"
#include "chrono.hpp"
#include "fs.hpp"
#include "printer.hpp"
#include "sys.hpp"
#include "test/Test.hpp"
#include "var.hpp"

class UnitTest : public test::Test {

public:
  using FS = FileSystem;
  using F = File;
  using D = Dir;
  using DF = fs::DataFile;

  UnitTest(var::StringView name) : test::Test(name) {}

  bool execute_class_api_case() {

    TEST_ASSERT_RESULT(file_api_case());
    TEST_ASSERT_RESULT(file_system_api_case());
    TEST_ASSERT_RESULT(dir_api_case());
    TEST_ASSERT_RESULT(fileinfo_api_case());
    TEST_ASSERT_RESULT(view_file_api_case());
    TEST_ASSERT_RESULT(data_file_api_case());

    return true;
  }

  bool data_file_api_case() {
    const StringView contents
      = "0123456789012345678901234567890123456789012345678901234567890123456789"
        "0123456789";

    API_ASSERT(DataFile().write(contents).return_value() == contents.length());

    {
      DataFile df(OpenMode::read_write());
      df.seek(0).data().resize(contents.length());
      Data buffer(contents.length() + 4);

      API_ASSERT(df.read(buffer).return_value() == contents.length());
      df.seek(0);
      buffer.resize(7);
      while (df.read(buffer).return_value() > 0) {
        int result = return_value();
        printer().key(
          "read",
          NumberString().format("%d of %d", result, df.size()));
      }
    }

    return true;
  }

  bool view_file_api_case() {

    const StringView contents
      = "0123456789012345678901234567890123456789012345678901234567890123456789"
        "0123456789";

    u32 value;

    API_ASSERT(
      ViewFile(View(value)).write(contents).return_value() == sizeof(u32));

    return true;
  }

  bool fileinfo_api_case() {
    printer::Printer::Object po(printer(), "fileinfo");
    var::PathString temp_path;
    {
      TemporaryDirectory td(".");
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
      TEST_ASSERT(file_info.permissions().is_owner_execute() == false);
      TEST_ASSERT(file_info.permissions().is_owner_read() == true);
      TEST_ASSERT(file_info.permissions().is_owner_write() == true);

      TEST_ASSERT(file_info.permissions().is_public_execute() == false);
      TEST_ASSERT(file_info.permissions().is_public_read() == true);
      TEST_ASSERT(file_info.permissions().is_public_write() == false);

      printer().object("file", file_info);

      TEST_ASSERT(
        FS().get_info(td.path() + "/test.txt").size()
        == new_test_contents.length());
    }

    TEST_ASSERT(FS().directory_exists(temp_path) == false);

    TEST_ASSERT(is_success());

    return true;
  }

  bool dir_api_case() {

    FS().remove_directory("tmp", FS::IsRecursive::yes);
    reset_error();
    FS().remove_directory("tmp2", FS::IsRecursive::yes);
    reset_error();

    TEST_ASSERT(FS().create_directory("tmp").is_success());
    TEST_ASSERT(
      F(F::IsOverwrite::yes, "tmp/test0.txt").write("test0\n").is_success());
    TEST_ASSERT(
      F(F::IsOverwrite::yes, "tmp/test1.txt").write("test1\n").is_success());
    TEST_ASSERT(
      F(F::IsOverwrite::yes, "tmp/test2.txt").write("test2\n").is_success());
    TEST_ASSERT(FS().create_directory("tmp2").is_success());
    TEST_ASSERT(
      F(F::IsOverwrite::yes, "tmp2/test0.txt").write("test0\n").is_success());
    TEST_ASSERT(F(F::IsOverwrite::yes, "tmp2/filesystem.txt")
                  .write("test1\n")
                  .is_success());
    TEST_ASSERT(
      F(F::IsOverwrite::yes, "tmp2/test2.txt").write("test2\n").is_success());

    TEST_ASSERT(D("tmp").is_success());

    {
      Vector<var::PathString> dir_list = FS().read_directory("tmp");
      printer().object("list", dir_list);
      TEST_ASSERT(dir_list.count() == 3);
    }

    {
      D d("tmp");
      int count = 0;
      var::PathString e;
      while ((e = d.get_entry()).is_empty() == false) {
        printer().key("tell", NumberString(d.tell()).string_view());
        printer().key(NumberString(count), StringView(e.cstring()));
        count++;
      }
      TEST_ASSERT(count == 5);
      TEST_ASSERT(d.tell() == (count - 1));
      TEST_ASSERT(d.seek(0).is_success());
      TEST_ASSERT(d.rewind().is_success());
      // const var::String entry = d.get_entry();
      // printf("entry is %s\n", entry.cstring());
      TEST_ASSERT(d.get_entry() == "tmp/.");

      TEST_ASSERT(d.rewind().is_success());
      if (System().is_macosx() == false) {
        printer().key("tell", NumberString(d.tell()).string_view());
        TEST_ASSERT(d.tell() == 0);
      }
    }

    {
      TEST_ASSERT(FS().directory_exists("tmp"));
      PathList list = FS().read_directory("tmp", FS::IsRecursive::yes);
      printer().object("files", list);
      TEST_ASSERT(
        list.find(var::PathString("tmp/test0.txt")) == "tmp/test0.txt");
      TEST_ASSERT(
        list.find(var::PathString("tmp/test1.txt")) == "tmp/test1.txt");
      TEST_ASSERT(
        list.find(var::PathString("tmp/test2.txt")) == "tmp/test2.txt");
    }

    {
      TEST_ASSERT(FS().directory_exists("tmp2"));
      PathList list = FS().read_directory(
        "tmp2",
        FS::IsRecursive::yes,
        [](StringView entry) -> bool {
          return entry.find("filesystem") != StringView::npos;
        });
      printer().object("files", list);
      TEST_ASSERT(
        list.find(var::PathString("tmp2/test0.txt"))
        == var::PathString("tmp2/test0.txt"));
      TEST_ASSERT(
        list.find(var::PathString("tmp2/filesystem.txt")) == var::PathString());
      TEST_ASSERT(
        list.find(var::PathString("tmp2/test2.txt"))
        == var::PathString("tmp2/test2.txt"));
    }

    {
      PathList list = FS().read_directory("tmp", FS::IsRecursive::no);
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
                  .remove_directory("tmp", FS::IsRecursive::yes)
                  .remove_directory("tmp2", FS::IsRecursive::yes)
                  .is_success());

    return true;
  }

  bool file_system_api_case() {

    printer::Printer::Object po(printer(), "file_system");

    {
      printer::Printer::Object po(printer(), "create/remove directories");

      constexpr const char *file_name = "filessytem.txt";
      const StringView dir_name = "tmpdir";
      const StringView dir_name_recursive = "tmpdir/tmp/dir";
      const StringView file_name2 = "filessytem2.txt";

      // cleanup
      reset_error();
      FS().remove_directory("tmpdir/tmp/dir", FS::IsRecursive::yes);
      reset_error();
      FS().remove_directory("tmpdir/tmp", FS::IsRecursive::yes);
      reset_error();
      FS().remove_directory("tmpdir", FS::IsRecursive::yes);
      reset_error();

      TEST_ASSERT(is_success());

      TEST_ASSERT(F(F::IsOverwrite::yes, file_name)
                    .write("Filesystem file")
                    .is_success());

      TEST_EXPECT(FS().exists(file_name));

      TEST_ASSERT(FS().exists("does_not_exist") == false);

      // not exists should not affect the error context
      TEST_EXPECT(!FS().exists(file_name2) && is_success());

      TEST_EXPECT(FS().remove(file_name).is_success());
      TEST_EXPECT(!FS().exists(file_name) && is_success());

      TEST_ASSERT(
        F(F::IsOverwrite::yes, file_name).write(file_name2).is_success());

      TEST_EXPECT(FS().get_info(file_name).size() == file_name2.length());

      TEST_ASSERT(FS().create_directory(dir_name).is_success());
      TEST_ASSERT(FS().remove_directory(dir_name).is_success());

      TEST_ASSERT(
        FS().create_directory(dir_name, FS::IsRecursive::no).is_success());
      TEST_ASSERT(
        FS().create_directory(dir_name, FS::IsRecursive::no).is_error());
      reset_error();
      TEST_ASSERT(FS().remove_directory(dir_name).is_success());

      TEST_EXPECT(FS().create_directory(dir_name_recursive).is_error());

      TEST_EXPECT(dir_name_recursive == error().message());
      TEST_EXPECT(error().message() == dir_name_recursive);

      reset_error();

      TEST_EXPECT(FS()
                    .create_directory(dir_name_recursive, FS::IsRecursive::yes)
                    .is_success());

      TEST_EXPECT(F(F::IsOverwrite::yes, dir_name_recursive + "/tmp.txt")
                    .write("Hello")
                    .is_success);

      TEST_ASSERT(
        DF()
          .write(F(dir_name_recursive + "/tmp.txt", OpenMode::read_only()))
          .data()
          .add_null_terminator()
        == StringView("Hello"));

      TEST_EXPECT(F(F::IsOverwrite::yes,
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

      TEST_EXPECT(
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

      TEST_EXPECT(FS().exists(dir_name_recursive) == true);

      TEST_EXPECT(
        FS().exists(fs::Path::parent_directory(dir_name_recursive)) == true);

      TEST_EXPECT(
        FS().exists(fs::Path::parent_directory(dir_name_recursive, 2)) == true);

      TEST_EXPECT(
        FS().remove_directory(dir_name, FS::IsRecursive::yes).is_success());

      TEST_EXPECT(
        FS().remove_directory(dir_name, FS::IsRecursive::yes).is_error());

      TEST_EXPECT(error().message() == dir_name);

      reset_error();
    }

    {
      printer::Printer::Object po(printer(), "directory permissions");
      Permissions permissions = FS().get_info(".").permissions();
      const StringView dir_name = "permdir";

      FS().remove_directory(dir_name);
      reset_error();

      TEST_ASSERT(FS().create_directory(dir_name).is_success());
      TEST_ASSERT(FS().get_info(dir_name).permissions() == permissions);
      TEST_ASSERT(FS().remove_directory(dir_name).is_success());
    }

    {
      printer::Printer::Object po(printer(), "utils");
      const StringView old_name = "old.txt";
      const StringView new_name = "new.txt";

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

    return true;
  }

  bool file_api_case() {
    using F = fs::File;
    using DF = fs::DataFile;
    using FS = fs::FileSystem;
    printer::Printer::Object po(printer(), "file");

    constexpr const char *file_name = "tmp.txt";

    const std::array<StringView, 5> test_strings = {
      "Testing String 0\n",
      "Testing String 1\n",
      "Testing String 2\n",
      "Testing String 3\n",
      "Testing String 4\n"};

    reset_error();

    DataFile f;

    for (const auto &value : test_strings) {
      f.write(value);
    }

    printer().key("size", NumberString(f.size()));
    printer().object("contents", View(f.data()));
    printer().key("line", f.gets().string_view());

    TEST_ASSERT(f.seek(0).gets() == test_strings.at(0));
    TEST_ASSERT(f.gets() == test_strings.at(1));
    TEST_ASSERT(f.gets() == test_strings.at(2));
    TEST_ASSERT(f.gets() == test_strings.at(3));
    TEST_ASSERT(f.gets() == test_strings.at(4));

    TEST_ASSERT(
      F(F::IsOverwrite::yes, file_name).write(test_strings.at(0)).is_success());

    TEST_EXPECT(
      F(F::IsOverwrite::no, file_name).write(test_strings.at(0)).is_error());

    TEST_EXPECT(var::StringView(error().message()) == file_name);

    reset_error();

    TEST_EXPECT(
      String(DF().write(F(file_name, OpenMode::read_only())).data())
      == test_strings.at(0));

    TEST_EXPECT(return_value() == StringView(test_strings.at(0)).length());

    TEST_ASSERT(F(F::IsOverwrite::yes, file_name)
                  .write(test_strings.at(0))
                  .write(test_strings.at(1))
                  .write(test_strings.at(2))
                  .write(test_strings.at(3))
                  .write(test_strings.at(4))
                  .is_success());

    TEST_EXPECT(F("tmp1.txt", OpenMode::read_only()).is_error());
    TEST_EXPECT(F(file_name, OpenMode::read_only()).is_error());

    reset_error();
    TEST_EXPECT(F(file_name, OpenMode::read_only()).is_success());

    {
      F tmp(file_name, OpenMode::read_write());

      TEST_EXPECT(FS().get_info(tmp).is_file());

      TEST_EXPECT(
        DataFile()
          .reserve(256)
          .write(tmp, F::Write().set_terminator('\n'))
          .data()
          .add_null_terminator()
        == test_strings.at(0));

      TEST_EXPECT(
        DataFile()
          .reserve(256)
          .write(tmp, F::Write().set_terminator('\n'))
          .data()
          .add_null_terminator()
        == test_strings.at(1));

      TEST_EXPECT(
        DataFile()
          .reserve(256)
          .write(tmp, F::Write().set_terminator('\n'))
          .data()
          .add_null_terminator()
        == test_strings.at(2));

      TEST_EXPECT(
        DataFile()
          .reserve(256)
          .write(tmp, F::Write().set_terminator('\n'))
          .data()
          .add_null_terminator()
        == test_strings.at(3));

      TEST_EXPECT(
        DataFile()
          .reserve(256)
          .write(tmp, F::Write().set_terminator('\n'))
          .data()
          .add_null_terminator()
        == test_strings.at(4));

      TEST_EXPECT(
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
      LambdaFile f
        = LambdaFile()
            .set_read_callback(
              [](void *context, int location, var::View view) -> int {
                Data *data = reinterpret_cast<Data *>(context);
                View data_at_location = View(*data).pop_front(location);
                const size_t size = data_at_location.size() > view.size()
                                      ? view.size()
                                      : data_at_location.size();
                view.copy(View(*data).pop_front(location));
                return size;
              })
            .set_write_callback(
              [](void *context, int location, const var::View view) -> int {
                Data *data = reinterpret_cast<Data *>(context);
                data->append(view);
                return view.size();
              })
            .set_context(&lambda_file_data)
            .move();

      const StringView hello = "hello";
      DataFile incoming;
      TEST_ASSERT(f.write(hello).is_success());

      TEST_ASSERT(incoming.write(f.seek(0)).is_success());
      PRINTER_TRACE(printer(), "");
      printer().key(
        "incoming",
        StringView(View(incoming.data()).to_const_char(), incoming.size()));
      TEST_ASSERT(incoming.size() == hello.length());
      TEST_ASSERT(f.size() == hello.length());

      TEST_ASSERT(incoming.data().add_null_terminator() == hello);
      TEST_ASSERT(lambda_file_data.add_null_terminator() == hello);
    }

    return true;
  }

private:
};
