#ifndef _DYNAMICARRAYTESTING_HH_
#define _DYNAMICARRAYTESTING_HH_

#include "dynamicarray.hh"
#include "jtest.hh"

class DynamicArrayTesting
{
	public:
		static void simpleArithmeticTest();
		static void assignmentTest();
		static void defaultConstructorTest();
		static void preAllocatedConstructorTest();
		static void pushFrontTest();
		static void pushBackTest();
		static void insertionTest();
		static void getTest();
		static void insertTest();
		static void removeTest();
		static void swapTest();
		static void lengthTest();
		static void capacityTest();
		static void memoryReallocationTest();
};

#endif