#include "GLFWMonitor.hpp"

#include "GLFW/glfw3.h"

namespace GLFWWindowPlugin
{
	GLFWMonitor::GLFWMonitor(const void* handle) :
		m_handle(handle),
		m_name(glfwGetMonitorName(reinterpret_cast<GLFWmonitor*>(const_cast<void*>(handle))))
	{
		//Initialize m_width and m_height
		const GLFWvidmode* mode = glfwGetVideoMode(reinterpret_cast<GLFWmonitor*>
			(const_cast<void*>(handle)));

		m_width = mode->width;
		m_height = mode->height;

		//Initialize m_refreshRate
		m_refreshRate = mode->refreshRate;

		//Initialize m_redBits, m_greenBits and m_blueBits
		m_redBits = mode->redBits;
		m_greenBits = mode->greenBits;
		m_blueBits = mode->blueBits;

		NOU_LOG_DEBUG("Monitor object created!");
	}

	NOU::sizeType GLFWMonitor::getWidth() const
	{
		return m_width;
	}

	NOU::sizeType GLFWMonitor::getHeight() const
	{
		return m_height;
	}

	NOU::sizeType GLFWMonitor::getRefreshRate() const
	{
		return m_refreshRate;
	}

	NOU::sizeType GLFWMonitor::getRedBits() const
	{
		return m_redBits;
	}

	NOU::sizeType GLFWMonitor::getGreenBits() const
	{
		return m_greenBits;
	}

	NOU::sizeType GLFWMonitor::getBlueBits() const
	{
		return m_blueBits;
	}

	const NOU::NOU_DAT_ALG::String8& GLFWMonitor::getName() const
	{
		return m_name;
	}

	const void* GLFWMonitor::getUnderlying() const
	{
		return m_handle;
	}
}