#ifndef NOE_WINDOW_GLFWWINDOW_HPP
#define NOE_WINDOW_GLFWWINDOW_HPP

#include "nostrautils/NostraUtils.hpp"

#include "nostraengine/core/StdIncludes.hpp"
#include "nostraengine/core/Initializable.hpp"

#include "nostraengine/window/Window.hpp"
#include "GLFWMonitor.hpp"

#define NOE_PLUGIN_CLASS __declspec(dllexport)

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
	class NOE_PLUGIN_CLASS GLFWWindow final : public NOE::NOE_WINDOW::Window, public NOE::NOE_CORE::Initializable
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

		const NOU::NOU_DAT_ALG::StringView8 CLASS_NAME = "GLFWWindow";

	public:

		/**
		\brief			Checks if the instance counter is 0, increases the counter and initializes GLFW.
		*/
		GLFWWindow();

		/**
		\brief			Decreases the instance counter and terminates GLFW.
		*/
		virtual ~GLFWWindow();
		virtual void createWindow(NOU::sizeType width = 500, NOU::sizeType height = 500,
			const NOU::NOU_DAT_ALG::String8& title = "Window Name",
			const NOE::NOE_WINDOW::Monitor* monitor = nullptr) override;
		virtual void setTitle(const NOU::NOU_DAT_ALG::String8& title) override;
		virtual void setSize(NOU::sizeType width, NOU::sizeType height) override;
		virtual void setPosition(NOU::sizeType xpos, NOU::sizeType ypos) override;
		virtual void closeWindow() override;
		virtual void minimize() override;
		virtual void maximize()	override;
		virtual void makeWindowed(NOU::sizeType xpos = 50, NOU::sizeType ypos = 50, 
			NOU::sizeType width = 480, NOU::sizeType height = 480, NOU::sizeType refreshRate = 60) override;
		virtual void setFullscreen(const NOE::NOE_WINDOW::Monitor* handle) override;
		virtual void update() override;
		virtual void* getUnderlying() override;
		virtual const NOE::NOE_WINDOW::Monitor* getPrimaryMonitor() override;
		virtual const NOU::NOU_DAT_ALG::Vector<const NOE::NOE_WINDOW::Monitor*>& 
			getConnectedMonitors() override;
		virtual const NOU::NOU_DAT_ALG::String8& getTitle() override;

		//Functions of the Initializable class
		virtual const NOU::NOU_DAT_ALG::StringView8& getName() const override;
		virtual NOE::NOE_CORE::Initializable::ExitCode initialize() override;
		virtual void terminate() override;
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
