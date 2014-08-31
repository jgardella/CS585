// Tests for push methods.

#include "dynamicarraytesting.hh"

// Tests push front method by pushing several element to the front and checking that they have been properly pushed.
void DynamicArrayTesting::pushFrontTest()
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
void DynamicArrayTesting::pushBackTest()
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
void DynamicArrayTesting::recenterTest()
{
	bool elementsCorrectlyRepositioned;
	int i;
	DynamicArray<int> *array = new DynamicArray<int>();
	array->pushFront(6);
	array->pushFront(5);
	array->pushFront(4);
	array->pushFront(3);
	array->pushFront(2);
	array->pushFront(1);
	
	elementsCorrectlyRepositioned = true;
	for(i = 0; i < array->length() && elementsCorrectlyRepositioned; i++)
	{
		if(array->get(i) != i + 1)
		{
			elementsCorrectlyRepositioned = false;
		}
	}

	JTest<int>::testEquality("Recenter test front, elements correctly repositioned", true, elementsCorrectlyRepositioned);
	JTest<int>::testEquality("Recenter test front, capacity unchanged", 10, array->capacity());

	array->pushBack(7);
	array->pushBack(8);
	array->pushBack(9);

	elementsCorrectlyRepositioned = true;
	for(i = 0; i < array->length() && elementsCorrectlyRepositioned; i++)
	{
		if(array->get(i) != i + 1)
		{
			elementsCorrectlyRepositioned = false;
		}
	}

	JTest<int>::testEquality("Recenter test back, elements correctly repositioned", true, elementsCorrectlyRepositioned);
	JTest<int>::testEquality("Recenter test back, capacity unchanged", 10, array->capacity());

	delete array;
}
