/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.
#ifndef SAPI_TEST_ENGINE_HPP_
#define SAPI_TEST_ENGINE_HPP_

/*! \cond */

#include "Test.hpp"
#include "../var/Queue.hpp"

namespace test {

class Engine : public var::Queue<Test*> {
public:
	Engine();



};

}

/*! \endcond */


#endif // SAPI_TEST_ENGINE_HPP_
