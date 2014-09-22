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
		
		// Parses a JSON Object, assuming the given filestream pointer is at the start of an object.
		// Parameters:
		// std::ifstream* file - the filestream being used to parse the JSON file; should be at start of an object.
		static JSONObject* readObject(std::ifstream* file);
		
		// Parses a JSON string, assuming the given filestream pointer is at the start of a string.
		// Parameters:
		// std::ifstream* file - the filestream being used to parse the JSON file; should be at start of a string.
		// Returns the parsed string. String is not wrapped so that this function can be used to retrieve both names and string values.
		static std::string readString(std::ifstream* file);
		
		// Parses a JSON value, assuming the given filestream pointer is at the start of a value.
		// Parameters:
		// std::ifstream* file - the filestream being used to parse the JSON file; should be at start of a value.
		// Returns a JSONItem pointer to the parsed value.
		static JSONItem* readValue(std::ifstream* file);

		// Parses a JSON number, assuming the given filestream pointer is at the start of a number.
		// Parameters:
		// std::ifstream* file - the filestream being used to parse the JSON file; should be at start of a number.
		// Returns a JSONItem pointer to the parsed number, wrapped in a JSONPrimitive.
		static JSONItem* readNumber(std::ifstream* file);

		// Parses a JSON Array, assuming the given filestream pointer is at the start of an array.
		// Parameters:
		// std::ifstream* file - the filestream being used to parse the JSON file; should be at start of an array.
		// Returns a pointer to the parsed JSONArray.
		static JSONArray* readArray(std::ifstream* file);

		// Parses a JSON boolean, assuming the given filestream pointer is at the start of a boolean.
		// Parameters:
		// std::ifstream* file - the filestream being used to parse the JSON file; should be at start of a boolean.
		// Returns a pointer to the parsed boolean, wrapped in a JSONPrimitive.
		static JSONItem* readBool(std::ifstream* file);		

};

#endif
