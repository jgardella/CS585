#ifndef _JSONPARSER_HH_
#define _JSONPARSER_HH_

#include "jsonobject.hh"
#include "jsonarray.hh"
#include "jsonprimitive.hh"
#include "dynamicarray.hh"
#include <fstream>
#include <cstdlib>
#include <string>
#include <cmath>

// Class containing static methods for parsing JSON.
class JSONParser
{
	public:
		// Parses the JSON file at the path specified by the given string and returns a JSONObject representing its contents.
		// Parameters:
		// string jsonFilePath - the file path of the JSON file
		// Returns a JSONObject representing the file's information.
		static DynamicArray<JSONItem*>* parseFile(std::string jsonFilePath);
	private:

		static JSONObject* readObject(std::ifstream* file);
		
		static std::string readString(std::ifstream* file);
		
		static JSONItem* readValue(std::ifstream* file);

		static JSONItem* readNumber(std::ifstream* file);

		static JSONArray* readArray(std::ifstream* file);

		static JSONItem* readBool(std::ifstream* file);		

};

#endif
