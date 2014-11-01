#ifndef _RANDOMLOCATIONCHARACTERSPAWNER_HH_
#define _RANDOMLOCATIONCHARACTERSPAWNER_HH_

#include "characterfactory.hh"
#include "itickable.hh"
#include "scenemanager.hh"
#include "levelmanager.hh"
#include <cstdlib>
#include <ctime>

class RandomLocationCharacterSpawner : public ITickable
{
	public:
		RandomLocationCharacterSpawner(int maxSpawnTime, std::string type);

		void tick(float dt);

	private:
		std::string type;
		float timeChange;
		float spawnTime;
		int maxSpawnTime;
};

#endif
