#ifndef NOE_CORE_NOSTRA_ENGINE_HPP
#define NOE_CORE_NOSTRA_ENGINE_HPP

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "nostrautils/NostraUtils.hpp"

#include "nostraengine/core/StdIncludes.hpp"
#include <iostream>

/**
\file core/NostraEngine

\author	 Dennis Franz
\author	 Leslie Marxen
\version 1.0.0
\since   1.0.0

\brief This is the main file of this engine. It contains the 3 main methods: initialize method , start method and terminate method.

\details 
Initialize-Method:	Every other "main" file , class or module needs to be initialized before used which can be done in the initialize method.
Start-Method:		In the start Method is the main loop of the engine, if there is something in the render Method it will be updated here.
Terminate-Method:	If the window gets closed , the terminate method will clean up and "terminate" every module which got initialized.
*/
namespace NOE
{
	class NOU_CLASS NostraEngine
	{
	private:
		NOU::int8 m_runState;
		/**
		\brief an ID for the Engine.
		*/
		NOU::int32 ID;

		/**
		\brief current FPS of the renderer
		*/
		NOU::uint64 m_currFPS;

		/**
		\brief the time in ms a frame took to render;
		*/
		NOU::uint32 m_frameTime;

		/**
		\brief the maximum Frames that are rendered per second. If the value is zero, the frame limiter gets disabled
		*/
		NOU::uint64 m_maxFPS;

		/**
		\brief uprates the FPS and frametime
		\param begin the begintime of the current render iteration
		\param end the end time of the current render iteration
		*/
		void updateFrameInformations(const NOU::uint32 begin, const NOU::uint32 end);

		/**
		\brief limits the fps measured by the set maxFPS
		*/
		void fpsLimitStart();

		/**
		\return		void

		\brief The Render-Method. Everything put in here will be, after each iteration of the loop in the start method, updated.
		*/
		void render();
	public:
		/**
		\brief Standard constructor for now.
		*/
		NostraEngine(NOU::int32 ID);
		/**
		/return		NOU::int8

		\brief Initialization-Method. Everything put in here will be initialized for later usage.
		*/
		NOU::int32 init();
		/**
		/return		NOU::int8

		\brief Start-Method. Holds the main loop of the engine. 
		*/
		NOU::int32 start();
		/**
		/return		NOU::int8

		\brief Terminate-Method. Everything put in here will be closed the right way if the program will be terminated.
		*/
		NOU::int32 terminate();

		/**
		\brief sets the maximum frames that are rendered per second.
		\param maXFPS sets the maximum FPS to the given value, if the value is zero, the frame limiter gets disabled
		*/
		void setMaxFPS(const NOU::uint64 maxFPS = 0);

		void terminateEngine();
		/**
		\brief getter for m_currFPS
		\return returns the current FPS
		*/
		const NOU::uint64& getCurrFPS();

		/**
		\brief getter for m_maxFPS
		\return returns the maximum set FPS
		*/
		const NOU::uint64& getMaxFPS();

		/**
		\brief getter for m_frameTime
		\return returns the current FrameTime
		*/
		const NOU::uint32& getFrameTime();

		/**
		\brief Returns the version of the engine.
		\return NOU::NOU_CORE::Version Type
		*/
		const NOU::NOU_DAT_ALG::String8 & getVersion();

		/**
		\brief Returns the window pointer
		\return NOU::NOU_WINDOW::Window* (window pointer)
		*/
		NOE::NOE_WINDOW::Window* getWindowPointer();

		/**
		\brief Set's the pointer for the window

		\param ptr_window		the new window pointer.
		*/
		void setWindowPointer(NOE::NOE_WINDOW::Window* ptr_window);
	};
}

#endif