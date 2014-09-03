#include "stack.hh"

#include <iostream>

int main()
{
	Stack<int> *stack = new Stack<int>();
	
	stack->push(5);
	stack->push(3);
	stack->push(1);

	int peek = stack->peek();
	
	std::cout << peek << std::endl;

	int pop = stack->pop();

	std::cout << pop << std::endl;

	pop = stack->pop();
	
	std::cout << pop << std::endl;

	pop = stack->pop();

	std::cout << pop << std::endl;

	return 0;
}
