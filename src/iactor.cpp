#include "iactor.hh"
#include "debug.hh"

IActor::IActor(unsigned int collisionLayer, std::string classType, Trie<double>* behavioralConfig)
{
	DEBUG_LOG("IACTOR", "Constructing IActor with (collisionLayer: " + std::to_string(collisionLayer) + ", classType: " + classType + ").");
	this->collisionLayer = collisionLayer;
	this->classType = classType;
	this->behavioralConfig = behavioralConfig;
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

Trie<double>* IActor::getBehavioralConfig()
{
	return behavioralConfig;
}

std::string IActor::inspect()
{
	return classType;
}
