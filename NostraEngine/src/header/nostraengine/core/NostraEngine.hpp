#ifndef NOSTRA_ENGINE_HPP
#define NOSTRA_ENGINE_HPP

#include "nostrautils/NostraUtils.hpp"

#include "nostraengine/core/StdIncludes.hpp"
#include <iostream>

#include "nostraengine/core/Initializable.hpp"
#include "nostraengine/core/Updatable.hpp"

/**
\file core/NostraEngine

\author	 Dennis Franz
\author	 Leslie Marxen
\version 1.0.0
\since   1.0.0

\brief This is the main file of this engine. It contains the 3 main methods: initialize method , start method and terminate method.
	   The Engine itself is implemented as Singelton.

\details 
Initialize-Method:	Every other "main" file , class or module needs to be initialized before used which can be done in the initialize method.
Start-Method:		In the start Method is the main loop of the engine, if there is something in the render Method it will be updated here.
Terminate-Method:	If the window gets closed , the terminate method will clean up and "terminate" every module which got initialized.
*/
namespace NOE::NOE_CORE
{
	class NOU_CLASS NostraEngine
	{
		// Dependencies
		friend class Initializable;
		friend class Updatable;

	private:
		/**
		\brief the only instance of the Engine, nullptr if no instance is yet activated
		*/
		static NostraEngine *s_instance;

		/**
		\brief the count of instances that are currently in use
		*/
		static NOU::uint8 s_instanceCount;

		/**
		\brief A logger for writing strings in files / at the console.
		*/
		NOU::NOU_CORE::Logger *m_logger;

        /**
        \brief Integer to see of the engine is running (-1 == terminate engine for now (version 0.0.0))
        */
		NOU::int8 m_runState;

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
		\brief A vector containing all object that have to be initialized before the actual main loop
		*/
		NOU::NOU_DAT_ALG::Vector<NOE::NOE_CORE::Initializable*> m_initializables;

		/**
		\brief A vector containing all objects that have to be updated every logic frame
		*/
		NOU::NOU_DAT_ALG::Vector<NOE::NOE_CORE::Updatable*> m_updatables;

        /**
        \brief The current version of the Engine.
        */
		NOU::NOU_CORE::Version m_version;

		/**
		\brief Counts how many Initializables were initialized without Errors
		*/
		NOU::sizeType m_initializedObjects;

		/**
		\brief Coutns how many Initializables were pre initialized without Errors
		*/
		NOU::sizeType m_preInitializedObjects;

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
		\return an eventual errorcode if something fails while pre Initialising
		\brief Initialiation-Methode that runs directly before the initializing stage
		*/
		ExitCode preInitialize();

		/**
		\return	an eventual errorcode if something fails while initializing

		\brief Initialization-Method. Everything put in here will be initialized for later usage.
		*/
		ExitCode initialize();


		/**
		\return an eventual errorcode if something fails while postInitialising
		\brief Initialiation-Methode that runs directly after the initializing stage
		*/
		ExitCode postInitialize();


		/**
		\return		NOU::int32

		\brief Terminate-Method. Everything put in here will be closed the right way if the program will be terminated.
		*/
		ExitCode terminate();

		/**
		\return		NOU::int32

		\brief post Terminate-Method. Every pulgin put in here will be closed the right way if the program will be terminated.
		*/
		ExitCode postTerminate();

		/**
		\brief Standard constructor for now.
		*/
		NostraEngine();

		/**
		\brief Manages the run of both Mainloops.
		*/
		void mainLoop();

		/**
		\brief gamelogic frames will be executed in here
		*/
		void logicMain();

		/**
		\brief every render frame will be processed in here;
		*/
		void renderMain();

		/**
		\brief Adds a Class that has to be initialized to the queue
		\param init The class that will be added to the queue
		\return true if successfull, false if not
		*/
		NOU::boolean addInitializable(NOE::NOE_CORE::Initializable *init);

		/**
		\brief removes a Class that has to be initialized from the queue
		\param init The class that will be removed from the queue
		\return true if successfull, false if not
		*/
		NOU::boolean removeInitializable(NOE::NOE_CORE::Initializable *init);

		/**
		\brief Adds a Class that has to be updated to the queue
		\param updt The class that will be added to the queue
		\return true if successfull, false if not
		*/
		NOU::boolean addUpdatable(NOE::NOE_CORE::Updatable *updt);

		/**
		\brief Removes a Class that has to be updated from the queue
		\param updt The class that will be removed from the queue
		\return true if successfull, false if not
		*/
		NOU::boolean removeUpdatable(NOE::NOE_CORE::Updatable *updt);

	public:

		
		/**
		\return		NOU::int8
		\brief Start-Method. Holds the main loop of the engine. 
		*/
		NOU::int32 start();

		/**
		\brief creates an instance of the engine but only once
		\return a pointer to the instance of the engine or nullptr if it has been created once
		*/
		static NostraEngine *createInstance();

		/**
		\brief Returns a reference to the isntance
		\return a reference to the instance
		*/
		static NostraEngine &get();

		/**
		\brief sets an instance of the Engine as the current active instance
		\param instacne the instance that will be set as active
		*/
		static void setActiveInstance(NostraEngine &instance);

		/**
		\brief Terminates the engine if this method is called.
		*/
		void terminateEngine();

		/**
		\brief calls the update Method of each updatable
		\return true on success, false if not
		*/
		void updateUpdatables();

		/**
		\brief sets the maximum frames that are rendered per second.
		\param maXFPS sets the maximum FPS to the given value, if the value is zero, the frame limiter gets disabled
		*/
		void setMaxFPS(const NOU::uint64 maxFPS = 0);

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
	};
}

#endif