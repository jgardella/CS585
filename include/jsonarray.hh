#ifndef _JSONARRAY_HH_
#define _JSONARRAY_HH_

#include "dynamicarray.hh"
#include "jsonitem.hh"

class JSONArray : public JSONItem
{
	public:
		// Constructs a JSONArray containing the given dynamic array.
		JSONArray(DynamicArray<JSONItem*>* array);
		~JSONArray();
		DynamicArray<JSONItem*>* getDynamicArray();
	private:
		DynamicArray<JSONItem*>* array;
};

#endif
