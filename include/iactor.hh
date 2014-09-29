#ifndef _IACTOR_HH_
#define _IACTOR_HH_

#include <string>

class IActor
{
	public:

		virtual bool isCollidable();
		virtual std::string getClass();		
	protected:
		bool isCollider;
		std::string classType;
		IActor(bool isCollider, std::string classType);
		virtual ~IActor();
};

#endif
