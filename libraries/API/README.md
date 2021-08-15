# API

## Overview

The API library is the base library for all `*API` libraries. It includes:

- Info about the API library families
- Execution Context Error Handling
- Shared library API (for Stratify OS)


## ApiInfo

This is a simple static class to track the version and git hash of the library:

```c++
#include <api.hpp>

printf(
  "Version:%s GitHash:%s\n", 
  api::ApiInfo::version(), 
  api::ApiInfo::git_hash());
```

## Error Handling

The `*API` family of libraries is designed to have at most one error per thread. There is one key axiom to follow to ensure proper error management:

> Any method that can change the error context or relies on an error-free state must abort if the thread has an error.

The API library provides macros for error managing error handling. For system calls (that affect errno), use this sequence:

```c++
File& File::open(const char * path){
    //abort if the context error is already set
  API_RETURN_VALUE_IF_ERROR(-1); 

  //use this whenever errno could be affected
  API_SYSTEM_CALL(path, open(path, O_RDWR));
  return *this;
}

File& File::write(const void * buf, int nbyte){
  API_RETURN_VALUE_IF_ERROR(-1); 
  API_SYSTEM_CALL("", write(fileno(), buf, nbyte));
  return *this;
}

//This code allows the following sequence
//if open fails, write will abort
char buffer[16];
if( File().open("path").write(buffer, sizeof(buffer)).is_error() ){
  //use api::ExecutionContext to look at the error
  Printer() << api::ExecutionContext::error();
}
```

When an error occurs, the `api::ExecutionContext` records the line number, a message, and a backtrace. You can use the error context to quickly find and fix errors.

### Ignoring Errors

Sometimes there is a need to ignore errors or to execute a system call even if the context has an error. The `api::ErrorGuard` class saves/restores the error context on construction/deconstruction.

```c++
File::~File(){
  if( fileno() > 0 ){
    //if the file is open, we want to close it even
    //if the context has an error
    api::ErrorGuard error_guard; //save context and reset error
    close();
  } //~ErrorGuard() restores the error context (value of errno)
}
```

### Thread Safety

`errno` is the mechanism for handling errors. `errno` is part of POSIX systems (Linux, Windows, Mac, and Stratify OS). On all supported systems, `errno` is thread-safe. `&errno` provides a unique signature for any method to resolve to the appropriate error context.

The API library automatically allocates an error context if an error context is requested in a new thread. Before the thread exits, it should call `api::free_context()`.
If using the `thread::Thread` class for thread management, `api::free_context()` will be called automatically.






