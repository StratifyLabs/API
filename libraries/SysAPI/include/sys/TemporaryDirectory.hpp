#ifndef TEMPORARYDIRECTORY_HPP
#define TEMPORARYDIRECTORY_HPP

#include "var/StackString.hpp"
#include "var/StringView.hpp"

namespace sys {

class TemporaryDirectory : public api::ExecutionContext {
public:
  explicit TemporaryDirectory(var::StringView parent = "");
  ~TemporaryDirectory();

private:
  API_AC(TemporaryDirectory, var::PathString, path);
};

} // namespace sys

#endif // TEMPORARYDIRECTORY_HPP
