#include "nostraengine/window/GLFWWindow.hpp"

namespace NOE::NOE_WINDOW
{
	NOE::NOE_WINDOW::GLFWWindow::GLFWWindow()
	{
		if (m_instanceCounter == 0)
		{
			if (!glfwInit())
			{
				NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(),
					NOE::NOE_WINDOW::ErrorCodes::GLFW_INITIALIZATION_FAILED, "Could not initialize GLFW!");
			}
			else
			{
				m_instanceCounter++;
			}
		}
	}

	NOE::NOE_WINDOW::GLFWWindow::~GLFWWindow()
	{
		m_instanceCounter--;
		if (m_instanceCounter == 0)
		{
			glfwTerminate();
		}
	}

	void NOE::NOE_WINDOW::GLFWWindow::createWindow(NOU::sizeType width, NOU::sizeType height,
		const NOU::NOU_DAT_ALG::String8& title, void* monitor)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

		GLFWmonitor* glwfMonitor = reinterpret_cast<GLFWmonitor*>(monitor);

		m_title = title;

		m_window = glfwCreateWindow(width, height, m_title.rawStr(), glwfMonitor, nullptr);

		if (!m_window)
		{
			closeWindow();
			NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(),
				ErrorCodes::WINDOW_INITIALIZATION_FAILED, "Could not initialize the window!");
		}

		glfwMakeContextCurrent(m_window);
		glfwSwapInterval(1);
	}

	void NOE::NOE_WINDOW::GLFWWindow::setTitle(const NOU::NOU_DAT_ALG::String8& title)
	{
		m_title = title;
		glfwSetWindowTitle(m_window, m_title.rawStr());
	}

	void NOE::NOE_WINDOW::GLFWWindow::setSize(NOU::sizeType width, NOU::sizeType height)
	{
		glfwSetWindowSize(m_window, width, height);
	}

	void NOE::NOE_WINDOW::GLFWWindow::setPosition(NOU::sizeType xpos, NOU::sizeType ypos)
	{
		glfwSetWindowPos(m_window, xpos, ypos);
	}

	void NOE::NOE_WINDOW::GLFWWindow::closeWindow()
	{
		glfwDestroyWindow(m_window);
	}

	void NOE::NOE_WINDOW::GLFWWindow::minimize()
	{
		glfwIconifyWindow(m_window);
	}

	void NOE::NOE_WINDOW::GLFWWindow::maximize()
	{
		glfwMaximizeWindow(m_window);
	}

	void NOE::NOE_WINDOW::GLFWWindow::makeWindowed()
	{
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		int widthMM = 0;
		int heightMM = 0;

		glfwGetMonitorPhysicalSize(monitor, &widthMM, &heightMM);

		glfwSetWindowMonitor(m_window, nullptr, widthMM, heightMM, 680, 680, mode->refreshRate);
	}

	void NOE::NOE_WINDOW::GLFWWindow::setFullscreen(NOU::boolean state)
	{
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		if (state)
		{
			glfwSetWindowMonitor(m_window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
		}
		else
		{
			makeWindowed();
		}
	}

	void NOE::NOE_WINDOW::GLFWWindow::update()
	{
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	void* NOE::NOE_WINDOW::GLFWWindow::getUnderlying()
	{
		return m_window;
	}

	void** NOE::NOE_WINDOW::GLFWWindow::getMonitors()
	{
		int count;
		GLFWmonitor** monitors = glfwGetMonitors(&count);

		return reinterpret_cast<void**>(monitors);
	}

	NOU::sizeType NOE::NOE_WINDOW::GLFWWindow::getMonitorCount()
	{
		int count;
		GLFWmonitor** monitors = glfwGetMonitors(&count);

		m_monitorCount = count;
		return m_monitorCount;
	}

	const NOU::NOU_DAT_ALG::String8& NOE::NOE_WINDOW::GLFWWindow::getTitle()
	{
		return m_title;
	}

#ifndef NOU_WINDOW_MAKE_ERROR
#define NOU_WINDOW_MAKE_ERROR(code) NOU::NOU_CORE::Error(#code, ErrorCodes::code)
#endif

	ErrorPool::ErrorPool() :
		m_errors //must be in order
	{
		NOU_WINDOW_MAKE_ERROR(GLFW_INITIALIZATION_FAILED),
		NOU_WINDOW_MAKE_ERROR(WINDOW_INITIALIZATION_FAILED)
	}
	{}

#undef NOU_WINDOW_MAKE_ERROR

	const NOU::NOU_CORE::Error* ErrorPool::queryError(NOU::NOU_CORE::ErrorPool::ErrorType id) const
	{
		if (id > ErrorCodes::FIRST_ELEMENT && id < ErrorCodes::LAST_ELEMENT)
		{
			NOU::sizeType index = id - ErrorCodes::FIRST_ELEMENT + 1;

			return m_errors + index;
		}
	}
}
