#ifndef _IACTOR_HH_
#define _IACTOR_HH_

#include <string>

class IActor
{
	public:

		// Returns the collision layer of the actor.
		virtual unsigned int getCollisionLayer();
		
		// Returns a string representing the class of the derivative actor.
		virtual std::string getClass();		
	
		virtual std::string inspect();

	protected:
		int collisionLayer;
		std::string classType;

		// Constructs an IActor with the given collision layer and class.
		// Parameters:
		// unsigned int collisionLayer - the layer on which the actor collides
		// std::string classType - a string representing the derivative class of the actor.
		IActor(unsigned int collisionLayer, std::string classType);
		virtual ~IActor();
};

#endif
