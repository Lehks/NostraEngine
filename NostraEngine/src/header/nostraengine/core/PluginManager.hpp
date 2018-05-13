#include "nostraengine/core/StdIncludes.hpp"

#include "nostraengine/core/NostraEngine.hpp"
#include "nostraengine/core/Plugin.hpp"

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

		NOU::boolean load();

		NOU::boolean unload();

		NOU::boolean isLoaded();

		typename Plugin::InitResult initialize(NostraEngine &engineInstance);
		typename Plugin::InitResult terminate(NostraEngine &engineInstance);
		void receive(Plugin::ID source, void *data, NOU::sizeType size, NOU::uint32 flags);

		/**
		\return The metadata of this plugin.

		\brief Returns the metadata of this plugin.
		*/
		const PluginMetadata& getMetadata() const;
	};

	class NOU_CLASS PluginManager final
	{
	public:
		class ErrorCodes
		{
		public:
			enum  Codes
			{
				FIRST_ELEMENT = 7000,

				PLUGIN_NOT_EXISTING,
				PLUGIN_ALREADY_LOADED,
				COULD_NOT_LOAD_LIBRARY,
				COULD_NOT_LOAD_FUNCTION,
				PLUGIN_NOT_LOADED,
				COULD_NOT_FREE_LIBRARY,

				LAST_ELEMENT
			};
		};

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
		NOU::NOU_DAT_ALG::HashMap<Plugin::ID, EnginePlugin> m_idIndexMap;

		explicit PluginManager();
	public:

		static PluginManager& get();

		PluginManager(const PluginManager &other) = delete;
		PluginManager(PluginManager &&) = delete;

		void initialize();
		void terminate();

		PluginMetadata getPluginMetdata(Plugin::ID id);
		EnginePlugin& getPlugin(Plugin::ID id);

		Plugin::SendResult send(Plugin::ID recipient, Plugin::ID source, void *data, NOU::sizeType size, 
			NOU::uint32 flags);

		NOU::boolean loadPlugins();

		NOU::NOU_DAT_ALG::Vector<EnginePlugin>& getPlugins();
	};

	constexpr Plugin::ID EnginePlugin::ENGINE_ID;
	constexpr Plugin::ID EnginePlugin::INVALID_ID;
}