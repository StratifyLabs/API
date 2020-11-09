/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.
#ifndef SAPI_TEST_FUNCTION_HPP_
#define SAPI_TEST_FUNCTION_HPP_

#include <mcu/types.h>
#include <errno.h>
#include <cstdio>
#include <cstring>
#include <limits.h>
#include <type_traits>

#include "Test.hpp"
#include "Case.hpp"
#include "../var/ConstString.hpp"

namespace test {

/*! \brief Function Test Class Template
 * \details The Function template class is designed
 * to test any arbitrary C or C++ function (not member
 * methods, just regular functions).
 *
 * The following is an example that tests open()
 * for various error conditions.
 *
 * \code
 *
 * #include <sapi/test.hpp>
 *
 * //because open() has variable arguments we wrap it to make it work with this class
 * int test_open(const char * path, int o_flags, int o_mode){
 *   return open(path, o_flags, o_mode);
 * }
 *
 * bool is_test_enabled = true;
 *
 * Test::initilize("test name", "0.1");
 *
 * if( is_test_enabled ){
 *   //when test is constructed
 *   Function<int, const char *, int, int> open_function_test("open", test_open);
 *
 *   open_function_test.execute("NO EXIST Read only", -1, ENOENT, "/home/non-existing-file.txt", O_RDONLY, 0);
 *   open_function_test.execute("NO EXIST Read Write", -1, ENOENT, "/home/non-existing-file.txt", O_RDWR, 0);
 *   open_function_test.execute("NO EXIST Read Write", -1, ENAMETOOLONG, "/home/non-existing-file-too-long-too-long-too-long-too-long-too-long-too-long-too-long-too-long-too-long-too-long.txt", O_RDWR, 0);
 *
 *   //open_function_test will call the deconstructor here before Test::finalize()
 * }
 *
 *
 * Test::finalize();
 *
 *
 * \endcode
 *
 *
 */
template<typename return_type, typename...args> class Function : public Test {
public:

	using ExpectedError = arg::Argument<int, struct FunctionExpectedErrorTag>;
	using ExpectedReturn = arg::Argument<return_type, struct FunctionExpectedErrorTag>;


	/*! \details Constructs a new function test object.
		*
		* @param test_name The name of the test
		* @param function A function pointer to the function that will be tested
		* @param parent The parent test or zero if there is no parent
		*
		*/
	Function(
			const var::String & test_name,
			return_type (*function)(args...),
			Test * parent = 0) :
		Test(test_name, parent){
		m_function = function;
	}

	~Function(){}

	/*! \details Executes a test case.
		*
		* @param case_name The name of the case
		* @param expected_value The expected return value
		* @param expected_errno The expected error number
		* @param arguments The arguments to pass to the test function
		* @return The value that the tested function returns
		*
		*/
	return_type execute_case_with_expected_return(const char * case_name, return_type expected_value, int expected_errno, args... arguments){
		return_type return_value;
		bool result = true;
		errno = 0;


		m_case_name = name();
		m_case_name += "(";
		int dummy[sizeof...(arguments)] = { (build_argument(arguments), 0)... };
		m_case_name.erase(
					var::String::Position(m_case_name.length()-1)
					);
		m_case_name << ")";

		{

			Case case_guard(this, m_case_name);

			case_timer().start();
			return_value = m_function(arguments...);
			case_timer().stop();

			if( expected_value < 0 ){
				if( return_value < 0 ){
					//good
				} else {
					//bad
				}
			} else {
				if( return_value == expected_value ){
					//good
				} else {
					//bad
				}
			}


			if( (return_value >= 0) && return_value != expected_value ){
				result = false;
				print_case_message("expected return %d != actual return %d", expected_value, return_value);
			} else {
				print_case_message("expected value returned");
			}

			if( expected_errno > 0 ){
				if( expected_errno != errno ){
					result = false;
					print_case_message("expected errno %d != actual errno %d", expected_errno, errno);
				} else {
					print_case_message("expected errno match: %d", errno);
				}
			}

		}
		return return_value;
	}

	return_type expect_result(
			return_type expected_result,
			args... arguments
			){
		return_type return_result;
		bool result = true;
		errno = 0;

		m_case_name = name();
		m_case_name += "(";
		int dummy[sizeof...(arguments)] = { (build_argument(arguments), 0)... };
		m_case_name.erase(
					var::String::Position(m_case_name.length()-1)
					);
		m_case_name << ")";

		errno = 0;
		{
			Case case_guard(this, m_case_name);
			case_timer().start();
			return_result = m_function(arguments...);
			case_timer().stop();

			if( return_result != expected_result ){
				print_case_failed(
							"result is not equal to expected result"
							);
			}

		}
		return return_result;
	}

	return_type execute_case_with_less_than_zero_on_error(const char * case_name, int expected_errno, args... arguments){
		return_type return_value;
		bool result = true;
		errno = 0;

		m_case_name = name();
		m_case_name += "(";
		int dummy[sizeof...(arguments)] = { (build_argument(arguments), 0)... };
		m_case_name.erase(
					var::String::Position(m_case_name.length()-1)
					);
		m_case_name << ")";

		{
			Case case_guard(this, m_case_name);
			case_timer().start();
			return_value = m_function(arguments...);
			case_timer().stop();

			if( expected_errno > 0 ){

				if( return_value >= 0 ){
					print_case_message("expected an error but returned: %d", return_value);
					result = false;
				}

				if( expected_errno != errno ){
					result = false;
					print_case_message("expected errno %d != actual errno %d", expected_errno, errno);
				} else {
					print_case_message("expected errno match: %d", errno);
				}

			} else {

				if( return_value < 0 ){
					result = false;
					print_case_message("expected success but ret: %d errno: %d", return_value, errno);
				} else {
					print_case_message("returned: %d", return_value);
				}

			}

		}
		return return_value;
	}

	return_type expect_error(
			int expected_errno,
			args... arguments
			){
		return_type return_value;
		bool result = true;
		errno = 0;

		m_case_name = name();
		m_case_name += "(";
		int dummy[sizeof...(arguments)] = { (build_argument(arguments), 0)... };
		m_case_name.erase(
					var::String::Position(m_case_name.length()-1)
					);
		m_case_name << ")";

		errno = 0;
		{
			Case case_guard(this, m_case_name);
			case_timer().start();
			return_value = m_function(arguments...);
			case_timer().stop();

			if( errno != expected_errno ){
				print_case_failed(
							"expected errno %d != actual errno %d",
							expected_errno,
							errno
							);
			}

		}
		return return_value;

	}


private:

	template<typename T> int build_argument(const T & t){
		var::String argument;
		if( std::is_integral<T>::value == true ){
			argument.format("%d,", t);
		} else

			if( std::is_pointer<T>::value == true ){
				argument.format("%s,", t);
			} else

				if( std::is_floating_point<T>::value == true ){
					argument.format("%f,", t);
				} else {
					argument = "?,";
				}

		m_case_name.append(argument);

		return 0;
	}

	return_type (*m_function)(args...);

	var::String m_case_name;
};

}

#endif // SAPI_TEST_FUNCTION_HPP_
