// Tests for memory reallocation.

#include "dynamicarraytesting.hh"

// Tests if memory is proprely reallocated when the array's capacity is exceeded on either the left or right side.
void DynamicArrayTesting::memoryReallocationTest()
{
	// Test array overflow on back side.
	DynamicArray<int> *array = new DynamicArray<int>();
	array->pushBack(1);
	array->pushBack(2);
	array->pushBack(3);
	array->pushBack(4);
	array->pushBack(5);
	array->pushBack(6);
	array->pushBack(7);
	array->pushBack(8);
	array->pushBack(9);
	array->pushBack(10);
	array->pushBack(11);
	JTest<int>::testEquality("Back memory reallocation test, array capacity expanded to hold more items", 15, array->capacity());
	JTest<int>::testEquality("Back memory reallocation test, element which surpassed capacity has been added", 11, array->get(10));
	delete array;
	
	// Test array overflow on front side.
	array = new DynamicArray<int>();
	array->pushFront(1);
	array->pushFront(2);
	array->pushFront(3);
	array->pushFront(4);
	array->pushFront(5);
	array->pushFront(6);
	array->pushFront(7);
	array->pushFront(8);
	array->pushFront(9);
	array->pushFront(10);
	array->pushFront(11);
	JTest<int>::testEquality("Front memory reallocation test, array capacity expanded to hold more items", 15, array->capacity());
	JTest<int>::testEquality("Front memory reallocation test, element which surpassed capacity has been added", 11, array->get(0));
	delete array;
}

// Tests that the reserve method correctly expands the array's capacity.
void DynamicArrayTesting::reserveTest()
{
	DynamicArray<int> *array = new DynamicArray<int>();
	array->reserve(100);
	JTest<int>::testEquality("Reserve test, array capacity expanded", 100, array->capacity());
	array->reserve(50);
	JTest<int>::testEquality("Reserve test, array capacity not expanded", 100, array->capacity());
	delete array;
}

// Adds a lot of elements to the array to check that it is correctly reallocated.
void DynamicArrayTesting::severalReallocationTest()
{
	DynamicArray<int> *array = new DynamicArray<int>();
	int i;
	for(i = 1; i <= 100; i++)
	{
		array->pushBack(i);
	}
	bool properlyExpanded = true;
	for(i = 0; i < array->length() && properlyExpanded; i++)
	{
		if(array->get(i) != i + 1)
			properlyExpanded = false;
	}
	JTest<int>::testEquality("Memory reallocation test, elements added and array reallocated several times.", 1, properlyExpanded);
}
