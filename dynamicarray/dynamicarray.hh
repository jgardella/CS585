#ifndef _DYNAMICARRAY_HH_
#define _DYNAMICARRAY_HH_

// Dynamically sized array
class DynamicArray<class T>
{
	public:
		DynamicArray();
		DynamicArray(unsigned int);
		~DynamicArray();
		pushFront(T);
		pushBack(T);
		swap(T, unsigned int, unsigned int);
		insert(T, unsigned int);		
		get(unsigned int);
		length();
		memoryUsage();
		remove(unsigned int);
	private:
		T[] array;
		unsigned int arrayLength;
}

#endif
