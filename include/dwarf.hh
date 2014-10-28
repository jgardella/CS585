#ifndef _DWARF_HH_
#define _DWARF_HH_

class Dwarf : public IActor
{
	public:
		// Constructs a new dwarf.
		Dwarf();

		// Deconstructs the dwarf.
		~Dwarf();

	private:
		unsigned int health;
		const unsigned int MAX_ATTACK = 5;
};

#endif
