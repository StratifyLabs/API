/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
#include "test/Case.hpp"

#include "test/Test.hpp"
using namespace test;

Case::Case(Test *test, var::StringView name) {
  m_test = test;
  test->open_case(name);
}

Case::~Case() { m_test->close_case(); }
