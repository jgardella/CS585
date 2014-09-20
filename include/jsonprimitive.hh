#ifndef _JSONPRIMITIVE_HH_
#define _JSONPRIMITIVE_HH_

// Wrapper class for JSONPrimitives.
template <class T>
class JSONPrimitive
{
	public:
		JSONPrimitive(T primitive)
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
