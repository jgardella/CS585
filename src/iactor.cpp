#include "iactor.hh"

IActor::IActor(unsigned int collisionLayer, std::string classType)
{
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
