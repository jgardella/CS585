#ifndef _BUILDINGINFO_HH_
#define _BUILDINGINFO_HH_

#include "trie.hh"

typedef struct sBuildingInfo
{	
	std::string type;
	Trie<double>* behavioralConfig;
} tBuildingInfo;

#endif
