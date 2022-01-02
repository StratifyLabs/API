# Version 1.3.0


## New Features

- Add `sys::System::launch_browser()` to open a link in the system browser
- Add `api::catch_segmentation_fault()` to call `API_ASSERT()` when a segmentation fault happens (desktop)

## Bug Fixes

- House keeping on `Process` for linux and mac
- Fix `Process` spawn on Windows when the path has a space. `argv[0]` is given just the executable name
- Add correct move semantics to StackString

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
