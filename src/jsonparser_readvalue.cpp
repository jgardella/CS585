// Function for reading value within JSON Object or JSON Array.
#include "jsonparser.hh"

JSONItem* JSONParser::readValue(std::ifstream* file)
{
	DEBUG_LOG("JSON", "Value parsing initiated.");
	char currentChar;
	char followingChars[4];
	while((currentChar = file->peek()))
	{
		switch(currentChar)
		{
			case ' ':
			case '\t':
			case '\n':
			case '\r': // ignore
				file->get();
				DEBUG_LOG("JSON", "Read whitespace while reading value, continuing.");
				continue;
			case '{': // parse object
				file->get();
				DEBUG_LOG("JSON", "Read left brace { while reading value, parsing object.");
				return readObject(file);
			case '"': // parse quote
				file->get();
				DEBUG_LOG("JSON", "Read quote while reading value, parsing string.");
				return new JSONPrimitive<std::string>(readString(file));
			case '0':	
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case '-': // parse number
				DEBUG_LOG("JSON", "Read number or - while reading value, parsing number.");
				return readNumber(file);
			case 't':
			case 'f': // parse boolean
				DEBUG_LOG("JSON", "Read t or f while reading value, parsing boolean.");
				return readBool(file);
			case 'n': // parse null
				file->get(followingChars, 5);
				if(std::string(followingChars).compare("null") == 0)
				{
					DEBUG_LOG("JSON", "Read null while reading value, returning NULL.");
					return NULL;
				}
				else
				{
					DEBUG_LOG("ERROR", "JSON file improperly formatted: invalid character where null value expected.");
					std::exit(1);
				}
			case '[': // parse array
				file->get();
				DEBUG_LOG("JSON", "Read left bracket [ while reading value, parsing array.");
				return readArray(file);
			default: // invalid
				DEBUG_LOG("ERROR", "JSON file improperly formatted: invalid character while reading value.");
				std::exit(1);
		}
	}
	DEBUG_LOG("ERROR", "JSON file improperly formatted: file ended unexpectedly while reading value.");
	std::exit(1);
}
