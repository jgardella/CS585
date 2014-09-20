#include "jsonparser.hh"

DynamicArray<JSONObject*>* JSONParser::parseString(std::string jsonString)
{
	DynamicArray<JSONObject*> topLevelObjects = new DynamicArray<JSONObject*>();
	unsigned int* i;
	for(*i = 0; *i < jsonString.length(); *i++)
	{
		char currentChar = jsonString.at(*i);
		switch(currentChar)
		{
			case ' ':
			case '\n':
			case '\r':
			case '\t':
				continue;
			case '{':
				topLevelObjects.pushBack(readObject(&jsonString, i));
			default:
				Debug::getInstance()->log("ERROR", "JSON file improperly formatted: invalid character at top level.");
				exit(1);
		}
	}
}
