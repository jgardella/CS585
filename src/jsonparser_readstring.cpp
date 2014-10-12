#include "jsonparser.hh"
// Function for reading JSON string.

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
