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
		\brief			Default constructor.
		*/
		virtual ~Monitor() = default;

		/**
		\return			The width of the monitor resolution.

		\brief			Returns the width of the monitor resolution.
		*/
		virtual NOU::sizeType getWidth() const = 0;
		
		/**
		\return			The height of the monitor resolution.

		\brief			Returns the height of the monitor resolution.
		*/
		virtual NOU::sizeType getHeight() const = 0;

		/**
		\return			The refresh rate

		\brief			Returns the refresh rate of the monitor.
		*/
		virtual NOU::sizeType getRefreshRate() const = 0;

		/**
		\return			The red bits

		\brief			Returns the red bits of the monitor.
		*/
		virtual NOU::sizeType getRedBits() const = 0;

		/**
		\return			The green bits

		\brief			Returns the green bits of the monitor.
		*/
		virtual NOU::sizeType getGreenBits() const = 0;

		/**
		\return			The blue bits

		\brief			Returns the blue bits of the monitor.
		*/
		virtual NOU::sizeType getBlueBits() const = 0;

		/**
		\return			The name of the monitor

		\brief			Returns the name of the monitor.
		*/
		virtual const NOU::NOU_DAT_ALG::String8& getName() const = 0;

		/**
		\return void*	Returns a const void pointer to the window handle.

		\brief			Returns the monitor handle.
		*/
		virtual const void* getUnderlying() const = 0;
	};
}
#endif