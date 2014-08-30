// This file contains constructors and deconstructors.

#include "dynamicarray.hh"

// Default constructor - allocates an internal array of size 10
template <class T>
DynamicArray<T>::DynamicArray()
{
	this->array = new T[10];
	this->dynamicArrayLength = 0;
	this->internalArrayLength = 10;	
	this->dynamicArrayFront = &array[internalArrayLength / 2];
	this->dynamicArrayBack = &array[internalArrayLength / 2];
	this->internalArrayFront = array - sizeof(T);
	this->internalArrayBack = array + sizeof(T) * internalArrayLength;
}

// Constructor which allocates an array of size 'preAllocatedLength'.
// Parameters:
// unsigned int preAllocatedLength - the length to initially allocate the internal array
template <class T>
DynamicArray<T>::DynamicArray(unsigned int preAllocatedLength)
{
	this->array = new T[preAllocatedLength];
	this->dynamicArrayLength = 0;
	this->internalArrayLength = preAllocatedLength;
	this->dynamicArrayFront = &array[this->internalArrayLength / 2];
	this->dynamicArrayBack = &array[this->internalArrayLength / 2];
	this->internalArrayFront = array - sizeof(T);
	this->internalArrayBack = array + sizeof(T) * internalArrayLength;
}

// Deconstructor, simply deletes array.
template <class T>
DynamicArray<T>::~DynamicArray()
{
	delete [] array;
}
