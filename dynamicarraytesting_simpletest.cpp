#include "dynamicarraytesting.hh"

void DynamicArrayTesting::simpleArithmeticTest()
{
	JTest<int>::testEquality("Simple arithmetic test", 2, 1+1);
}

void DynamicArrayTesting::assignmentTest()
{
	int a = 5;
	JTest<int>::testEquality("Assignment test", 5, a);
}
