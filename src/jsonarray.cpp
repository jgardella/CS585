#include "jsonarray.hh"

JSONArray::JSONArray(DynamicArray<JSONItem*>* array) : JSONItem(ARRAY)
{
	this->array = array;
}

JSONArray::~JSONArray()
{
	delete array;
}

DynamicArray<JSONItem*>* JSONArray::getDynamicArray()
{
	return array;
}
