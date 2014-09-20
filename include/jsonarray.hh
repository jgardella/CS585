#ifndef _JSONARRAY_HH_
#define _JSONARRAY_HH_

class JSONArray
{
	public:
		// Constructs a JSONArray containing the given dynamic array.
		JSONArray(DynamicArray<*JSONItem>* array);
		DynamicArray<*JSONItem>* getDynamicArray();
	private:
		DynamicArray<*JSONItem>* array;
};

#endif
