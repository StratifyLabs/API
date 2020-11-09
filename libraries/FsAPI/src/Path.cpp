#include "fs/Path.hpp"
#include "printer/Printer.hpp"

using namespace fs;
using namespace var;

var::StringView Path::suffix(const StringView path) {
  size_t pos = path.reverse_find(".");

  if (pos == var::String::npos) {
    return var::StringView();
  }

  return StringView(path.data() + pos + 1);
}

var::StringView Path::name(const StringView path) {
  size_t pos = path.reverse_find('/');

  if (pos == var::String::npos) {
    return path;
  }

  return StringView(path.data() + pos + 1);
}

var::StringView Path::parent_directory(const StringView path, size_t depth) {
  size_t pos = path.reverse_find('/');

  if (pos == var::String::npos) {
    return var::StringView();
  }

  const StringView result = StringView(path.data(), pos);

  if (depth > 1) {
    return parent_directory(result, depth - 1);
  }
  return result;
}

var::StringView Path::base_name(const StringView path) {
  return no_suffix(name(path));
}

var::StringView Path::no_suffix(const StringView path) {
  size_t pos = path.reverse_find('.');

  if (pos == StringView::npos) {
    return path;
  }

  return StringView(path.data(), pos);
}

bool Path::is_hidden(const StringView path) {
  if (name(path).find(".") == 0) {
    return true;
  }

  var::StringView parent_directory_path = parent_directory(path);
  if (parent_directory_path != path) {
    return is_hidden(parent_directory(parent_directory_path));
  }

  return false;
}
