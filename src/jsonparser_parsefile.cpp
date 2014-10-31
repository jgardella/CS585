// Function for parsing JSON file.
#include "jsonparser.hh"

DynamicArray<JSONItem*>* JSONParser::parseFile(std::string jsonFileName)
{
	DEBUG_LOG("JSON", "JSON file parsing initiated.");
	DynamicArray<JSONItem*>* topLevelStructures = new DynamicArray<JSONItem*>();
	char currentChar;
	std::ifstream jsonFile;
	DEBUG_LOG("JSON", "Opening JSON file \"/data/" + jsonFileName + "\"");
	jsonFile.open(("data/" + jsonFileName + ".json").c_str(), std::ifstream::in);
	while(jsonFile.get(currentChar))
	{
		switch(currentChar)
		{
			case ' ':
			case '\n':
			case '\r':
			case '\t': // ignore
				continue;
			case '{': // parse object
				DEBUG_LOG("JSON", "Parsing top level Object.");
				topLevelStructures->pushBack(readObject(&jsonFile));
				break;
			case '[': // parse array
				DEBUG_LOG("JSON", "Parsing top level Array.");
				topLevelStructures->pushBack(readArray(&jsonFile));
				break;
			default: // invalid
				DEBUG_LOG("ERROR", "JSON file improperly formatted: invalid character at top level.");
				std::exit(1);
		}
	}
	DEBUG_LOG("JSON", "Finished parsing JSON file.");
	return topLevelStructures;
}
