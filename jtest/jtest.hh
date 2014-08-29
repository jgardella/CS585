#ifndef _JTEST_HH_
#define _JTEST_HH_

#include <assert.h>

// Testing framework
template <class T> 
class JTest
{
	public:
		static bool testEquality(char*, T, T);
		static bool testLessThan(char*, T, T);
		static bool testGreaterThan(char*, T, T);
};

#endif
