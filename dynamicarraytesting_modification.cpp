#include "dynamicarraytesting.hh"

// Tests the swap method of dynamicarray by adding two elements, swapping them, and then checking to make sure
// they were correctly swapped.
void DynamicArrayTesting::swapTest()
{
	DynamicArray<int> *array = new DynamicArray<int>();
	array->pushFront(1);
	array->pushBack(2);
	array->swap(0, 1);
	JTest<int>::testEquality("Swap test, element at indexTwo is in indexOne", 2, array->get(0));
	JTest<int>::testEquality("Swap test, element at indexOne is in indexTwo", 1, array->get(1));
	delete array;
}

// Tests the insert method of dynamic array by adding one element, then inserting a new element in its position, checking if the replaced element is returned and the
// inserted element is in the correct position.
void DynamicArrayTesting::insertTest()
{
	DynamicArray<int> *array = new DynamicArray<int>();
	array->pushBack(1);
	int replacedElement = array->insert(2, 0);
	JTest<int>::testEquality("Insert test, replaced element returned", 1, replacedElement);
	JTest<int>::testEquality("Insert test, inserted element is in correct position", 2, array->get(0));
	delete array;	
}

// Tests the get method of dynamic array by inserting an element and then getting that element and checking that the corrent element is returned.
void DynamicArrayTesting::getTest()
{
	DynamicArray<int> *array = new DynamicArray<int>();
	array->pushBack(0);
	JTest<int>::testEquality("Get test, calling get returns correct element", 0, array->get(0));
	delete array;
}

// Tests the remove methodby inserting 5 elements, removing the middle one, and then checking that the remaining elements are properly shifted and the length is decreased.
void DynamicArrayTesting::removeTest()
{
	int i;
	DynamicArray<int> *array = new DynamicArray<int>();
	array->pushBack(1);
	array->pushBack(2);
	array->pushBack(3);
	array->pushBack(4);
	array->pushBack(5);
	int removedElement = array->remove(2);
	JTest<int>::testEquality("Remove test, removed element correctly returned", 3, removedElement);
	JTest<int>::testEquality("Remove test, element one did not move", 1, array->get(0));
	JTest<int>::testEquality("Remove test, element two did not move", 2, array->get(1));
	JTest<int>::testEquality("Remove test, element four is now element three", 4, array->get(2));
	JTest<int>::testEquality("Remove test, element five is now element four", 5, array->get(3));
	JTest<int>::testEquality("Remove tset, array length decreased", 4, array->length());
	delete array;
}
