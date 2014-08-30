#include "dynamicarraytesting.hh"

// Tests the swap method of dynamicarray by adding two elements, swapping them, and then checking to make sure
// they were correctly swapped.
void DynamicArrayTesting::swapTest()
{
	DynamicArray<int> *array = new DynamicArray<int>();
	array->pushFront(1);
	array->pushBack(2);
	array->swap(0, 1);
	JTest<int>::testEquality("Swap test, get(0) ?= 2", 2, array->get(0));
	JTest<int>::testEquality("Swap test, get(1) ?= 1", 1, array->get(1));
}
