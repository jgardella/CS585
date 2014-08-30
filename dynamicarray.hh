#ifndef _DYNAMICARRAY_HH_
#define _DYNAMICARRAY_HH_

#include <iostream> // TODO: remove

// Dynamically sized array
template <class T>
class DynamicArray
{
	public:
		
		//------------------------- CONSTRUCTORS -------------------------//

		// Default constructor - allocates an internal array of size 10
		DynamicArray()
		{
			this->array = new T[10];
			this->dynamicArrayLength = 0;
			this->internalArrayLength = 10;
			this->dynamicArrayFront = &array[internalArrayLength / 2];
			this->dynamicArrayBack = &array[internalArrayLength / 2] + 1;
			this->internalArrayFront = array - 1;
			this->internalArrayBack = array + internalArrayLength;
		}

		// Constructor which allocates an array of size 'preAllocatedLength'.
		// Parameters:
		// unsigned int preAllocatedLength - the length to initially allocate the internal array
		DynamicArray(unsigned int preAllocatedLength)
		{
			this->array = new T[preAllocatedLength];
			this->dynamicArrayLength = 0;
			this->internalArrayLength = preAllocatedLength;
			this->dynamicArrayFront = &array[this->internalArrayLength / 2];
			this->dynamicArrayBack = &array[this->internalArrayLength / 2] + 1;
			this->internalArrayFront = array - 1;
			this->internalArrayBack = array + internalArrayLength;
		}

		// Deconstructor, simply deletes array.
		~DynamicArray()
		{
			delete [] array;
		}
		
		//------------------------- PUSHING -------------------------//
		
		// Adds a new element onto the front end of the array.
		// Parameters:
		// T newElement - the new element to be added to the array
		void pushFront(T newElement)
		{
			// reallocate internal array if front side of array is full
			if(this->dynamicArrayFront == this->internalArrayFront)	
			{
				reallocate((unsigned int)(internalArrayLength * 1.5));
			}
			*dynamicArrayFront-- = newElement;
			dynamicArrayLength++;
		}
		
		// Adds a new element onto the back end of the array.
		// Parameters:
		// T newElement - the new element to be added to the array
		void pushBack(T newElement)
		{
			// reallocate internal array if back side of array is full
			if(this->dynamicArrayBack == this->internalArrayBack)
			{
				reallocate((unsigned int)(internalArrayLength * 1.5));
			}
			*dynamicArrayBack++ = newElement;
			dynamicArrayLength++;
		}

		
		//------------------------- MODIFICATION -------------------------//

		// Inserts the element newElement at position index in the array.
		// Parameters:
		// T newElement - the new element to insert into the array
		// unsigned int index - the index at which to insert te new element
		// Returns the element that was in position index before insertion, or NULL if the insertion did not complete because the provided index was out of bounds.
		T insert(T newElement, unsigned int index)
		{
			if(index < dynamicArrayLength)
			{
				T oldElement = this->dynamicArrayFront[index + 1];
				this->dynamicArrayFront[index + 1] = newElement;
				return oldElement;
			}
		}
		
		// Swaps two elements in the array.
		// Parameters:
		// unsigned int indexOne - the index of the first item
		// unsigned int indexTwo - the index of the second item
		void swap(unsigned int indexOne, unsigned int indexTwo)
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
		T get(unsigned int index)
		{
			if(index < this->dynamicArrayLength)
			{
				return this->dynamicArrayFront[index + 1];
			}
		}
		
		// Removes the item at the specified index.
		// Parameters:
		// unsigned int index - the index of the item to remove
		// Returns the item after removal, or NULL if the item could not be removed because the provided index was out of bounds.
		T remove(unsigned int index)
		{
			int i;
			if(index < this->dynamicArrayLength)
			{
				T removedElement = this->get(index);
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
				return removedElement;
			}
		}

		
		//------------------------- LENGTH -------------------------//

		// Returns the number of elements in the dynamic array.
		unsigned int length()
		{
			return dynamicArrayLength;
		}

		// Returns the length of the internal array.
		unsigned int memoryUsage()
		{
			return internalArrayLength;
		}

		//------------------------- MEMORY REALLOCATION -------------------------//

		// Reallocates the internal array such that it can hold the number of elements specified by sizeToReserve.
		// Parameters:
		// unsigned int sizeToReserve - the size to reserve for the internal array (must be greater than the current length of the internal array)
		void reserve(unsigned int sizeToReserve)
		{
			if(sizeToReserve > internalArrayLength)
			{
				reallocate(sizeToReserve);
			}
		}

	private:
		T* array;
		unsigned int dynamicArrayLength; // length of dynamic array
		unsigned int internalArrayLength; // length of internal array
		T* dynamicArrayFront; // pointer to empty position at front of dynamic array
		T* dynamicArrayBack; // pointer to empty position at back of dynamic array
		T* internalArrayFront; // pointer to memory location before front of internal array
	        T* internalArrayBack; // pointer to nemory location after back of internal array	
		
		// Reallocates the internal array to the size specified by newSize.
		// Parameters:
		// unsigned int newSize - the new size for the internal array (must be greater than the current length of the dynamic array)
		void reallocate(unsigned int newSize)
		{
			int i;
			T* temp;
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
				dynamicArrayFront = &temp[(newSize - dynamicArrayLength) / 2] - 1;
				dynamicArrayBack = &temp[(newSize + dynamicArrayLength) / 2];
				internalArrayFront = temp - 1;
				internalArrayBack = temp + newSize;
				internalArrayLength = newSize;
				// delete old array and change pointer to point to new array
				delete [] array;
				array = temp;
			}
		}		
};

#endif
