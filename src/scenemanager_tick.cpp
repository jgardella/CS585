// Functions for ticking and adding tickables to SceneManager.
#include "scenemanager.hh"

void SceneManager::tick(float dt)
{
	unsigned int i;
	if(!paused)
	{
		for(i = 0; i < tickables->length(); i++)
		{
			(*tickables->get(i))->tick(dt);
		}
	}
}

void SceneManager::addTickable(ITickable *tickable)
{
	DEBUG_LOG("MANAGER", "Adding tickable to scene manager.");
	tickables->pushBack(tickable);
}

void SceneManager::pause()
{
	paused = true;
}

void SceneManager::unpause()
{
	paused = false;
}
