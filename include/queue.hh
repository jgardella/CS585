#ifndef _QUEUE_HH_
#define _QUEUE_HH_

#include "dynamicarray.hh"
#include "debug.hh"

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
		// Returns a pointer to the former front element of the queue. If the queue is empty, behaviour is undefined.
		T dequeue()
		{
			Debug::getInstance()->log("QUEUE", "Dequeue method entered.");
			T dequeuedItem = dynamicArray->remove(0);
			Debug::getInstance()->log("QUEUE", "Item dequeued.");
			return dequeuedItem;
		}

		// Pushes an item to the back of the queue.
		// If the queue has a bounded capacity, the item will not be added if capacity has been reached.
		// Parameters:
		// T item - the item to push to the back of the queue. 
		void enqueue(T item)
		{
			Debug::getInstance()->log("QUEUE", "Enqueue method entered");
			if(!isBounded || dynamicArray->length() < dynamicArray->capacity())
			{
				dynamicArray->pushBack(item);
				Debug::getInstance()->log("QUEUE", "Item enqueued");
			}
		}
		
		// Peeks at the front element of the queue, without removing it.
		// Returns the front element of the queue if the queue is not empty. If the queue is empty, behaviour is undefined.		
		T front()
		{
			Debug::getInstance()->log("QUEUE", "Front method entered");
			T frontItem = dynamicArray->get(0);
			Debug::getInstance()->log("QUEUE", "Front item returned");
			return frontItem;
		}

	private:
		DynamicArray<T> *dynamicArray;
		bool isBounded;
};

#endif
