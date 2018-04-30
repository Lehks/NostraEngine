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
		\param monitor	A pointer to a monitor object.
		\param width	A pointer to a NOU::sizeType. The width will be saved in this pointer.
		\param height	A pointer to a NOU::sizeType. The height will be saved in this pointer.

		\brief			Returns the resolution of the passed monitor in the passed pointers.
		*/
		virtual void getMonitorResolution(Monitor* monitor, NOU::sizeType* width, NOU::sizeType* height) = 0;

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