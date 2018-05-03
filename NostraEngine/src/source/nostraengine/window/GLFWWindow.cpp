#include "nostraengine/window/GLFWWindow.hpp"

namespace NOE::NOE_WINDOW
{
	NOU::sizeType NOE::NOE_WINDOW::GLFWWindow::s_instanceCounter = 0;

	NOU::NOU_DAT_ALG::Vector<GLFWMonitor> NOE::NOE_WINDOW::GLFWWindow::m_monitors;

	NOU::NOU_DAT_ALG::Vector<Monitor*> NOE::NOE_WINDOW::GLFWWindow::m_monitorPointer;

	NOE::NOE_WINDOW::GLFWWindow::GLFWWindow() :
		m_window(nullptr)
	{
		if (s_instanceCounter == 0)
		{
			if (!glfwInit())
			{
				NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(),
					NOE::NOE_WINDOW::ErrorCodes::GLFW_INITIALIZATION_FAILED, "Could not initialize GLFW!");
			}
			else
			{
				s_instanceCounter++;
			}
		}
	}

	NOE::NOE_WINDOW::GLFWWindow::~GLFWWindow()
	{
		s_instanceCounter--;
		if (s_instanceCounter == 0)
		{
			glfwTerminate();
		}
	}

	void NOE::NOE_WINDOW::GLFWWindow::createWindow(NOU::sizeType width, NOU::sizeType height,
		const NOU::NOU_DAT_ALG::String8& title, Monitor* monitor)
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

	void NOE::NOE_WINDOW::GLFWWindow::makeWindowed(GLFWmonitor* handle)
	{
		const GLFWvidmode* mode = glfwGetVideoMode(handle);

		int widthMM = 0;
		int heightMM = 0;

		glfwGetMonitorPhysicalSize(handle, &widthMM, &heightMM);

		glfwSetWindowMonitor(m_window, nullptr, widthMM, heightMM, 680, 680, mode->refreshRate);
	}

	void NOE::NOE_WINDOW::GLFWWindow::setFullscreen(GLFWmonitor* handle, NOU::boolean state)
	{
		const GLFWvidmode* mode = glfwGetVideoMode(handle);
		if (state)
		{
			glfwSetWindowMonitor(m_window, handle, 0, 0, mode->width, mode->height, mode->refreshRate);
		}
		else
		{
			makeWindowed(handle);
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
	
	NOE::NOE_WINDOW::Monitor* NOE::NOE_WINDOW::GLFWWindow::getPrimaryMonitor()
	{
		if (m_monitors.size() == 0)
		{
			getConnectedMonitors();
		}

		return m_monitorPointer.at(0);
	}

	NOU::NOU_DAT_ALG::Vector<Monitor*> NOE::NOE_WINDOW::GLFWWindow::getConnectedMonitors()
	{
		//Only callable once. After that with monitor callback
		if (m_monitors.size() == 0)
		{
			int size;
			GLFWmonitor** glfwMonitors = glfwGetMonitors(&size);

			for (int i = 0; i < size; i++)
			{
				m_monitors.push(glfwMonitors[i]);
				m_monitorPointer.push(&m_monitors[i]);
			}
		}
		else
		{
			glfwSetMonitorCallback(monitorCallback);
		}
		
		return m_monitorPointer;
	}

	const NOU::NOU_DAT_ALG::String8& NOE::NOE_WINDOW::GLFWWindow::getTitle()
	{
		return m_title;
	}

	void NOE::NOE_WINDOW::GLFWWindow::monitorCallback(GLFWmonitor* monitor, int event)
	{
		if (event == GLFW_CONNECTED)
		{
			m_monitors.push(monitor);
			m_monitorPointer.push(&m_monitors[m_monitors.size() - 1]);
		}
		else if (event == GLFW_DISCONNECTED)
		{
			for (int i = 0; i < m_monitors.size(); i++)
			{
				if (m_monitors[i].getUnderlying() == monitor)
				{
					m_monitors.remove(i);
					m_monitorPointer.remove(i);
				}
			}
		}
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
