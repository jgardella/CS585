#include "dynamicarray.hh"
#include "jtest.hh"

void dynamicArraySimpleArithmeticTest()
{
	JTest<int>::testEquality("Simple arithmetic test", 2, 1+1);
}

void dynamicArrayAssignmentTest()
{
	int a = 5;
	JTest<int>::testEquality("Assignment test", 5, a);
}

// Tests the default constructor by making sure it correctly instantiates length and capacity.
void dynamicArrayDefaultConstructorTest()
{
	DynamicArray<int> *array = new DynamicArray<int>();
	JTest<int>::testEquality("Default constructor test, length set", 0, array->length());
	JTest<int>::testEquality("Default constructor test: capacity set", 10, array->capacity());
	delete array;
}

// Tests the manual constructor by making sure it correctly instantiates length and capacity.
void dynamicArrayPreAllocatedConstructorTest()
{
	DynamicArray<int> *array = new DynamicArray<int>(20);
	JTest<int>::testEquality("Manual constructor test, length set", 0, array->length());
	JTest<int>::testEquality("Manual constructor test, capacity set", 20, array->capacity());
	delete array;
}

// Tests if memory is proprely reallocated when the array's capacity is exceeded on either the left or right side.
void dynamicArrayMemoryReallocationTest()
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
void dynamicArrayReserveTest()
{
	DynamicArray<int> *array = new DynamicArray<int>();
	array->reserve(100);
	JTest<int>::testEquality("Reserve test, array capacity expanded", 100, array->capacity());
	array->reserve(50);
	JTest<int>::testEquality("Reserve test, array capacity not expanded", 100, array->capacity());
	delete array;
}

// Adds a lot of elements to the array to check that it is correctly reallocated.
void dynamicArraySeveralReallocationTest()
{
	DynamicArray<int> *array = new DynamicArray<int>();
	int i;
	for(i = 1; i <= 100; i++)
	{
		array->pushBack(i);
	}
	bool isProperlyExpanded = true;
	for(i = 0; i < array->length() && isProperlyExpanded; i++)
	{
		if(array->get(i) != i + 1)
			isProperlyExpanded = false;
	}
	JTest<int>::testEquality("Memory reallocation test, elements added and array reallocated several times", 1, isProperlyExpanded);
}

// Tests the swap method of dynamicarray by adding two elements, swapping them, and then checking to make sure
// they were correctly swapped.
void dynamicArraySwapTest()
{
	DynamicArray<int> *array = new DynamicArray<int>();
	array->pushFront(1);
	array->pushBack(2);
	array->swap(0, 1);
	JTest<int>::testEquality("Swap test, element at indexTwo is in indexOne", 2, array->get(0));
	JTest<int>::testEquality("Swap test, element at indexOne is in indexTwo", 1, array->get(1));
	delete array;
}

// Tests the set method of dynamic array by adding one element, then setting a new element in its position, checking if the new element is in the correct position.
void dynamicArraySetTest()
{
	DynamicArray<int> *array = new DynamicArray<int>();
	array->pushBack(1);
	int replacedElement = array->set(2, 0);
	JTest<int>::testEquality("Set test, replaced element returned", 1, replacedElement);
	JTest<int>::testEquality("Set test, inserted element is in correct position", 2, array->get(0));
	delete array;	
}

// Tests the get method of dynamic array by inserting an element and then getting that element and checking that the corrent element is returned.
void dynamicArrayGetTest()
{
	DynamicArray<int> *array = new DynamicArray<int>();
	array->pushBack(0);
	JTest<int>::testEquality("Get test, calling get returns correct element", 0, array->get(0));
	delete array;
}

// Tests the remove methodby inserting 5 elements, removing the middle one, and then checking that the remaining elements are properly shifted and the length is decreased.
// There are separate tests for removing from the left half and right half of the array because the remove method behaves differently depending on which side of the array the item
// is removed from.
void dynamicArrayRemoveTest()
{
	int i;
	DynamicArray<int> *array = new DynamicArray<int>();
	array->pushBack(1);
	int removedElement = array->remove(0);
	JTest<int>::testEquality("Remove test, remove with only one element, element returned", 1, removedElement);
	JTest<int>::testEquality("Remove test, length decremented", 0, array->length());

	array->pushBack(1);
	array->pushBack(2);
	array->pushBack(3);
	array->pushBack(4);
	array->pushBack(5);
	// Test remove method when an item is removed from the left half of the array.
	removedElement = array->remove(2);
	JTest<int>::testEquality("Left side remove test, removed element correctly returned", 3, removedElement);
	JTest<int>::testEquality("Left side remove test, element one did not move", 1, array->get(0));
	JTest<int>::testEquality("Left side remove test, element two did not move", 2, array->get(1));
	JTest<int>::testEquality("Left side remove test, element four is now element three", 4, array->get(2));
	JTest<int>::testEquality("Left side remove test, element five is now element four", 5, array->get(3));
	JTest<int>::testEquality("Left side remove test, array length decreased", 4, array->length());
	
	// Test remove method when an item is removed from the right half of the array.
	array->pushBack(6);
	array->pushBack(7);
	removedElement = array->remove(3);
	JTest<int>::testEquality("Right side remove test, removed element correctly returned", 5, removedElement);
	JTest<int>::testEquality("Right side remove test, element one did not move", 1, array->get(0));
	JTest<int>::testEquality("Right side remove test, element two did not move", 2, array->get(1));
	JTest<int>::testEquality("Right side remove test, element three did not move", 4, array->get(2));
	JTest<int>::testEquality("Right side remove test, element five is now element four", 6, array->get(3));
	JTest<int>::testEquality("Right side remove test, element six is now element five", 7, array->get(4));
	delete array;
}

// Tests push front method by pushing several element to the front and checking that they have been properly pushed.
void dynamicArrayPushFrontTest()
{
	DynamicArray<int> *array = new DynamicArray<int>();
	array->pushFront(1);
	JTest<int>::testEquality("Push front test, element one pushed to front", 1, array->get(0));
	JTest<int>::testEquality("Push front test, length incremented", 1, array->length());
	array->pushFront(2);
	JTest<int>::testEquality("Push front test, element two pushed to front", 2, array->get(0));
	JTest<int>::testEquality("Push front test, element one now in position 2", 1, array->get(1));
	JTest<int>::testEquality("Push front test, length incremented", 2, array->length());
	delete array;
}

// Tests the push back method by pushing several elements to the back and checking that they have been properly pushed.
void dynamicArrayPushBackTest()
{
	DynamicArray<int> *array = new DynamicArray<int>();
	array->pushBack(1);
	JTest<int>::testEquality("Push back test, element one pushed to back", 1, array->get(0));
	JTest<int>::testEquality("Push back test, length incremented", 1, array->length());
	array->pushBack(2);
	JTest<int>::testEquality("Push back test, element one still in position one", 1, array->get(0));
	JTest<int>::testEquality("Push back test, element two in position two", 2, array->get(1));
	JTest<int>::testEquality("Push back test, length incremented", 2, array->length());
	delete array;
}

// Tests the recenter method by causing an overflow on the front and back of the array.
void dynamicArrayRecenterTest()
{
	bool areElementsCorrectlyRepositioned;
	int i;
	DynamicArray<int> *array = new DynamicArray<int>();
	array->pushFront(10);
	array->pushFront(9);
	array->pushFront(8);
	array->pushFront(7);
	array->pushFront(6);
	array->pushFront(5);
	
	areElementsCorrectlyRepositioned = true;
	for(i = 0; i < array->length() && areElementsCorrectlyRepositioned; i++)
	{
		if(array->get(i) != i + 5)
		{
			areElementsCorrectlyRepositioned = false;
		}
	}

	JTest<int>::testEquality("Recenter test front, elements correctly repositioned", true, areElementsCorrectlyRepositioned);
	JTest<int>::testEquality("Recenter test front, capacity unchanged", 10, array->capacity());

	array->pushFront(4);
	array->pushFront(3);
	array->pushFront(2);
	array->pushFront(1);

	areElementsCorrectlyRepositioned = true;
	for(i = 0; i < array->length() && areElementsCorrectlyRepositioned; i++)
	{
		if(array->get(i) != i + 1)
		{
			areElementsCorrectlyRepositioned = false;
		}
	}

	JTest<int>::testEquality("Recenter test front, elements correctly repositioned", true, areElementsCorrectlyRepositioned);
	JTest<int>::testEquality("Recenter test front, capacity unchanged", 10, array->capacity());
	
	delete array;

	array = new DynamicArray<int>();
	array->pushBack(1);
	array->pushBack(2);
	array->pushBack(3);
	array->pushBack(4);
	array->pushBack(5);
	array->pushBack(6);
	
	areElementsCorrectlyRepositioned = true;
	for(i = 0; i < array->length() && areElementsCorrectlyRepositioned; i++)
	{
		if(array->get(i) != i + 1)
		{
			areElementsCorrectlyRepositioned = false;
		}
	}

	JTest<int>::testEquality("Recenter test back, elements correctly repositioned", true, areElementsCorrectlyRepositioned);
	JTest<int>::testEquality("Recenter test back, capacity unchanged", 10, array->capacity());

	array->pushBack(7);
	array->pushBack(8);
	array->pushBack(9);
	array->pushBack(10);

	areElementsCorrectlyRepositioned = true;
	for(i = 0; i < array->length() && areElementsCorrectlyRepositioned; i++)
	{
		if(array->get(i) != i + 1)
		{
			areElementsCorrectlyRepositioned = false;
		}
	}

	JTest<int>::testEquality("Recenter test back, elements correctly repositioned", true, areElementsCorrectlyRepositioned);
	JTest<int>::testEquality("Recenter test back, capacity unchanged", 10, array->capacity());
	delete array;
}

int main()
{
	// -------------------- DYNAMIC ARRAY TESTS -------------------- 
	dynamicArraySimpleArithmeticTest();
	dynamicArrayAssignmentTest();
	dynamicArrayDefaultConstructorTest();
	dynamicArrayPreAllocatedConstructorTest();
	dynamicArrayMemoryReallocationTest();
	dynamicArrayReserveTest();
	dynamicArraySeveralReallocationTest();
	dynamicArraySwapTest();
	dynamicArraySetTest();
	dynamicArrayGetTest();
	dynamicArrayRemoveTest();
	dynamicArrayPushFrontTest();
	dynamicArrayPushBackTest();
	dynamicArrayRecenterTest();
	// -------------------- END DYNAMIC ARRAY TESTS -------------------- 
	
	
	return 0;
}
