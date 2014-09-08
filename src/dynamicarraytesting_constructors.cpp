// Tests for constructors.

#include "dynamicarraytesting.hh"

// Tests the default constructor by making sure it correctly instantiates length and capacity.
void DynamicArrayTesting::defaultConstructorTest()
{
	DynamicArray<int> *array = new DynamicArray<int>();
	JTest<int>::testEquality("Default constructor test, length set", 0, array->length());
	JTest<int>::testEquality("Default constructor test: capacity set", 10, array->capacity());
	delete array;
}

// Tests the manual constructor by making sure it correctly instantiates length and capacity.
void DynamicArrayTesting::preAllocatedConstructorTest()
{
	DynamicArray<int> *array = new DynamicArray<int>(20);
	JTest<int>::testEquality("Manual constructor test, length set", 0, array->length());
	JTest<int>::testEquality("Manual constructor test, capacity set", 20, array->capacity());
	delete array;
}
