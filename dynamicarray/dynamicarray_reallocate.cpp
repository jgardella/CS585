#include "dynamicarray.hh"

// Reallocates the internal array to the size specified by newSize.
// Parameters:
// unsigned int newSize - the new size for the internal array (must be greater than the current length of the dynamic array)
void DynamicArray<T>::reallocate(unsigned int newSize)
{
	int i;
	T[] temp;
	if(newSize > dynamicArrayLength)
	{
		// allocate new array of specified size
		temp = new T[newSize];
		// fill array centrally, such that there is equal free space on the front and back of the internal array
		for(i = 0; i < dynamicArrayLength; i++)
		{
			temp[i + (newSize - dynamicArrayLength) / 2] = dynamicArrayFront[i + 1];
		}
		// adjust front and back pointers to point to correct location in new array
		dynamicArrayFront = &temp[(newSize - dynamicArrayLength) / 2] - sizeof(T);
		dynamicArrayBack = &temp[(newSize + dynamicArrayLength) / 2];
		internalArrayFront = temp - sizeof(T);
		internalArrayBack = temp + sizeof(T) * newSize;
		internalArrayLength = newSize;
		// delete old array and change pointer to point to new array
		delete [] array;
		array = temp;
	}
}

// Reallocates the internal array such that it can hold the number of elements specified by sizeToReserve.
// Parameters:
// unsigned int sizeToReserve - the size to reserve for the internal array (must be greater than the current length of the internal array)
void DynamicArray<T>::reserve(unsigned int sizeToReserve)
{
	if(sizeToReserve > internalArrayLength)
	{
		reallocate(sizeToReserve);
	}
}
