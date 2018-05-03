#include "nostraengine/window/GLFWMonitor.hpp"

namespace NOE::NOE_WINDOW
{
	NOE::NOE_WINDOW::GLFWMonitor::GLFWMonitor()
	{

	}

	void NOE::NOE_WINDOW::GLFWMonitor::getMonitorResolution(Monitor* monitor, NOU::sizeType* width,
		NOU::sizeType* height)
	{
		const GLFWvidmode * mode = glfwGetVideoMode(reinterpret_cast<GLFWmonitor*>(monitor));

		*width = mode->width;
		*height = mode->height;

	}

	NOU::NOU_DAT_ALG::String8 NOE::NOE_WINDOW::GLFWMonitor::getMonitorName(Monitor* monitor)
	{
		return glfwGetMonitorName(reinterpret_cast<GLFWmonitor*>(monitor));
	}

	void* NOE::NOE_WINDOW::GLFWMonitor::getUnderlying()
	{
		return m_handle;
	}
}