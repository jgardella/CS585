// Tests if the actual value of an operation is equal to the expected value of an operation.
// Parameters:
// char* testName - the name of the test being performed
// T expectedValue - the expected result of the operation
// T actualValue - the actual result of the operation
template <class T>
static void testEquality(char* testName, T expectedValue, T actualValue)
{
	assert(expectedValue == actualValue && "[ Failed ] " << testName << ": expected value not equal to actual value (expected: " << expectedValue << ", actual: " << actualValue << ")");
	// assert passed, output positive test result
	std::cout << "[ Passed ] " << testName << endl;
}

// Tests if the result of an operation is less than a specified upper bound.
// Parameters:
// char* testName - the name of the test being performed
// T upperBound - the value which the actual value must be under for the test to pass
// T actualValue - the result of the operation
template <class T>
static void testLessThan(char* testName, T upperBound, T actualValue)
{
	assert(actualValue < upperBound && "[ Failed ] " << testName << ": actual value not less than upper bound (upperBound: " << upperBound << ", value: " << actualValue << ")");
	// assert passed, output positive test result
	std::cout << "[ Passed ] " << testName << endl;
}

// Tests if the result of an operation is greater than a specified lower bound.
// Parameters:
// char* testName - the name of the test being performed
// T lowerBound - the value which the actual value must be over for the test to pass
// T actualValue - the result of the operation
template <class T>
static void testGreaterThan(char* testName, T lowerBound, T actualValue)
{
	assert(actualValue > lowerBound && "[ Failed ] " << testName << ": actual value not greater than lower bound (lowerBound: " << lowerBound << ", value: " << actualValue << ")");
	// assert passed, output positive test result
	std::cout << "[ Passed ] " << testName << endl;
}
