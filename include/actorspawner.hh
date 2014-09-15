#include "actor.hh"

class ActorSpawner : public ITickable
{
	public:
		void tick(float dt);
	private:
		SceneManager *sceneManager;
		DynamicArray<std::string> *names;
		DynamicArray<Actor*> *actors;
		int secondsBetweenSpawns;
		int namesLeft;
		int spawnX;
		int spawnY;
		float timeCounter;
};
