#include "nostraengine/window/GLFWWindow.hpp"

namespace NOE::NOE_WINDOW
{

	//NOE::NOE_WINDOW::GLFWWindow::GLFWWindow(NOU::sizeType sizeWidth, NOU::sizeType sizeHeight, 
	//	NOU::NOU_DAT_ALG::String8 title, GLFWmonitor* monitor, GLFWwindow* share)
	//{
	//	if (!glfwInit())
	//	{
	//		exit(EXIT_FAILURE);
	//	}
	//	glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	//	glfwWindowHint(GLFW_VERSION_MINOR, 0);
	//	m_window = glfwCreateWindow(sizeWidth, sizeHeight, title.rawStr(), monitor, share);
	//	if (!m_window)
	//	{
	//		glfwTerminate();
	//		exit(EXIT_FAILURE);
	//	}
	//	glfwMakeContextCurrent(m_window);
	//	glfwSwapInterval(1);
	//
	//	while (!glfwWindowShouldClose(m_window))
	//	{
	//		NOU::float32 ratio;
	//		NOU::int32 width, height;
	//		glfwGetFramebufferSize(m_window, &width, &height);
	//		ratio = width / (float)height;
	//		glViewport(0, 0, width, height);
	//		glClear(GL_COLOR_BUFFER_BIT);
	//
	//		glfwSwapBuffers(m_window);
	//		glfwPollEvents();
	//	}
	//
	//	glfwDestroyWindow(m_window);
	//	glfwTerminate();
	//	exit(EXIT_SUCCESS);
	//}

	void NOE::NOE_WINDOW::GLFWWindow::setTitle(NOU::NOU_DAT_ALG::String8 title)
	{
	}

	void NOE::NOE_WINDOW::GLFWWindow::setSize(NOU::sizeType width, NOU::sizeType height)
	{
	}

	void NOE::NOE_WINDOW::GLFWWindow::setPosition(NOU::sizeType width, NOU::sizeType height)
	{
	}

	void NOE::NOE_WINDOW::GLFWWindow::close(GLFWwindow* window)
	{
		glfwDestroyWindow(window);
	}

	void NOE::NOE_WINDOW::GLFWWindow::minimize()
	{
	}

	void NOE::NOE_WINDOW::GLFWWindow::maximize()
	{
	}

	void NOE::NOE_WINDOW::GLFWWindow::makeWindowed()
	{
	}

	void NOE::NOE_WINDOW::GLFWWindow::decorated(NOU::boolean state)
	{
	}

	void NOE::NOE_WINDOW::GLFWWindow::setFullscreen(NOU::boolean state)
	{
	}

	void NOE::NOE_WINDOW::GLFWWindow::update()
	{
	}

	NOE::NOE_WINDOW::Device NOE::NOE_WINDOW::GLFWWindow::getDevices()
	{
		return NOE_WINDOW::Device();
	}

	NOU::NOU_DAT_ALG::String8 NOE::NOE_WINDOW::GLFWWindow::getTitle()
	{
		return NOU::NOU_DAT_ALG::String8();
	}

	void * NOE::NOE_WINDOW::GLFWWindow::getUnderlying()
	{
		return nullptr;
	}
}
