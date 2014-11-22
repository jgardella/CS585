#ifndef _BUILDINGFUNCTION_HH_
#define _BUILDINGFUNCTION_HH_

#include <string>

class BuildingFunction
{
	
	public:
		virtual void parseKeyPress(int key, int cursorX, int cursorY) = 0;

	protected:
		BuildingFunction(std::string type) : type(type);
		std::string type;
		
}

#endif
