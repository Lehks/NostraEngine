#ifndef NOE_WINDOW_WINDOW_HPP
#define NOE_WINDOW_WINDOW_HPP

#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

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
namespace NOE_WINDOW
{
	class Window
	{
	
	public:
		using sizeType = NOU::sizeType;
		
		virtual void setTitle() = 0;
		virtual void setSize(sizeType width, sizeType height) = 0;
		virtual void setPosition(sizeType width, sizeType height) = 0;
		virtual void close() = 0;
		virtual void minimize() = 0;
		virtual void maximize() = 0;
		virtual void makeWindowed() = 0;
		virtual void decorated(bool state) = 0;
		virtual void setFullscreen(bool state) = 0;
		virtual void update() = 0;
		virtual NOE_WINDOW::Device getDevices() = 0;
		virtual NOU::NOU_DAT_ALG::String8 getName() = 0;
		virtual void* getUnderlying() = 0;
	};

	class GLFWWindow : Window
	{
	private:
		NOU::NOU_DAT_ALG::String8 m_title;
		NOU::NOU_DAT_ALG::String8 m_name;
		sizeType m_sizeWidth;
		sizeType m_sizeHeight;
		sizeType m_posWidth;
		sizeType m_posHeight;
	public:

		void setTitle();
		void setSize(sizeType width, sizeType height);
		void setPosition(sizeType width, sizeType height);
		void close();
		void minimize();
		void maximize();
		void makeWindowed();
		void decorated(bool state);
		void setFullscreen(bool state);
		void update();
		NOE_WINDOW::Device getDevices();
		NOU::NOU_DAT_ALG::String8 getName();
		void* getUnderlying();

	};
}

#endif