#include "queue.hh"

#include <iostream>

int main()
{
	Queue<int> *queue = new Queue<int>();
	int i;
	for(i = 0; i < 10; i++)
		queue->enqueue(i);
	
	for(i = 0; i < 10; i++)
		std::cout << queue->dequeue() << std::endl;

	return 0;
}
