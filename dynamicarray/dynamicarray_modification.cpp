#include "dynamicarray.hh"

// Inserts the element newElement at position index in the array.
// Parameters:
// T newElement - the new element to insert into the array
// unsigned int index - the index at which to insert te new element
// Returns the element that was in position index before insertion, or NULL if the insertion did not complete because the provided index was out of bounds.
T DynamicArray<T>::insert(T newElement, unsigned int index)
{
	if(index < arrayLength)
	{
		T oldElement = this->firstElementPointer[index];
		this->firstElementPointer[index] = newElement;
		return oldElement;
	}
	return NULL;
}

// Swaps two elements in the array.
// Parameters:
// unsigned int indexOne - the index of the first item
// unsigned int indexTwo - the index of the second item
void DynamicArray<T>::swap(unsigned int indexOne, unsigned int indexTwo)
{
	if(indexOne < this->arrayLength && indexTwo < this->arrayLength)
	{
		T temp = this->firstElementPointer[indexOne];
		this->firstElementPointer[indexOne] = this->firstElementPointer[indexTwo];
		this->firstElementPointer[indexTwo] = temp;	
	}
}

// Gets the item at the specified index.
// Parameters:
// unsigned int index - the index of the item to retrieve
// Returns the item at position index, or NULL if the provided index is out of bounds.
T DynamicArray<T>::get(unsigned int index)
{
	if(index < this->arrayLength)
	{
		return this->firstElementPointer[index];
	}
	return NULL;
}

// Removes the item at the specified index.
// Parameters:
// unsigned int index - the index of the item to remove
// Returns the item after removal, or NULL if the item could not be removed because the provided index was out of bounds.
T DynamicArray<T>::remove(unsigned int index)
{
	int i;
	if(index < this->arrayLength)
	{
		// if the index being removed is in the right half of the array, it will be more efficient to
		// shift the elements on the right
		if(index > arrayLength / 2)
		{
			for(i = index + 1; i < arrayLength; i++)
			{
				this->firstElementPointer[i - 1] = this->firstElementPointer[i];
			}
		}
		else // index is in left half ot array, so it is more efficient to shift the elements on the left
		{
			for(i = index - 1; i >= 0; i--)
			{
				this->firstElementPointer[i + 1] = this->firstElementPointer[i];
			}
			firstElementPointer++; // move pointer to new front of array
		}
	}
	return NULL;
}
