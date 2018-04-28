#ifndef NOE_WINDOW_WINDOW_HPP
#define NOE_WINDOW_WINDOW_HPP

#include "nostrautils/NostraUtils.hpp"

#include "nostraengine/core/StdIncludes.hpp"

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
		\brief			Destructor of the Window.
		*/
		virtual ~Window() = default;

		/**
		\param width	The width of the window.
		\param height	The height of the window.
		\param title	The title of the window.
		\param monitor	A pointer to the monitor object.
		\param share	A pointer to the window for sharing context.

		\brief			Creates a new window and stores it in the m_window handle.

		\details		The parameter monitor can be:
						-nullptr if the window should be in window mode
						-A pointer to a monitor where the window should be in full screen mode
		*/
		virtual void createWindow(NOU::sizeType width, NOU::sizeType height,
			NOU::NOU_DAT_ALG::String8 title, void* monitor = nullptr, void* share = nullptr) = 0;

		/**
		\param title	The new title of the window.

		\brief			Sets a new title for the window.
		*/
		virtual void setTitle(NOU::NOU_DAT_ALG::String8 title) = 0;

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
		\brief			Makes the window windowed.
		*/
		virtual void makeWindowed() = 0;

		/**
		\param state	True if full screen and false if not.

		\brief			Makes the window full screen.

		\details		If state is set to false than the makeWindowed() is called. This results in making
						exiting the full screen mode and making the window windowed again.
		*/
		virtual void setFullscreen(NOU::boolean state) = 0;

		/**
		\brief			All operations that are performed in the window like updating images, etc.
		*/
		virtual void update() = 0;

		/**
		\return void*	Returns a void pointer to the window.

		\brief			Returns the window handle.
		*/
		virtual void* getUnderlying() = 0;

		/**
		\return			Returns an array of void pointer.

		\brief			Returns all connected monitors.

		\details		The first array element is the primary monitor. For getting the count of monitors
						call the getMonitorsCount method.
		*/
		virtual void** getMonitors() = 0;

		/**
		\returns		The monitor count.

		\brief			Returns the count of monitors connected.
		*/
		virtual NOU::sizeType getMonitorCount() = 0;

		/**
		\return			Returns the title.

		\brief			Returns the title of the window.
		*/
		virtual NOU::NOU_DAT_ALG::String8 getTitle() = 0;
	};
}

#endif