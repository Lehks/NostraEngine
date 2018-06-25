#define GLAD_GLAPI_EXPORT //needed for exporting glad

#include "nostraengine/window/GLFWWindow.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace NOE::NOE_WINDOW
{
	NOU::sizeType NOE::NOE_WINDOW::GLFWWindow::s_instanceCounter = 0;

	NOU::NOU_DAT_ALG::Vector<GLFWMonitor> NOE::NOE_WINDOW::GLFWWindow::s_monitors;

	NOU::NOU_DAT_ALG::Vector<const Monitor*> NOE::NOE_WINDOW::GLFWWindow::s_monitorPointer;

	NOU::NOU_CORE::Logger& windowLog = NOU::NOU_CORE::Logger::get();

	NOE::NOE_WINDOW::GLFWWindow::GLFWWindow() :
		m_window(nullptr)
	{
		if (s_instanceCounter == 0)
		{
			if (!glfwInit())
			{
				NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(),
					NOE::NOE_WINDOW::ErrorCodes::GLFW_INITIALIZATION_FAILED, "Could not initialize GLFW!");

				NOU_LOG_DEBUG("GLFW initialization failed!");
			}
			else
			{
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

#ifdef __APPLE__
				glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

				NOU_LOG_DEBUG("GLFW initialization successful!");
				s_instanceCounter++;
			}
		}
	}

	NOE::NOE_WINDOW::GLFWWindow::~GLFWWindow()
	{
		s_instanceCounter--;
		if (s_instanceCounter == 0)
		{
			NOU_LOG_DEBUG("GLFW successfully terminated!");
			s_monitorPointer.clear();
			s_monitors.clear();
			glfwTerminate();
		}
	}

	void NOE::NOE_WINDOW::GLFWWindow::createWindow(NOU::sizeType width, NOU::sizeType height,
		const NOU::NOU_DAT_ALG::String8& title, const Monitor* monitor)
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

	void NOE::NOE_WINDOW::GLFWWindow::makeWindowed(NOU::sizeType xpos, NOU::sizeType ypos,
		NOU::sizeType width, NOU::sizeType height, NOU::sizeType refreshRate)
	{
		glfwSetWindowMonitor(reinterpret_cast<GLFWwindow*>(m_window), 
			nullptr, xpos, ypos, width, height, refreshRate);
	}

	void NOE::NOE_WINDOW::GLFWWindow::setFullscreen(const Monitor* handle)
	{
		glfwSetWindowMonitor(reinterpret_cast<GLFWwindow*>(m_window), 
			const_cast<GLFWmonitor*>(reinterpret_cast<const GLFWmonitor*>(handle->getUnderlying())), 
			0, 0, handle->getWidth(), handle->getHeight(), handle->getRefreshRate());
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
		int size;
		GLFWmonitor** glfwMonitors = glfwGetMonitors(&size);

		for (int i = 0; i < size; i++)
		{
			if (s_monitors.empty())
			{
				for (int j = 0; j < size; j++)
				{
					s_monitors.pushBack(glfwMonitors[j]);

					NOU_LOG_DEBUG("Added new monitor to the monitor vector.");
				}
			}
			else if (reinterpret_cast<const GLFWmonitor*>
				(s_monitors.at(i).getUnderlying()) != glfwMonitors[i])
			{
				s_monitorPointer.remove(i);

				NOU_LOG_DEBUG("Removed pointer to a monitor in the monitor pointer vector.");

				s_monitors.remove(i);

				NOU_LOG_DEBUG("Removed a monitor in the monitor vector.");

				s_monitors.pushBack(glfwMonitors[i]);

				NOU_LOG_DEBUG("Added new monitor to the monitor vector.");

				s_monitorPointer.pushBack(&s_monitors[s_monitors.size() - 1]);

				NOU_LOG_DEBUG("Added pointer to a monitor to the monitor pointer vector.");
			}
		}

		if (s_monitorPointer.empty())
		{
			for (int i = 0; i < size; i++)
			{
				s_monitorPointer.pushBack(&s_monitors[i]);

				NOU_LOG_DEBUG("Added pointer to a monitor to the monitor pointer vector.");
			}
		}
		
		return s_monitorPointer;
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
