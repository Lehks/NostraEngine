#define GLAD_GLAPI_EXPORT //needed for exporting glad

#include "GLAD/glad.h"
#include "GLFW/glfw3.h"

#include "nostraengine/window/GLFWWindow.hpp"

namespace NOE::NOE_WINDOW
{
	NOU::sizeType NOE::NOE_WINDOW::GLFWWindow::s_instanceCounter = 0;

	const NOU::NOU_DAT_ALG::Vector<GLFWMonitor> NOE::NOE_WINDOW::GLFWWindow::s_monitors;

	const NOU::NOU_DAT_ALG::Vector<Monitor*> NOE::NOE_WINDOW::GLFWWindow::s_monitorPointer;

	void monitorCallback(GLFWmonitor* monitor, int event);

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

		glfwMakeContextCurrent(reinterpret_cast<GLFWwindow*>(m_window));
		glfwSwapInterval(1);
	}

	void NOE::NOE_WINDOW::GLFWWindow::setTitle(const NOU::NOU_DAT_ALG::String8& title)
	{
		m_title = title;
		glfwSetWindowTitle(reinterpret_cast<GLFWwindow*>(m_window), m_title.rawStr());
	}

	void NOE::NOE_WINDOW::GLFWWindow::setSize(NOU::sizeType width, NOU::sizeType height)
	{
		glfwSetWindowSize(reinterpret_cast<GLFWwindow*>(m_window), width, height);
	}

	void NOE::NOE_WINDOW::GLFWWindow::setPosition(NOU::sizeType xpos, NOU::sizeType ypos)
	{
		glfwSetWindowPos(reinterpret_cast<GLFWwindow*>(m_window), xpos, ypos);
	}

	void NOE::NOE_WINDOW::GLFWWindow::closeWindow()
	{
		glfwDestroyWindow(reinterpret_cast<GLFWwindow*>(m_window));
	}

	void NOE::NOE_WINDOW::GLFWWindow::minimize()
	{
		glfwIconifyWindow(reinterpret_cast<GLFWwindow*>(m_window));
	}

	void NOE::NOE_WINDOW::GLFWWindow::maximize()
	{
		glfwMaximizeWindow(reinterpret_cast<GLFWwindow*>(m_window));
	}

	void NOE::NOE_WINDOW::GLFWWindow::makeWindowed(Monitor* handle)
	{
		int widthMM = 0;
		int heightMM = 0;

		glfwGetMonitorPhysicalSize(reinterpret_cast<GLFWmonitor*>(handle->getUnderlying()), &widthMM, &heightMM);

		glfwSetWindowMonitor(reinterpret_cast<GLFWwindow*>(m_window), 
			nullptr, widthMM, heightMM, 680, 680, handle->getRefreshRate());
	}

	void NOE::NOE_WINDOW::GLFWWindow::setFullscreen(Monitor* handle, NOU::boolean state)
	{
		if (state)
		{
			glfwSetWindowMonitor(reinterpret_cast<GLFWwindow*>(m_window), reinterpret_cast<GLFWmonitor*>
				(handle->getUnderlying()), 0, 0, handle->getWidth(), handle->getHeight(), handle->getRefreshRate());
		}
		else
		{
			makeWindowed(handle);
		}
	}

	void NOE::NOE_WINDOW::GLFWWindow::update()
	{
		glfwSwapBuffers(reinterpret_cast<GLFWwindow*>(m_window));
		glfwPollEvents();
	}

	void* NOE::NOE_WINDOW::GLFWWindow::getUnderlying()
	{
		return m_window;
	}
	
	NOE::NOE_WINDOW::Monitor* NOE::NOE_WINDOW::GLFWWindow::getPrimaryMonitor()
	{
		if (s_monitors.size() == 0)
		{
			getConnectedMonitors();
		}

		return s_monitorPointer.at(0);
	}

	NOU::NOU_DAT_ALG::Vector<Monitor*> NOE::NOE_WINDOW::GLFWWindow::getConnectedMonitors()
	{
		//Only callable once. After that with monitor callback
		if (GLFWWindow::getMonitors().size() == 0)
		{
			int size;
			GLFWmonitor** glfwMonitors = glfwGetMonitors(&size);

			for (int i = 0; i < size; i++)
			{
				const_cast<NOU::NOU_DAT_ALG::Vector<GLFWMonitor>&>(GLFWWindow::getMonitors()).push(glfwMonitors[i]);

				const_cast<NOU::NOU_DAT_ALG::Vector<Monitor*>&>(GLFWWindow::getMonitorPointer())
					.push(&const_cast<NOU::NOU_DAT_ALG::Vector<GLFWMonitor>&>(GLFWWindow::getMonitors())[i]);
			}
		}
		else
		{
			glfwSetMonitorCallback(monitorCallback);
		}
		
		return s_monitorPointer;
	}

	const NOU::NOU_DAT_ALG::String8& NOE::NOE_WINDOW::GLFWWindow::getTitle()
	{
		return m_title;
	}

	const NOU::NOU_DAT_ALG::Vector<GLFWMonitor>& NOE::NOE_WINDOW::GLFWWindow::getMonitors() 
	{
		return s_monitors;
	}

	const NOU::NOU_DAT_ALG::Vector<Monitor*>& NOE::NOE_WINDOW::GLFWWindow::getMonitorPointer() 
	{
		return s_monitorPointer;
	}

	void monitorCallback(GLFWmonitor* monitor, int event)
	{
		if (event == GLFW_CONNECTED)
		{
			const_cast<NOU::NOU_DAT_ALG::Vector<GLFWMonitor>&>(GLFWWindow::getMonitors()).push(monitor);

			const_cast<NOU::NOU_DAT_ALG::Vector<Monitor*>&>(GLFWWindow::getMonitorPointer())
				.push(&const_cast<NOU::NOU_DAT_ALG::Vector<GLFWMonitor>&>(
					GLFWWindow::getMonitors())[GLFWWindow::getMonitors().size() - 1]);
		}
		else if (event == GLFW_DISCONNECTED)
		{
			for (int i = 0; i < GLFWWindow::getMonitors().size(); i++)
			{
				if (GLFWWindow::getMonitors()[i].getUnderlying() == monitor)
				{
					const_cast<NOU::NOU_DAT_ALG::Vector<GLFWMonitor>&>(GLFWWindow::getMonitors()).remove(i);
					const_cast<NOU::NOU_DAT_ALG::Vector<Monitor*>&>(GLFWWindow::getMonitorPointer()).remove(i);
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