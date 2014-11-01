// Function for reading JSON number.
#include "jsonparser.hh"

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
			case '\n':
			case '\t':
			case ',':
			case ']':
			case '}': // end of number?
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
