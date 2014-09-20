#include "jsonarray.hh"

JSONArray::JSONArray(DynamicArray<*JSONItem>* array)
{
	this->array = array;
	this->type = ARRAY;
}

DynamicArray<*JSONItem>* JSONArray::getDynamicArray()
{
	return array;
}
