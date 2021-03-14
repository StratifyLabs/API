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

## Condition Variables

The `thread::Cond` class is a wrapper for `pthread_cond` style condition variables. The class needs a reference to the associated mutex.

```c++
#include <thread.hpp>

Mutex mutex;
Cond cond(mutex);

//mutex must be locked before calling wait
//wait blocks and atomically unlocks the mutex
cond.lock().wait();

//in another thread use broadcast or signal to unblock the cond
//lock()/unlock() are optional with broadcast()
cond.lock().broadcast().unlock();

//or to just unblock ONE waiting thread
cond.lock().signal().unlock();
```

## Sched

The `Sched` class wraps posix-style `sched_` functions which allow you to change the calling thread's priority and scheduling policy.

```c++

#include <thread.hpp>

//yield the processor
Sched().yield();

// change to fifo style with priority 1
Sched().set_scheduler(Sched::SetScheduler()
  .set_policy(Sched::Policy::fifo)
  .set_priority(1));
```

## Signals

The `Signal` and `SignalHandler` classes can be used to install process level signal handling functions. These classes are wrappers for posix-style signals.

```c++
#include <thread.hpp>

void interrupt_signal_handler(int a){
  //will be executed on SIGINT
}

Signal(Signal::Number::interrupt)
  .set_handler(SignalHandler(SignalHandler::Construct()
      .set_function(interrupt_signal_handler)));


//send SIGINT to calling process
Signal(Signal::Number::interrupt).send(Sched::get_pid());
```


