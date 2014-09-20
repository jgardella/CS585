#ifndef _JSONITEM_HH_
#define _JSONITEM_HH_

enum jsonType_t {ARRAY, OBJECT, PRIMITIVE}; // enum containing different types of JSON items

// Abstract class for JSON items.
class JSONItem
{
	public:
		jsonType_t getType();
		JSONItem(jsonType_t type);

	private:
		jsonType_t type; // the type of JSONItem that the implementing class is (used for downcasting)
};

#endif
