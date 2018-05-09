#include "nostraengine/window/GLFWMonitor.hpp"

namespace NOE::NOE_WINDOW
{
	NOE::NOE_WINDOW::GLFWMonitor::GLFWMonitor(GLFWmonitor* handle) :
		m_handle(handle)
	{
		//Initialize m_width and m_height
		const GLFWvidmode * mode = glfwGetVideoMode(m_handle);

		m_width = mode->width;
		m_height = mode->height;

		//Initialize m_refreshRate
		m_refreshRate = mode->refreshRate;

		//Initialize m_redBits, m_greenBits and m_blueBits
		m_redBits = mode->redBits;
		m_greenBits = mode->greenBits;
		m_blueBits = mode->blueBits;
	}

	NOU::sizeType NOE::NOE_WINDOW::GLFWMonitor::getWidth() const
	{
		return m_width;
	}

	NOU::sizeType NOE::NOE_WINDOW::GLFWMonitor::getHeight() const
	{
		return m_height;
	}

	NOU::sizeType NOE::NOE_WINDOW::GLFWMonitor::getRefreshRate() const
	{
		return m_refreshRate;
	}

	NOU::sizeType NOE::NOE_WINDOW::GLFWMonitor::getRedBits() const
	{
		return m_redBits;
	}

	NOU::sizeType NOE::NOE_WINDOW::GLFWMonitor::getGreenBits() const
	{
		return m_greenBits;
	}

	NOU::sizeType NOE::NOE_WINDOW::GLFWMonitor::getBlueBits() const
	{
		return m_blueBits;
	}

	NOU::NOU_DAT_ALG::String8 NOE::NOE_WINDOW::GLFWMonitor::getName() const
	{
		return glfwGetMonitorName(m_handle);
	}

	void* NOE::NOE_WINDOW::GLFWMonitor::getUnderlying()
	{
		return m_handle;
	}

	const void* NOE::NOE_WINDOW::GLFWMonitor::getUnderlying() const
	{
		return m_handle;
	}
}