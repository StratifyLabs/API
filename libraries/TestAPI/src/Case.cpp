// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#include "test/Case.hpp"

#include "test/Test.hpp"
using namespace test;

Case::Case(Test *test, var::StringView name) {
  m_test = test;
  test->open_case(name);
}

Case::~Case() { m_test->close_case(); }
