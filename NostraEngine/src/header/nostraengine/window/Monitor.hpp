#ifndef NOE_WINDOW_MONITOR_HPP
#define NOE_WINDOW_MONITOR_HPP

#include "nostrautils/NostraUtils.hpp"

#include "nostraengine/core/StdIncludes.hpp"

/**
\file window/Monitor.hpp

\author  Lukas Gross
\version 0.0.1
\since   0.0.1

\brief A file that provides the functionality for accessing all connected monitors.
*/
namespace NOE::NOE_WINDOW
{
	class NOU_CLASS Monitor
	{
	public:

		virtual Monitor* getPrimaryMonitor() = 0;
		virtual NOU::NOU_DAT_ALG::Vector<Monitor*> getConnectedMonitors() = 0;
	};
}

#endif