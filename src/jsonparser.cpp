#include "jsonparser.hh"

DynamicArray<JSONItem*>* JSONParser::parseFile(std::string jsonFileName)
{
	DynamicArray<JSONItem*> topLevelStructures = new DynamicArray<JSONItem*>();
	char currentChar;
	ifstream jsonFile ("data/" + jsonFileName);
	while(jsonFile.get(&currentChar))
	{
		switch(currentChar)
		{
			case ' ':
			case '\n':
			case '\r':
			case '\t':
				continue;
			case '{':
				topLevelStructures->pushBack(readObject(&jsonFile));
				break;
			case '[':
				topLevelStructures->pushBack(readArray(&jsonFile));
				break;
			default:
				Debug::getInstance()->log("ERROR", "JSON file improperly formatted: invalid character at top level.");
				std::exit(1);
		}
	}
	return topLevelStructures;
}

JSONObject* JSONParser::readObject(ifstream* file)
{
	Trie<JSONItem*>* trie = new Trie<JSONItem*>();
	char currentChar;
	std::string name;
	bool readName = false;
	while(file->get(&currentChar))
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
					return new JSONObject(trie);
				}
				else
				{
					Debug::getInstance()->log("ERROR" "JSON file improperly formatted: expected value before end of object.");
					std::exit(1);
				}
				break;
			case '"':
				name = readString(file);
				readName = true;
				break;
			case ':':
				if(readName)
				{
					trie.add(name, readValue(file));
					readName = false;
				}
				else
				{
					Debug::getInstance()->log("ERROR", "JSON file improperly formatted: expected name before value.");
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

std::string JSONParser::readString(ifstream* file)
{
	std::string str = "";
	bool readEscapeCharacter = false;
	char currentChar;
	while(file->get(&currentChar))
	{
		switch(currentChar)
		{
			case '"':
				if(readEscapeCharacter)
				{
					str.push_back(currentChar);
					readEscapeCharacter = false;
				}
				else
				{
					return str;
				}
				break;
			case '\\':
				readEscapeCharacter = true;
				str.push_back(currentChar);
				break;
			default:
				str.push_back(currentChar);
				readEscapeCharacter = false;
				break;
		}
	}
	Debug::getInstance()->log("ERROR", "JSON file improperly formatted: string missing end quote.");
	std::exit(1);
}

JSONItem* JSONParser::readValue(ifstream* file)
{
	char currentChar;
	char* followingChars;
	while(file->get(&currentChar))
	{
		switch(currentChar)
		{
			case ' ':
			case '\t':
			case '\n':
			case '\r':
				continue;
			case '{':
				return readObject(file);
			case '"':
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
				return readNumber(file, currentChar);
			case 't':
			case 'f':
				return new readBool(file, currentChar);
			case 'n':
				file->get(followingChars, 3);
				if(std::string(followingChars).compare("ull") == 0)
				{
					return NULL;
				}
				else
				{
					Debug::getInstance()->log("ERROR", "JSON file improperly formatted: invalid character where null value expected.");
					std::exit(1);
				}
			case '[':
				return readArray(file);
			default:
				Debug::getInstance()->log("ERROR", "JSON file improperly formatted: invalid character while reading value.");
				std::exit(1);
		}
	}
	Debug::getInstance()->log("ERROR", "JSON file improperly formatted: file ended unexpectedly while reading value.");
	std::exit(1);
}

JSONArray* readArray(ifstream* file)
{
	char currentChar;
	bool justReadValue = false;
	DynamicArray<JItem*>* array = new DynamicArray<JItem*>();
	while(file->peek(&currentChar))
	{
		switch(currentChar)
		{
			case ' ':
			case '\n':
			case '\t':
			case '\r':
				file->get();
				continue;
			case ']':
				if(justReadValue)
				{
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
					array->pushBack(readValue(file));
				}
				else
				{
					Debug::getInstance()->log("ERROR", "JSON file improperly formatted: read invalid character when expecing comma while reading array.");
					std::exit(1);
				}
		}
	}	       
}

JSONItem* readNumber(ifstream* file, char lastChar)
{
	char currentChar;
	std::string numStr = lastChar;
	bool readDecimal = false;
	bool endOfNumberReached = false;
	bool readExpIndicator = false;
	std::string expStr = "";
	while(file->peek(&currentChar) && !endOfNumberReached)
	{
		switch(currentChar)
		{
			case '.':
				if(!readDecimal)
				{
					readDecimal = true;
					file->get();
					numStr.append(currentChar);
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
					file->get();
					numStr.append(currentChar);
				}
				else
				{
					file->get();
					expStr.append(currentChar);
				}
				break;
			case 'e':
			case 'E':
				if(!readExpIndicator)
				{
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
				if(numStr.back() == 'e' || numStr.back() == "E")
				{
					file->get();
					expStr.append(currentChar);
					break;
				}
			case ' ':
			case ',':
				if(numStr.back() != '.' && numStr.back() != 'e' && numStr.back() != 'E' && numStr.back() != '+' && numStr.back() != '-')
				{
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
		float fNum = stof(numStr);
		if(readExpIndicator)
		{
			float expNum = stof(expStr);
			fNum *= std::pow(10, expNum);
		}
		return new JSONPrimitive<float>(fNum);
	}
	int iNum = stoi(numStr);
	if(readExpIndicator)
	{
		int expNum = stoi(expStr);
		iNum = (int) std::pow(10, expNum);
	}
	return new JSONPrimitive<int>(iNum);
}

JSONPrimitive<bool>* readBool(ifstream* file, char lastChar)
{
	char* followingChars;
	if(lastChar == 't')
	{
		file->get(followingChars, 3);
		if(std::string(followingChars).compare("rue") == 0)
		{
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
		return new JSONPrimitive<bool>(false);
	}
	else
	{
		Debug::getInstance()->log("ERROR", "JSON file improperly formatted: invalid character where false value expected.");
		std::exit(1);
	}
}
