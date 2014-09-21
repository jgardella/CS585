#ifndef _JSONPARSER_HH_
#define _JSONPARSER_HH_

#include "jsonobject.hh"
#include "dynamicarray.hh"
#include "ifstream.hh"
#include <cstdlib>
#include <string>
#include <cmath>

// Class containing static methods for parsing JSON.
class JSONParser
{
	public:
		// Parses the JSON file at the path specified by the given string and returns a JSONObject representing its contents.
		// Parameters:
		// string - jsonFilePath - the file path of the JSON file
		// Returns a JSONObject representing the file's information.
		static DynamicArray<JSONObject*>* parseFile(std::string jsonFilePath);

	private:

		JSONObject* readObject(ifstream* file);
		
		std::string readString(ifstream* file);
		
		JSONItem* readValue(ifstream* file);

		JSONItem* readNumber(ifstream* file, char lastChar);

		JSONArray* readArray(ifstream* file);

		JSONPrimitive<bool>* readBool(ifstream* file, char lastChar);		

};

#endif
