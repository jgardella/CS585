#include "jsonparser.hh"

DynamicArray<JSONItem*>* JSONParser::parseFile(std::string jsonFileName)
{
	DEBUG_LOG("JSON", "JSON file parsing initiated.");
	DynamicArray<JSONItem*>* topLevelStructures = new DynamicArray<JSONItem*>();
	char currentChar;
	std::ifstream jsonFile;
	DEBUG_LOG("JSON", "Opening JSON file \"/data/" + jsonFileName + "\"");
	jsonFile.open(("data/" + jsonFileName).c_str(), std::ifstream::in);
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

std::string JSONParser::readString(std::ifstream* file)
{
	DEBUG_LOG("JSON", "Parsing string.");
	std::string str = "";
	bool readEscapeCharacter = false; // if escape character was just read
	char currentChar;
	while(file->get(currentChar))
	{
		switch(currentChar)
		{
			case '\\': // escape character
				if(readEscapeCharacter) // read backslash after escape character, add to string
				{
					DEBUG_LOG("JSON", "Read backslash (\\) after escape character (\\), adding to string.");
					str.push_back('\\');
					readEscapeCharacter = false;
				}
				else // read backslash not preceded by escape, set escape character flag to true
				{
					readEscapeCharacter = true;
				}
				break;
			case '"':
				if(readEscapeCharacter) // read quote after escape, add to string
				{
					DEBUG_LOG("JSON", "Read quote (\") after escape character (\\), adding to string.");
					str.push_back('\"');
					readEscapeCharacter = false;
					break;
				}
				else // read quote not preceded by escape, returning string
				{
					DEBUG_LOG("JSON", "Read quote (\") not preceded by escape character (\\), end of string reached, returning string.");
					return str;
				}
			case 'f': // form feed?
				if(readEscapeCharacter) // read f after escape, add form feed to string
				{
					DEBUG_LOG("JSON", "Read character 'f' after escape character (\\), adding form feed to string.");
					str.push_back('\f');
					readEscapeCharacter = false;
					break;
				}
			case 'n': // newline?
				if(readEscapeCharacter) //  read n after escape, add newline to string
				{
					DEBUG_LOG("JSON", "Read character 'n' ater escape character (\\), adding newline to string.");
					str.push_back('\n');
					readEscapeCharacter = false;
					break;
				}
			case 't': // tab?
				if(readEscapeCharacter) // read t after escape, add tab to string
				{
					DEBUG_LOG("JSON", "Read character 't' after escape character (\\), adding tab to string.");
					str.push_back('\t');
					readEscapeCharacter = false;
					break;
				}
			case 'r': // carriage return?
				if(readEscapeCharacter) // read r after escape, add carriage return to string
				{
					DEBUG_LOG("JSON", "Read character 'r' after escape character (\\), adding carriage return to string.");
					str.push_back('\r');
					readEscapeCharacter = false;
					break;
				}
			case 'b': // backspace?
				if(readEscapeCharacter) // read b after escape, add backspace to string
				{
					DEBUG_LOG("JSON", "Read character 'b' after escape character (\\), adding backspace to string.");
					str.push_back('\b');
					readEscapeCharacter = false;
				}
			default: // any other character can just be added to string. also, escape characters above will go to default case if they were not escaped.
				DEBUG_LOG("JSON", "Read non-special character, adding to string.");
				str.push_back(currentChar);
				readEscapeCharacter = false;
				break;
		}
	}
	DEBUG_LOG("ERROR", "JSON file improperly formatted: string missing end quote.");
	std::exit(1);
}

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

JSONItem* JSONParser::readNumber(std::ifstream* file)
{
	DEBUG_LOG("JSON", "Number parsing initiated.");
	char currentChar;
	std::string numStr = ""; // string representation of number
	std::string expStr = ""; // string representation of exponent
	bool readDecimal = false; // has decimal already been read?
	bool endOfNumberReached = false; // has end of number been reached?
	bool readExpIndicator = false; // has an exp indicator (e or E) been read?
	bool justReadExpIndicator = false; // was exp indicator (e or E) just read?
	while((currentChar = file->peek()) && !endOfNumberReached)
	{
		switch(currentChar)
		{
			case '.': // decimal
				if(!readDecimal) // if decimal hasn't yet been read, add decimal to string
				{
					DEBUG_LOG("JSON", "Read decimal point while parsing number, pushing to number string.");
					readDecimal = true;
					file->get();
					numStr.push_back(currentChar);
					break;
				}
				else
				{
					DEBUG_LOG("ERROR", "JSON file improperly formatted: read invalid decimal point in number; decimal already read.");
					std::exit(1);
				}
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9': // numbers
				if(!readExpIndicator) // if exp indicator hasn't been read yet, append number to numStr
				{
					DEBUG_LOG("JSON", "Read number character while parsing number, pushing to number string.");
					file->get();
					numStr.push_back(currentChar);
				}
				else // exp indicator has been read, append number to expStr
				{
					DEBUG_LOG("JSON", "Read number character after reading exponent indicator while parsing number, pushing to exponent string.");
					file->get();
					expStr.push_back(currentChar);
					if(justReadExpIndicator)
					{
						justReadExpIndicator = false;
					}
				}
				break;
			case 'e':
			case 'E': // exponent indicator
				if(!readExpIndicator) // if exp indicator hasn't already been read
				{
					DEBUG_LOG("JSON", "Read e or E while parsing number, enabling exponent mode.");
					file->get();
					readExpIndicator = true;
					justReadExpIndicator = true;
					break;
				}
				else
				{
					DEBUG_LOG("ERROR", "JSON file improperly formatted: read more than one scientific notation indicator in one number.");
					std::exit(1);
				}
			case '+':
			case '-': // sign indicator
				if(justReadExpIndicator) // if just read exp indicator, add sign indicator to expStr
				{
					DEBUG_LOG("JSON", "Read + or - immediately after reading exponent indicator while parsing number, appending to exponent string.");
					file->get();
					expStr.push_back(currentChar);
					justReadExpIndicator = false;
					break;
				}
				else if(numStr.length() == 0) // if first character, add sign indicator to numStr
				{
					DEBUG_LOG("JSON", "Read + or - at start of number, appending to number string.");
					file->get();
					numStr.push_back(currentChar);
					break;
				}
				DEBUG_LOG("ERROR", "JSON file improperly formatted: read unexpected + or - while reading number.");
				std::exit(1);
			case ' ':
			case ',':
			case ']': // end of number?
				if(!justReadExpIndicator && (!readExpIndicator || (expStr.length() != 0 && expStr.at(expStr.length() - 1) != '+' && expStr.at(expStr.length() - 1) != '-'))) // ensure that the number didn't end on an invalid character (e/E/+/-)
				{
					DEBUG_LOG("JSON", "Read whitespace or comma while parsing string, end of number reached.");
					endOfNumberReached = true;
					break;
				}
				else
				{
					DEBUG_LOG("ERROR", "JSON file improperly formatted: expected more number values before finishing reading number.");
					std::exit(1);
				}
	
		}
	}
	if(readDecimal) // process floating point number and wrap and return JSONPrimitive
	{
		DEBUG_LOG("JSON", "Converting string to decimal after parsing.");
		double dNum = std::atof(numStr.c_str());
		if(readExpIndicator)
		{
			int expNum = std::atoi(expStr.c_str());
			dNum *= std::pow(10, expNum);
		}
		DEBUG_LOG("JSON", "Wrapping and returning converted decimal.");
		return new JSONPrimitive<double>(dNum);
	}
	// process integer number and wrap and return JSONPrimitive
	DEBUG_LOG("JSON", "Converting string to int after parsing.");
	int iNum = std::atoi(numStr.c_str());
	if(readExpIndicator)
	{
		int expNum = std::atoi(expStr.c_str());
		iNum = (int) std::pow(10, expNum);
	}
	DEBUG_LOG("JSON", "Wrapping and returning converted int.");
	return new JSONPrimitive<int>(iNum);
}

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
