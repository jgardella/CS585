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
			case '\\':
				if(readEscapeCharacter)
				{
					Debug::getInstance()->log("JSON", "Read backslash (\\) after escape character (\\), adding to string.");
					str.push_back('\\');
					readEscapeCharacter = false;
				}
				else
				{
					readEscapeCharacter = true;
				}
				break;
			case '"':
				if(readEscapeCharacter)
				{
					Debug::getInstance()->log("JSON", "Read quote (\") after escape character (\\), adding to string.");
					str.push_back('\"');
					readEscapeCharacter = false;
					break;
				}
				else
				{
					Debug::getInstance()->log("JSON", "Read quote (\") not preceded by escape character (\\), end of string reached, returning string.");
					return str;
				}
			case 'f':
				if(readEscapeCharacter)
				{
					Debug::getInstance()->log("JSON", "Read character 'f' after escape character (\\), adding form feed to string.");
					str.push_back('\f');
					readEscapeCharacter = false;
					break;
				}
			case 'n':
				if(readEscapeCharacter)
				{
					Debug::getInstance()->log("JSON", "Read character 'n' ater escape character (\\), adding newline to string.");
					str.push_back('\n');
					readEscapeCharacter = false;
					break;
				}
			case 't':
				if(readEscapeCharacter)
				{
					Debug::getInstance()->log("JSON", "Read character 't' after escape character (\\), adding tab to string.");
					str.push_back('\t');
					readEscapeCharacter = false;
					break;
				}
			case 'r':
				if(readEscapeCharacter)
				{
					Debug::getInstance()->log("JSON", "Read character 'r' after escape character (\\), adding carriage return to string.");
					str.push_back('\r');
					readEscapeCharacter = false;
					break;
				}
			case 'b':
				if(readEscapeCharacter)
				{
					Debug::getInstance()->log("JSON", "Read character 'b' after escape character (\\), adding backspace to string.");
					str.push_back('\b');
					readEscapeCharacter = false;
				}
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
	while((currentChar = file->peek()))
	{
		switch(currentChar)
		{
			case ' ':
			case '\t':
			case '\n':
			case '\r':
				file->get();
				Debug::getInstance()->log("JSON", "Read whitespace while reading value, continuing.");
				continue;
			case '{':
				file->get();
				Debug::getInstance()->log("JSON", "Read left brace { while reading value, parsing object.");
				return readObject(file);
			case '"':
				file->get();
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
				return readNumber(file);
			case 't':
			case 'f':
				Debug::getInstance()->log("JSON", "Read t or f while reading value, parsing boolean.");
				return readBool(file);
			case 'n':
				file->get(followingChars, 4);
				if(std::string(followingChars).compare("null") == 0)
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
				file->get();
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
	bool justReadComma = false;
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
				if(!justReadComma)
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
				if(array->length() != 0)
				{
					Debug::getInstance()->log("JSON", "Read comma while parsing array.");
					justReadComma = true;
					file->get();
					break;
				}
				else
				{
					Debug::getInstance()->log("ERROR", "JSON file improperly formatted: read invalid comma while reading array.");
					std::exit(1);
				}
			default:
				if(justReadComma || array->length() == 0)
				{
					Debug::getInstance()->log("JSON", "Read non-special character while parsing array, parsing value.");
					justReadComma = false;
					array->pushBack(readValue(file));
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

JSONItem* JSONParser::readNumber(std::ifstream* file)
{
	Debug::getInstance()->log("JSON", "Number parsing initiated.");
	char currentChar;
	std::string numStr = "";
	bool readDecimal = false;
	bool endOfNumberReached = false;
	bool readExpIndicator = false;
	bool justReadExpIndicator = false;
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
					if(justReadExpIndicator)
					{
						justReadExpIndicator = false;
					}
				}
				break;
			case 'e':
			case 'E':
				if(!readExpIndicator)
				{
					Debug::getInstance()->log("JSON", "Read e or E while parsing number, enabling exponent mode.");
					file->get();
					readExpIndicator = true;
					justReadExpIndicator = true;
					break;
				}
				else
				{
					Debug::getInstance()->log("ERROR", "JSON file improperly formatted: read more than one scientific notation indicator in one number.");
					std::exit(1);
				}
			case '+':
			case '-':
				if(justReadExpIndicator)
				{
					Debug::getInstance()->log("JSON", "Read + or - immediately after reading exponent indicator while parsing number, appending to exponent string.");
					file->get();
					expStr.push_back(currentChar);
					justReadExpIndicator = false;
					break;
				}
				else if(numStr.length() == 0)
				{
					Debug::getInstance()->log("JSON", "Read + or - at start of number, appending to number string.");
					file->get();
					numStr.push_back(currentChar);
					break;
				}
				Debug::getInstance()->log("ERROR", "JSON file improperly formatted: read unexpected + or - while reading number.");
				std::exit(1);
			case ' ':
			case ',':
			case ']':
				if(!justReadExpIndicator && (!readExpIndicator || (expStr.length() != 0 && expStr.at(expStr.length() - 1) != '+' && expStr.at(expStr.length() - 1) != '-')))
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
			int expNum = std::atoi(expStr.c_str());
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

JSONItem* JSONParser::readBool(std::ifstream* file)
{
	Debug::getInstance()->log("JSON", "Initiating boolean parsing.");
	char followingChars[4];
	followingChars[3] = '\0';
	if(file->get() == 't')
	{
		file->get(followingChars, 4);
	}
	else
	{
		file->get(followingChars, 5);
	}
	if(std::string(followingChars).compare("rue") == 0)
	{
		Debug::getInstance()->log("JSON", "Read true while parsing boolean, wrapping and returning true value.");
		return new JSONPrimitive<bool>(true);
	}
	else if(std::string(followingChars).compare("alse") == 0)
	{
		Debug::getInstance()->log("JSON", "Read false while parsing boolean, wrapping and returning false value.");
		return new JSONPrimitive<bool>(false);
	}
	Debug::getInstance()->log("ERROR", "JSON file improperly formatted: invalid character where true or false value expected.");
	std::exit(1);
}
