#include <iostream>
#include "check.hpp"
#include <vector>
#include "Vector.hpp"
#include <stack>
#include "Stack.hpp"
#include <map>
#include "Map.hpp"

#include "test_vector.hpp"
#include "test_stack.hpp"
#include "test_map.hpp"

int main(int argc, char **argv)
{
	TestVector _TestVector;
	TestStack _TestStack;
	TestMap _TestMap;

	if (argc > 1)
	{
		for (int x = 1; x < argc; x++)
		{
			std::string str = std::string(argv[x]);
			if (str == "vector")
				_TestVector.StartTest();
			else if (str == "stack")
				_TestStack.StartTest();
			else if (str == "map")
				_TestMap.StartTest();
		}
	}
	else
	{
		_TestVector.StartTest();
		_TestStack.StartTest();
		_TestMap.StartTest();
	}
	return 0;
}
