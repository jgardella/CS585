#include "testgame.hh"

TestGame::TestGame()
{
	gameObject = new GameObject();
}

void TestGame::simulate()
{
	std::clock_t startTime, finishTime;
	bool isPlaying = true;
	while(isPlaying)
	{
		startTime = clock();
		isPlaying = update((finishTime - startTime) / CLOCKS_PER_TICK);
		finishTime = clock();
	}
}
