/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.

#ifndef CHRONO_API_CHRONO_HPP_
#define CHRONO_API_CHRONO_HPP_

/*! \brief Chrono (managing time, timers and clocks)
 *
 *	#### [Example Code on Github](https://github.com/StratifyLabs/StratifyDocsCode/blob/master/StratifyAPI/code/chrono/src/main.cpp)
 *
 * The chrono namespace includes the following time-measurement
 * objects.
 *
 * - Microseconds: 32-bit value for microseconds
 * - ClockTime: 64-bit value for seconds and nanoseconds (clock as in CPU clock)
 * - Time: 32-bit value in seconds (basically a time_t object)
 *
 * The parent object for all chrono items is api::WorkObject or api::InfoObject.
 * Both of the top level objects provide a way to insert a static delay.
 *
 * ```
 * //md2code:include
 * #include <sapi/chrono.hpp>
 * ```
 *
 * ```
 * //md2code:main
 * wait(Seconds(1)); //wait for one second
 * wait(Milliseconds(1000)); //wait for one second
 * wait(Microseconds(1000000)); //wait for one second
 *
 * ClockTime clock_time;
 * wait(clock_time); //wait based on a clock time value
 *
 * Microseconds microseconds;
 * microseconds = Milliseconds(100);
 * wait(microseconds); //wait based on a microsecond value
 * ```
 *
 *
 */
namespace chrono {}

#include "chrono/ClockTime.hpp"
#include "chrono/ClockTimer.hpp"
#include "chrono/DateTime.hpp"
#include "chrono/MicroTime.hpp"

using namespace chrono;


#endif /* CHRONO_API_CHRONO_HPP_ */
