#include "iactor.hh"

IActor::IActor(bool isCollider, std::string classType)
{
	this->isCollider = isCollider;
	this->classType = classType;
}

IActor::~IActor()
{

}

bool IActor::isCollidable()
{
	return isCollider;
}

std::string IActor::getClass()
{
	return classType;
}
