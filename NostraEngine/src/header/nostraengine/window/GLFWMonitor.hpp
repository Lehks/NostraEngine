#ifndef NOE_WINDOW_GLFW_MONITOR_HPP
#define NOE_WINDOW_GLFW_MONITOR_HPP
#define GLAD_GLAPI_EXPORT //needed for exporting glad

#include "GLAD/glad.h"
#include "GLFW/glfw3.h"

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
	/**
	\brief				A class that implements the provided functions of the Monitor class. The
						behavior of all functions is defined in the Monitor class.
	*/
	class NOU_CLASS GLFWMonitor : public Monitor
	{
	private:

		/**
		\brief			A vector of all connected monitors.
		*/
		static NOU::NOU_DAT_ALG::Vector<Monitor*> s_monitors;
	public:

		virtual void getMonitorResolution(Monitor* monitor, NOU::sizeType* width,
			NOU::sizeType* height) override;
		virtual Monitor* getPrimaryMonitor() override;
		virtual NOU::NOU_DAT_ALG::Vector<Monitor*> getConnectedMonitors() override;
	};
}

#endif