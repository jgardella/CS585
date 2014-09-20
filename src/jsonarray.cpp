#include "jsonarray.hh"

JSONArray::JSONArray(DynamicArray<*JSONItem>* array)
{
	this->array = array;
	this->type = ARRAY;
}

JSONArray::~JSONArray()
{
	delete array;
}

DynamicArray<*JSONItem>* JSONArray::getDynamicArray()
{
	return array;
}
