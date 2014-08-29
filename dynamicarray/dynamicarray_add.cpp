#include "dynamicarray.hh"

// Adds a new element onto the front end of the array.
// Parameters:
// T newElement - the new element to be added to the array
DynamicArray<T>::pushFront(T newElement)
{
	this->firstElementPointer--;
	firstElementPointer[0] = newElement;
	arrayLength++;
}

// Adds a new element onto the back end of the array.
// Parameters:
// T newElement - the new element to be added to the array
DynamicArray<T>::pushBack(T newElement)
{
	firstElementPointer[arrayLength] = new Element;
	arrayLength++;
}
