#ifndef _IACTOR_HH_
#define _IACTOR_HH_

#include <string>

class IActor
{
	public:

		virtual unsigned int getCollisionLayer();
		virtual std::string getClass();		
	protected:
		int collisionLayer;
		std::string classType;
		IActor(unsigned int collisionLayer, std::string classType);
		virtual ~IActor();
};

#endif
