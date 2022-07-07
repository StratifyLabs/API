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
  TemporaryDirectory(const TemporaryDirectory&) = delete;
  TemporaryDirectory& operator=(const TemporaryDirectory&) = delete;
  ~TemporaryDirectory();

private:
  API_AC(TemporaryDirectory, var::PathString, path);
};

} // namespace sys

#endif // TEMPORARYDIRECTORY_HPP
