# Version 1.1

## New Features

- Add `Var::View::find()` to find a view within another view
- Add `API_OR_ENUM_CLASS` macro for adding flag operators to an enum class
- Add `from_string` to `var::View`

## Bug Fixes

- Remove bugs with `interface_closedir()` and `interface_opendir()` to avoid virtual methods in constructor/deconstuctor
- Permissions class now returns access permissions instead of full type with `permissions()` method
- Add a newline when closing markdown code section

# Version 1.0

Initial stable release.
