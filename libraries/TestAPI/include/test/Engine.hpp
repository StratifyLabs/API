/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
#ifndef SAPI_TEST_ENGINE_HPP_
#define SAPI_TEST_ENGINE_HPP_

/*! \cond */

#include "var/Queue.hpp"
#include "Test.hpp"

namespace test {

class Engine : public var::Queue<Test *> {
public:
  Engine();
};

} // namespace test

/*! \endcond */

#endif // SAPI_TEST_ENGINE_HPP_
