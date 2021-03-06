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
			DEBUG_LOG("QUEUE", "Constructing unbounded queue.");
			dynamicArray = new DynamicArray<T>();
			isBounded = false;
		}

		// Constructor for a queue of bounded capacity.
		// Parameters:
		// unsigned int capacity - the bounded capacity of the queue
		Queue(unsigned int capacity)
		{
			DEBUG_LOG("QUEUE", "Constructing bounded queue with capacity: " + std::to_string(capacity) + ".");
			dynamicArray = new DynamicArray<T>(capacity);
			isBounded = true;
		}
	
		~Queue()
		{
			DEBUG_LOG("QUEUE", "Deconstructing queue.");
			delete dynamicArray;
		}

		// Removes and returns a pointer to the front element of the queue if it is not empty.
		// Returns a pointer to the former front element of the queue. If the queue is empty, behaviour is undefined.
		T dequeue()
		{
			DEBUG_LOG("QUEUE", "Dequeue method entered.");
			T dequeuedItem = dynamicArray->remove(0);
			DEBUG_LOG("QUEUE", "Item dequeued.");
			return dequeuedItem;
		}

		// Pushes an item to the back of the queue.
		// If the queue has a bounded capacity, the item will not be added if capacity has been reached.
		// Parameters:
		// T item - the item to push to the back of the queue. 
		void enqueue(T item)
		{
			DEBUG_LOG("QUEUE", "Enqueue method entered");
			if(!isBounded || dynamicArray->length() < dynamicArray->capacity())
			{
				dynamicArray->pushBack(item);
				DEBUG_LOG("QUEUE", "Item enqueued");
			}
		}
		
		// Peeks at the front element of the queue, without removing it.
		// Returns the front element of the queue if the queue is not empty. If the queue is empty, behaviour is undefined.		
		T front()
		{
			DEBUG_LOG("QUEUE", "Front method entered");
			T frontItem = *dynamicArray->get(0);
			DEBUG_LOG("QUEUE", "Front item returned");
			return frontItem;
		}

		bool empty()
		{
			DEBUG_LOG("QUEUE", "Checking if queue is empty.");
			if(dynamicArray->length() == 0)
			{
				DEBUG_LOG("QUEUE", "Queue is empty.");
				return true;
			}
			DEBUG_LOG("QUEUE", "Queue is not empty.");
			return false;
		}

	private:
		DynamicArray<T> *dynamicArray;
		bool isBounded;
};

#endif
