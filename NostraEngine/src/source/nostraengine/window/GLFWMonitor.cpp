#define GLAD_GLAPI_EXPORT //needed for exporting glad

#include "nostraengine/window/GLFWMonitor.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace NOE::NOE_WINDOW
{
	NOU::NOU_CORE::Logger* monitorLog = NOU::NOU_CORE::Logger::instance();

	NOE::NOE_WINDOW::GLFWMonitor::GLFWMonitor(const void* handle) :
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

		NOU_WRITE_LOG(monitorLog, NOU::NOU_CORE::EventLevelCodes::DEBUG,
			"Monitor object created!", "DebugLog.txt");
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

	const NOU::NOU_DAT_ALG::String8& NOE::NOE_WINDOW::GLFWMonitor::getName() const
	{
		return m_name;
	}

	const void* NOE::NOE_WINDOW::GLFWMonitor::getUnderlying() const
	{
		return m_handle;
	}
}