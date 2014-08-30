#include "dynamicarraytesting.hh"

void DynamicArrayTesting::pushFrontTest()
{
	DynamicArray<int> *array = new DynamicArray<int>();
	array->pushFront(1);
	JTest<int>::testEquality("Push front test, array->get(0) ?= 1", 1, array->get(0));
	JTest<int>::testEquality("Push front test, length?=1", 1, array->length());
	array->pushFront(2);
	JTest<int>::testEquality("Push front test, array->get(0) ?= 2", 2, array->get(0));
	JTest<int>::testEquality("Push front test, array->get(1) ?= 1", 1, array->get(1));
	JTest<int>::testEquality("Push front test, array->length() ?= 2", 2, array->length());
	delete array;
}

void DynamicArrayTesting::pushBackTest()
{
	DynamicArray<int> *array = new DynamicArray<int>();
	array->pushBack(1);
	JTest<int>::testEquality("Push back test, array->get(0) ?= 1", 1, array->get(0));
	JTest<int>::testEquality("Push back test, length ?= 1", 1, array->length());
	array->pushBack(2);
	JTest<int>::testEquality("Push back test, array->get(0) ?= 1", 1, array->get(0));
	JTest<int>::testEquality("Push back test, array->get(1) ?= 2", 2, array->get(1));
	JTest<int>::testEquality("Push back test, length ?= 2", 2, array->length());
	delete array;
}

