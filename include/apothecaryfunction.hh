#ifndef _APOTHECARYFUNCTION_HH_
#define _APOTHECARYFUNCTION_HH_

#include "buildingfunction.hh"
#include "levelmanager.hh"
#include "trie.hh"
#include "menumanager.hh"

class ApothecaryFunction : public BuildingFunction
{
	public:
		ApothecaryFunction(Trie<double>* behavioralConfig);
		virtual bool parseKeyPress(int key, int cursorX, int cursorY);
	private:
		Trie<double>* behavioralConfig;
};

#endif
