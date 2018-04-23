#ifndef NOE_WINDOW_GLFWWINDOW_HPP
#define NOE_WINDOW_GLFWWINDOW_HPP

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
	\brief A class that implements the provided template functions of the pure virtual class Window.
	*/
	class NOU_CLASS GLFWWindow : Window
	{
	private:
		GLFWwindow * m_window;
	public:

		virtual void createWindow(NOU::sizeType m_sizeWidth, NOU::sizeType m_sizeHeight,
			NOU::NOU_DAT_ALG::String8 m_title, GLFWmonitor* monitor = NULL, 
			GLFWwindow* share = NULL) override;
		virtual void setTitle(NOU::NOU_DAT_ALG::String8 title) override;
		virtual void setSize(NOU::sizeType width, NOU::sizeType height) override;
		virtual void setPosition(NOU::sizeType width, NOU::sizeType height) override;
		virtual void close() override;
		virtual void minimize() override;
		virtual void maximize()	override;
		virtual void makeWindowed()	override;
		virtual void decorated(NOU::boolean state) override;
		virtual void setFullscreen(NOU::boolean state) override;
		virtual void update() override;
		virtual NOE_WINDOW::Device getDevices() override;
		virtual NOU::NOU_DAT_ALG::String8 getTitle() override;
		virtual void* getUnderlying() override;				 //return unterliegendes handle

	};
}

#endif
