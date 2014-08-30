#include "dynamicarray.hh"
#include "jtest.hh"

int main()
{
	DynamicArray<int> *array = new DynamicArray<int>();
	array->pushBack(10);
	std::cout << array->get(1) << std::endl;
	return 0;
}
