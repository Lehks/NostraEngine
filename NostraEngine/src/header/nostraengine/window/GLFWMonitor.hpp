#ifndef NOE_WINDOW_GLFW_MONITOR_HPP
#define NOE_WINDOW_GLFW_MONITOR_HPP

#include "nostrautils/NostraUtils.hpp"

#include "nostraengine/core/StdIncludes.hpp"

#include "nostraengine/window/Monitor.hpp"

/**
\file window/GLFWMonitor.hpp

\author  Lukas Gross
\version 0.0.1
\since   0.0.1

\brief A file that provides the functionality for accessing all connected monitors.
*/
namespace NOE::NOE_WINDOW
{
	class NOU_CLASS GLFWMonitor : public Monitor
	{
	public:
		virtual Monitor* getPrimaryMonitor() override;
		virtual NOU::NOU_DAT_ALG::Vector<Monitor*> getConnectedMonitors() override;
	};
}

#endif