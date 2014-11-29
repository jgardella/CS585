#include "blacksmithfunction.hh"

BlacksmithFunction::BlacksmithFunction(Trie<double>* behavioralConfig) : BuildingFunction("blacksmith")
{
	this->behavioralConfig = behavioralConfig;
}

bool BlacksmithFunction::parseKeyPress(int key, int cursorX, int cursorY)
{
	switch(key)
	{
		case 'u':
			return true;
	}
	return false;
}
