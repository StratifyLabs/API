# Version 1.1

## New Features

- Add `Mutex::unlock_with_error_check()` to check errors when unlocking a mutex
- Malloc chunk size reference is no longer tied to the target chunk size
- Add `Var::View::find()` to find a view within another view
- Add `API_OR_ENUM_CLASS` macro for adding flag operators to an enum class
- Add `from_string` to `var::View`

## Bug Fixes

- `Thread::set_cancel_state()` and `Thread::set_cancel_type()` changed to static methods
- Remove bugs with `interface_closedir()` and `interface_opendir()` to avoid virtual methods in constructor/deconstuctor
- Permissions class now returns access permissions instead of full type with `permissions()` method
- Add a newline when closing markdown code section

# Version 1.0

Initial stable release.
