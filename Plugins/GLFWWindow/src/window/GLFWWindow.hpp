#ifndef PLUGIN_GLFW_WINDOW_HPP
#define PLUGIN_GLFW_WINDOW_HPP

#include "nostrautils/NostraUtils.hpp"

#include "nostraengine/NostraEngine.hpp"
#include "nostraengine/core/StdIncludes.hpp"

#include "nostraengine/window/Window.hpp"
#include "GLFWMonitor.hpp"

#include "GLFW/glfw3.h"

/**
\file window/GLFWWindow.hpp

\author  Lukas Gross 
\version 0.0.1
\since   0.0.1

\brief A file that provides the functionality for creating and operating a window with GLFW.
*/
namespace GLFWWindowPlugin
{
	/**
	\brief				A class that implements the provided functions of the Window class. The
						behavior of all functions is defined in the Window class.
	*/
	class GLFWWindow final : public NOE::NOE_WINDOW::Window, public NOE::NOE_CORE::Initializable
	{
	private:

		/**
		\brief			The handle of the window.
		*/
		void* m_window;

		/**
		\brief			Stores the title of the window.
		*/
		NOU::NOU_DAT_ALG::String8 m_title;

		/**
		\brief			Stores the count of GLFW instances.
		*/
		static NOU::sizeType s_instanceCounter;

		/**
		\brief			The vector that stores the monitors as GLFWMonitors.
		*/
		NOU::NOU_DAT_ALG::Vector<GLFWMonitor> s_monitors;

		/**
		\brief			The vector that stores the monitors as Monitor pointers.
		*/
		NOU::NOU_DAT_ALG::Vector<const NOE::NOE_WINDOW::Monitor*> s_monitorPointer;

		/**
		\brief			A constant that stores the name of the class.
		*/
		const NOU::NOU_DAT_ALG::StringView8 CLASS_NAME = "GLFWWindow";

	public:
		static void windowCloseCallback(GLFWwindow *win);
		
		/**
		\brief			Checks if the instance counter is 0, increases the counter and initializes GLFW.
		*/
		NOE_PLUGIN_FUNC GLFWWindow();

		/**
		\brief			Decreases the instance counter and terminates GLFW.
		*/
		NOE_PLUGIN_FUNC virtual ~GLFWWindow();
		NOE_PLUGIN_FUNC virtual void createWindow(NOU::sizeType width = 500, NOU::sizeType height = 500,
			const NOU::NOU_DAT_ALG::String8& title = "Window Name",
			const NOE::NOE_WINDOW::Monitor* monitor = nullptr) override;
		NOE_PLUGIN_FUNC virtual void setTitle(const NOU::NOU_DAT_ALG::String8& title) override;
		NOE_PLUGIN_FUNC virtual void setSize(NOU::sizeType width, NOU::sizeType height) override;
		NOE_PLUGIN_FUNC virtual void setPosition(NOU::sizeType xpos, NOU::sizeType ypos) override;
		NOE_PLUGIN_FUNC virtual void closeWindow() override;
		NOE_PLUGIN_FUNC virtual void minimize() override;
		NOE_PLUGIN_FUNC virtual void maximize()	override;
		NOE_PLUGIN_FUNC virtual void makeWindowed(NOU::sizeType xpos = 50, NOU::sizeType ypos = 50, 
			NOU::sizeType width = 480, NOU::sizeType height = 480, NOU::sizeType refreshRate = 60) override;
		NOE_PLUGIN_FUNC virtual void setFullscreen(const NOE::NOE_WINDOW::Monitor* handle) override;
		NOE_PLUGIN_FUNC virtual void update() override;
		NOE_PLUGIN_FUNC virtual void* getUnderlying() override;
		NOE_PLUGIN_FUNC virtual const NOE::NOE_WINDOW::Monitor* getPrimaryMonitor() override;
		NOE_PLUGIN_FUNC virtual const NOU::NOU_DAT_ALG::Vector<const NOE::NOE_WINDOW::Monitor*>& 
			getConnectedMonitors() override;
		NOE_PLUGIN_FUNC virtual const NOU::NOU_DAT_ALG::String8& getTitle() override;

		//Functions of the Initializable class
		NOE_PLUGIN_FUNC virtual const NOU::NOU_DAT_ALG::StringView8& getName() const override;
		NOE_PLUGIN_FUNC virtual NOE::NOE_CORE::Initializable::ExitCode initialize() override;
		NOE_PLUGIN_FUNC virtual void terminate() override;
	};

	/**
	\brief				The error codes that are used by the GLFWWindow class.
	*/
	class ErrorCodes
	{
	public:

		enum
		{
			/**
			\brief		Always the first element in the enum. This has only technical purposes and is not an
						actual error code.
			*/
			FIRST_ELEMENT = 5100,

			/**
			\brief		The initialization of the GLFW failed.
			*/
			GLFW_INITIALIZATION_FAILED,

			/**
			\brief		The initialization of the window failed.
			*/
			WINDOW_INITIALIZATION_FAILED,

			/**
			\brief		Always the last element in the enum. This has only technical purposes and is not an
						actual error code.
			*/
			LAST_ELEMENT
		};
	};

	/**
	\brief				The error pool that is used to provide the errors for the SQLite interfaces. 
						This is barely documented because it behaves according to the rules that are set 
						up by nostra::utils::core::ErrorPool.
	*/
	class ErrorPool : public NOU::NOU_CORE::ErrorPool
	{
		NOU::NOU_CORE::Error m_errors[ErrorCodes::LAST_ELEMENT - ErrorCodes::FIRST_ELEMENT - 1];

	public:

		ErrorPool();

		virtual const NOU::NOU_CORE::Error* queryError(NOU::NOU_CORE::ErrorPool::ErrorType id) const;
	};
}

#endif
