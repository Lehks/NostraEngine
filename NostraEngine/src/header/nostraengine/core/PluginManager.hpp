#include "nostraengine/core/StdIncludes.hpp"

#include "nostraengine/core/NostraEngine.hpp"
#include "nostraengine/core/Plugin.hpp"

namespace NOE::NOE_CORE
{
	/**
	\brief A class that allows access to the data of a single plugin in the plugin database.
	*/
	class NOU_CLASS PluginMetadata final
	{
	public:
		/**
		\brief The type of a priority of a plugin. 0 is the lowest priority and -1 (the maximum value of an
		unsigned integer) is the highest priority.
		*/
		using Priority = NOU::uint32;

		static const NOU::NOU_DAT_ALG::StringView8 PLUGIN_FILE_EXTENSION;
		static const Priority LOWEST_PRIORITY;
		static const Priority HIGHEST_PRIORITY;

	private:
		/**
		\brief The ID of the plugin. If the plugin does not exist, this will be EnginePlugin::INVALID_ID.
		*/
		Plugin::ID m_id;

		NOU::NOU_DAT_ALG::String8 m_name;
		NOU::NOU_DAT_ALG::String8 m_description;
		NOU::NOU_CORE::Version m_version;
		NOU::NOU_FILE_MNGT::Path m_path;
		Priority m_priority;

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
		const NOU::NOU_CORE::Version& getVersion() const;

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

	class NOU_CLASS EnginePlugin final
	{
	public:
		using FunctionStartup = void(*)();
		using FunctionShutdown = void(*)();
		using FunctionReceive = void (*)(NOU::uint32 source, void *data, NOU::sizeType size, 
			NOU::uint32 flags);

		using FunctionInitialize = NOU::uint32(*)(void*);
		using FunctionTerminate = NOU::uint32(*)(void*);

		static const NOU::NOU_DAT_ALG::StringView8 PLUGIN_STARTUP_FUNCNAME;
		static const NOU::NOU_DAT_ALG::StringView8 PLUGIN_SHUTDOWN_FUNCNAME;
		static const NOU::NOU_DAT_ALG::StringView8 PLUGIN_RECEIVE_FUNCNAME;

		static const NOU::NOU_DAT_ALG::StringView8 INITIALIZE_FUNCNAME;
		static const NOU::NOU_DAT_ALG::StringView8 TERMINATE_FUNCNAME;

		constexpr static Plugin::ID ENGINE_ID = 0;
		constexpr static Plugin::ID INVALID_ID = ENGINE_ID;

	private:
		void *m_library;

		PluginMetadata m_metadata;

		FunctionInitialize m_initializeFunc;
		FunctionTerminate  m_terminateFunc;
		FunctionReceive  m_receiveFunc;

		FunctionShutdown m_shutdownFunc;

	public:
		explicit EnginePlugin(const NOU::NOU_FILE_MNGT::Path &config);
		EnginePlugin();
		EnginePlugin(EnginePlugin && other);

		EnginePlugin(const EnginePlugin &other) = delete;

		~EnginePlugin();

		NOU::boolean load();

		NOU::boolean unload();

		NOU::boolean isLoaded();

		typename Plugin::InitResult initialize(NostraEngine &engineInstance);
		typename Plugin::InitResult terminate(NostraEngine &engineInstance);
		void receive(Plugin::ID source, void *data, NOU::sizeType size, NOU::uint32 flags);

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