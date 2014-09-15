#include "scenenode.hh"

class Actor
{
	public:
		Actor(std::string, int initialX, int initialY, Collider col);
		std::string getName();
	private:
		std::string name;
		SceneNode sceneNode;
};
