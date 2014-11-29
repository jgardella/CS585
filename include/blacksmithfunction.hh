#ifndef _BLACKSMITHFUNCTION_HH_
#define _BLACKSMITHFUNCTION_HH_

#include "buildingfunction.hh"
#include "trie.hh"

class BlacksmithFunction : public BuildingFunction
{
	public:
		BlacksmithFunction(Trie<double>* behavioralConfig);
		virtual bool parseKeyPress(int key, int cursorX, int cursorY);
	private:
		Trie<double>* behavioralConfig;
};

#endif
