#ifndef _HEALTHPOTION_HH_
#define _HEALTHPOTION_HH_

#include <string>
#include "quality.hh"

class HealthPotion
{

	public:
		
		HealthPotion(std::string name, int quality, int healValue);
		
		std::string getName();
		int getQuality();
		int getHealValue();


	private:
		std::string name;
		int quality;
		int healValue;
};

#endif
