// Function for reading JSON boolean.
#include "jsonparser.hh"

JSONItem* JSONParser::readBool(std::ifstream* file)
{
	DEBUG_LOG("JSON", "Initiating boolean parsing.");
	char followingChars[4];
	followingChars[3] = '\0'; // add to indicate end of "rue" string, will be overwritten if reading "alse"
	if(file->get() == 't') // get 4 chars to check for true
	{
		file->get(followingChars, 4);
		if(std::string(followingChars).compare("rue") == 0) // check if chars following 't' are 'rue'
		{
			DEBUG_LOG("JSON", "Read true while parsing boolean, wrapping and returning true value.");
			return new JSONPrimitive<bool>(true);
		}
	}
	else // get 5 chars to check for false
	{
		file->get(followingChars, 5);
		if(std::string(followingChars).compare("alse") == 0) // check if chars following 'f' are 'alse'
		{
			DEBUG_LOG("JSON", "Read false while parsing boolean, wrapping and returning false value.");
			return new JSONPrimitive<bool>(false);
		}
	}
	DEBUG_LOG("ERROR", "JSON file improperly formatted: invalid character where true or false value expected.");
	std::exit(1);
}
