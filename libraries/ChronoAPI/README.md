# ChronoAPI

## Overview

The ChronoAPI is for managing clock time (clock as in system oscillator) and calendar time.

Classes:

- [ClockTime](include/chrono/ClockTime.hpp): for reading the system oscillator clock time
- [ClockTimer](include/chrono/ClockTimer.hpp): For real-time tracking of [ClockTime](include/chrono/ClockTime.hpp)
- [DateTime](include/chrono/DateTime.hpp): for managing calendar time (down to the second)
- [MicroTime](include/chrono/MicroTime.hpp): for managing short durations of time (less than 30 minutes) using sub-second accuracy.

## Clock Time

The primary way to make use of the system oscillator clock is using the `ClockTimer` class.

```c++
#include <chrono.hpp>

ClockTimer timer;

timer.start(); //start counting (if not already started)
timer.stop(); //stop counting
timer.resume(); //start counting after stop
timer.restart(); //start counting from zero (even if already running)

//microtime comparisons
if( timer.micro_time() > 1_seconds ){
  timer.restart();
}

if( timer.micro_time() < 50_milliseconds ){
  timer.restart();
}
```

## Calendar Time

The `DateTime` class is basically a C++ wrapper for using C based `time` functions. The storage unit is `time_t`.

## MicroTime

The `MicroTime` class base unit of storage is a 32-bit value representing microseconds. It will overflow 71.5 minutes. So it is only useful for short durations.

The `MicroTime` class also provides operators for time conversion between `seconds`, `milliseconds`, `microseconds` and `nanoseconds`;

```c++
#include <chrono.hpp>

const u32 x_milliseconds;

wait(1_seconds); //same as sleep(1);
wait(x_milliseconds * 1_milliseconds); //delay

const MicroTime period = 2_seconds + 500_milliseconds;
```


