#include "testgame.hh"
#include <iostream>

TestGame::TestGame()
{
	gameObject = new GameObject();
}

void TestGame::simulate()
{
	std::clock_t startTime = clock(), finishTime = startTime;
	bool isPlaying = true;
	while(isPlaying)
	{
		startTime = clock();
		isPlaying = gameObject->update((startTime - finishTime) / CLOCKS_PER_SEC);
		finishTime = startTime;
	}
}
