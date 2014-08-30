// This file contains methods which add elements to the array, specifically push front and push back.

#include "dynamicarray.hh"

// Adds a new element onto the front end of the array.
// Parameters:
// T newElement - the new element to be added to the array
void DynamicArray<T>::pushFront(T newElement)
{
	// reallocate internal array if front side of array is full
	if(this->dynamicArrayFront == this->internalArrayFront)	
	{
		reallocate((unsigned int)(internalArrayLength * 1.5));
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
		reallocate((unsigned int) std::log(internalArrayLength));
	}
	*dynamicArrayBack++ = newElement;
	dynamicArrayLength++;
}
