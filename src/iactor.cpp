#include "iactor.hh"
#include "debug.hh"

IActor::IActor(unsigned int collisionLayer, std::string classType)
{
	DEBUG_LOG("IACTOR", "Constructing IActor with (collisionLayer: " + std::to_string(collisionLayer) + ", classType: " + classType + ").");
	this->collisionLayer = collisionLayer;
	this->classType = classType;
}

IActor::~IActor()
{

}

unsigned int IActor::getCollisionLayer()
{
	return collisionLayer;
}

std::string IActor::getClass()
{
	return classType;
}
