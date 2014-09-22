#ifndef _JTEST_HH_
#define _JTEST_HH_

#include <assert.h>
#include <iostream>

// Testing framework
template <class T> 
class JTest
{
	public:
		// Tests if the actual value of an operation is equal to the expected value of an operation.
		// Parameters:
		// char* testName - the name of the test being performed
		// T expectedValue - the expected result of the operation
		// T actualValue - the actual result of the operation
		static void testEquality(const char* testName, T expectedValue, T actualValue)
		{
			if(expectedValue != actualValue)
			{
				std::cout << "[ Failed ] " << testName << ": expected value not equal to actual value (expected: " << expectedValue << ", actual: " << actualValue << ")" << std::endl;
			}
			assert(expectedValue == actualValue);
			// assert passed, output positive test result
			std::cout << "[ Passed ] " << testName << std::endl;
		}
		
		// Tests if the actual string value of an operation is equal to the expected string value of an operation.
		// Parameters:
		// char* testName - the name of the test being performed
		// string expectedValue - the expected string result of the operation
		// string actualValue - the actual string result of the operation	
		static void testEqualityStr(const char* testName, std::string expectedValue, std::string actualValue)
		{
			if(expectedValue.compare(actualValue) != 0)
			{
				std::cout << "[ Failed ] " << testName << ": expected value not equal to actual value (expected: " << expectedValue << ", actual: " << actualValue << ")" << std::endl;
			}
			assert(expectedValue.compare(actualValue) == 0);
			// assert passed, output positive test result
			std::cout << "[ Passed ] " << testName << std::endl;
		}

		// Tests if the actual value of an operation is not equal to a certain value.
		// Parameters:
		// char* testName - the name of the test being performed
		// T unexpectedValue - the value which the actual value should not be
		// T actualValue - the actual result of the operation
		static void testInequality(const char* testName, T unexpectedValue, T actualValue)
		{
			if(unexpectedValue == actualValue)
			{
				std::cout << "[ Failed ] " << testName << ": actual value equal to unexpected value (unexpected: " << unexpectedValue << ", actual: " << actualValue << ")" << std::endl;
			}
			assert(unexpectedValue != actualValue);
			// assert passed, output positive test result
			std::cout << "[ Passed ] " << testName << std::endl;
		}

		// Tests if the result of an operation is less than a specified upper bound.
		// Parameters:
		// char* testName - the name of the test being performed
		// T upperBound - the value which the actual value must be under for the test to pass
		// T actualValue - the result of the operation
		static void testLessThan(const char* testName, T upperBound, T actualValue)
		{
			if(actualValue >= upperBound)
			{
				std::cout << "[ Failed ] " << testName << ": expected value exceeded upper bound (upper bound: " << upperBound << ", actual: " << actualValue << ")" << std::endl;
			}
			assert(actualValue < upperBound);
			// assert passed, output positive test result
			std::cout << "[ Passed ] " << testName << std::endl;
		}

		// Tests if the result of an operation is greater than a specified lower bound.
		// Parameters:
		// char* testName - the name of the test being performed
		// T lowerBound - the value which the actual value must be over for the test to pass
		// T actualValue - the result of the operation
		static void testGreaterThan(const char* testName, T lowerBound, T actualValue)
		{
			if(actualValue <= lowerBound)
			{
				std::cout << "[ Failed ] " << testName << ": expected value exceeded lower bound (lower bound: " << lowerBound << ", actual: " << actualValue << ")" << std::endl;
			}
			assert(actualValue > lowerBound);
			// assert passed, output positive test result
			std::cout << "[ Passed ] " << testName << std::endl;
		}
};

#endif
