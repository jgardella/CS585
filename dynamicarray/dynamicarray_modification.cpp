#include "dynamicarray.hh"

void DynamicArray<T>::insert(T newElement, unsigned int index)
{
	if(index < arrayLength)
	{
		this->firstElementPointer[index] = newElement;
	}
}

void DynamicArray<T>::swap(unsigned int indexOne, unsigned int indexTwo)
{
	if(indexOne < this->arrayLength && indexTwo < this->arrayLength)
	{
		T temp = this->firstElementPointer[indexOne];
		this->firstElementPointer[indexOne] = this->firstElementPointer[indexTwo];
		this->firstElementPointer[indexTwo] = temp;	
	}
}

T DynamicArray<T>::get(unsigned int index)
{
	if(index < this->arrayLength)
	{
		return this->firstElementPointer[index];
	}
}

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
}
