#include "nostraengine/window/GLFWMonitor.hpp"

namespace NOE::NOE_WINDOW
{
	NOU::NOU_DAT_ALG::Vector<Monitor*> GLFWMonitor::s_monitors;

	void NOE::NOE_WINDOW::GLFWMonitor::getMonitorResolution(Monitor* monitor, NOU::sizeType* width,
		NOU::sizeType* height)
	{
		const GLFWvidmode * mode = glfwGetVideoMode(reinterpret_cast<GLFWmonitor*>(monitor));

		*width = mode->width;
		*height = mode->height;

	}
	NOE::NOE_WINDOW::Monitor* NOE::NOE_WINDOW::GLFWMonitor::getPrimaryMonitor()
	{
		s_monitors.at(0) = reinterpret_cast<Monitor*>(glfwGetPrimaryMonitor());
		return s_monitors.peekFront();
	}
	NOU::NOU_DAT_ALG::Vector<NOE::NOE_WINDOW::Monitor*> NOE::NOE_WINDOW::GLFWMonitor::getConnectedMonitors()
	{
		int size;
		GLFWmonitor** glfwMonitors = glfwGetMonitors(&size);

		for (int i = 0; i < size ; i++)
		{
			s_monitors.pushBack(reinterpret_cast<Monitor*>(glfwMonitors[i]));
		}

		return s_monitors;
	}
}