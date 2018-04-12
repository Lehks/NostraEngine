
#include "GLFW/glfw3.h"

#include <iostream>

int main()
{
	glfwInit();

	GLFWwindow *win = glfwCreateWindow(600, 800, "w", nullptr, nullptr);

	while (!glfwWindowShouldClose(win))
	{
		glfwPollEvents();
	}

	glfwDestroyWindow(win);

	glfwTerminate();

	std::cin.get();
}