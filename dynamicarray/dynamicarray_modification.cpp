// This file contains methods for modifying the contents of the dynamic array, specifically insert, swap, get, and remove.

#include "dynamicarray.hh"

// Inserts the element newElement at position index in the array.
// Parameters:
// T newElement - the new element to insert into the array
// unsigned int index - the index at which to insert te new element
// Returns the element that was in position index before insertion, or NULL if the insertion did not complete because the provided index was out of bounds.
template <class T>
T DynamicArray<T>::insert(T newElement, unsigned int index)
{
	if(index < dynamicArrayLength)
	{
		T oldElement = this->dynamicArrayFront[index + 1];
		this->dynamicArrayFront[index + 1] = newElement;
		return oldElement;
	}
	return NULL;
}

// Swaps two elements in the array.
// Parameters:
// unsigned int indexOne - the index of the first item
// unsigned int indexTwo - the index of the second item
template <class T>
void DynamicArray<T>::swap(unsigned int indexOne, unsigned int indexTwo)
{
	if(indexOne < this->dynamicArrayLength && indexTwo < this->dynamicArrayLength)
	{
		T temp = this->dynamicArrayFront[indexOne + 1];
		this->dynamicArrayFront[indexOne + 1] = this->dynamicArrayFront[indexTwo + 1];
		this->dynamicArrayFront[indexTwo + 1] = temp;	
	}
}

// Gets the item at the specified index.
// Parameters:
// unsigned int index - the index of the item to retrieve
// Returns the item at position index, or NULL if the provided index is out of bounds.
template <class T>
T DynamicArray<T>::get(unsigned int index)
{
	if(index < this->dynamicArrayLength)
	{
		return this->dynamicArrayFront[index + 1];
	}
	return NULL;
}

// Removes the item at the specified index.
// Parameters:
// unsigned int index - the index of the item to remove
// Returns the item after removal, or NULL if the item could not be removed because the provided index was out of bounds.
template <class T>
T DynamicArray<T>::remove(unsigned int index)
{
	int i;
	if(index < this->dynamicArrayLength)
	{
		// if the index being removed is in the right half of the dynamic array, it will be more efficient to
		// shift the elements on the right
		if(index > dynamicArrayLength / 2)
		{
			for(i = index + 2; i < dynamicArrayLength; i++)
			{
				this->dynamicArrayFront[i - 1] = this->dynamicArrayFront[i];
			}
			dynamicArrayBack--; // move pointer to new back of array
		}
		else // index is in left half of the dynamic array, so it is more efficient to shift the elements on the left
		{
			for(i = index - 2; i >= 0; i--)
			{
				this->dynamicArrayFront[i + 1] = this->dynamicArrayFront[i];
			}
			dynamicArrayFront++; // move pointer to new front of array
		}
		dynamicArrayLength--;
	}
	return NULL;
}
