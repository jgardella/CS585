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
	private:
		T* firstElementPointer;
		unsigned int arrayLength;
}

#endif
