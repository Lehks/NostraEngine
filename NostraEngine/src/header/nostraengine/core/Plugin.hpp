#ifndef NOE_CORE_PLUGIN_HPP
#define NOE_CORE_PLUGIN_HPP

#include "nostraengine/core/StdIncludes.hpp"
#include "nostraengine/core/NostraEngine.hpp"

#ifndef NOE_SET_AS_ACTIVE_PLUGIN_CLASS

#define NOE_SET_AS_ACTIVE_PLUGIN_CLASS(PLUGIN)															   \
																										   \
/*version*/																								   \
extern "C" NOU_FUNC NOU::uint32 noePluginGetVersion()													   \
{																										   \
	return NOE::NOE_CORE::Plugin::get()->getVersion().getRaw();											   \
}																										   \
																										   \
/*startup*/																								   \
extern "C" NOU_FUNC void noePluginStartup(NOU::uint32 id)												   \
{																										   \
	NOE::NOE_CORE::Plugin::set(new PLUGIN());															   \
																										   \
	NOE::NOE_CORE::Plugin::get()->setID(id);															   \
}																										   \
																										   \
/*shutdown*/																							   \
extern "C" NOU_FUNC void noePluginShutdown()															   \
{																										   \
	delete NOE::NOE_CORE::Plugin::get();																   \
}																										   \
																										   \
/*receive*/																								   \
extern "C" void noePluginReceive(NOU::uint32 source, void *data, NOU::sizeType size,					   \
	NOU::uint32 flags)																					   \
{																										   \
	NOE::NOE_CORE::Plugin::get()->receive(source, data, size, flags);									   \
}																										   \
																										   \
/*initialize*/																							   \
extern "C" NOU_FUNC NOU::uint32 noePluginInitialize(void * engineInstance)								   \
{																										   \
	NOE::NostraEngine *engine = reinterpret_cast<NOE::NostraEngine*>(engineInstance);					   \
																										   \
	NOE::NOE_CORE::Plugin::InitResult result = NOE::NOE_CORE::Plugin::get()->initialize(*engine);		   \
																										   \
	return NOU::uint32(result);																			   \
}																										   \
																										   \
/*terminate*/																							   \
extern "C" NOU_FUNC NOU::uint32 noePluginTerminate(void *engineInstance)								   \
{																										   \
	NOE::NostraEngine *engine = reinterpret_cast<NOE::NostraEngine*>(engineInstance);					   \
																										   \
	NOE::NOE_CORE::Plugin::InitResult result = NOE::NOE_CORE::Plugin::get()->terminate(*engine);		   \
																										   \
	return NOU::uint32(result);																			   \
}

#endif

extern "C" NOU_FUNC NOU::uint32 noePluginGetVersion();

extern "C" NOU_FUNC void noePluginStartup(NOU::uint32 id);
extern "C" NOU_FUNC void noePluginShutdown();
extern "C" NOU_FUNC void noePluginReceive();

extern "C" NOU_FUNC NOU::uint32 noePluginInitialize(void *engineInstance);
extern "C" NOU_FUNC NOU::uint32 noePluginTerminate(void *engineInstance);

namespace NOE::NOE_CORE
{
	/**
	\brief The plugin-side interface of a plugin.

	\details
	The plugin-side interface of a plugin. Every plugin needs to have a single class that inherits from this one to
	be able to be loaded as a plugin.
	*/
	class NOU_CLASS Plugin
	{
	public:
		/**
		\brief The type of a plugin ID.
		*/
		using ID = NOU::uint32;

		/**
		\brief The error codes that can be returned bei either initialize() or terminate().
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
		enum class SendResult
		{
			/**
			\brief The sending was successful.
			*/
			SUCCESS = 0,

			/**
			\brief The recipient plugin was not found.
			*/
			PLUGIN_NOT_FOUND,

			/**
			\brief The recipient ID is the same as the sender ID, or it is the same as EnginePlugin::ENGINE_ID.
			*/
			INVALID_RECIPIENT
		};

	private:
		//for setID()
		friend void ::noePluginStartup(NOU::uint32);

		/**
		\brief A pointer to the instance that was set by NOE_SET_AS_ACTIVE_PLUGIN_CLASS.
		*/
		static Plugin *s_plugin;

		/**
		\brief The ID of this plugin.
		*/
		ID m_id;

		/**
		\param id The new value for m_id.

		\brief Sets m_id.
		*/
		void setID(ID id);

	public:
		/**
		\param plugin A pointer to the plugin that should be active.

		\brief Sets the currently active plugin.

		\note
		This method is only supposed to be called by the plugin management system and not by a user.
		*/
		static void set(Plugin *plugin);

		/**
		\return The currently active plugin.

		\brief Returns the plugin that is currently active.
		*/
		static Plugin* get();

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
		\p size should be set to the size of the memory that \p data points to (in bytes).
		\p flags can be used to send additional data that might give a hint on what kind of data \p data points to.
		*/
		SendResult send(ID recipient, void *data, NOU::sizeType size, NOU::uint32 flags);

		/**
		\return The ID of this plugin.

		\brief Returns the ID of this plugin.
		*/
		ID getID() const;

		/**
		\return A literal from the InitResult enum, see detailed section for more information.

		\brief Initializes the plugin.

		\details
		Initializes the plugin. This method will be called by the Engine in the pre-init phase.

		The resulting return value may be:
		- InitResult::SUCCESS: The initialization was completed with no errors whatsoever.
		- InitResult::WARNING: Some errors happened during the initialization, but they could be fixed and the plugin 
		                       is mostly still able to work as intended.
		- InitResult::FAILED:  The initialization failed and the plugin is not usable. This will cause the engine to 
		                       exit.
		*/
		virtual InitResult initialize(NostraEngine &engineInstance) = 0;

		/**
		\return A literal from the InitResult enum, see detailed section for more information.

		\brief Terminates the plugin.

		\details
		Terminates the plugin. This method will be called by the Engine in the post-terminate phase.

		The resulting return value may be:
		- InitResult::SUCCESS: The termination was completed with no errors whatsoever.
		- InitResult::WARNING: Some errors happened during the termination, but they could be fixed and the plugin
		is mostly still able to work as intended.
		- InitResult::FAILED:  The termination failed and the plugin is not usable. This will cause the engine to
		exit.
		*/
		virtual InitResult terminate(NostraEngine &engineInstance) = 0;

		/**
		\param source The ID of the source (see detailed section for further information).
		\param data   The data that was send by the sender.
		\param size   The size of \p data.
		\param flags  Some arbitrary flags that are set by the sender.
		
		\brief Receives data from another plugin or the engine.

		\details
		Receives data from another plugin or the engine. This is the counterpart to Plugin::send(). Any data that was
		send using that method, will be received by this method.

		See documentation of Plugin::send() for further information on what data the parameters are supposed to 
		
		The source ID (parameter \p source) is either the ID of the plugin that has send the message, or it is
		EnginePlugin::ENGINE_ID. In that case, the data has been send using PluginManager::send().
		*/
		virtual void receive(ID source, void *data, NOU::sizeType size, NOU::uint32 flags) = 0;
	};
}

#endif