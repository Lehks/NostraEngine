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
	/**
	\brief				A class that implements the provided functions of the Monitor class. The
						behavior of all functions is defined in the Monitor class.
	*/
	class NOU_CLASS GLFWMonitor : public Monitor
	{
	private:

		/**
		\brief			The handle of the monitor.
		*/
		const void* m_handle;

		/**
		\brief			The width of the monitor resolution.
		*/
		NOU::sizeType m_width;

		/**
		\brief			The height of the monitor resolution.
		*/
		NOU::sizeType m_height;

		/**
		\brief			The refresh rate of the monitor.
		*/
		NOU::sizeType m_refreshRate;

		/**
		\brief			The red bits of the monitor.
		*/
		NOU::sizeType m_redBits;

		/**
		\brief			The green bits of the monitor.
		*/
		NOU::sizeType m_greenBits;

		/**
		\brief			The blue bits of the monitor.
		*/
		NOU::sizeType m_blueBits;

		/**
		\brief			The name of the monitor.
		*/
		NOU::NOU_DAT_ALG::String8 m_name;

	public:

		GLFWMonitor(const void *handle);
		virtual ~GLFWMonitor() = default;
		virtual NOU::sizeType getWidth() const override;
		virtual NOU::sizeType getHeight() const override;
		virtual NOU::sizeType getRefreshRate() const override;
		virtual NOU::sizeType getRedBits() const override;
		virtual NOU::sizeType getGreenBits() const override;
		virtual NOU::sizeType getBlueBits() const override;
		virtual const NOU::NOU_DAT_ALG::String8& getName() const override;
		virtual const void* getUnderlying() const override;
	};
}
#endif