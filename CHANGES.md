# Version 1.2.0

## New Features

> Important! `fs::TemporaryDirectory()` which is not used often was moved to `sys::TemporaryDirectory()` to avoid a circular dependency between SysAPI and FsAPI. This is a symantic versioning breaking change (though a small one)

- Add `test::Test::Scope` for managing application level test initialization and finalization
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

- `Sem::wait_timed()` now adds the time argument to the system time and passes absolute time to `sem_timedwait()`
- `Thread::Attributes` now inherits `api::ExecutionContext`
- Fix bug in `Thread::Attributes::get_inherit_sched()` where the wrong call was made
- `Thread::set_cancel_state()` and `Thread::set_cancel_type()` changed to static methods
- Remove bugs with `interface_closedir()` and `interface_opendir()` to avoid virtual methods in constructor/deconstuctor
- Permissions class now returns access permissions instead of full type with `permissions()` method
- Add a newline when closing markdown code section

# Version 1.0.0

Initial stable release.
