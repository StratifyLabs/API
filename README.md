# API

![Build](https://github.com/StratifyLabs/API/workflows/Build/badge.svg)

## Overview

API is a collection of cross-platform C++ libraries for 

- Windows
- MacOS
- Linux
- Stratify OS (embedded)

including

- [API](libraries/API): error handling and execution context
- [ChronoAPI](libraries/ChronoAPI): time and timing
- [FsAPI](libraries/FsAPI): File systems
- [PrinterAPI](libraries/PrinterAPI): printing variables
- SysAPI: misc system functions
- [ThreadAPI: thread management](libraries/ThreadAPI)
- VarAPI: data management

## Design

The API framework is a hard to mis-use, non-onerous C++ API acheived using the following principles

- Thread Local Error Context
- Method Chaining
- Filesystem Inspired Abstraction
- Strong Arguments
- RAII for Resource Management

### Thread Local Error Context

#### Error Context

- Cascading errors by returning `int` can be a huge pain
- Use a single error context per thread
  - Tracks return value of read/write and other system calls
  - Monitors `errno` after system calls
  - Execute backtrace on error for debugging
  - Do not nest errors. If thread `is_error()`, operation is aborted.

This means anything that can affect the error context (including changing the value of `errno`) must abort if the thread already has an error.

```c++
const FileObject &FileObject::read(void *buf, int nbyte) const {
  API_RETURN_VALUE_IF_ERROR(*this); //don't modify erroneous context
  API_SYSTEM_CALL("", interface_read(buf, nbyte)); //update error context if needed
  return *this; //used for method chaining
}
```

#### Thread Local Error Context

The process (primary thread) error context is created statically at compile time. The value of `&errno` provides an error context signature for each thread. An error context is dynamically allocated if a new thread has an error.

```c++
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

Having a per thread error context, allows for very powerful (and concise) code using method chaining. This approach also helps to create strong arguments that are hard for application developers to use incorrectly.

```c++
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

Almost any data in the `API` framework can be treated a `FileObject`. This provides a unified way to move data around between memory, the filesystem, the internet, and devices.

```c++
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

```c++
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

The constructor/deconstructor paradigm built into the C++ language is an excellent way to manage resources. If anything is "opened", it is done so in the constructor and then closed in the desctructor. This goes for lock/unlock, malloc/free, initialize/finalize and so on.

Here are a few examples:

```c++
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
  MutexGuard mutex_guard(mutex); //lock mutex
  File f("file.txt");
  printf("file size is %d\n", f.size());
} // f is closed then mutex is unlocked
```

One limitation to this approach comes when, for example, you want to construct a File but open it later. The `API` allows for constructing an unopened file and swapping it for something valid later.

Keep in mind, you can `move` a `File` but you cannot copy the object. This will be true throughout the `API` for any class that is associated with a system resource.

```c++
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

```c++
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

```c++
//copy file.txt -> new_file.txt
File(File::IsOverwrite::yes, "new_file.txt").write(File("file.txt"));
if( api::ExecutionContext::is_error() ){
  //something didn't work -- error context has the details
}
```

The error context of the thread will record the precise location of the error and provide a backtrace.

