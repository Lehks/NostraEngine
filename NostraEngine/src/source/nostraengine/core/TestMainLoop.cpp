#include "nostraengine\core\TestMainLoop.hpp"

namespace NOE
{
	__declspec(dllexport) void start()
	{
		glfwInit();

		glfwTerminate();
	}
}