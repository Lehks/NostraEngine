
#include "nostraengine/core/StdIncludes.hpp"

#include <iostream>

__declspec(dllexport) int test()
{
	std::cout << "Hello" << std::endl;

	return 0;
}