#ifndef _DYNAMICARRAY_HH_
#define _DYNAMICARRAY_HH_

// Dynamically sized array
template <class T>
class DynamicArray
{
	public:
		
		//------------------------- CONSTRUCTORS -------------------------//

		// Default constructor - allocates an internal array of size 10
		DynamicArray()
		{
			array = new T[10];
			dynamicArrayLength = 0;
			internalArrayLength = 10;
			dynamicArrayFront = &array[internalArrayLength / 2 - 1];
			dynamicArrayBack = &array[internalArrayLength / 2];
			internalArrayFront = array - 1;
			internalArrayBack = array + internalArrayLength;
		}

		// Constructor which allocates an array of size 'preAllocatedLength'.
		// Parameters:
		// unsigned int preAllocatedLength - the length to initially allocate the internal array
		DynamicArray(unsigned int preAllocatedLength)
		{
			array = new T[preAllocatedLength];
			dynamicArrayLength = 0;
			internalArrayLength = preAllocatedLength;
			dynamicArrayFront = &array[internalArrayLength / 2 - 1];
			dynamicArrayBack = &array[internalArrayLength / 2];
			internalArrayFront = array - 1;
			internalArrayBack = array + internalArrayLength;
		}

		// Deconstructor, simply deletes the internal array.
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
			// if the front of the array is full
			if(dynamicArrayFront == internalArrayFront)	
			{
				// if capacity has been reached (i.e. internal array is full), reallocate larger array
				if(length() == capacity())
				{
					reallocate((unsigned int)(internalArrayLength * 1.5));
				}
				else // there is still space in the internal array, re-center the dynamic array within the internal array
				{
					recenter(true);
				}
			}
			*dynamicArrayFront-- = newElement;
			dynamicArrayLength++;
		}
		
		// Adds a new element onto the back end of the array.
		// Parameters:
		// T newElement - the new element to be added to the array
		void pushBack(T newElement)
		{
			// if the back of the array is full
			if(dynamicArrayBack == internalArrayBack)
			{
				// if capacity has been reached (i.e. internal array is full), reallocate larger array
				if(length() == capacity())
				{
					reallocate((unsigned int)(internalArrayLength * 1.5));
				}
				else // there is still space in the internal array, re-center the dynamic array within the internal array
				{
					recenter(false);
				}
			}
			*dynamicArrayBack++ = newElement;
			dynamicArrayLength++;
		}

		
		//------------------------- MODIFICATION -------------------------//

		void insert(T newElement, unsigned int index)
		{
			unsigned int i;
			if(length() == capacity())
			{
				reallocate((unsigned int)(internalArrayLength * 1.5));
			}
			// if the element is being inserted on the right half of the dynamic array and the right side is not full, it will be more efficient to
			// shift the elements on the right
			if(index > dynamicArrayLength / 2 && dynamicArrayBack != internalArrayBack)
			{
				for(i = dynamicArrayLength - 1; i > index; i--)
				{
					set(get(i), i + 1);
				}
				dynamicArrayBack++; // move pointer to new back of array
				
			}
			else // index is in left half of the dynamic array, or right half of array is full, so it is more efficient to shift the elements on the left
			{
				for(i = 0; i < index; i++)
				{
					set(get(i), i - 1);
				}
				dynamicArrayFront--; // move pointer to new front of array
			}
			set(newElement, index); // add new element	
			dynamicArrayLength++;
		}

		// Replaces the element at index with newElement. Keeping with the C++ spirit, if the provided index is outside the dynamic array the behavior is undefined.
		// Parameters:
		// T newElement - the new element
		// unsigned int index - the index at which to set the new element, should be from 0 to length() - 1
		// Returns the element that was in position index before setting.
		T set(T newElement, unsigned int index)
		{
			T oldElement = dynamicArrayFront[index + 1];
			dynamicArrayFront[index + 1] = newElement;
			return oldElement;
		}
		
		// Swaps two elements in the array. Keeping with the C++ spirit, if the provided index is outside the dynamic array the behavior is undefined.
		// Parameters:
		// unsigned int indexOne - the index of the first item, should be from 0 to length() - 1
		// unsigned int indexTwo - the index of the second item, should be from 0 to length() - 1
		void swap(unsigned int indexOne, unsigned int indexTwo)
		{
			T temp = dynamicArrayFront[indexOne + 1];
			dynamicArrayFront[indexOne + 1] = dynamicArrayFront[indexTwo + 1];
			dynamicArrayFront[indexTwo + 1] = temp;	
		}
		
		// Gets the item at the specified index. Keeping with the C++ spirit, if the provided index is outside the dynamic array the behavior is undefined.
		// Parameters:
		// unsigned int index - the index of the item to retrieve, should be from 0 to length() - 1
		// Returns the item at position index.
		T get(unsigned int index)
		{
			return dynamicArrayFront[index + 1];
		}
		
		// Removes the item at the specified index. Keeping with the C++ spirit, if the provided index is outside the dynamic array the behavior is undefined.
		// Parameters:
		// unsigned int index - the index of the item to remove, should be from 0 to length() - 1
		// Returns the item after removal.
		T remove(unsigned int index)
		{
			unsigned int i;
			T removedElement = get(index);
			// if the index being removed is in the right half of the dynamic array, it will be more efficient to
			// shift the elements on the right
			if(index > dynamicArrayLength / 2)
			{
				for(i = index; i < dynamicArrayLength; i++)
				{
					set(get(i + 1), i);
				}
				dynamicArrayBack--; // move pointer to new back of array
			}
			else // index is in left half of the dynamic array, so it is more efficient to shift the elements on the left
			{
				for(i = index; i > 0; i--)
				{
					set(get(i - 1), i);
				}
				dynamicArrayFront++; // move pointer to new front of array
			}
			dynamicArrayLength--;
			return removedElement;
		}

		
		//------------------------- LENGTH -------------------------//

		// Returns the number of elements in the dynamic array.
		unsigned int length()
		{
			return dynamicArrayLength;
		}

		// Returns the length of the internal array.
		unsigned int capacity()
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
			unsigned int i;
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
				dynamicArrayFront = &temp[(newSize - dynamicArrayLength) / 2 - 1];
				dynamicArrayBack = &temp[(newSize + dynamicArrayLength) / 2];
				internalArrayFront = temp - 1;
				internalArrayBack = temp + newSize;
				internalArrayLength = newSize;
				// delete old array and change pointer to point to new array
				delete [] array;
				array = temp;
			}
		}
		
		// Re-centers the dynamic array within the internal array. Used after there has been an overflow on either the front or back of the internal array.
		// Parameters:
		// bool shouldRecenterFront - true if there has been an overflow on the front of the array, false if there has been an overflow on the back of the array
		void recenter(bool shouldRecenterFront)
		{
			unsigned int i;
			int buffer = ((internalArrayLength - dynamicArrayLength) / 2); // free space on each side of the internal array
			if(shouldRecenterFront)
			{
				// shift all elements right such that there is equal free space on the front and back of the internal array
				for(i = dynamicArrayLength; i > 0; i--)
				{
					dynamicArrayFront[i + buffer + 1] = dynamicArrayFront[i];
				}
				// adjust pointers to new positions
				dynamicArrayFront += buffer + 1;
				dynamicArrayBack += buffer + 1;
			}
			else
			{
				// adjust pointers to new positions
				dynamicArrayFront -= buffer + 1;
				dynamicArrayBack -= buffer + 1;
				// shift all elements left such that there is equal free space on the front and back of the internal array
				for(i = 1; i <= dynamicArrayLength; i++)
				{
					dynamicArrayFront[i] = dynamicArrayFront[i + buffer + 1];
				}
			}
		}	

};

#endif
