#include "jsonparser.hh"

DynamicArray<JSONItem*>* JSONParser::parseFile(std::string jsonFileName)
{
	Debug::getInstance()->log("JSON", "JSON file parsing initiated.");
	DynamicArray<JSONItem*>* topLevelStructures = new DynamicArray<JSONItem*>();
	char currentChar;
	std::ifstream jsonFile;
	Debug::getInstance()->log("JSON", "Opening JSON file \"/data/" + jsonFileName + "\"");
	jsonFile.open(("data/" + jsonFileName).c_str(), std::ifstream::in);
	while(jsonFile.get(currentChar))
	{
		switch(currentChar)
		{
			case ' ':
			case '\n':
			case '\r':
			case '\t':
				continue;
			case '{':
				Debug::getInstance()->log("JSON", "Parsing top level Object.");
				topLevelStructures->pushBack(readObject(&jsonFile));
				break;
			case '[':
				Debug::getInstance()->log("JSON", "Parsing top level Array.");
				topLevelStructures->pushBack(readArray(&jsonFile));
				break;
			default:
				Debug::getInstance()->log("ERROR", "JSON file improperly formatted: invalid character at top level.");
				std::exit(1);
		}
	}
	Debug::getInstance()->log("JSON", "Finished parsing JSON file.");
	return topLevelStructures;
}

JSONObject* JSONParser::readObject(std::ifstream* file)
{
	Debug::getInstance()->log("JSON", "Object parsing initiated.");
	Trie<JSONItem*>* trie = new Trie<JSONItem*>();
	char currentChar;
	std::string name;
	bool readName = false;
	bool justReadValue = false;
	while(file->get(currentChar))
	{
		switch(currentChar)
		{
			case ' ':
			case '\n':
			case '\t':
			case '\r':
				continue;
			case '}':
				if(!readName)
				{
					Debug::getInstance()->log("JSON", "Finished parsing Object, wrapping trie and returning.");
					return new JSONObject(trie);
				}
				else
				{
					Debug::getInstance()->log("ERROR", "JSON file improperly formatted: expected value before end of object.");
					std::exit(1);
				}
				break;
			case '"':
				Debug::getInstance()->log("JSON", "JSON parser reading name in Object.");
				name = readString(file);
				readName = true;
				break;
			case ':':
				if(readName)
				{
					Debug::getInstance()->log("JSON", "Parsing value within Object.");
					trie->add(name, readValue(file));
					readName = false;
					justReadValue = true;
				}
				else
				{
					Debug::getInstance()->log("ERROR", "JSON file improperly formatted: expected name before value.");
					std::exit(1);
				}
				break;
			case ',':
				if(justReadValue)
				{
					Debug::getInstance()->log("JSON", "Read comma after value, expecting next name.");
					justReadValue = false;
				}
				else
				{
					Debug::getInstance()->log("ERROR", "JSON file improperly formatted: unexpected comma in object.");
					std::exit(1);
				}
				break;
			default:
				Debug::getInstance()->log("ERROR", "JSON file improperly formatted: invalid character inside object.");
				std::exit(1);
		}
	}
	Debug::getInstance()->log("ERROR", "JSON file improperly formatted: object missing ending brace.");
	std::exit(1);
}

std::string JSONParser::readString(std::ifstream* file)
{
	Debug::getInstance()->log("JSON", "Parsing string.");
	std::string str = "";
	bool readEscapeCharacter = false;
	char currentChar;
	while(file->get(currentChar))
	{
		switch(currentChar)
		{
			case '"':
				if(readEscapeCharacter)
				{
					Debug::getInstance()->log("JSON", "Read quote (\") after escape character (\\), adding to string.");
					str.push_back(currentChar);
					readEscapeCharacter = false;
				}
				else
				{
					Debug::getInstance()->log("JSON", "Read quote (\") not preceded by escape character (\\), returning string.");
					return str;
				}
				break;
			case '\\':
				Debug::getInstance()->log("JSON", "Read escape character (\\).");
				readEscapeCharacter = true;
				break;
			default:
				Debug::getInstance()->log("JSON", "Read non-special character, adding to string.");
				str.push_back(currentChar);
				readEscapeCharacter = false;
				break;
		}
	}
	Debug::getInstance()->log("ERROR", "JSON file improperly formatted: string missing end quote.");
	std::exit(1);
}

JSONItem* JSONParser::readValue(std::ifstream* file)
{
	Debug::getInstance()->log("JSON", "Value parsing initiated.");
	char currentChar;
	char followingChars[3];
	while(file->get(currentChar))
	{
		switch(currentChar)
		{
			case ' ':
			case '\t':
			case '\n':
			case '\r':
				Debug::getInstance()->log("JSON", "Read whitespace while reading value, continuing.");
				continue;
			case '{':
				Debug::getInstance()->log("JSON", "Read left brace { while reading value, parsing object.");
				return readObject(file);
			case '"':
				Debug::getInstance()->log("JSON", "Read quote while reading value, parsing string.");
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
			case '-':
				Debug::getInstance()->log("JSON", "Read number or - while reading value, parsing number.");
				return readNumber(file, currentChar);
			case 't':
			case 'f':
				Debug::getInstance()->log("JSON", "Read t or f while reading value, parsing boolean.");
				return readBool(file, currentChar);
			case 'n':
				file->get(followingChars, 3);
				if(std::string(followingChars).compare("ull") == 0)
				{
					Debug::getInstance()->log("JSON", "Read null while reading value, returning NULL.");
					return NULL;
				}
				else
				{
					Debug::getInstance()->log("ERROR", "JSON file improperly formatted: invalid character where null value expected.");
					std::exit(1);
				}
			case '[':
				Debug::getInstance()->log("JSON", "Read left bracket [ while reading value, parsing array.");
				return readArray(file);
			default:
				Debug::getInstance()->log("ERROR", "JSON file improperly formatted: invalid character while reading value.");
				std::exit(1);
		}
	}
	Debug::getInstance()->log("ERROR", "JSON file improperly formatted: file ended unexpectedly while reading value.");
	std::exit(1);
}

JSONArray* JSONParser::readArray(std::ifstream* file)
{
	Debug::getInstance()->log("JSON", "Array parsing initiated.");
	char currentChar;
	bool justReadValue = false;
	DynamicArray<JSONItem*>* array = new DynamicArray<JSONItem*>();
	while((currentChar = file->peek()))
	{
		switch(currentChar)
		{
			case ' ':
			case '\n':
			case '\t':
			case '\r':
				Debug::getInstance()->log("JSON", "Read whitespace while parsing array, continuing.");
				file->get();
				continue;
			case ']':
				if(!justReadValue || array->length() == 0)
				{
					Debug::getInstance()->log("JSON", "Read right bracket ] while parsing array, wrapping and returning array.");
					file->get();
					return new JSONArray(array);
				}
				else
				{
					Debug::getInstance()->log("ERROR", "JSON file improperly formatted: unexpected closing bracket when value expected while reading array.");
					std::exit(1);
				}
			case ',':
				if(justReadValue)
				{
					Debug::getInstance()->log("JSON", "Read comma while parsing array, parsing value.");
					justReadValue = false;
					file->get();
					array->pushBack(readValue(file));
					break;
				}
				else
				{
					Debug::getInstance()->log("ERROR", "JSON file improperly formatted: read invalid comma while reading array.");
					std::exit(1);
				}
			default:
				if(!justReadValue)
				{
					Debug::getInstance()->log("JSON", "Read non-special character while parsing array, parsing value.");
					array->pushBack(readValue(file));
					justReadValue = true;
				}
				else
				{
					Debug::getInstance()->log("ERROR", "JSON file improperly formatted: read invalid character when expecing comma while reading array.");
					std::exit(1);
				}
		}
	}
	Debug::getInstance()->log("ERROR", "JSON file improperly formatted: file ended unexpectedly while reading array.");	
	std::exit(1);
}

JSONItem* JSONParser::readNumber(std::ifstream* file, char lastChar)
{
	Debug::getInstance()->log("JSON", "Number parsing initiated.");
	char currentChar;
	std::string numStr = "" + lastChar;
	bool readDecimal = false;
	bool endOfNumberReached = false;
	bool readExpIndicator = false;
	std::string expStr = "";
	while((currentChar = file->peek()) && !endOfNumberReached)
	{
		switch(currentChar)
		{
			case '.':
				if(!readDecimal)
				{
					Debug::getInstance()->log("JSON", "Read decimal point while parsing number, pushing to number string.");
					readDecimal = true;
					file->get();
					numStr.push_back(currentChar);
					break;
				}
				else
				{
					Debug::getInstance()->log("ERROR", "JSON file improperly formatted: read invalid decimal point in number; decimal already read.");
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
			case '9':
				if(!readExpIndicator)
				{
					Debug::getInstance()->log("JSON", "Read number character while parsing number, pushing to number string.");
					file->get();
					numStr.push_back(currentChar);
				}
				else
				{
					Debug::getInstance()->log("JSON", "Read number character after reading exponent indicator while parsing number, pushing to exponent string.");
					file->get();
					expStr.push_back(currentChar);
				}
				break;
			case 'e':
			case 'E':
				if(!readExpIndicator)
				{
					Debug::getInstance()->log("JSON", "Read e or E while parsing number, enabling exponent mode.");
					file->get();
					readExpIndicator = true;
					break;
				}
				else
				{
					Debug::getInstance()->log("ERROR", "JSON file improperly formatted: read more than one scientific notation indicator in one number.");
					std::exit(1);
				}
			case '+':
			case '-':
				if(numStr.at(numStr.length() - 1) == 'e' || numStr.at(numStr.length() - 1) == 'E')
				{
					Debug::getInstance()->log("JSON", "Read + or - immediately after reading exponent indicator while parsing number, appending to exponent string.");
					file->get();
					expStr.push_back(currentChar);
					break;
				}
			case ' ':
			case ',':
				if(numStr.at(numStr.length() - 1) != '.' && numStr.at(numStr.length() - 1) != 'e' && numStr.at(numStr.length() - 1) != 'E' && numStr.at(numStr.length() - 1) != '+' && numStr.at(numStr.length() - 1) != '-')
				{
					Debug::getInstance()->log("JSON", "Read whitespace or comma while parsing string, end of number reached.");
					endOfNumberReached = true;
					break;
				}
				else
				{
					Debug::getInstance()->log("ERROR", "JSON file improperly formatted: expected more number values before finishing reading number.");
					std::exit(1);
				}
	
		}
	}
	if(readDecimal)
	{
		Debug::getInstance()->log("JSON", "Converting string to decimal after parsing.");
		double dNum = std::atof(numStr.c_str());
		if(readExpIndicator)
		{
			double expNum = std::atof(expStr.c_str());
			dNum *= std::pow(10, expNum);
		}
		Debug::getInstance()->log("JSON", "Wrapping and returning converted decimal.");
		return new JSONPrimitive<double>(dNum);
	}
	Debug::getInstance()->log("JSON", "Converting string to int after parsing.");
	int iNum = std::atoi(numStr.c_str());
	if(readExpIndicator)
	{
		int expNum = std::atoi(expStr.c_str());
		iNum = (int) std::pow(10, expNum);
	}
	Debug::getInstance()->log("JSON", "Wrapping and returning converted int.");
	return new JSONPrimitive<int>(iNum);
}

JSONItem* JSONParser::readBool(std::ifstream* file, char lastChar)
{
	Debug::getInstance()->log("JSON", "Initiating boolean parsing.");
	char followingChars[4];
	followingChars[3] = '\0';
	if(lastChar == 't')
	{
		file->get(followingChars, 3);
		if(std::string(followingChars).compare("rue") == 0)
		{
			Debug::getInstance()->log("JSON", "Read true while parsing boolean, wrapping and returning true value.");
			return new JSONPrimitive<bool>(true);
		}
		else
		{
			Debug::getInstance()->log("ERROR", "JSON file improperly formatted: invalid character where true value expected.");
			std::exit(1);
		}
	}
	file->get(followingChars, 4);
	if(std::string(followingChars).compare("alse") == 0)
	{
		Debug::getInstance()->log("JSON", "Read false while parsing boolean, wrapping and returning false value.");
		return new JSONPrimitive<bool>(false);
	}
	else
	{
		Debug::getInstance()->log("ERROR", "JSON file improperly formatted: invalid character where false value expected.");
		std::exit(1);
	}
}
