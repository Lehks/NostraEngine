#ifndef NOE_WINDOW_WINDOW_HPP
#define NOE_WINDOW_WINDOW_HPP

#include "nostrautils/NostraUtils.hpp"

#include "nostraengine/core/StdIncludes.hpp"
#include "nostraengine/window/Monitor.hpp"

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

		/**
		\param width	The width of the window.
		\param height	The height of the window.
		\param title	The title of the window.
		\param monitor	A pointer to the monitor object.

		\brief			Creates a new window and stores it in the m_window handle.

		\details		The parameter monitor can be:
						-nullptr if the window should be in window mode
						-A pointer to a monitor where the window should be in full screen mode
		*/
		virtual void createWindow(NOU::sizeType width, NOU::sizeType height,
			const NOU::NOU_DAT_ALG::String8& title, const Monitor* monitor = nullptr) = 0;

		/**
		\param title	The new title of the window.

		\brief			Sets a new title for the window.
		*/
		virtual void setTitle(const NOU::NOU_DAT_ALG::String8& title) = 0;

		/**
		\param width	The new width of the window.
		\param height	The new height of the window.

		\brief			Resizes the window.
		*/
		virtual void setSize(NOU::sizeType width, NOU::sizeType height) = 0;

		/**
		\param xpos		The new position of the window on the x-axis.
		\param ypos		The new position of the window on the y-axis.

		\brief			Changes the position of the window.
		*/
		virtual void setPosition(NOU::sizeType xpos, NOU::sizeType ypos) = 0;

		/**
		\brief			Closes the window.
		*/
		virtual void closeWindow() = 0;

		/**
		\brief			Minimizes the window.
		*/
		virtual void minimize() = 0;

		/**
		\brief			Maximizes the window.
		*/
		virtual void maximize() = 0;

		/**
		\param xpos			The x-axis position of the window.
		\param ypos			The y-axis position of the window.
		\param width		The width of the window.
		\param height		The height of the window.
		\param refreshRate	The refresh rate of the window.

		\brief				Makes the window windowed.

		\details			Each parameter has its own default value.
		*/
		virtual void makeWindowed(NOU::sizeType xpos, NOU::sizeType ypos, 
			NOU::sizeType width, NOU::sizeType height, NOU::sizeType refreshRate) = 0;

		/**
		\param handle	The monitor where to make the window full screen.

		\brief			Makes the window full screen.
		*/
		virtual void setFullscreen(const Monitor* handle) = 0;

		/**
		\brief			All operations that are performed in the window like updating images, etc.

		\details		The run loop of the window must be created by the user who implements the window.
						This can be done by using the glfwWindowShouldClose() and using the returned result
						of the getUnderlying().
						e.g.: 
						while(!glfwWindowShouldClose(
						reinterpret_cast<GLFWwindow*>(windowObject.getUnderlying())))
						{
							//windowObject.update();
						}

						The reinterpret_cast is necessary because getUnderlying returns a void* and 
						glfwWindowShouldClose() needs a GLFWwindow*.
		*/
		virtual void update() = 0;

		/**
		\return void*	Returns a void pointer to the window.

		\brief			Returns the window handle.
		*/
		virtual void* getUnderlying() = 0;

		/**
		\return			A pointer to an monitor object.

		\brief			Returns the primary monitor as a Monitor*.
		*/
		virtual const Monitor* getPrimaryMonitor() = 0;

		/**
		\return			Returns an vector with Monitor pointer.

		\brief			Returns all connected monitors.

		\details		The first array element is the primary monitor.
		*/
		virtual const NOU::NOU_DAT_ALG::Vector<const Monitor*>& getConnectedMonitors() = 0;

		/**
		\return			Returns the title.

		\brief			Returns the title of the window.
		*/
		virtual const NOU::NOU_DAT_ALG::String8& getTitle() = 0;
	};
}

#endif