//
// Created by Tyler Gilbert on 7/14/22.
//

#ifndef VAR_API_MAGIC_ENUM_HPP_
#define VAR_API_MAGIC_ENUM_HPP_

#include "magic_enum.hpp"

#include "String.hpp"

namespace var {

template <class Type> class MagicEnum {
  MagicEnum() = default;

public:
  static StringView to_string_view(Type value) {
    return StringView{magic_enum::enum_name(value)};
  }

  static constexpr auto from_cstring(const char *name) {
    return magic_enum::enum_cast<Type>(name);
  }

  static auto from_string(var::StringView name) {
    return magic_enum::enum_cast<Type>(name.to_std_string_view());
  }

  static Type from_string_with_invalid(var::StringView name, Type invalid) {
    const auto result = from_string(name);
    return result.has_value() ? result.value() : invalid;
  }

  static size_t count() { return magic_enum::enum_count<Type>(); }

  static constexpr auto list() { return magic_enum::enum_values<Type>(); }

private:
};

} // namespace var
#endif // VAR_API_MAGIC_ENUM_HPP_
