// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

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

  API_NO_DISCARD API_MAYBE_UNUSED const char *app_git_hash() const {
    return m_app_git_hash;
  }

  API_NO_DISCARD var::GeneralString to_general_string() const;
  API_NO_DISCARD var::StringView at(u16 value) const;

  API_NO_DISCARD var::StringView get_option(
    var::StringView name,
    var::StringView help = var::StringView()) const;

  API_NO_DISCARD u32 count() const { return m_argc; }
  API_NO_DISCARD u32 size() const { return m_argc; }

  API_NO_DISCARD var::StringView get_name() const;
  API_NO_DISCARD var::StringView get_path() const;

  class ShowHelp {
    API_AF(ShowHelp, var::StringView, publisher, "");
    API_AF(ShowHelp, var::StringView, version, "");
  };

  API_MAYBE_UNUSED const Cli &show_help(const ShowHelp &options) const;
  API_MAYBE_UNUSED const Cli &show_version(const ShowHelp &options) const;

private:
  u16 m_argc = 0;
  char **m_argv = nullptr;
  bool m_is_case_sensitive = true;
  const char *m_app_git_hash = nullptr;
  mutable var::Vector<var::PathString> m_help_list;
};

} /* namespace sys */

namespace printer {
class Printer;
Printer &operator<<(Printer &printer, const sys::Cli &a);
} // namespace printer

#endif /* SAPI_SYS_CLI_HPP_ */
