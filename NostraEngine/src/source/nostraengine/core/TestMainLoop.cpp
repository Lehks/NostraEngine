#include "nostraengine\core\TestMainLoop.hpp"

#include "GLFW/glfw3.h"

namespace NOE
{
	__declspec(dllexport) void start()
	{
		glfwInit();

		GLFWwindow *window = glfwCreateWindow(800, 600, "", nullptr, nullptr);

		while (!glfwWindowShouldClose(window))
		{
			glfwPollEvents();
		}

		glfwTerminate();
	}
}