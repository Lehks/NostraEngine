#ifndef NOSTRA_ENGINE_HPP
#define NOSTRA_ENGINE_HPP

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
	class NostraEngine
	{
	private:
		/**
		\brief an ID for the Engine.
		*/
		NOU::int32 ID;
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
		NOU::int8 init();
		/**
		/return		NOU::int8

		\brief Start-Method. Holds the main loop of the engine. 
		*/
		NOU::int8 start();
		/**
		/return		NOU::int8

		\brief Terminate-Method. Everything put in here will be closed the right way if the program will be terminated.
		*/
		NOU::int8 terminate();
	};
}

#endif

