#ifndef PLUGIN_GLFW_MONITOR_HPP
#define PLUGIN_GLFW_MONITOR_HPP

#include "nostraengine/NostraEngine.hpp"

/**
\file window/GLFWMonitor.hpp

\author  Lukas Gross
\version 0.0.1
\since   0.0.1

\brief A file that provides the functionality for accessing all connected monitors.
*/
namespace GLFWWindowPlugin
{
	/**
	\brief				A class that implements the provided functions of the Monitor class. The
						behavior of all functions is defined in the Monitor class.
	*/
	class GLFWMonitor : public NOE::NOE_WINDOW::Monitor
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

		NOE_PLUGIN_FUNC GLFWMonitor(const void *handle);
		NOE_PLUGIN_FUNC virtual ~GLFWMonitor() = default;
		NOE_PLUGIN_FUNC virtual NOU::sizeType getWidth() const override;
		NOE_PLUGIN_FUNC virtual NOU::sizeType getHeight() const override;
		NOE_PLUGIN_FUNC virtual NOU::sizeType getRefreshRate() const override;
		NOE_PLUGIN_FUNC virtual NOU::sizeType getRedBits() const override;
		NOE_PLUGIN_FUNC virtual NOU::sizeType getGreenBits() const override;
		NOE_PLUGIN_FUNC virtual NOU::sizeType getBlueBits() const override;
		NOE_PLUGIN_FUNC virtual const NOU::NOU_DAT_ALG::String8& getName() const override;
		NOE_PLUGIN_FUNC virtual const void* getUnderlying() const override;
	};
}
#endif