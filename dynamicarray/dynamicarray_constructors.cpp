#include "dynamicarray.hh"

DynamicArray<T>::DynamicArray()
{
	this->firstElementPointer = new int[10];
	this->arrayLength = 0;	
}

DynamicArray<T>::DynamicArray(unsigned int preAllocatedLength)
{
	this->firstElementPointer = new int[preAllocatedLength];
	this->arrayLength = 0;
}

DynamicArray<T>::~DynamicArray()
{
	delete firstElementPointer;
}
