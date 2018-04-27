#include "nostraengine/window/GLFWWindow.hpp"

namespace NOE::NOE_WINDOW
{
	NOE::NOE_WINDOW::GLFWWindow::GLFWWindow()
	{
		if (!glfwInit())
		{
			//NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::UNKNOWN, "Could not initialize GLFW!");
		}
	}

	void NOE::NOE_WINDOW::GLFWWindow::createWindow(NOU::sizeType sizeWidth, NOU::sizeType sizeHeight,
		NOU::NOU_DAT_ALG::String8 title, void* monitor = nullptr,
		void* share = nullptr)
	{
	}

	void NOE::NOE_WINDOW::GLFWWindow::setTitle(NOU::NOU_DAT_ALG::String8 title)
	{
	}

	void NOE::NOE_WINDOW::GLFWWindow::setSize(NOU::sizeType width, NOU::sizeType height)
	{
	}

	void NOE::NOE_WINDOW::GLFWWindow::setPosition(NOU::sizeType width, NOU::sizeType height)
	{
	}

	void NOE::NOE_WINDOW::GLFWWindow::closeWindow()
	{
		glfwDestroyWindow(m_window);
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

	void* NOE::NOE_WINDOW::GLFWWindow::getUnderlying()
	{
		return m_window;
	}
}
