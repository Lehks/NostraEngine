#ifndef NOE_WINDOW_GLFWWINDOW_HPP
#define NOE_WINDOW_GLFWWINDOW_HPP
#define GLAD_GLAPI_EXPORT

#include "GLAD/glad.h"
#include "GLFW/glfw3.h"

#include "nostrautils/NostraUtils.hpp"

#include "nostraengine/core/StdIncludes.hpp"

#include "nostraengine/window/Window.hpp"

/**
\file window/GLFWWindow.hpp

\author  Lukas Gross
\version 0.0.1
\since   0.0.1

\brief A file that provides the functionality for creating and operating a window with GLFW.
*/
namespace NOE::NOE_WINDOW
{
	/**
	\brief				A class that implements the provided template functions of the Window class.
	*/
	class NOU_CLASS GLFWWindow : public Window
	{
	private:

		/**
		\brief			The handle of the window.
		*/
		GLFWwindow* m_window = nullptr;

		/**
		\brief			Stores the title of the window.
		*/
		NOU::NOU_DAT_ALG::String8 m_title;

		/**
		\brief			The count of monitors connected.
		*/
		NOU::sizeType m_monitorCount;
	public:

		/**
		\brief			Destructor of the GLFWWindow.
		*/
		virtual ~GLFWWindow() = default;

		/**
		\param width	The width of the window.
		\param height	The height of the window.
		\param title	The title of the window.
		\param monitor	A pointer to the monitor object.
		\param share	A pointer to the window for sharing context.

		\brief			Creates a new GLFWWindow and stores it in the m_window handle.

		\details		The parameter monitor can be:
						-nullptr if the window should be in window mode
						-A pointer to a monitor where the window should be in full screen mode
		*/
		virtual void createWindow(NOU::sizeType width, NOU::sizeType height,
			NOU::NOU_DAT_ALG::String8 title, void* monitor = nullptr, void* share = nullptr) override;

		/**
		\param title	The new title of the window.

		\brief			Sets a new title for the window.
		*/
		virtual void setTitle(NOU::NOU_DAT_ALG::String8 title) override;

		/**
		\param width	The new width of the window.
		\param height	The new height of the window.

		\brief			Resizes the window.
		*/
		virtual void setSize(NOU::sizeType width, NOU::sizeType height) override;

		/**
		\param xpos		The new position of the window on the x-axis.
		\param ypos		The new position of the window on the y-axis.

		\brief			Changes the position of the window.
		*/
		virtual void setPosition(NOU::sizeType xpos, NOU::sizeType ypos) override;

		/**
		\brief			Closes the window.
		*/
		virtual void closeWindow() override;

		/**
		\brief			Minimizes the window.
		*/
		virtual void minimize() override;

		/**
		\brief			Maximizes the window.
		*/
		virtual void maximize()	override;

		/**
		\brief			Makes the window windowed.
		*/
		virtual void makeWindowed()	override;

		/**
		\param state	True if full screen and false if not.

		\brief			Makes the window full screen.

		\details		If state is set to false than the makeWindowed() is called. This results in making
						exiting the full screen mode and making the window windowed again.
		*/
		virtual void setFullscreen(NOU::boolean state) override;

		/**
		\brief			All operations that are performed in the window like updating images, etc.
		*/
		virtual void update() override;

		/**
		\return void*	Returns a void pointer to the window.

		\brief			Returns the window handle.
		*/
		virtual void* getUnderlying() override;

		/**
		\return			Returns an array of void pointer.

		\brief			Returns all connected monitors.

		\details		The first array element is the primary monitor. For getting the count of monitors
						call the getMonitorsCount method.
		*/
		virtual void** getMonitors() override;

		/**
		\returns		The monitor count.

		\brief			Returns the count of monitors connected.
		*/
		virtual NOU::sizeType getMonitorCount() override;

		/**
		\return			Returns the title.

		\brief			Returns the title of the window.
		*/
		virtual NOU::NOU_DAT_ALG::String8 getTitle() override;

	};
}

#endif
