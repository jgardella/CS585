#ifndef _STACK_HH_
#define _STACK_HH_

#include "../dynamicarray/dynamicarray.hh"

#define NULL 0

// Queue data structure (FIFO)
template <class T>
class Queue
{
	public:
		
		// Constructor for an unbounded queue.
		Queue()
		{
			dynamicArray = new DynamicArray<T>();
			isBounded = false;
		}

		// Constructor for a queue of bounded capacity.
		// Parameters:
		// unsigned int capacity - the bounded capacity of the queue
		Queue(unsigned int capacity)
		{
			dynamicArray = new DynamicArray<T>(capacity);
			isBounded = true;
		}

		// Removes and returns a pointer to the front element of the queue if it is not empty.
		// Returns a pointer to the former front element of the queue, or if the queue is empty returns a null pointer.
		T dequeue()
		{
			if(dynamicArray->length() != 0)
			{
				T dequeuedItem = dynamicArray->remove(0);
				return dequeuedItem;
			}	
			return NULL;		
		}

		// Pushes an item to the back of the queue.
		// If the queue has a bounded capacity, the item will not be added if capacity has been reached.
		// Parameters:
		// T item - the item to push to the back of the queue. 
		void enqueue(T item)
		{
			if(!isBounded || dynamicArray->length() == dynamicArray->capacity())
			{
				dynamicArray->pushBack(item);
			}
		}
		
		// Peeks at the front element of the queue, without removing it.
		// Returns the front element of the queue if the queue is not empty, or if the queue is empty returns a null pointer.		
		T front()
		{
			if(dynamicArray->length() != 0)
			{
				T frontItem = dynamicArray->get(0);
				return frontItem;
			}
			return NULL;
		}

	private:
		DynamicArray<T> *dynamicArray;
		bool isBounded;
};

#endif