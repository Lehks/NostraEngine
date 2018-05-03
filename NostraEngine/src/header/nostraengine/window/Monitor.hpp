#ifndef NOE_WINDOW_MONITOR_HPP
#define NOE_WINDOW_MONITOR_HPP

#include "nostrautils/NostraUtils.hpp"

#include "nostraengine/core/StdIncludes.hpp"

/**
\file window/Monitor.hpp

\author  Lukas Gross
\version 0.0.2
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
		\param monitor	The monitor you want the name of.	

		\return			The name of the monitor

		\brief			Returns the name of the monitor.
		*/
		virtual NOU::NOU_DAT_ALG::String8 getMonitorName(Monitor* monitor) = 0;

		/**
		\param monitor	A pointer to a monitor object.
		\param width	A pointer to a NOU::sizeType. The width will be saved in this pointer.
		\param height	A pointer to a NOU::sizeType. The height will be saved in this pointer.

		\brief			Returns the resolution of the passed monitor in the passed pointers.
		*/
		virtual void getMonitorResolution(Monitor* monitor, NOU::sizeType* width, NOU::sizeType* height) = 0;

		/**
		\return void*	Returns a void pointer to the window handle.

		\brief			Returns the monitor handle.
		*/
		virtual void* getUnderlying() = 0;
	};
}

#endif