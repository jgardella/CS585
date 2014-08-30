#ifndef _DYNAMICARRAY_HH_
#define _DYNAMICARRAY_HH_

// Dynamically sized array
class DynamicArray<class T>
{
	public:
		DynamicArray();
		DynamicArray(unsigned int);
		~DynamicArray();
		void pushFront(T);
		void pushBack(T);
		void swap(T, unsigned int, unsigned int);
		void insert(T, unsigned int);		
		T get(unsigned int);
		unsigned int length();
		unsigned int memoryUsage();
		T remove(unsigned int);
		void reserve(unsigned int);
	private:
		T[] array;
		unsigned int dynamicArrayLength; // length of dynamic array
		unsigned int internalArrayLength; // length of internal array
		T* dynamicArrayFront; // pointer to empty position at front of dynamic array
		T* dynamicArrayBack; // pointer to empty position at back of dynamic array
		T* internalArrayFront; // pointer to memory location before front of internal array
	        T* internalArrayBack; // pointer to nemory location after back of internal array	
		void reallocate();
}

#endif
