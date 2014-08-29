#include "dynamicarray.hh"

// Default constructor - allocates an array of size 10
DynamicArray<T>::DynamicArray()
{
	this->firstElementPointer = new T[10];
	this->arrayLength = 0;	
}

// Constructor which allocates an array of size 'preAllocatedLength'.
DynamicArray<T>::DynamicArray(unsigned int preAllocatedLength)
{
	this->firstElementPointer = new T[preAllocatedLength];
	this->arrayLength = 0;
}

// Deconstructor, simply deletes array.
DynamicArray<T>::~DynamicArray()
{
	delete firstElementPointer;
}
