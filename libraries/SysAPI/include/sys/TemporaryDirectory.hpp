#ifndef TEMPORARYDIRECTORY_HPP
#define TEMPORARYDIRECTORY_HPP

#include "var/StackString.hpp"
#include "var/StringView.hpp"

namespace sys {

/*! \details
 *
 * This class creates a temporary directory in the
 * System::user_data_path() folder.
 *
 * When the instance of this class goes out of scope,
 * the directory is deleted.
 *
 *
 */
class TemporaryDirectory : public api::ExecutionContext {
public:
  explicit TemporaryDirectory(var::StringView parent = "");

  API_NO_DISCARD var::StringView path() const & {
    return path_resource.value().string_view();
  }

  API_NO_DISCARD var::PathString path() const && {
    return path_resource.value();
  }

private:
  static void deleter(var::PathString * path);
  api::SystemResource<var::PathString, decltype(&deleter)> path_resource;
};

} // namespace sys

#endif // TEMPORARYDIRECTORY_HPP
