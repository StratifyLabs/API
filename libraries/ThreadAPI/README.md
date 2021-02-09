# ThreadAPI

## Overview

The `ThreadAPI` library has classes to manage threads and the associated synchronization mechanisms such as semaphores, mutexes, and message queues.

## Threads

Thread creation and destruction follows RAII principles throughout the `API` family of libraries. A thread starts executed when it is constructed and stops when it is destructed.

```c++
#include <thread.hpp>

//Construct, execute and join a do nothing thread
Thread(
  Thread::Construct().set_argument(nullptr).set_function([]()->void *{ return nullptr; }), 
  Thread::Attributes().set_detach_state(Thread::DetachState::joinable)).join();
```

## Mutexes

A mutex is ready to use once it has been constructed. The best way to lock/unlock mutexes is using the `MutexGuard` class which will lock/unlock on construction/deconstruction.

```c++
#include <thread.hpp>

Mutex mutex;

{
  MutexGuard mutex_guard(mutex);
  // do some things with the shared resource

} //~MutexGuard() unlocks the mutex
```




