#ifndef NOE_WINDOW_WINDOW_HPP
#define NOE_WINDOW_WINDOW_HPP

#include "nostrautils/NostraUtils.hpp"

#include "nostraengine/core/StdIncludes.hpp"

#include "nostraengine/window/Device.hpp"

/**
\file window/Window.hpp

\author  Lukas Gross
\version 0.0.1
\since   0.0.1

\brief A file that provides the functionality for creating and operating a window.
*/
namespace NOE::NOE_WINDOW
{
	/**
	\brief A pure virtual class that provides a template for the implementation of a window.
	*/
	class NOU_CLASS Window
	{
	public:
		
		//Window() = default;
		virtual ~Window() = default;
		Window() = default;
		virtual void setTitle(NOU::NOU_DAT_ALG::String8 title) = 0;
		virtual void setSize(NOU::sizeType width, NOU::sizeType height) = 0;
		virtual void setPosition(NOU::sizeType width, NOU::sizeType height) = 0;
		virtual void close(GLFWwindow* window) = 0;
		virtual void minimize() = 0;
		virtual void maximize() = 0;
		virtual void makeWindowed() = 0;
		virtual void decorated(NOU::boolean state) = 0;
		virtual void setFullscreen(NOU::boolean state) = 0;
		virtual void update() = 0;
		virtual NOE::NOE_WINDOW::Device getDevices() = 0;
		virtual NOU::NOU_DAT_ALG::String8 getTitle() = 0;
		virtual void* getUnderlying() = 0;
	};
}

#endif