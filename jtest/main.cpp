#include "jtest.hh"

int main()
{
	JTest<int>::testEquality((char*)"Simple arithmetic test.", 3, 1 + 1);
	return 0;
}
