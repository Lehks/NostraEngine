#include "nostraengine/core/TestMainLoop.hpp"
#include "nostrautils/NostraUtils.hpp"

#include "GLFW/glfw3.h"

namespace NOE
{
	__declspec(dllexport) void start()
	{
		NOU::int32 i = NOU::NOU_CORE::max(1, 2);

		glfwInit();

		GLFWwindow *window = glfwCreateWindow(800, 600, "", nullptr, nullptr);

		while (!glfwWindowShouldClose(window))
		{
			glfwPollEvents();
		}

		glfwTerminate();
	}
}