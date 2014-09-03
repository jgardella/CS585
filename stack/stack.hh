#ifndef _STACK_HH_
#define _STACK_HH_

#include "../dyamicarray/dynamicarray.hh"

// Stack data structure (LIFO)
template <class T>
class Stack
{
	public:
		
		// Constructor for an unbounded stack.
		Stack()
		{
			dynamicArray = new DynamicArray<T>();
			isBounded = false;
		}

		// Constructor for a stack of bounded capacity.
		// Parameters:
		// unsigned int capacity - the bounded capacity of the stack
		Stack(unsigned int capacity)
		{
			dynamicArray = new DynamicArray<T>(capacity);
			isBounded = true;
		}

		// Removes and returns a pointer to the top element of the stack if it is not empty.
		// Returns a pointer to the former top element of the stack, or if the stack is empty returns a null pointer.
		T* pop()
		{
			if(dynamicArray->length() != 0)
			{
				return dynamicArray->remove(0);
			}	
			return nullptr;		
		}

		// Pushes an item to the top of the stack.
		// If the stack has a bounded capacity, the item will not be added if capacity has been reached.
		// Parameters:
		// T item - the item to push to the top of the stack. 
		void push(T item)
		{
			if(!isBounded || dynamicArray->length() == dynamicArray->capactiy())
			{
				dynamicArray->pushFront(item);
			}
		}
		
		// Peeks at the top element of the stack.
		// Returns the top element of the stack if the stack is not empty, or if the stack is empty returns a null pointer.		
		T* peek()
		{
			if(dynamicArray->length() != 0)
			{
				return dynamicArray->get(0);
			}
			return nullptr;
		}

	private:
		DynamicArray<T> *dynamicArray;
		bool isBounded;
};

#endif
