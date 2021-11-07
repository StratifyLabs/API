// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef SOSAPI_HPP
#define SOSAPI_HPP

namespace sys {}

#include "sys/Cli.hpp"
#include "sys/System.hpp"
#include "sys/TemporaryDirectory.hpp"
#include "sys/Version.hpp"

#if defined __link
#include "sys/Process.hpp"
#endif

using namespace sys;

#endif /* SOSAPI_HPP */
