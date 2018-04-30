#ifndef NOE_WINDOW_GLFWWINDOW_HPP
#define NOE_WINDOW_GLFWWINDOW_HPP
#define GLAD_GLAPI_EXPORT //needed for exporting glad

#include "GLAD/glad.h"
#include "GLFW/glfw3.h"

#include "nostrautils/NostraUtils.hpp"

#include "nostraengine/core/StdIncludes.hpp"

#include "nostraengine/window/Window.hpp"
#include "nostraengine/window/GLFWMonitor.hpp"

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
	\brief				A class that implements the provided functions of the Window class. The
						behavior of all functions is defined in the Window class.
	*/
	class NOU_CLASS GLFWWindow : public Window
	{
	private:

		/**
		\brief			The handle of the window.
		*/
		GLFWwindow* m_window;

		/**
		\brief			Stores the title of the window.
		*/
		NOU::NOU_DAT_ALG::String8 m_title;

		/**
		\brief			The count of monitors connected.
		*/
		NOU::sizeType m_monitorCount;

		/**
		\brief			Stores the count of GLFW instances.
		*/
		static NOU::sizeType s_instanceCounter;

		/**
		\brief			An object of the GLFWMonitor class.
		*/
		NOE::NOE_WINDOW::GLFWMonitor m_monitor;
	public:

		/**
		\brief			Checks if the instance counter is 0, increases the counter and initializes GLFW.
		*/
		GLFWWindow();

		/**
		\brief			Decreases the instance counter and terminates GLFW.
		*/
		virtual ~GLFWWindow();
		virtual void createWindow(NOU::sizeType width, NOU::sizeType height,
			const NOU::NOU_DAT_ALG::String8& title, Monitor* monitor = nullptr) override;
		virtual void setTitle(const NOU::NOU_DAT_ALG::String8& title) override;
		virtual void setSize(NOU::sizeType width, NOU::sizeType height) override;
		virtual void setPosition(NOU::sizeType xpos, NOU::sizeType ypos) override;
		virtual void closeWindow() override;
		virtual void minimize() override;
		virtual void maximize()	override;
		virtual void makeWindowed()	override;
		virtual void setFullscreen(NOU::boolean state) override;
		virtual void update() override;
		virtual void* getUnderlying() override;
		virtual Monitor* getPrimaryMonitor() override;
		virtual NOU::NOU_DAT_ALG::Vector<Monitor*> getMonitors() override;
		virtual NOU::sizeType getMonitorCount() override;
		virtual const NOU::NOU_DAT_ALG::String8& getTitle() override;

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
			FIRST_ELEMENT = 6000,

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
