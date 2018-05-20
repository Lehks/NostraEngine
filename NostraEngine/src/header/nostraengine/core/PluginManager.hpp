#include "nostraengine/core/StdIncludes.hpp"

#include "nostraengine/core/Plugin.hpp"
#include "nostraengine/core/NostraEngine.hpp"

namespace NOE::NOE_CORE
{
	/**
	\brief A class that represents the data that is stored in the Plugin-Configuration (.pconf) file of a 
	       single plugin.


	\details
	A class that represents the data that is stored in the Plugin-Configuration (.pconf) file of a single 
	plugin. Each loaded plugin has an instance of this class associated with it. 
	*/
	class NOU_CLASS PluginMetadata final
	{
	public:
		/**
		\brief The type of a priority of a plugin. 0 is the lowest priority and -1 (the maximum value of an
		unsigned integer) is the highest priority.
		*/
		using Priority = NOU::uint32;

		/**
		\brief The extension of a plugin shared library file.
		       
		\details
		The extension of a plugin shared library file. On a Windows system, those are actually .dll files and
		on Linux/Unix, these are actually .so files. This unified file extension has been put into place to 
		avoid having to differentiate between operating systems.
		*/
		static const NOU::NOU_DAT_ALG::StringView8 PLUGIN_FILE_EXTENSION;

		/**
		\brief The lowest possible priority of a plugin.
		*/
		static const Priority LOWEST_PRIORITY;

		/**
		\brief The highest possible priority of a plugin.
		*/
		static const Priority HIGHEST_PRIORITY;

	private:
		/**
		\brief The ID of the plugin. If the plugin does not exist, this will be EnginePlugin::INVALID_ID.
		*/
		Plugin::ID m_id;

		/**
		\brief The name of the plugin.
		*/
		NOU::NOU_DAT_ALG::String8 m_name;

		/**
		\brief The description of the plugin.
		*/
		NOU::NOU_DAT_ALG::String8 m_description;

		/**
		\brief The version of the plugin.
		*/
		NOU::NOU_CORE::Version m_version;

		/**
		\brief The version of the engine that is required by the.
		*/
		NOU::NOU_CORE::Version m_requiredVersion;

		/**
		\brief The path to the shared library file of the plugin.
		*/
		NOU::NOU_FILE_MNGT::Path m_path;

		/**
		\brief The priority of the plugin.
		*/
		Priority m_priority;

		/**
		\param config The Plugin-Configuration file.

		\brief Loads the metadata of the plugin.

		\details
		Loads the metadata of the plugin.

		If the loading was successful, getID() will return a value other than EnginePlugin::INVALID_ID and
		isValid() will return true.
		*/
		void load(const NOU::NOU_FILE_MNGT::Path &config);

	public:
		/**
		\param config The path to the configuration file of the plugin.

		\brief Constructs a new instance from the passed configuration file.
		*/
		explicit PluginMetadata(const NOU::NOU_FILE_MNGT::Path &config);

		/**
		\brief Constructs an invalid plugin. The ID will be EnginePlugin::INVALID_ID.
		*/
		PluginMetadata();

		/**
		\return The ID of the plugin that this metadata is associated with, or EnginePlugin::INVALID_ID if 
		        the plugin does not exist.

		\brief Returns the ID of the plugin that this metadata is associated with.
		*/
		Plugin::ID getID() const;

		/**
		\return The name of the plugin that this metadata is associated with.

		\brief Returns the name of the plugin that this metadata is associated with.
		*/
		const NOU::NOU_DAT_ALG::String8& getName() const;

		/**
		\return The description of the plugin that this metadata is associated with.

		\brief Returns the description of the plugin that this metadata is associated with.
		*/
		const NOU::NOU_DAT_ALG::String8& getDescription() const;

		/**
		\return The version of the plugin that this metadata is associated with.

		\brief Returns the version of the plugin that this metadata is associated with.
		*/
		const NOU::NOU_CORE::Version& getPluginVersion() const;

		/**
		\return The minimum engine version that is required for the plugin to run.

		\brief Returns the minimum engine version that is required for the plugin to run.
		*/
		const NOU::NOU_CORE::Version& getRequiredVersion() const;

		/**
		\return The path to the shared library file of the plugin that this metadata is associated with.

		\brief Returns the path to the shared library file of the plugin that this metadata is associated 
		       with.
		*/
		NOU::NOU_FILE_MNGT::Path getPath() const;

		/**
		\return The priority of the plugin that this metadata is associated with.

		\brief Returns the priority of the plugin that this metadata is associated with.
		*/
		Priority getPriority() const;

		/**
		\brief Returns whether this plugin is valid (it exists and can be loaded).

		\details
		Returns whether this plugin is valid (it exists and can be loaded). If this method returns false, 
		no other methods can called for this class (except getID(), which will return 
		EnginePlugin::INVALID_ID).
		*/
		NOU::boolean isValid() const;

		/**
		\return isValid()

		\brief The same as isValid().
		*/
		operator NOU::boolean() const;
	};

	/**
	\brief The engine-side interface of a plugin. 

	\details
	The engine-side interface of a plugin. This class is able to build up a connection to a plugin and call 
	the functions in that plugin.
	*/
	class NOU_CLASS EnginePlugin final
	{
	public:
		/**
		\brief The signature of the function "noePluginStartup" in the plugin.
		*/
		using FunctionStartup = void(*)();

		/**
		\brief The signature of the function "noePluginShutdown" in the plugin.
		*/
		using FunctionShutdown = void(*)();

		/**
		\brief The signature of the function "noePluginReceive" in the plugin.
		*/
		using FunctionReceive = void (*)(NOU::uint32 source, void *data, NOU::sizeType size, 
			NOU::uint32 flags);

		/**
		\brief The signature of the function "noePluginInitialize" in the plugin.
		*/
		using FunctionInitialize = NOU::uint32(*)(void*);

		/**
		\brief The signature of the function "noePluginTerminate" in the plugin.
		*/
		using FunctionTerminate = NOU::uint32(*)(void*);

		/**
		\brief The name of the function "noePluginStartup" in the plugin.
		*/
		static const NOU::NOU_DAT_ALG::StringView8 PLUGIN_STARTUP_FUNCNAME;

		/**
		\brief The name of the function "noePluginShutdown" in the plugin.
		*/
		static const NOU::NOU_DAT_ALG::StringView8 PLUGIN_SHUTDOWN_FUNCNAME;

		/**
		\brief The name of the function "noePluginReceive" in the plugin.
		*/
		static const NOU::NOU_DAT_ALG::StringView8 PLUGIN_RECEIVE_FUNCNAME;

		/**
		\brief The name of the function "noePluginInitialize" in the plugin.
		*/
		static const NOU::NOU_DAT_ALG::StringView8 INITIALIZE_FUNCNAME;

		/**
		\brief The name of the function "noePluginTerminate" in the plugin.
		*/
		static const NOU::NOU_DAT_ALG::StringView8 TERMINATE_FUNCNAME;

		/**
		\brief The "PluginID" of the engine.

		\details
		The "PluginID" of the engine (the engine is not actually a plugin, but it may send data to a plugin 
		using send() which requires an ID).

		This is the same as INVALID_ID. Although this is technically ambiguous, it does not present a problem
		in practice, since this constant is only used for send() and receive() operations as a source ID and
		the source can not be an invalid plugin.

		In context other then send() and receive(), this constant will signify an invalid plugin ID.
		*/
		constexpr static Plugin::ID ENGINE_ID = 0;

		/**
		\brief The ID of any invalid plugin.
		*/
		constexpr static Plugin::ID INVALID_ID = ENGINE_ID;

	private:
		/**
		\brief A pointer to the (operating system specific) dynamically loaded shared library of the plugin.
		*/
		void *m_library;

		/**
		\brief The metadata of this plugin.
		*/
		PluginMetadata m_metadata;

		/**
		\brief The pointer to noePluginInitialize() in the plugin.
		*/
		FunctionInitialize m_initializeFunc;

		/**
		\brief The pointer to noePluginTerminate() in the plugin.
		*/
		FunctionTerminate  m_terminateFunc;

		/**
		\brief The pointer to noePluginReceive() in the plugin.
		*/
		FunctionReceive  m_receiveFunc;

		/**
		\brief The pointer to noePluginShutdown() in the plugin.
		*/
		FunctionShutdown m_shutdownFunc;

	public:
		/**
		\param config The Plugin-Configuration to load the plugin from.

		\brief Constructs a new instance from the passed Plugin-Configuration file.

		\details
		Constructs a new instance from the passed Plugin-Configuration file. This constructor will only 
		load the metadata of the plugin but it does not load the shared library (this needs to be done with
		load()).
		*/
		explicit EnginePlugin(const NOU::NOU_FILE_MNGT::Path &config);

		/**
		\brief Constructs an invalid instance.

		\details
		Constructs an invalid instance. The metadata of this instance will be invalid as well and the plugin
		can never be loaded.
		*/
		EnginePlugin();

		/**
		\param other The instance to move the data from.

		\brief Moves the data from the passed instance to the one that is being constructed by this 
		       constructor.
		*/
		EnginePlugin(EnginePlugin && other);

		EnginePlugin(const EnginePlugin &other) = delete;

		/**
		\brief If the plugin is loaded, this will automatically unload it.

		\details
		If the plugin is loaded, this will automatically unload it.

		This constructor will behave like this:
		\code{.cpp}
		if(isLoaded())
			unload();
		\endcode
		*/
		~EnginePlugin();

		/**
		\brief Loads the plugin.

		\return True on success and false on failure.

		\details
		Loads the plugin.

		Loading a plugin is only possible, if \code{.cpp} getMetadata().isValid()\endcode returns true.

		Only after a successful call to this method, the methods initialize(), terminate(), receive() and
		unload() can be called.

		Generally, this method does two things:
		1. It loads the shared library file of the plugin.
		2. It calls the startup function for the plugin.

		If the loading was successful, this method will return true. If it was not successful, false will be 
		returned and an error will be pushed to the error handler. The possible error codes are:
		- PluginManager::ErrorCodes::PLUGIN_ALREADY_LOADED: The plugin was already loaded previously.
		- PluginManager::ErrorCodes::PLUGIN_NOT_EXISTING: The plugin does not exist (the metadata is not
		  valid).
		- PluginManager::ErrorCodes::COULD_NOT_LOAD_LIBRARY: The system call to load the plugin's shared 
		  library failed.
		- PluginManager::ErrorCodes::COULD_NOT_LOAD_FUNCTION: The plugin's shared library could be loaded, 
		  but a function could not be loaded.

		In the case of the error code PluginManager::ErrorCodes::COULD_NOT_LOAD_FUNCTION, it is possible that
		multiple errors are pushed to the error handler, one for each function that could not be loaded 
		(which is 5 functions at most).
		*/
		NOU::boolean load();

		/**
		\brief Unloads the plugin.

		\return True on success and false on failure.

		\details
		Unloads the plugin.

		Unloading a plugin is only possible, if it was already loaded previously.

		This method will free the plugin's shared library file.

		If the unloading was successful, this method will return true. If it was not successful, false will be
		returned and an error will be pushed to the error handler. The possible error codes are:
		- PluginManager::ErrorCodes::COULD_NOT_FREE_LIBRARY: The system call to free the plugin's shared
		  library failed.
		- PluginManager::ErrorCodes::PLUGIN_NOT_LOADED: The plugin was not loaded.
		*/
		NOU::boolean unload();

		/**
		\return True, if the plugin is loaded and false if not.

		\brief Returns whether the plugin is loaded or not.

		\details
		Returns whether the plugin is loaded or not. A plugin is loaded, if a call to load() was successful.
		*/
		NOU::boolean isLoaded() const;

		/**
		\return The value that was returned by Plugin::initialize().

		\brief Initializes the plugin by calling Plugin::initialize().

		\details
		Initializes the plugin by calling Plugin::initialize(). This function will fail (and most likely 
		crash the program) if the plugin is not loaded yet.
		*/
		typename Plugin::InitResult initialize(NostraEngine &engineInstance);

		/**
		\return The value that was returned by Plugin::terminate().

		\brief Initializes the plugin by calling Plugin::terminate().

		\details
		Initializes the plugin by calling Plugin::terminate(). This function will fail (and most likely
		crash the program) if the plugin is not loaded yet.
		*/
		typename Plugin::InitResult terminate(NostraEngine &engineInstance);

		/**
		\brief Initializes the plugin by calling Plugin::receive().

		\details
		Initializes the plugin by calling Plugin::receive(). This function will fail (and most likely
		crash the program) if the plugin is not loaded yet.

		\note
		This method is not meant to be called directly by a user.
		*/
		void receive(Plugin::ID source, void *data, NOU::sizeType size, NOU::uint32 flags);

		/**
		\return The metadata of this plugin.

		\brief Returns the metadata of this plugin.
		*/
		const PluginMetadata& getMetadata() const;
	};

	/**
	\brief A class that gives access to all plugins. 
	*/
	class NOU_CLASS PluginManager final
	{
	public:
		/**
		\brief A singleton class that contains all of the error codes that are used by the plugin system.
		*/
		class ErrorCodes
		{
		public:
			enum  Codes
			{
				/**
				\brief Not an actual error, but always the first element in the enum.
				*/
				FIRST_ELEMENT = 7000,

				/**
				\brief A plugin does either not exist, or it is set to disabled in it Plugin-Configuration.
				*/
				PLUGIN_NOT_EXISTING,

				/**
				\brief The plugin is already loaded.
				*/
				PLUGIN_ALREADY_LOADED,

				/**
				\brief The system call to load the shared library of a plugin failed.
				*/
				COULD_NOT_LOAD_LIBRARY,

				/**
				\brief The system call to load a function in the shared library of a plugin failed.
				*/
				COULD_NOT_LOAD_FUNCTION,

				/**
				\brief The plugin is not loaded.
				*/
				PLUGIN_NOT_LOADED,

				/**
				\brief The system call to free the shared library of a plugin failed.
				*/
				COULD_NOT_FREE_LIBRARY,

				/**
				\brief Not an actual error, but always the last element in the enum.
				*/
				LAST_ELEMENT
			};
		};

		/**
		\brief The error pool that provides the errors that are used by the plugin management.
		*/
		class ErrorPool : public NOU::NOU_CORE::ErrorPool
		{
		private:
			NOU::NOU_CORE::Error m_errors[ErrorCodes::LAST_ELEMENT - ErrorCodes::FIRST_ELEMENT - 1];

		public:
			ErrorPool();

			virtual const NOU::NOU_CORE::Error* queryError
										(typename NOU::NOU_CORE::ErrorHandler::ErrorType id) const override;
		};

	private:
		/**
		\brief A map that allows access to the single plugins by their ID. Not sorted.
		*/
//		NOU::NOU_DAT_ALG::HashMap<Plugin::ID, EnginePlugin> m_idIndexMap;

		/**
		\brief A list of all plugins, sorted after their priority.
		*/
		NOU::NOU_DAT_ALG::Vector<EnginePlugin*> m_sortedPlugins;

		/**
		\brief Constructs a new instance.
		*/
		explicit PluginManager();
	public:
		/**
		\brief Returns the instance of the class.
		*/
		static PluginManager& get();

		PluginManager(const PluginManager &other) = delete;
		PluginManager(PluginManager &&) = delete;

		/**
		\brief Initializes the plugin manager.

		\details
		Initializes the plugin manager. This function must be called before any of the other methods are
		usable.
		*/
		void initialize();

		/**
		\brief Terminates the plugin manager.

		\details
		Terminates the plugin manager. This function must be called before any of the other methods are 
		usable.
		*/
		void terminate();

		/**
		\param id The ID of the plugin.

		\brief Returns the instance of the plugin with the passed ID.

		\details
		Returns the instance of the plugin with the passed ID. If the ID is invalid (the plugin does not
		exist), an invalid instance will be returned. 

		To use this method, createPluginList() needs to have been called before.
		*/
		EnginePlugin& getPlugin(Plugin::ID id);

		/**
		\param recipient The ID of the plugin that should receive the message.
		\param data      A pointer to a chunk of memory that will be send to the plugin.
		\param size      The size (amount of bytes) of the memory that \p data points to.
		\param flags     An arbitrary number that might help the recipient to identify what data was send to
		                 it.

		\brief Sends the passed data to the recipient plugin.

		\details
		Sends the passed data to the recipient plugin. The sender-ID will be set to EnginePlugin::ENGINE_ID.

		To use this method, createPluginList() needs to have been called before and the recipient plugin 
		needs to be loaded.
		*/
		Plugin::SendResult send(Plugin::ID recipient, void *data, NOU::sizeType size, NOU::uint32 flags);

		/**
		\param recipient The ID of the plugin that should receive the message.
		\param recipient The ID of the plugin that send the message.
		\param data      A pointer to a chunk of memory that will be send to the plugin.
		\param size      The size (amount of bytes) of the memory that \p data points to.
		\param flags     An arbitrary number that might help the recipient to identify what data was send to
		                 it.

		\brief Sends the passed data to the recipient plugin.

		\note
		This method is not supposed to be used by a user, it is only called by other methods of the engine.
		*/
		Plugin::SendResult sendImpl(Plugin::ID recipient, Plugin::ID source, void *data, NOU::sizeType size,
			NOU::uint32 flags);

		/**
		\return True, if the method was successful, false if not.

		\brief Reads the plugins-folder and parses all of their Plugin-Configurations.

		\details
		Reads the plugins-folder and parses all of their Plugin-Configurations. This method needs to be called
		before any other of the method that access the plugins.

		\note
		This method only constructs the plugin instances - it does not load them.
		*/
		NOU::boolean createPluginList();

		/**
		\brief Returns a list of all of the plugins sorted after their priority.

		\details
		Returns a list of all of the plugins sorted after their priority.

		To use this method, createPluginList() needs to have been called before.
		*/
		NOU::NOU_DAT_ALG::Vector<EnginePlugin*>& getPlugins();
	};

	constexpr Plugin::ID EnginePlugin::ENGINE_ID;
	constexpr Plugin::ID EnginePlugin::INVALID_ID;
}