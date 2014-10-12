// Function for reading JSON object.
#include "jsonparser.hh"

JSONObject* JSONParser::readObject(std::ifstream* file)
{
	DEBUG_LOG("JSON", "Object parsing initiated.");
	Trie<JSONItem*>* trie = new Trie<JSONItem*>();
	char currentChar;
	std::string name;
	bool readName = false; // if a name was just read
	bool justReadValue = false; // if a value was just read
	while(file->get(currentChar))
	{
		switch(currentChar)
		{
			case ' ':
			case '\n':
			case '\t':
			case '\r': // ignore
				continue;
			case '}': // end of object, return if just read value
				if(!readName)
				{
					DEBUG_LOG("JSON", "Finished parsing Object, wrapping trie and returning.");
					return new JSONObject(trie);
				}
				else
				{
					DEBUG_LOG("ERROR", "JSON file improperly formatted: expected value before end of object.");
					std::exit(1);
				}
				break;
			case '"': // parse name
				DEBUG_LOG("JSON", "JSON parser reading name in Object.");
				name = readString(file);
				readName = true;
				break;
			case ':': // parse value if just read name
				if(readName)
				{
					DEBUG_LOG("JSON", "Parsing value within Object.");
					trie->add(name, readValue(file));
					readName = false;
					justReadValue = true;
				}
				else
				{
					DEBUG_LOG("ERROR", "JSON file improperly formatted: expected name before value.");
					std::exit(1);
				}
				break;
			case ',': // parse name if just read value
				if(justReadValue)
				{
					DEBUG_LOG("JSON", "Read comma after value, expecting next name.");
					justReadValue = false;
				}
				else
				{
					DEBUG_LOG("ERROR", "JSON file improperly formatted: unexpected comma in object.");
					std::exit(1);
				}
				break;
			default: // invalid
				DEBUG_LOG("ERROR", "JSON file improperly formatted: invalid character inside object.");
				std::exit(1);
		}
	}
	DEBUG_LOG("ERROR", "JSON file improperly formatted: object missing ending brace.");
	std::exit(1);
}
