#ifndef _JSONARRAY_HH_
#define _JSONARRAY_HH_

#include "dynamicarray.hh"
#include "jsonitem.hh"

// Wrapper class for JSON array, stored as dynamic array.
class JSONArray : public JSONItem
{
	public:
		// Constructs a JSONArray containing the given dynamic array.
		// Parameters:
		// DynamicArray<JSONItem>* array - dynamic array to store in the JSON Array
		JSONArray(DynamicArray<JSONItem*>* array);
		~JSONArray();
		DynamicArray<JSONItem*>* getDynamicArray();
	private:
		DynamicArray<JSONItem*>* array;
};

#endif
