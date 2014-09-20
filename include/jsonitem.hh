#ifndef _JSONITEM_HH_
#define _JSONITEM_HH_

// Abstract class for JSON items.
class JSONItem
{
	public:
		static enum jsonType_t = {ARRAY, OBJECT, PRIMITIVE}; // enum containing different types of JSON items
		jsonType_t getType();

	private:
		JSONItem(){ }; // constructor is private because JSONItem should not be constructed, only its children
		jsonType_t type; // the type of JSONItem that the implementing class is (used for downcasting)
};

#endif
