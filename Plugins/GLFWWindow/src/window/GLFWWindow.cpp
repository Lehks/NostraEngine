#define GLAD_GLAPI_EXPORT //needed for exporting glad

#include "GLFWWindow.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace GLFWWindowPlugin
{
	const NOU::NOU_DAT_ALG::Vector<GLFWMonitor> GLFWWindow::s_monitors;

	const NOU::NOU_DAT_ALG::Vector<const NOE::NOE_WINDOW::Monitor*> GLFWWindow::s_monitorPointer;

	GLFWWindow::GLFWWindow() :
		m_window(nullptr)
	{}

	void GLFWWindow::createWindow(NOU::sizeType width, NOU::sizeType height,
		const NOU::NOU_DAT_ALG::String8& title, const NOE::NOE_WINDOW::Monitor* monitor)
	{
		GLFWmonitor* glfwMonitor;

		if(monitor == nullptr)
			glfwMonitor = nullptr;
		else
			glfwMonitor = const_cast<GLFWmonitor*>(
				reinterpret_cast<const GLFWmonitor*>(monitor->getUnderlying()));

		m_title = title;

		m_window = glfwCreateWindow(width, height, m_title.rawStr(), glfwMonitor, nullptr);

		if (!m_window)
		{
			closeWindow();
			NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(),
				ErrorCodes::WINDOW_INITIALIZATION_FAILED, "Could not initialize the window!");
			NOU_LOG_DEBUG("Window initialization failed!");
		}

		glfwMakeContextCurrent(reinterpret_cast<GLFWwindow*>(m_window));
		glfwSwapInterval(1);
	}

	void GLFWWindow::setTitle(const NOU::NOU_DAT_ALG::String8& title)
	{
		m_title = title;
		glfwSetWindowTitle(reinterpret_cast<GLFWwindow*>(m_window), m_title.rawStr());
	}

	void GLFWWindow::setSize(NOU::sizeType width, NOU::sizeType height)
	{
		glfwSetWindowSize(reinterpret_cast<GLFWwindow*>(m_window), width, height);
	}

	void GLFWWindow::setPosition(NOU::sizeType xpos, NOU::sizeType ypos)
	{
		glfwSetWindowPos(reinterpret_cast<GLFWwindow*>(m_window), xpos, ypos);
	}

	void GLFWWindow::closeWindow()
	{
		glfwDestroyWindow(reinterpret_cast<GLFWwindow*>(m_window));
	}

	void GLFWWindow::minimize()
	{
		glfwIconifyWindow(reinterpret_cast<GLFWwindow*>(m_window));
	}

	void GLFWWindow::maximize()
	{
		glfwMaximizeWindow(reinterpret_cast<GLFWwindow*>(m_window));
	}

	void GLFWWindow::makeWindowed(NOU::sizeType xpos, NOU::sizeType ypos,
		NOU::sizeType width, NOU::sizeType height, NOU::sizeType refreshRate)
	{
		glfwSetWindowMonitor(reinterpret_cast<GLFWwindow*>(m_window), 
			nullptr, xpos, ypos, width, height, refreshRate);
	}

	void GLFWWindow::setFullscreen(const NOE::NOE_WINDOW::Monitor* handle)
	{
		glfwSetWindowMonitor(reinterpret_cast<GLFWwindow*>(m_window), 
			const_cast<GLFWmonitor*>(reinterpret_cast<const GLFWmonitor*>(handle->getUnderlying())), 
			0, 0, handle->getWidth(), handle->getHeight(), handle->getRefreshRate());
	}

	void GLFWWindow::update()
	{
		glfwSwapBuffers(reinterpret_cast<GLFWwindow*>(m_window));
		glfwPollEvents();
	}

	void* GLFWWindow::getUnderlying()
	{
		return m_window;
	}
	
	const NOE::NOE_WINDOW::Monitor* GLFWWindow::getPrimaryMonitor()
	{
		if (s_monitors.size() == 0)
		{
			getConnectedMonitors();
		}

		return s_monitorPointer.at(0);
	}

	const NOU::NOU_DAT_ALG::Vector<const NOE::NOE_WINDOW::Monitor*>& GLFWWindow::getConnectedMonitors()
	{
		int size;
		GLFWmonitor** glfwMonitors = glfwGetMonitors(&size);

		for (int i = 0; i < size; i++)
		{
			if (const_cast<NOU::NOU_DAT_ALG::Vector<GLFWMonitor>&>
				(GLFWWindow::getMonitors()).empty() == true)
			{
				for (int j = 0; j < size; j++)
				{
					const_cast<NOU::NOU_DAT_ALG::Vector<GLFWMonitor>&>
						(GLFWWindow::getMonitors()).pushBack(glfwMonitors[j]);

					NOU_LOG_DEBUG("Added new monitor to the monitor vector.");
				}
			}
			else if (const_cast<GLFWmonitor*>(reinterpret_cast<const GLFWmonitor*>
				(GLFWWindow::getMonitors().at(i).getUnderlying())) != glfwMonitors[i])
			{
				const_cast<NOU::NOU_DAT_ALG::Vector<const NOE::NOE_WINDOW::Monitor*>&>(
					GLFWWindow::getMonitorPointer()).remove(i);

				NOU_LOG_DEBUG("Removed pointer to a monitor in the monitor pointer vector.");

				const_cast<NOU::NOU_DAT_ALG::Vector<GLFWMonitor>&>(GLFWWindow::getMonitors()).remove(i);

				NOU_LOG_DEBUG("Removed a monitor in the monitor vector.");

				const_cast<NOU::NOU_DAT_ALG::Vector<GLFWMonitor>&>
					(GLFWWindow::getMonitors()).pushBack(glfwMonitors[i]);

				NOU_LOG_DEBUG("Added new monitor to the monitor vector.");

				const_cast<NOU::NOU_DAT_ALG::Vector<const NOE::NOE_WINDOW::Monitor*>&>
					(GLFWWindow::getMonitorPointer()).pushBack(
						&const_cast<NOU::NOU_DAT_ALG::Vector<GLFWMonitor>&>(
						GLFWWindow::getMonitors())[GLFWWindow::getMonitors().size() - 1]);

				NOU_LOG_DEBUG("Added pointer to a monitor to the monitor pointer vector.");
			}
			
		}

		if (const_cast<NOU::NOU_DAT_ALG::Vector<const NOE::NOE_WINDOW::Monitor*>&>(
			GLFWWindow::getMonitorPointer()).empty() == true)
		{
			for (int i = 0; i < size; i++)
			{
				const_cast<NOU::NOU_DAT_ALG::Vector<const NOE::NOE_WINDOW::Monitor*>&>(
					GLFWWindow::getMonitorPointer()).pushBack(
						&const_cast<NOU::NOU_DAT_ALG::Vector<GLFWMonitor>&>(GLFWWindow::getMonitors())[i]);

				NOU_LOG_DEBUG("Added pointer to a monitor to the monitor pointer vector.");
			}
		}

		
		return s_monitorPointer;
	}

	const NOU::NOU_DAT_ALG::String8& GLFWWindow::getTitle()
	{
		return m_title;
	}

	const NOU::NOU_DAT_ALG::Vector<GLFWMonitor>& GLFWWindow::getMonitors() 
	{
		return s_monitors;
	}

	const NOU::NOU_DAT_ALG::Vector<const NOE::NOE_WINDOW::Monitor*>& GLFWWindow::getMonitorPointer()
	{
		return s_monitorPointer;
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
