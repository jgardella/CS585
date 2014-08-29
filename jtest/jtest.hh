#ifndef _JTEST_HH_
#define _JTEST_HH_

#include <assert.h>

// Testing framework
template <class T> 
class JTest
{
	public:
		static void testEquality(char*, T, T);
		static void testLessThan(char*, T, T);
		static void testGreaterThan(char*, T, T);
};

#endif
