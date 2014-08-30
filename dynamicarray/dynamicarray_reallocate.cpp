#include "dynamicarray.hh"

// Reallocates a new internal array of twice the size of the original internal array and copies the elements
// of the old array over.
void DynamicArray<T>::reallocate()
{
	int i;
	// allocate new array of twice size of old array
	T[] temp = new T[internalArrayLength * 2];
	// fill array centrally, such that there is equal free space on the front and back of the internal array
	for(i = 0; i < internalArrayLength; i++)
	{
		temp[i + internalArrayLength / 2] = array[i];
	}
	// adjust front and back pointers to point to correct location in new array
	dynamicArrayFront = &temp[internalArrayLength / 2];
	dynamicArrayBack = &temp[3 * internalArrayLength / 2];
	internalArrayFront = temp - sizeof(T);
	internalArrayBack = temp + sizeof(T) * internalArrayLength * 2;
	internalArrayLength *= 2;
	// delete old array and change pointer to point to new array
	delete [] array;
	array = temp;
}
