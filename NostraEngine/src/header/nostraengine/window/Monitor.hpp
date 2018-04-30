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
	/**
	\brief A abstract class that defines the functionality for accessing monitors.
	*/
	class NOU_CLASS Monitor
	{
	public:

		/**
		\return			A pointer to the primary monitor.

		\brief			Returns the primary monitor.
		*/
		virtual Monitor* getPrimaryMonitor() = 0;

		/**
		\return			A vector of Monitor*

		\brief			Returns an array of all connected monitors. The first element is the primary monitor.
		*/
		virtual NOU::NOU_DAT_ALG::Vector<Monitor*> getConnectedMonitors() = 0;
	};
}

#endif