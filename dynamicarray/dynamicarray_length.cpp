// This file contains methods for getting the length of both the dynamic array and the internal array.

#include "dynamicarray.hh"

// Returns the number of elements in the dynamic array.
template <class T>
unsigned int DynamicArray<T>::length()
{
	return dynamicArrayLength;
}

// Returns the length of the internal array.
template <class T>
unsigned int DynamicArray<T>::memoryUsage()
{
	return internalArrayLength;
}
