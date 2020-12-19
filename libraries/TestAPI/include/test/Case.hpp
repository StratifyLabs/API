// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef SAPI_TEST_CASE_HPP_
#define SAPI_TEST_CASE_HPP_

#include "var/String.hpp"

namespace test {

class Test;

class Case {
public:
  Case(Test *test, var::StringView name);
  ~Case();

private:
  Test *m_test;
};

} // namespace test

#endif // SAPI_TEST_CASE_HPP_
