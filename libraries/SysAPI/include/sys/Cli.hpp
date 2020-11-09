/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.

#ifndef SAPI_SYS_CLI_HPP_
#define SAPI_SYS_CLI_HPP_

#include "var/String.hpp"
#include "var/StringView.hpp"

namespace sys {

class Cli : public api::ExecutionContext {
public:
  Cli(int argc, char *argv[]);

  class HandleVersion {
    API_AC(HandleVersion, var::StringView, version);
    API_AC(HandleVersion, var::StringView, publisher);
    API_AC(HandleVersion, var::StringView, githash);
  };

  const Cli &handle_version(const HandleVersion &options) const;
  inline const Cli &operator()(const HandleVersion &options) const {
    return handle_version(options);
  }

  Cli &set_case_sensitive(bool value = true) {
    m_is_case_sensitive = value;
    return *this;
  }

  bool is_case_senstive() const { return m_is_case_sensitive; }

  const char *app_git_hash() const { return m_app_git_hash; }

  var::String to_string() const;
  var::StringView at(u16 value) const;

  var::StringView get_option(
    var::StringView name,
    var::StringView help = var::StringView()) const;

  u32 count() const { return m_argc; }
  u32 size() const { return m_argc; }

  var::StringView get_name() const;
  var::StringView get_path() const;

  class ShowHelp {
    API_AF(ShowHelp, var::StringView, publisher, "");
    API_AF(ShowHelp, var::StringView, version, "");
  };

  Cli &show_help(const ShowHelp &options);
  Cli &show_version(const ShowHelp &options);

private:
  u16 m_argc;
  char **m_argv;
  bool m_is_case_sensitive;
  const char *m_app_git_hash;
  mutable var::StringList m_help_list;
};

} /* namespace sys */

namespace printer {
class Printer;
Printer &operator<<(Printer &printer, const sys::Cli &a);
} // namespace printer

#endif /* SAPI_SYS_CLI_HPP_ */
