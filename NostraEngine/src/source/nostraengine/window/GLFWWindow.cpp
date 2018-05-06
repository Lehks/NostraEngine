#define GLAD_GLAPI_EXPORT //needed for exporting glad

#include "nostraengine/window/GLFWWindow.hpp"

#include "GLAD/glad.h"
#include "GLFW/glfw3.h"

namespace NOE::NOE_WINDOW
{
	NOU::sizeType NOE::NOE_WINDOW::GLFWWindow::s_instanceCounter = 0;

	const NOU::NOU_DAT_ALG::Vector<GLFWMonitor> NOE::NOE_WINDOW::GLFWWindow::s_monitors;

	const NOU::NOU_DAT_ALG::Vector<const Monitor*> NOE::NOE_WINDOW::GLFWWindow::s_monitorPointer;

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

		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

		GLFWmonitor* glwfMonitor;
		if(monitor == nullptr)
			glwfMonitor = reinterpret_cast<GLFWmonitor*>(monitor);
		else
			glwfMonitor = reinterpret_cast<GLFWmonitor*>(monitor->getUnderlying());

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
	
	const NOE::NOE_WINDOW::Monitor* NOE::NOE_WINDOW::GLFWWindow::getPrimaryMonitor()
	{
		if (s_monitors.size() == 0)
		{
			getConnectedMonitors();
		}

		return s_monitorPointer.at(0);
	}

	const NOU::NOU_DAT_ALG::Vector<const Monitor*>& NOE::NOE_WINDOW::GLFWWindow::getConnectedMonitors()
	{
		const_cast<NOU::NOU_DAT_ALG::Vector<GLFWMonitor>&>(GLFWWindow::getMonitors()).clear();
		const_cast<NOU::NOU_DAT_ALG::Vector<const Monitor*>&>(GLFWWindow::getMonitorPointer()).clear();

		int size;
		GLFWmonitor** glfwMonitors = glfwGetMonitors(&size);

		for (int i = 0; i < size; i++)
		{
			const_cast<NOU::NOU_DAT_ALG::Vector<GLFWMonitor>&>(GLFWWindow::getMonitors()).pushBack(glfwMonitors[i]);
		}

		for (int i = 0; i < size; i++)
		{
			const_cast<NOU::NOU_DAT_ALG::Vector<const Monitor*>&>(GLFWWindow::getMonitorPointer())
				.pushBack(&const_cast<NOU::NOU_DAT_ALG::Vector<GLFWMonitor>&>(GLFWWindow::getMonitors())[i]);
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

	const NOU::NOU_DAT_ALG::Vector<const Monitor*>& NOE::NOE_WINDOW::GLFWWindow::getMonitorPointer() 
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
