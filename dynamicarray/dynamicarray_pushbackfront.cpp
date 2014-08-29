#include "dynamicarray.hh"


DynamicArray<T>::pushFront(T newElement)
{
	this->firstElementPointer--;
	firstElementPointer[0] = newElement;
	arrayLength++;
}

DynamicArray<T>::pushBack(T newElement)
{
	firstElementPointer[arrayLength] = new Element;
	arrayLength++;
}
