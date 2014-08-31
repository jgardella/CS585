#include "dynamicarraytesting.hh"

int main()
{
	DynamicArrayTesting::simpleArithmeticTest();
	DynamicArrayTesting::assignmentTest();
	DynamicArrayTesting::defaultConstructorTest();
	DynamicArrayTesting::preAllocatedConstructorTest();
	DynamicArrayTesting::pushFrontTest();
	DynamicArrayTesting::pushBackTest();
	DynamicArrayTesting::recenterTest();
	DynamicArrayTesting::getTest();
	DynamicArrayTesting::insertTest();
	DynamicArrayTesting::swapTest();
	DynamicArrayTesting::removeTest();
	DynamicArrayTesting::memoryReallocationTest();
	DynamicArrayTesting::reserveTest();
	return 0;
}
