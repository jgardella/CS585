#ifndef _STACK_HH_
#define _STACK_HH_

#include "dynamicarray.hh"
#include "debug.hh"


#define NULL 0

// Stack data structure (LIFO)
template <class T>
class Stack
{
	public:
		
		// Constructor for an unbounded stack.
		Stack()
		{
			Debug::getInstance()->addChannel("STACK");
			dynamicArray = new DynamicArray<T>();
			isBounded = false;
		}

		// Constructor for a stack of bounded capacity.
		// Parameters:
		// unsigned int capacity - the bounded capacity of the stack
		Stack(unsigned int capacity)
		{
			Debug::getInstance()->addChannel("STACK");
			dynamicArray = new DynamicArray<T>(capacity);
			isBounded = true;
		}

		// Removes and returns a pointer to the top element of the stack if it is not empty.
		// Returns a pointer to the former top element of the stack. If the stack is empty, behaviour is undefined.
		T pop()
		{
			Debug::log("STACK", "Pop method entered.");
			T poppedItem = dynamicArray->remove(0);
			Debug::log("STACK", "Item popped.");
			return poppedItem;
		}

		// Pushes an item to the top of the stack.
		// If the stack has a bounded capacity, the item will not be added if capacity has been reached.
		// Parameters:
		// T item - the item to push to the top of the stack. 
		void push(T item)
		{
			Debug::log("STACK", "Push method entered.");
			if(!isBounded || dynamicArray->length() < dynamicArray->capacity())
			{
				dynamicArray->pushFront(item);
				Debug::log("STACK", "Item pushed.");
			}
		}
		
		// Peeks at the top element of the stack.
		// Returns the top element of the stack if the stack is not empty. If the stack is empty, behaviour is undefined.		
		T peek()
		{
			Debug::log("STACK", "Peek method entered");
			T peekedItem = dynamicArray->get(0);
			Debug::log("STACK", "Item peeked.");
			return peekedItem;
		}

	private:
		DynamicArray<T> *dynamicArray;
		bool isBounded;
};

#endif
