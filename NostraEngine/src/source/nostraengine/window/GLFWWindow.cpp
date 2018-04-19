#include "nostraengine/window/GLFWWindow.hpp"

namespace NOE::NOE_WINDOW
{

	void NOE::NOE_WINDOW::GLFWWindow::createWindow(NOU::sizeType m_sizeWidth, NOU::sizeType m_sizeHeight, 
		NOU::NOU_DAT_ALG::String8 m_title, GLFWmonitor* monitor, GLFWwindow* share)
	{
		m_window = glfwCreateWindow(m_sizeWidth, m_sizeHeight, m_title.rawStr(), monitor, share);
	}

	void NOE::NOE_WINDOW::GLFWWindow::setTitle()
	{
	}

	void NOE::NOE_WINDOW::GLFWWindow::setSize(NOU::sizeType width, NOU::sizeType height)
	{
	}

	void NOE::NOE_WINDOW::GLFWWindow::setPosition(NOU::sizeType width, NOU::sizeType height)
	{
	}

	void NOE::NOE_WINDOW::GLFWWindow::close()
	{
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

	NOU::NOU_DAT_ALG::String8 NOE::NOE_WINDOW::GLFWWindow::getName()
	{
		return NOU::NOU_DAT_ALG::String8();
	}

	void * NOE::NOE_WINDOW::GLFWWindow::getUnderlying()
	{
		return nullptr;
	}
}
