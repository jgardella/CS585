#ifndef _JSONPARSER_HH_
#define _JSONPARSER_HH_

#include "debug.hh"
#include <cstdlib>

// Class containing static methods for parsing JSON.
class JSONParser
{
	public:

		// Parses the given JSON string and returns a JSONObject representing its contents.
		// Parameters:
		// string jsonString - the json string to parse
		// Returns a JSONObject representing the string's information.
		static JSONObject parseString(std::string jsonString);

		// Parses the JSON file at the path specified by the given string and returns a JSONObject representing its contents.
		// Parameters:
		// string - jsonFilePath - the file path of the JSON file
		// Returns a JSONObject representing the file's information.
		static JSONObject parseFile(std::string jsonFilePath);
};

#endif
