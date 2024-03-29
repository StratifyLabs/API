# API

## Overview

API is a collection of cross-platform C++ libraries for 

- Windows
- MacOS
- Linux
- [Stratify OS](https://github.com/StratifyLabs/StratifyOS) (embedded)

including

- API: error handling and execution context
- ChronoAPI: time and timing
- FsAPI: File systems
- PrinterAPI: printing variables
- SysAPI: command line interface, system name, semantic versions
- ThreadAPI: thread management
- VarAPI: data and strings

## How to Build

The `API` library is designed to be a CMake sub-project. To build, please use one of these projects:

- Desktop [Command Line Interface](https://github.com/StratifyLabs/cli)
- [Stratify OS on Nucleo-144](https://github.com/StratifyLabs/StratifyOS-Nucleo144)

## Design

The API framework is a hard to mis-use, non-onerous C++ API achieved using the following principles:

- [Thread Local Error Context](#thread-local-error-context)
- [Method Chaining](#method-chaining)
- [Filesystem Inspired Abstraction](#filesystem-inspired-abstraction)
- [Strong Arguments](#strong-arguments)
- [RAII for Resource Management](#use-raii-for-resource-management)

### Thread Local Error Context

#### Error Context

- Cascading errors by returning `int` can be a huge pain
- Use a single error context per thread
  - Tracks return value of read/write and other system calls
  - Monitors `errno` after system calls
  - Execute backtrace on error for debugging
  - Do not nest errors. If thread `is_error()`, operation is aborted.

This means anything that can affect the error context (including changing the value of `errno`) must abort if the thread already has an error.

```cpp
const FileObject &FileObject::read(void *buf, int nbyte) const {
  API_RETURN_VALUE_IF_ERROR(*this); //don't modify erroneous context
  API_SYSTEM_CALL("", interface_read(buf, nbyte)); //update error context if needed
  return *this; //used for method chaining
}
```

#### Thread Locality

The process (primary thread) error context is created statically at compile time. The value of `&errno` provides an error context signature for each thread. An error context is dynamically allocated if a new thread has an error.

```cpp
Error &PrivateExecutionContext::get_error() {
  if (&(errno) == m_error.m_signature) {
    return m_error;
  }
  if (m_error_list == nullptr) {
    m_error_list = new std::vector<Error>();
    API_ASSERT(m_error_list != nullptr);
  }
  for (Error &error : *m_error_list) {
    if (error.m_signature == &(errno)) {
      return error;
    }
    if (error.m_signature == nullptr) {
      error.m_signature = &(errno);
      return error;
    }
  }
  m_error_list->push_back(Error(&(errno)));
  return m_error_list->back();
}
```

### Method Chaining

Having a per-thread error context allows for very powerful (and concise) code using method chaining. This approach also helps to create strong arguments that are hard for application developers to use incorrectly.

```cpp
class Point {
public:
  int x() const { return m_x; }
  int y() const { return m_y; }

  Point& set_x(int value){
    m_x = value;
    return *this;
  }

  Point& set_y(int value){
    m_y = value;
    return *this;
  }

private:
  int m_x = 0;
  int m_y = 0;
}

Point p = Point().set_x(50).set_y(100);
```

### Filesystem Inspired Abstraction

Almost any data in the `API` framework can be treated as a `FileObject`. This provides a unified way to move data around between memory, the filesystem, the internet, and devices.

```cpp
//defines interface for using file like objects
class FileObject {
  //write source to this file
  FileObject & write(const FileObject & source);
}

//interacts with a real file (POSIX style)
class File : public FileObject;

//uses malloc/free to manage contents
class DataFile : public FileObject;

//looks at existing memory for file contents
class ViewFile : public FileObject;

//use callbacks for file contents
class LambdaFile : public FileObject;

// these are part of the InetAPI (separate repo)
class Socket : public FileObject;
class SecureSocket : public FileObject;
```

### Strong Arguments

`API` classes are designed so that the functionality is obvious without looking at the declaration. The code below illustrates one example.

```cpp
//weak -- don't do this
FileSystem& rename(const StringView old_path, const StringView new_path);

//which is old and which is new?
FileSystem().rename("my_file.txt", "your_file.txt");

//strong
class Rename {
  //API_ACCESS is a getter/setter macro supporting
  //method chaining
  API_ACCESS(Rename,StringView,old_path);
  API_ACCESS(Rename,StringView,new_path);
}
FileSystem& rename(const Rename & options);

//unambiguous functionality
FileSystem().rename(
  Rename()
    .set_old_path("my_file.txt")
    .set_new_path("your_file.txt"));

// strong argument calls also include a call operator shortcut
FileSystem& operator()(const Rename & options){
  return rename(options);
}

//called like this
FileSystem()(Rename()
  .set_old_path("my_file.txt")
  .set_new_path("your_file.txt"));

```


### Use RAII for resource management

> RAII = resource acquisition is initialization

The constructor/deconstructor paradigm built into the C++ language is an excellent way to manage resources. If anything is "opened", it is done so in the constructor and then closed in the destructor. This goes for lock/unlock, malloc/free, initialize/finalize, and so on.

Here are a few examples:

```cpp
//open/close
DataFile my_file;
{
  //file is opened on construction
  //OR that is, it is "initialized" on "acquisition"
  File f("myfile.txt"); 
  //read from f, write to my_file
  my_file.write(f); 
} //f is closed when leaving scope

printf("my file is %s\n", my_file.data().add_null_terminator());

//lock/unlock
Mutex mutex;
{
  Mutex::Scope mutex_scope(mutex); //lock mutex
  File f("file.txt");
  printf("file size is %d\n", f.size());
} // f is closed then mutex is unlocked
```

One limitation to this approach comes when, for example, you want to construct a File but open it later. The `API` allows for constructing an unopened file and swapping it for something valid later.

Keep in mind, you can `move` a `File` but you cannot copy the object. This will be true throughout the `API` for any class that is associated with a system resource.

```cpp
//this will just be an unopened file for now
File f;

if( f.is_valid() == false ){
 //yep, it's not valid (also not erroneous)
}

//This is how we open it later
f = File("myfile.txt").move();

//this is also OK
f = std::move(File("myfile.txt"));

//But we can never make copies
//this won't compile because the
//copy constructor is deleted
File f_copy = f;
```

### File Copy Example

Using traditional C/POSIX style programming to copy a file looks something like this:

```cpp
int file_fd = open("file.txt", O_READONLY);
if( f < 0 ){ /*cascade the error up the chain*/ }

int new_file_fd = open("new_file.txt", O_APPEND | O_CREAT | O_TRUNC, 0666);
if( new_file_fd < 0 ){ /*cascade the error up the chain*/ }

char buffer[64];
int bytes_read = 0;

while( (bytes_read = read(file_fd, buffer, 64)) > 0 ){
  if( write(new_file_fd, buffer, bytes_read) < 0 ){
    //cascade the error up the chain
  }
}

if( close(file_fd) < 0){ /*cascade the error up the chain*/ }
if( close(new_file_fd) < 0){ /*cascade the error up the chain*/ }
```

The `API` way is much more concise.

```cpp
//copy file.txt -> new_file.txt
File(File::IsOverwrite::yes, "new_file.txt").write(File("file.txt"));
if( api::ExecutionContext::is_error() ){
  //something didn't work -- error context has the details
}
```

The error context of the thread will record the precise location of the error and provide a backtrace.

## Conventions

## getters and setters

The `API` framework uses `set_value()` for setting and `value()` for access to a value. If the method needs to do something extra to return the value, `get_value()` is used.

The `chrono::ClockTime` has some good examples:

```cpp
//access seconds -- nothing to calculate or fetch
s32 seconds() const { return m_value.tv_sec; }

//setting the seconds
ClockTime &set_seconds(u32 seconds) {
  m_value.tv_sec = seconds;
  return *this;
}

// the age isn't readily available, so we do get_age() rather than age()
ClockTime get_age() const { return get_system_time() - *this; }
```

## `is_valid()`

If a class can have a valid/invalid state, the method `is_valid()` is used to check.

Examples:

```cpp
#include <thread.hpp>
#include <fs.hpp>

File f;
if( f.is_valid() ){}

Thread t;
if( t.is_valid() ){}
```

## Documentation

The code and a few guides (README.md docs in the repo) are all the available documentation. For many years, I believed in Doxygen style comments, but most of the documentation just ended up being redundant. This snippet was taken directly from the code before the comments were removed.

```cpp
/*! \details Compares <= to another MicroTime object. */
bool operator<=(const MicroTime &a) const {
  return microseconds() <= a.microseconds();
}
```

Comments in the code exist to explain why and give insights that are not obvious. They are not there to explain what. The API and code should do that on their own.
