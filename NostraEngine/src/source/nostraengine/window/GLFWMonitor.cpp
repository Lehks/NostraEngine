#include "nostraengine/window/GLFWMonitor.hpp"

namespace NOE::NOE_WINDOW
{
	NOU::NOU_DAT_ALG::Vector<GLFWmonitor*> GLFWMonitor::s_monitors;
	NOE::NOE_WINDOW::Monitor* NOE::NOE_WINDOW::GLFWMonitor::getPrimaryMonitor()
	{
		s_monitors.at(0) = glfwGetPrimaryMonitor();
		return reinterpret_cast<Monitor*>(s_monitors.at(0));
	}
	NOU::NOU_DAT_ALG::Vector<NOE::NOE_WINDOW::Monitor*> NOE::NOE_WINDOW::GLFWMonitor::getConnectedMonitors()
	{
		int size;
		GLFWmonitor** glfwMonitors = glfwGetMonitors(&size);

		for (int i = 0; i < size ; i++)
		{
			s_monitors.pushBack(glfwMonitors[i]);
		}
	}
}