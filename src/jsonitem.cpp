#include "jsonitem.hh"

JSONItem::JSONItem(jsonType_t type)
{
	this->type = type;
}

jsonType_t JSONItem::getType()
{
	return type;
}
