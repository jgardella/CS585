// Function for reading JSON Array.
#include "jsonparser.hh"

JSONArray* JSONParser::readArray(std::ifstream* file)
{
	DEBUG_LOG("JSON", "Array parsing initiated.");
	char currentChar;
	bool justReadComma = false; // if comma was just read
	DynamicArray<JSONItem*>* array = new DynamicArray<JSONItem*>();
	while((currentChar = file->peek()))
	{
		switch(currentChar)
		{
			case ' ':
			case '\n':
			case '\t':
			case '\r': // ignore
				DEBUG_LOG("JSON", "Read whitespace while parsing array, continuing.");
				file->get();
				continue;
			case ']': // end of array?
				if(!justReadComma) // if comma was just read, array cannot yet end
				{
					DEBUG_LOG("JSON", "Read right bracket ] while parsing array, wrapping and returning array.");
					file->get();
					return new JSONArray(array);
				}
				else
				{
					DEBUG_LOG("ERROR", "JSON file improperly formatted: unexpected closing bracket when value expected while reading array.");
					std::exit(1);
				}
			case ',': // parse new value?
				if(array->length() != 0) // first non-whitespace character cannot be comma
				{
					DEBUG_LOG("JSON", "Read comma while parsing array.");
					justReadComma = true;
					file->get();
					break;
				}
				else
				{
					DEBUG_LOG("ERROR", "JSON file improperly formatted: read invalid comma while reading array.");
					std::exit(1);
				}
			default:
				if(justReadComma || array->length() == 0) // if just read comma or haven't read any values yet, new value can be read
				{
					DEBUG_LOG("JSON", "Read non-special character while parsing array, parsing value.");
					justReadComma = false;
					array->pushBack(readValue(file));
				}
				else
				{
					DEBUG_LOG("ERROR", "JSON file improperly formatted: read invalid character when expecing comma while reading array.");
					std::exit(1);
				}
		}
	}
	DEBUG_LOG("ERROR", "JSON file improperly formatted: file ended unexpectedly while reading array.");	
	std::exit(1);
}
