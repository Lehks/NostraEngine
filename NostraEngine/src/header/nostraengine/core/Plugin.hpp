#ifndef NOE_CORE_PLUGIN_HPP
#define NOE_CORE_PLUGIN_HPP

#include "nostraengine/core/StdIncludes.hpp"
#include "nostraengine/core/NostraEngine.hpp"

/**
\file    core/Plugin.hpp
\author  Lukas Reichmann
\version 1.0.0
\since   0.0.1

\brief A file that contains the plugin-side interface of the plugin system.
*/

#ifndef NOE_SET_AS_ACTIVE_PLUGIN_CLASS

/**
\param PLUGIN The (fully qualified) name of the plugin class.

\brief A macro that needs to be placed under the declaration of the plugin class (and outside of any 
namespace) of every plugin.

\details
A macro that needs to be placed somewhere under the declaration of the plugin class of every plugin.

This macro defines the global functions that will be loaded by the plugin manager in the engine.
*/
#define NOE_SET_AS_ACTIVE_PLUGIN_CLASS(PLUGIN)															   \
																										   \
/*startup*/																								   \
																										   \
PLUGIN *pluginPtr;																						   \
																										   \
extern "C" NOE_PLUGIN_FUNC void noePluginStartup(NOU::uint32 id)										   \
{																										   \
    pluginPtr = new PLUGIN();															   				   \
																										   \
	pluginPtr->setID(id);															   					   \
}																										   \
																										   \
/*shutdown*/																							   \
extern "C" NOE_PLUGIN_FUNC void noePluginShutdown()														   \
{																										   \
	delete pluginPtr;																   					   \
}																										   \
																										   \
/*receive*/																								   \
extern "C" void noePluginReceive(NOU::uint32 source, void *data, NOU::sizeType size,					   \
	NOU::uint32 flags)																					   \
{																										   \
	pluginPtr->receive(source, data, size, flags);									   					   \
}																										   \
																										   \
/*initialize*/																							   \
extern "C" NOE_PLUGIN_FUNC NOU::uint32 noePluginInitialize(void * engineInstance)						   \
{																										   \
	NOE::NOE_CORE::NostraEngine *engine = 															       \
		reinterpret_cast<NOE::NOE_CORE::NostraEngine*>(engineInstance);                                    \
																										   \
	NOE::NOE_CORE::Plugin::InitResult result = pluginPtr->initialize(*engine);		   					   \
																										   \
	return NOU::uint32(result);																			   \
}																										   \
																										   \
/*terminate*/																							   \
extern "C" NOE_PLUGIN_FUNC NOU::uint32 noePluginTerminate(void *engineInstance)							   \
{																										   \
	NOE::NOE_CORE::NostraEngine *engine = 															       \
		reinterpret_cast<NOE::NOE_CORE::NostraEngine*>(engineInstance);                                    \
																										   \
	NOE::NOE_CORE::Plugin::InitResult result = pluginPtr->terminate(*engine);		   					   \
																										   \
	return NOU::uint32(result);																			   \
}

#endif

/**
\param id The ID of the plugin.

\brief Constructs a new instance of the user defined plugin class and sets that instance as active instance.

\details
Constructs a new instance of the user defined plugin class and sets that instance as active instance. This is 
one of the functions that will be defined by NOE_SET_AS_ACTIVE_PLUGIN_CLASS.
*/
extern "C" NOE_PLUGIN_FUNC void noePluginStartup(NOU::uint32 id);

/**
\brief Deletes the instance of the user defined plugin class.

\details
Deletes the instance of the user defined plugin class. This is one of the functions that will be defined by
NOE_SET_AS_ACTIVE_PLUGIN_CLASS.
*/
extern "C" NOE_PLUGIN_FUNC void noePluginShutdown();

/**
\param source The ID of the source plugin.
\param data   The data to receive.
\param size   The size of \p data.
\param flags  Arbitrary flags.

\brief The interface function for Plugin::receive().

\details
The interface function for Plugin::receive(). This is one of the functions that will be defined by
NOE_SET_AS_ACTIVE_PLUGIN_CLASS.
*/
extern "C" NOE_PLUGIN_FUNC void noePluginReceive(NOU::uint32 source, void *data, NOU::sizeType size,
	NOU::uint32 flags);

/**
\param engineInstance A pointer to the instance of the engine.

\return A value from InitResult cast to uint32.

\brief The interface function for Plugin::initialize().

\details
The interface function for Plugin::initialize(). This is one of the functions that will be defined by
NOE_SET_AS_ACTIVE_PLUGIN_CLASS.
*/
extern "C" NOE_PLUGIN_FUNC NOU::uint32 noePluginInitialize(void *engineInstance);

/**
\param engineInstance A pointer to the instance of the engine.

\return A value from InitResult cast to uint32.

\brief The interface function for Plugin::terminate().

\details
The interface function for Plugin::terminate(). This is one of the functions that will be defined by
NOE_SET_AS_ACTIVE_PLUGIN_CLASS.
*/
extern "C" NOE_PLUGIN_FUNC NOU::uint32 noePluginTerminate(void *engineInstance);

namespace NOE::NOE_CORE
{
	/**
	\brief The plugin-side interface of a plugin.

	\details
	The plugin-side interface of a plugin. Every plugin needs to have a single class that inherits from this 
	one to be able to be loaded as a plugin.
	*/
	class Plugin
	{
	public:
		/**
		\brief The type of a plugin ID.
		*/
		using ID = NOU::uint32;

		/**
		\brief The error codes that can be returned by either initialize() or terminate().
		*/
		enum class InitResult : NOU::uint32
		{
			/**
			\brief The initialization or termination was successful.
			*/
			SUCCESS = 0,

			/**
			\brief The initialization was successful, but some, minor and fixable, errors occurred.
			*/
			WARNING = 1,

			/**
			\brief The initialization or termination failed.
			*/
			FAILED = 2
		};

		/**
		\brief The error codes that can occur when sending data from one plugin to another.
		*/
		enum class SendResult : NOU::uint32
		{
			/**
			\brief The sending was successful.
			*/
			SUCCESS = 0,

			/**
			\brief The recipient plugin was not found.
			*/
			PLUGIN_NOT_FOUND = 1,

			/**
			\brief The recipient ID is the same as the sender ID, or it is the same as 
			       EnginePlugin::ENGINE_ID.
			*/
			INVALID_RECIPIENT = 2
		};

	private:
		//for setID()
		friend void ::noePluginStartup(NOU::uint32);

		/**
		\brief The ID of this plugin.
		*/
		ID m_id;

		/**
		\param id The new value for m_id.

		\brief Sets m_id.
		*/
		NOE_FUNC void setID(ID id);

	public:
		Plugin() = default;
		virtual ~Plugin() = default;

		Plugin(const Plugin &other) = delete;
		Plugin(Plugin &&) = delete;

		/**
		\return SendResult::SUCCESS on success, or an other error code when the sending of data failed.

		\brief Sends data to the plugin with the ID \p recipient.

		\details
		Sends data to the plugin with the ID \p recipient.

		The intended usage is as follows: 
		To send any data, \p data should be used. 
		- \p size should be set to the size of the memory that \p data points to (in bytes).
		- \p flags can be used to send additional data that might give a hint on what kind of data \p data 
		  points to.
		*/
		NOE_FUNC SendResult send(ID recipient, void *data, NOU::sizeType size, NOU::uint32 flags);

		/**
		\return The ID of this plugin.

		\brief Returns the ID of this plugin.
		*/
		NOE_FUNC ID getID() const;

		/**
		\return A literal from the InitResult enum, see detailed section for more information.

		\brief Initializes the plugin.

		\details
		Initializes the plugin. This method will be called by the Engine in the pre-init phase.

		The resulting return value may be:
		- InitResult::SUCCESS: The initialization was completed with no errors whatsoever.
		- InitResult::WARNING: Some errors happened during the initialization, but they could be fixed and the 
		                       plugin is still able to work as intended.
		- InitResult::FAILED:  The initialization failed and the plugin is not usable. This will cause the 
		                       engine to exit.
		*/
		virtual InitResult initialize(NostraEngine &engineInstance) = 0;

		/**
		\return A literal from the InitResult enum, see detailed section for more information.

		\brief Terminates the plugin.

		\details
		Terminates the plugin. This method will be called by the Engine in the post-terminate phase.

		The resulting return value may be:
		- InitResult::SUCCESS: The termination was completed with no errors whatsoever.
		- InitResult::WARNING: Some errors happened during the termination, but they could be fixed and the 
		                       plugin is mostly still able to work as intended.
		- InitResult::FAILED:  The termination failed and the plugin is not usable. This will cause the engine
		                       to exit.
		*/
		virtual InitResult terminate(NostraEngine &engineInstance) = 0;

		/**
		\param source The ID of the source (see detailed section for further information).
		\param data   The data that was send by the sender.
		\param size   The size of \p data.
		\param flags  Some arbitrary flags that are set by the sender.
		
		\brief Receives data from another plugin or the engine.

		\details
		Receives data from another plugin or the engine. This is the counterpart to Plugin::send(). Any data 
		that was send using that method, will be received by this method.

		See documentation of Plugin::send() for further information on what data the parameters are supposed 
		to represent.
		
		The source ID (parameter \p source) is either the ID of the plugin that has send the message, or it is
		EnginePlugin::ENGINE_ID. In that case, the data has been send using PluginManager::send().
		*/
		virtual void receive(ID source, void *data, NOU::sizeType size, NOU::uint32 flags) = 0;
	};
}

#endif