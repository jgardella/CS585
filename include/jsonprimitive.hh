#ifndef _JSONPRIMITIVE_HH_
#define _JSONPRIMITIVE_HH_

#include "jsonitem.hh"

// Wrapper class for JSONPrimitives.
template <class T>
class JSONPrimitive : public JSONItem
{
	public:
		JSONPrimitive(T primitive) : JSONItem(PRIMITIVE)
		{
			this->primitive = primitive;
		}

		T getPrimitive()
		{
			return primitive;
		}

	private:
		T primitive;
};

#endif
