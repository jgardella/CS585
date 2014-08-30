#include "dynamicarraytesting.hh"

void DynamicArrayTesting::defaultConstructorTest()
{
	DynamicArray<int> *array = new DynamicArray<int>();
	JTest<int>::testEquality("Default constructor test: length=?0", 0, array->length());
	JTest<int>::testEquality("Default constructor test: capacity=?10", 10, array->memoryUsage());
	delete array;
}

void DynamicArrayTesting::preAllocatedConstructorTest()
{
	DynamicArray<int> *array = new DynamicArray<int>(20);
	JTest<int>::testEquality("Manual constructor test: length?=0", 0, array->length());
	JTest<int>::testEquality("Manual constructor test: capacity=?20", 20, array->memoryUsage());
	delete array;
}
