#include "dynamicarray.hh"

// Adds a new element onto the front end of the array.
// Parameters:
// T newElement - the new element to be added to the array
void DynamicArray<T>::pushFront(T newElement)
{
	// reallocate internal array if front side of array is full
	if(this->dynamicArrayFront == this->internalArrayFront)	
	{
		reallocate();
	}
	*dynamicArrayFront-- = newElement;
	dynamicArrayLength++;
}

// Adds a new element onto the back end of the array.
// Parameters:
// T newElement - the new element to be added to the array
void DynamicArray<T>::pushBack(T newElement)
{
	// reallocate internal array if back side of array is full
	if(this->dynamicArrayBack == this->internalArrayBack)
	{
		reallocate();
	}
	*dynamicArrayBack++ = newElement;
	dynamicArrayLength++;
}
