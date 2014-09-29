#include "dynamicarray.hh"
#include "stack.hh"
#include "queue.hh"
#include "trie.hh"
#include "jtest.hh"
#include "jsonprimitive.hh"
#include "jsonarray.hh"
#include "jsonobject.hh"
#include "jsonparser.hh"

// -------------------- DYNAMIC ARRAY TESTS -------------------- 

void dynamicArraySimpleArithmeticTest()
{
	JTest<int>::testEquality("Simple arithmetic test", 2, 1+1);
}

void dynamicArrayAssignmentTest()
{
	int a = 5;
	JTest<int>::testEquality("Assignment test", 5, a);
}

// Tests the default constructor by making sure it correctly instantiates length and capacity.
void dynamicArrayDefaultConstructorTest()
{
	DynamicArray<int> *array = new DynamicArray<int>();
	JTest<int>::testEquality("Default constructor test, length set", 0, array->length());
	JTest<int>::testEquality("Default constructor test: capacity set", 10, array->capacity());
	delete array;
}

// Tests the manual constructor by making sure it correctly instantiates length and capacity.
void dynamicArrayPreAllocatedConstructorTest()
{
	DynamicArray<int> *array = new DynamicArray<int>(20);
	JTest<int>::testEquality("Manual constructor test, length set", 0, array->length());
	JTest<int>::testEquality("Manual constructor test, capacity set", 20, array->capacity());
	delete array;
}

// Tests if memory is proprely reallocated when the array's capacity is exceeded on either the left or right side.
void dynamicArrayMemoryReallocationTest()
{
	// Test array overflow on back side.
	DynamicArray<int> *array = new DynamicArray<int>();
	array->pushBack(1);
	array->pushBack(2);
	array->pushBack(3);
	array->pushBack(4);
	array->pushBack(5);
	array->pushBack(6);
	array->pushBack(7);
	array->pushBack(8);
	array->pushBack(9);
	array->pushBack(10);
	array->pushBack(11);
	JTest<int>::testEquality("Back memory reallocation test, array capacity expanded to hold more items", 15, array->capacity());
	JTest<int>::testEquality("Back memory reallocation test, element which surpassed capacity has been added", 11, *array->get(10));
	delete array;
	
	// Test array overflow on front side.
	array = new DynamicArray<int>();
	array->pushFront(1);
	array->pushFront(2);
	array->pushFront(3);
	array->pushFront(4);
	array->pushFront(5);
	array->pushFront(6);
	array->pushFront(7);
	array->pushFront(8);
	array->pushFront(9);
	array->pushFront(10);
	array->pushFront(11);
	JTest<int>::testEquality("Front memory reallocation test, array capacity expanded to hold more items", 15, array->capacity());
	JTest<int>::testEquality("Front memory reallocation test, element which surpassed capacity has been added", 11, *array->get(0));
	delete array;
}

// Tests that the reserve method correctly expands the array's capacity.
void dynamicArrayReserveTest()
{
	DynamicArray<int> *array = new DynamicArray<int>();
	array->reserve(100);
	JTest<int>::testEquality("Reserve test, array capacity expanded", 100, array->capacity());
	array->reserve(50);
	JTest<int>::testEquality("Reserve test, array capacity not expanded", 100, array->capacity());
	delete array;
}

// Adds a lot of elements to the array to check that it is correctly reallocated.
void dynamicArraySeveralReallocationTest()
{
	DynamicArray<int> *array = new DynamicArray<int>();
	unsigned int i;
        int j;
	for(i = 1; i <= 100; i++)
	{
		array->pushBack(i);
	}
	bool isProperlyExpanded = true;
	for(i = 0, j = 1; i < array->length() && isProperlyExpanded; i++, j++)
	{
		if(*array->get(i) != j)
		{
			isProperlyExpanded = false;
		}
	}
	JTest<int>::testEquality("Memory reallocation test, elements added and array reallocated several times", 1, isProperlyExpanded);
	delete array;
}

// Tests the swap method of dynamicarray by adding two elements, swapping them, and then checking to make sure
// they were correctly swapped.
void dynamicArraySwapTest()
{
	DynamicArray<int> *array = new DynamicArray<int>();
	array->pushFront(1);
	array->pushBack(2);
	array->swap(0, 1);
	JTest<int>::testEquality("Swap test, element at indexTwo is in indexOne", 2, *array->get(0));
	JTest<int>::testEquality("Swap test, element at indexOne is in indexTwo", 1, *array->get(1));
	delete array;
}

// Tests the set method of dynamic array by adding one element, then setting a new element in its position, checking if the new element is in the correct position.
void dynamicArraySetTest()
{
	DynamicArray<int> *array = new DynamicArray<int>();
	array->pushBack(1);
	int replacedElement = array->set(2, 0);
	JTest<int>::testEquality("Set test, replaced element returned", 1, replacedElement);
	JTest<int>::testEquality("Set test, inserted element is in correct position", 2, *array->get(0));
	delete array;	
}

// Tests the insert method of dynamic array by adding several elements, then inserting one and checking that the element is correctly inserted and the other elements are correctly shifted.
void dynamicArrayInsertTest()
{
	DynamicArray<int> *array = new DynamicArray<int>(5);
	array->pushBack(1);
	array->pushBack(2);
	array->pushBack(4);
	array->pushBack(5);
	array->insert(3, 2);
	JTest<int>::testEquality("Insert test, element correctly inserted", 3, *array->get(2));
	JTest<int>::testEquality("Insert test, elements correctly shifted for insert", 4, *array->get(3));
	array->insert(2, 1);
	JTest<int>::testEquality("Insert test, full array reallocated and element inserted", 2, *array->get(1));
	JTest<int>::testEquality("Insert test, full array reallocated and elements shifted for insert", 2, *array->get(2));
	delete array;
}

// Tests the get method of dynamic array by inserting an element and then getting that element and checking that the corrent element is returned.
void dynamicArrayGetTest()
{
	DynamicArray<int> *array = new DynamicArray<int>();
	array->pushBack(0);
	JTest<int>::testEquality("Get test, calling get returns correct element", 0, *array->get(0));
	delete array;
}

// Tests the remove methodby inserting 5 elements, removing the middle one, and then checking that the remaining elements are properly shifted and the length is decreased.
// There are separate tests for removing from the left half and right half of the array because the remove method behaves differently depending on which side of the array the item
// is removed from.
void dynamicArrayRemoveTest()
{
	DynamicArray<int> *array = new DynamicArray<int>();
	array->pushBack(1);
	int removedElement = array->remove(0);
	JTest<int>::testEquality("Remove test, remove with only one element, element returned", 1, removedElement);
	JTest<int>::testEquality("Remove test, length decremented", 0, array->length());

	array->pushBack(1);
	array->pushBack(2);
	array->pushBack(3);
	array->pushBack(4);
	array->pushBack(5);
	// Test remove method when an item is removed from the left half of the array.
	removedElement = array->remove(2);
	JTest<int>::testEquality("Left side remove test, removed element correctly returned", 3, removedElement);
	JTest<int>::testEquality("Left side remove test, element one did not move", 1, *array->get(0));
	JTest<int>::testEquality("Left side remove test, element two did not move", 2, *array->get(1));
	JTest<int>::testEquality("Left side remove test, element four is now element three", 4, *array->get(2));
	JTest<int>::testEquality("Left side remove test, element five is now element four", 5, *array->get(3));
	JTest<int>::testEquality("Left side remove test, array length decreased", 4, array->length());
	
	// Test remove method when an item is removed from the right half of the array.
	array->pushBack(6);
	array->pushBack(7);
	removedElement = array->remove(3);
	JTest<int>::testEquality("Right side remove test, removed element correctly returned", 5, removedElement);
	JTest<int>::testEquality("Right side remove test, element one did not move", 1, *array->get(0));
	JTest<int>::testEquality("Right side remove test, element two did not move", 2, *array->get(1));
	JTest<int>::testEquality("Right side remove test, element three did not move", 4, *array->get(2));
	JTest<int>::testEquality("Right side remove test, element five is now element four", 6, *array->get(3));
	JTest<int>::testEquality("Right side remove test, element six is now element five", 7, *array->get(4));
	delete array;
}

// Tests push front method by pushing several element to the front and checking that they have been properly pushed.
void dynamicArrayPushFrontTest()
{
	DynamicArray<int> *array = new DynamicArray<int>();
	array->pushFront(1);
	JTest<int>::testEquality("Push front test, element one pushed to front", 1, *array->get(0));
	JTest<int>::testEquality("Push front test, length incremented", 1, array->length());
	array->pushFront(2);
	JTest<int>::testEquality("Push front test, element two pushed to front", 2, *array->get(0));
	JTest<int>::testEquality("Push front test, element one now in position 2", 1, *array->get(1));
	JTest<int>::testEquality("Push front test, length incremented", 2, array->length());
	delete array;
}

// Tests the push back method by pushing several elements to the back and checking that they have been properly pushed.
void dynamicArrayPushBackTest()
{
	DynamicArray<int> *array = new DynamicArray<int>();
	array->pushBack(1);
	JTest<int>::testEquality("Push back test, element one pushed to back", 1, *array->get(0));
	JTest<int>::testEquality("Push back test, length incremented", 1, array->length());
	array->pushBack(2);
	JTest<int>::testEquality("Push back test, element one still in position one", 1, *array->get(0));
	JTest<int>::testEquality("Push back test, element two in position two", 2, *array->get(1));
	JTest<int>::testEquality("Push back test, length incremented", 2, array->length());
	delete array;
}

// Tests the recenter method by causing an overflow on the front and back of the array.
void dynamicArrayRecenterTest()
{
	bool areElementsCorrectlyRepositioned;
	unsigned int i;
	int j;
	DynamicArray<int> *array = new DynamicArray<int>();
	array->pushFront(10);
	array->pushFront(9);
	array->pushFront(8);
	array->pushFront(7);
	array->pushFront(6);
	array->pushFront(5);
	
	areElementsCorrectlyRepositioned = true;
	for(i = 0, j = 0; i < array->length() && areElementsCorrectlyRepositioned; i++, j++)
	{
		if(*array->get(i) != j + 5)
		{
			areElementsCorrectlyRepositioned = false;
		}
	}

	JTest<int>::testEquality("Recenter test front, elements correctly repositioned", true, areElementsCorrectlyRepositioned);
	JTest<int>::testEquality("Recenter test front, capacity unchanged", 10, array->capacity());

	array->pushFront(4);
	array->pushFront(3);
	array->pushFront(2);
	array->pushFront(1);

	areElementsCorrectlyRepositioned = true;
	for(i = 0, j = 1; i < array->length() && areElementsCorrectlyRepositioned; i++, j++)
	{
		if(*array->get(i) != j)
		{
			areElementsCorrectlyRepositioned = false;
		}
	}

	JTest<int>::testEquality("Recenter test front, elements correctly repositioned", true, areElementsCorrectlyRepositioned);
	JTest<int>::testEquality("Recenter test front, capacity unchanged", 10, array->capacity());
	
	delete array;

	array = new DynamicArray<int>();
	array->pushBack(1);
	array->pushBack(2);
	array->pushBack(3);
	array->pushBack(4);
	array->pushBack(5);
	array->pushBack(6);
	
	areElementsCorrectlyRepositioned = true;
	for(i = 0, j = 1; i < array->length() && areElementsCorrectlyRepositioned; i++, j++)
	{
		if(*array->get(i) != j)
		{
			areElementsCorrectlyRepositioned = false;
		}
	}

	JTest<int>::testEquality("Recenter test back, elements correctly repositioned", true, areElementsCorrectlyRepositioned);
	JTest<int>::testEquality("Recenter test back, capacity unchanged", 10, array->capacity());

	array->pushBack(7);
	array->pushBack(8);
	array->pushBack(9);
	array->pushBack(10);

	areElementsCorrectlyRepositioned = true;
	for(i = 0, j = 1; i < array->length() && areElementsCorrectlyRepositioned; i++, j++)
	{
		if(*array->get(i) != j)
		{
			areElementsCorrectlyRepositioned = false;
		}
	}

	JTest<int>::testEquality("Recenter test back, elements correctly repositioned", true, areElementsCorrectlyRepositioned);
	JTest<int>::testEquality("Recenter test back, capacity unchanged", 10, array->capacity());
	delete array;
}

// -------------------- END DYNAMIC ARRAY TESTS -------------------- 

// --------------------      STACK TESTS        --------------------

void stackPushAndPopTest()
{
	Stack<int> *stack = new Stack<int>();
	stack->push(5);
	stack->push(4);
	stack->push(3);
	stack->push(2);
	stack->push(1);

	JTest<int>::testEquality("Push and pop test, first element popped", 1, stack->pop());
	JTest<int>::testEquality("Push and pop test, second element popped", 2, stack->pop());
	JTest<int>::testEquality("Push and pop test, third element popped", 3, stack->pop());
	JTest<int>::testEquality("Push and pop test, fourth element popped", 4, stack->pop());
	JTest<int>::testEquality("Push and pop test, fifth element popped", 5, stack->pop());

	delete stack;
}

void stackPeekTest()
{
	Stack<int> *stack = new Stack<int>();
	stack->push(1);

	JTest<int>::testEquality("Peek test, first element peeked", 1, stack->peek());
	JTest<int>::testEquality("Peek test, first element still in stack", 1, stack->pop());

	delete stack;
}

void stackBoundedTest()
{
	Stack<int> *stack = new Stack<int>(5);
	stack->push(5);
	stack->push(4);
	stack->push(3);
	stack->push(2);
	stack->push(1);
	stack->push(0);

	JTest<int>::testEquality("Bounded stack test, element not added when capacity reached", 1, stack->peek());

	delete stack;
}

// --------------------  END STACK TESTS        --------------------


// --------------------    QUEUE TESTS          --------------------

void queueEnqueueAndDequeueTest()
{
	Queue<int> *queue = new Queue<int>();
	queue->enqueue(1);
	queue->enqueue(2);
	queue->enqueue(3);
	queue->enqueue(4);
	queue->enqueue(5);
	
	JTest<int>::testEquality("Enqueue and dequeue, first element dequeued", 1, queue->dequeue());
	JTest<int>::testEquality("Enqueue and dequeue, second element dequeued", 2, queue->dequeue());
	JTest<int>::testEquality("Enqueue and dequeue, third element dequeued", 3, queue->dequeue());
	JTest<int>::testEquality("Enqueue and dequeue, fourth element dequeued", 4, queue->dequeue());
	JTest<int>::testEquality("Enqueue and dequeue, fifth element dequeued", 5, queue->dequeue());

	delete queue;
}

void queueFrontTest()
{
	Queue<int> *queue = new Queue<int>();
	queue->enqueue(1);

	JTest<int>::testEquality("Front test, front element returned", 1, queue->front());
	JTest<int>::testEquality("Front test, front element still in queue", 1, queue->dequeue());

	delete queue;
}

void queueBoundedTest()
{
	unsigned int i;
	Queue<int> *queue = new Queue<int>(5);
	
	queue->enqueue(1);
	queue->enqueue(2);
	queue->enqueue(3);
	queue->enqueue(4);
	queue->enqueue(5);
	queue->enqueue(6);
	
	for(i = 0; i < 5; i++)
	{
		queue->dequeue();
	}
	JTest<int>::testInequality("Bounded queue test, element not added when capacity reached.", 6, queue->dequeue());

	delete queue;
}

// ----------------    END QUEUE TESTS          --------------------

// --------------------    TRIE TESTS          --------------------

void trieAddGetTest()
{
	std::cout << "Trie test" << std::endl;

	Trie<int>* trie = new Trie<int>();

	trie->add("cat", 5);
	trie->add("can", 10);
	trie->add("banana", 15);
	trie->add("ball", 20);

	JTest<int>::testEquality("Add and get test, first element added and retrieved", 5, *trie->get("cat"));
	JTest<int>::testEquality("Add and get test, second element added and retrieved", 10, *trie->get("can"));
	JTest<int>::testEquality("Add and get test, third element added and retrieved", 15, *trie->get("banana"));
	JTest<int>::testEquality("Add and get test, fourth element added and retrieved", 20, *trie->get("ball"));

	delete trie;
}

// -----------------   END TRIE TESTS          --------------------

// -----------------   JSON WRAPPER TESTS      --------------------

void jsonPrimitiveTest()
{
	JSONPrimitive<int>* primitiveInt = new JSONPrimitive<int>(5);

	JTest<int>::testEquality("JSONPrimitive test, succesfully created JSONPrimitive and retrieved value.", 5, primitiveInt->getPrimitive());
	
	delete primitiveInt;
}

void jsonArrayTest()
{
	DynamicArray<JSONItem*>* array = new DynamicArray<JSONItem*>();
	array->pushBack(new JSONPrimitive<int>(1));
	array->pushBack(new JSONPrimitive<int>(2));
	array->pushBack(new JSONPrimitive<int>(3));
	array->pushBack(new JSONPrimitive<int>(4));
	array->pushBack(new JSONPrimitive<int>(5));

	JSONArray* jsonArray = new JSONArray(array);

	JTest<DynamicArray<JSONItem*>*>::testEquality("JSONArray test, succesfully created JSONArray and retrieved DynamicArray.", array, jsonArray->getDynamicArray());

	delete array;
}

void jsonObjectTest()
{
	Trie<JSONItem*>* trie = new Trie<JSONItem*>();
	
	DynamicArray<JSONItem*>* favoriteColors = new DynamicArray<JSONItem*>();
	favoriteColors->pushBack(new JSONPrimitive<std::string>("red"));
	favoriteColors->pushBack(new JSONPrimitive<std::string>("two"));
	favoriteColors->pushBack(new JSONPrimitive<std::string>("three"));
	favoriteColors->pushBack(new JSONPrimitive<std::string>("four"));
	favoriteColors->pushBack(new JSONPrimitive<std::string>("five"));

	trie->add("one", new JSONPrimitive<int>(1));
	trie->add("two", new JSONPrimitive<int>(1));
	trie->add("three", new JSONPrimitive<int>(1));
	trie->add("four", new JSONPrimitive<int>(1));
	trie->add("five", new JSONPrimitive<int>(1));
	
	JSONObject* jsonObject = new JSONObject(trie);
	
	JTest<Trie<JSONItem*>*>::testEquality("JSONObject test, succesfully created JSONObject and retrieved Trie.", trie, jsonObject->getTrie());

	delete jsonObject;
}

// ------------------ END JSON WRAPPER TESTS --------------------

// ------------------ JSON PARSER TESTS -------------------------

void readJSONArray()
{
	unsigned int i;
	int j;
	
	DynamicArray<JSONItem*>* topLevelArray = JSONParser::parseFile("arraytest.json");
	DynamicArray<JSONItem*>* jsonArray = ((JSONArray*)(*topLevelArray->get(0)))->getDynamicArray();

	for(i = 0, j = 0; i < jsonArray->length(); i++, j++)
	{
		JTest<int>::testEquality("Item correctly stored in JSON Array.", j, ((JSONPrimitive<int>*)(*jsonArray->get(i)))->getPrimitive());
	}
	
	delete topLevelArray;
	delete jsonArray;
}

void readJSONNumbers()
{
	DynamicArray<JSONItem*>* topLevelArray = JSONParser::parseFile("numbertest.json");
	DynamicArray<JSONItem*>* jsonArray = ((JSONArray*)(*topLevelArray->get(0)))->getDynamicArray();
	
	JTest<int>::testEquality("Single digit int correctly stored.", 1, ((JSONPrimitive<int>*)(*jsonArray->get(0)))->getPrimitive());
	JTest<int>::testEquality("Multi-digit int correctly stored.", 15, ((JSONPrimitive<int>*)(*jsonArray->get(1)))->getPrimitive());
	JTest<int>::testEquality("Negative int correctly stored.", -7, ((JSONPrimitive<int>*)(*jsonArray->get(2)))->getPrimitive());
	JTest<double>::testEquality("Double correctly stored.", 1.5, ((JSONPrimitive<double>*)(*jsonArray->get(3)))->getPrimitive());
	JTest<double>::testEquality("Negative double correctly stored.", -1.5, ((JSONPrimitive<double>*)(*jsonArray->get(4)))->getPrimitive());
	JTest<double>::testEquality("Double in scientific notation correctly stored.", 150.0, ((JSONPrimitive<double>*)(*jsonArray->get(5)))->getPrimitive());
	JTest<double>::testEquality("Double in scientific notation with positive sign explicitly specified correctly stored.", 150, ((JSONPrimitive<double>*)(*jsonArray->get(6)))->getPrimitive());
	JTest<double>::testEquality("Double in scientific notation with negative sign specified correctly stored.", 0.015, ((JSONPrimitive<double>*)(*jsonArray->get(7)))->getPrimitive());

	delete topLevelArray;
	delete jsonArray;
}

void readJSONBools()
{
	DynamicArray<JSONItem*>* topLevelArray = JSONParser::parseFile("booltest.json");
	DynamicArray<JSONItem*>* jsonArray = ((JSONArray*)(*topLevelArray->get(0)))->getDynamicArray();
	
	JTest<bool>::testEquality("True boolean correctly stored.", true, ((JSONPrimitive<bool>*)(*jsonArray->get(0)))->getPrimitive());
	JTest<bool>::testEquality("False boolean correctly stored.", false, ((JSONPrimitive<bool>*)(*jsonArray->get(1)))->getPrimitive());

	delete topLevelArray;
	delete jsonArray;
}

void readJSONStrings()
{
	DynamicArray<JSONItem*>* topLevelArray = JSONParser::parseFile("stringtest.json");
	DynamicArray<JSONItem*>* jsonArray = ((JSONArray*)(*topLevelArray->get(0)))->getDynamicArray();

	JTest<std::string>::testEqualityStr("String correctly stored.", "abc", ((JSONPrimitive<std::string>*)(*jsonArray->get(0)))->getPrimitive());	
	JTest<std::string>::testEqualityStr("String with quotes correctly stored.", "string with \"quotes\"", ((JSONPrimitive<std::string>*)(*jsonArray->get(1)))->getPrimitive());	
	JTest<std::string>::testEqualityStr("Empty string correctly stored.", "", ((JSONPrimitive<std::string>*)(*jsonArray->get(2)))->getPrimitive());	
	JTest<std::string>::testEqualityStr("String with backslashes correctly stored.", "string with \\slashes\\", ((JSONPrimitive<std::string>*)(*jsonArray->get(3)))->getPrimitive());	

	delete topLevelArray;
	delete jsonArray;
}

void readJSONNull()
{
	DynamicArray<JSONItem*>* topLevelArray = JSONParser::parseFile("nulltest.json");
	DynamicArray<JSONItem*>* jsonArray = ((JSONArray*)(*topLevelArray->get(0)))->getDynamicArray();
	
	JTest<JSONItem*>::testEquality("Null correctly stored.", NULL, *jsonArray->get(0));
	
	delete topLevelArray;
	delete jsonArray;
}

void readJSONObject()
{
	DynamicArray<JSONItem*>* topLevelArray = JSONParser::parseFile("objecttest.json");
	Trie<JSONItem*>* jsonObject = ((JSONObject*)(*topLevelArray->get(0)))->getTrie();
	
	JTest<std::string>::testEqualityStr("String item in object correctly stored.", "jason", ((JSONPrimitive<std::string>*)(*jsonObject->get("name")))->getPrimitive());	
	JTest<int>::testEquality("Number item in object correctly stored.", 19, ((JSONPrimitive<int>*)(*jsonObject->get("age")))->getPrimitive());	
	JTest<bool>::testEquality("Boolean item in object correctly stored.", true, ((JSONPrimitive<bool>*)(*jsonObject->get("issoftwareengineer")))->getPrimitive());
	
	DynamicArray<JSONItem*>* nestedArray = ((JSONArray*)*jsonObject->get("hobbies"))->getDynamicArray();	
	JTest<std::string>::testEqualityStr("First item of array item in object correctly stored.", "guitar", ((JSONPrimitive<std::string>*)(*nestedArray->get(0)))->getPrimitive());	
	JTest<std::string>::testEqualityStr("Second item of array item in object correctly stored.", "piano", ((JSONPrimitive<std::string>*)(*nestedArray->get(1)))->getPrimitive());	
	JTest<std::string>::testEqualityStr("Third item of array item in object correctly stored.", "gaming", ((JSONPrimitive<std::string>*)(*nestedArray->get(2)))->getPrimitive());	

	delete topLevelArray;
	delete jsonObject;
	delete nestedArray;

}

// --------------- END JSON PARSER TESTS -------------------------

void dynamicArrayTests()
{
	std::cout << "Dynamic Array Tests" << std::endl;
	dynamicArraySimpleArithmeticTest();
	dynamicArrayAssignmentTest();
	dynamicArrayDefaultConstructorTest();
	dynamicArrayPreAllocatedConstructorTest();
	dynamicArrayMemoryReallocationTest();
	dynamicArrayReserveTest();
	dynamicArraySeveralReallocationTest();
	dynamicArraySwapTest();
	dynamicArraySetTest();
	dynamicArrayInsertTest();
	dynamicArrayGetTest();
	dynamicArrayRemoveTest();
	dynamicArrayPushFrontTest();
	dynamicArrayPushBackTest();
	dynamicArrayRecenterTest();
}

void stackTests()
{
	std::cout << "Stack Tests" << std::endl;
	stackPushAndPopTest();
	stackPeekTest();
	stackBoundedTest();
}

void queueTests()
{
	std::cout << "Queue Tests" << std::endl;
	queueEnqueueAndDequeueTest();
	queueFrontTest();
	queueBoundedTest();
}

void JSONWrapperTests()
{
	std::cout << "JSON Wrapper Tests" << std::endl;
	jsonPrimitiveTest();
	jsonArrayTest();
	jsonObjectTest();
}

void JSONParserTests()
{
	std::cout << "JSON Parser Tests" << std::endl;
	readJSONArray();
	readJSONNumbers();
	readJSONBools();
	readJSONStrings();
	readJSONNull();
	readJSONObject();
}

void initializeDebug()
{	
	#ifndef DEBUG
	Debug::getInstance()->setDebugStatus(false);
	#else
	Debug::getInstance()->setDebugStatus(true);
	Debug::getInstance()->setTerminalLogging(true);
	Debug::getInstance()->addChannel("DYNAMICARRAY");
	Debug::getInstance()->addChannel("STACK");
	Debug::getInstance()->addChannel("QUEUE");
	Debug::getInstance()->addChannel("TRIE");
	Debug::getInstance()->addChannel("JSON");
	Debug::getInstance()->muteAllExcept("JSON");
	Debug::getInstance()->setChannelMute("ERROR", false);
	#endif
}

int main()
{
	initializeDebug();
	dynamicArrayTests();	
	stackTests();	
	queueTests();
	trieAddGetTest();
	JSONWrapperTests();
	JSONParserTests();
	return 0;
}
