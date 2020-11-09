/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.

#ifndef THREADAPI_THREAD_HPP_
#define THREADAPI_THREAD_HPP_

/*! \brief System Access (POSIX wrappers)
 * \details The sys namespace includes classes for
 * accessing the system.
 *
 */
namespace thread {}

#include "thread/Mutex.hpp"
#include "thread/Sched.hpp"
#include "thread/Sem.hpp"
#include "thread/Signal.hpp"
#include "thread/Thread.hpp"

using namespace thread;

#endif /* THREADAPI_THREAD_HPP_ */
