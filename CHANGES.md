> Please see [Semantic Versioning on Github](https://blog.stratifylabs.dev/device/2021-07-12-Semantic-Versioning-and-Github/) for more details on managing the `CHANGES.md` file.

# Version 1.6.0 (not released)

## New Features

- WARNING: There are some **breaking changes**. These were either bug-prone or safety concerns
  - Removed `FileObject::write(void * buffer, size_t size)` use `FileObject::write(var::View view)`
  - Removed `FileObject::read(void * buffer, size_t size)` use `FileObject::read(var::View view)`
  - Fixed spelling of `delimiter` in `var::Tokenizer` (was `delimeter`)
  - Use api::Function with api::ProgressCallback instead of `context` and `callback`
    - This is a much safer alternative (really more of a bug fix)
  - Removed `FileObject::ioctl(const Ioctl&)` use `FileObject::ioctl(int request, Type * type)`
  - `fs::LambdaFile` using `api::Function` rather than a c-style function pointer
    - `context` was passed but now must be captured in the lambda
  - Removed `fs::FileObject::gets()` use `fs::FileObject::get_line()`
  - Use `api::Function` for the `fs::FileSystem::ExcludeCallback`
  - `Test::initialize` is now part of `Test::Scope` to guarantee the existence of a printer
- Add `var::Tokenizer::DelimiterType::ordered_characters` to tokenize with an ordered set of characters
  - For example: `1+2=3` can tokenize with `+=` and get `1`, `2`, and `3`.
- Add `var::Tokenizer::DelimiterType::ordered_strings` to tokenize with an ordered set of strings
  - For example: `1+=2==3` can tokenize with `|+=|==` and get `1`, `2`, and `3`.
  - The first character in the `delimiters` is the one character delimiter for the strings in the set
- Add `operator bool()` to `thread::Cond` to check if the condition is asserted
- Separate `var::StackString` logic from the template
- Added `rvalue` reference functions for some function-chained member functions
- Escape characters that are printed within quotes with `printer::Printer::print()`
- Add `is_character_wise` to `var::ReplaceString` which replaces each character in `old_string`
- Add `StringView::pop_encapsulated()` which will get a substring after the encapsulation
- Add `StringView::get_encapsulated` to find encapsulated tokens in a string
- Add option to execute threads with a lambda
- Add ignore between `(){}[]<>` to `var::Tokenizer`
  - Also handles recursive symbols `${${test}}`
- Add `var::Base64::is_valid()` to check to see if a string view is valid Base64
- Add `var::OrderedSet`, `var::UnorderedSet`, `var::OrderedMultiset` and `var::UnorderedMultiset`
- Update `var::Tokenizer` to support delimiters as characters or as a single string
- Add additional functions and documentation to `var::StringView`
  - Strip trailing whitespace
  - Strip leading whitespace
  - Truncate a string view
  - `contains_any_of` for both finding characters and strings (using a template)
- Use `cmsdk2_` functions for build

## Bug Fixes

- Fix build warning on Linux with `sys::System::launch_browswer()`
- Fixed `var::Ring` and added unit tests
- Make `var::StringView::pop_front(), pop_back(), and truncate()` safe (checks length)
- `fs::FileObject` uses `size_t` for size
- Fixed `Printer::trace` to never truncate
- Fixed a bug with `var::StringView::find_last_not_of` assigning the end position to `0`.
- Fixed a bug with `fs::FileObject::get_line()`
- Fixed a build error with the `VarAPI` Unit test
- Fixed crashing bug with multi-threaded apps and error handling
- Fixed bug with `sys::Process` where `thread.cancel()` was causing a crash
- Fixed a build error with `var::Stack`

# Version 1.5.0

## New Features

- Updated CMake files to use CMakeSDK v2.0 or greater
- Add `magic_enum` to `VarAPI` to convert `enum class` to/from string and to iterate all values

## Bug Fixes

- Remove unused member from `fs::Path`
- Make `fs::Path` a `static` only class (cannot be constructed)
- Fixed a regression error with `fs::LocationScope`

# Version 1.4.0

## New Features

- Add `ActionFlags` for signals on linux
- Add `operator bool()` to `var::StringView` to check for non-empty strings
- Add `operator bool()` to `var::StackString` to check for non-empty strings
- Build `mq_*` on linux and link to `rt` library
- Make dummy `sys::launch_browser()` available in Stratify OS
- Support move with `var::Vector::push_back()`
- Add `api::UniquePointer` as alias of `std::unique_ptr`

## Bug Fixes

- Removed superfluous cmake code from tests 
- Use smart pointers in implementation of `api::Demanlger`
- Fix a bug that allows `fs::FileMemberAccess` to be moved properly
- Fixed a bug when truncating `var::StackString` objects
- `sys::Sys::Process` needs to initialize `m_process` on windows
- Use `gettimeofday` for `ClockTime` on Linux
- Fix build problem with undefined reference to `atof` on Stratify OS
- add `var/StackString.hpp` include to `sys/Cli.hpp` to prevent some build errors

# Version 1.3.0

## New Features

- Add `var::List` as a wrapper for `std::list`
- Add `var::ContainerObject` as the base to container classes
  - Provides more access to algorithms. Allows for easier iteration.
- Add `api::SystemResource` to encapsulate system resources and minimize the use of the rule of 5.
- Documentation updates for `API`
- Use a `printer::Printer*` to print help when using `sys::Cli::show_help()`
- Add `sys::System::get_executable_suffix()` for desktop builds
- Add `fs::AssetFileSystem` for use on desktop builds to manage bundled assets
- Add `var::ReplaceCharacter` and `var::ReplaceString` structs
  - `var::String::Replace` is now an alias of `var::ReplaceString`
  - `var::StackString::Replace` is now an alias of `var::ReplaceCharacter`
- Add function to access `Process::pid()`
- Add `to_string()` and `from_string()` to `chrono::ClockTime`
- Add operator for printing `Date` as an object
- Add aliases to `StackString` types with the max length of the string (e.g. `StackString24`)
- Add `double` detection for `var::NumberString` for `__link` builds
- Add static function for `sys::Pipe::make_fifo()` for linux and macOS
- `sys::Process` no longer provides a pipe. It gives an `fs::DataFile` for standard output and error.
- Add `sys::System::launch_browser()` to open a link in the system browser
- Add `api::catch_segmentation_fault()` to call `API_ASSERT()` when a segmentation fault happens (desktop)
- Use `fs::PathContainer` instead of `fs::PathList`. `fs::PathList` will be deprecated. `Container` is a more accurate description.

## Bug Fixes

- Many minor bug fixes based on `SonarLint` suggestions
- The function `sys::Cli::show_version` was not implemented (it is now)
- Remove relative links in `README.md`
- Minor (SonarLint) fixes in `printer::MarkdownPrinter`
- Make `printer::Printer::~Printer` virtual
- Assign `Dir::m_dirp` to `nullptr` after the object is closed
- Fix various minor issues with `fs::FileInfo`
- Remove redundant base functions from `fs::DirObject`
- Make `fs::DirObject::~DirObject` virtual and default
- Remove `#include "chrono/MicroTime.hpp"` from `chrono::MicroTime.hpp`
- When creating a thread, the error context needs to be generated for the first time with a mutex
- Ensure `PWD` exists for new process before starting the process
- House keeping on `Process` for linux and mac
- Fix `Process` spawn on Windows when the path has a space. `argv[0]` is given just the executable name
- Add correct move semantics to StackString
- Fix `Process` threads that monitor stdout and stderr
- Don't set system time in `Date().set_system_time()` if there is an error

# Version 1.2.0

## New Features

> Important! `fs::TemporaryDirectory()` which is not used often was moved to `sys::TemporaryDirectory()` to avoid a circular dependency between SysAPI and FsAPI. This is a symantic versioning breaking change (though a small one)

- Updates to CMake test structure, added `API_test` target
- Improved performance of `File::get_line()`
- Add `StrackString<>::truncate()` method
- Better test integration with super projects (`api_tests` target)
- Add `API_IS_TEST` cmake option for enabling tests
- Add `.clang-format`
- Add `thread::Cond::wait_until_asserted()` to wait for a condition to be asserted
- Increased the size of `var::PathString` on Windows from `262` to `4096`
- Added a bool member to `thread::Cond` that can be used for thread synchronization
- Make printer progress keys unique on multiple calls
- Add `API_PUBLIC_MEMBER_AZ()` and its shortcut `API_PMAZ()` for adding public members that are written in such a way to be easily sorted alphabetically by IDE tools
- Add `API_PUBLIC_BOOL()` for public boolean members
- Add `API_PUBLIC_MEMBERS()` macros for declaring and accessing purely public members
- Add more ways to construct a Thread (less cumbersome)
- Add `api::Range` and `api::Index` for creating simple ranges for range based for loops
  - `api::Index` can take one argument and count from zero to `end-1` and automatically infer the type
- Return `IsExclude` when using `FileSystem::read_directory()` (added a method for backward compatibility too)
- Add `get_line()` to file object to read a line into an arbitrary string type
- Add `test::Test::Scope` for managing application level test initialization and finalization
- Use `~` when printing simple indeterminate progress
- Add `sys::Process` and `sys::Pipe` (only for desktop builds)
- implement operator for sending `sys::Cli` to a `printer::Printer`
- Add `API_SINGLETON_CUSTOM_CONSTRUCTOR()` macro for singletons that have logic in the constructor
- minor improvements to `var::StackString` types
- Add `Mq::File` to create a `FileObject` based on a message queue
- Add `API_SINGLETON()` macro for creating singleton classes
- Added `DescriptorScope` to `File` to temporarily use a file descriptor
- Add templated `to_string<>()` method to `ClockTime`
- Add `accumulate()` to container classes (work in progress)

## Bug Fixes

- Fixed some bugs when configuring threads in Windows
- Tidy (with clang-tidy)
- fixed a bug in `fs::Path::suffix` and `fs::Path::name` when getting a suffix of a stringview that is part of a larger null terminated string
- Check for zero size when adding a null terminator to `var::Data`
- Change `fs::File&` to `const fs::FileObject&` when constructing a `fs::DataFile` from another File
- Fixed broken build on StratifyOS with Signal casting to `_sig_func_ptr`

# Version 1.1.0

## New Features

- Add `Signal::HandlerScope` to restore the default handler when the object goes out of scope
- Add `Test::TimedScope` class to check for testing durations
- Add enum class `chrono::Date::Month` for a list of months
- Add class `Thread::Mq` to support posix mqueue
- Add optional stack size parameter when constructing `Thread::Attributes`
- If `Thread::Attributes` changes policy or priority, policy inherit is disabled
- Add `Mutex::unlock_with_error_check()` to check errors when unlocking a mutex
- Malloc chunk size reference is no longer tied to the target chunk size
- Add `Var::View::find()` to find a view within another view
- Add `API_OR_ENUM_CLASS` macro for adding flag operators to an enum class
- Add `from_string` to `var::View`

## Bug Fixes

- Fixed a bug when starting new threads that are immediately moved
- `Sem::wait_timed()` now adds the time argument to the system time and passes absolute time to `sem_timedwait()`
- `Thread::Attributes` now inherits `api::ExecutionContext`
- Fix bug in `Thread::Attributes::get_inherit_sched()` where the wrong call was made
- `Thread::set_cancel_state()` and `Thread::set_cancel_type()` changed to static methods
- Remove bugs with `interface_closedir()` and `internal_opendir()` to avoid virtual methods in constructor/deconstuctor
- Permissions class now returns access permissions instead of full type with `permissions()` method
- Add a newline when closing markdown code section

# Version 1.0.0

Initial stable release.
