#include "dynamicarray.hh"

// Returns the number of elements in the dynamic array.
unsigned int DynamicArray<T>::length()
{
	return dynamicArrayLength;
}

// Returns the length of the internal array.
unsigned int DynamicArray<T>::memoryUsage()
{
	return internalArrayLength;
}
