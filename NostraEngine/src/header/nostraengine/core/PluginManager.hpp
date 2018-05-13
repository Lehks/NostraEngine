#include "nostraengine/core/StdIncludes.hpp"

#include "nostraengine/core/NostraEngine.hpp"
#include "nostraengine/core/Plugin.hpp"

namespace NOE::NOE_CORE
{
	class NOU_CLASS PluginMetadata final
	{
	public:
		using Priority = NOU::uint32;

	private:
		Plugin::ID m_id;

	public:
		PluginMetadata(Plugin::ID id);

		Plugin::ID getId() const;
		NOU::NOU_DAT_ALG::String8 getName() const;
		NOU::NOU_DAT_ALG::String8 getDescription() const;
		NOU::NOU_FILE_MNGT::Path getPath() const;
		Priority getPriority() const;
		NOU::boolean isValid() const;
	};

	class NOU_CLASS EnginePlugin final
	{
	public:
		using FunctionGetVersion = NOU::uint32(*)();

		using FunctionStartup = void(*)();
		using FunctionShutdown = void(*)();
		using FunctionReceive = void (*)(NOU::uint32 source, void *data, NOU::sizeType size, 
			NOU::uint32 flags);

		using FunctionInitialize = NOU::uint32(*)(void*);
		using FunctionTerminate = NOU::uint32(*)(void*);

		static const NOU::NOU_DAT_ALG::StringView8 GET_VERSION_FUNCNAME;

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

		NOU::NOU_DAT_ALG::Uninitialized<NOU::NOU_CORE::Version> m_version;

		FunctionInitialize m_initializeFunc;
		FunctionTerminate  m_terminateFunc;
		FunctionReceive  m_receiveFunc;

		FunctionShutdown m_shutdownFunc;

	public:
		explicit EnginePlugin(Plugin::ID id = INVALID_ID);
		EnginePlugin(EnginePlugin && other);

		EnginePlugin(const EnginePlugin &other) = delete;

		~EnginePlugin();

		NOU::boolean load();

		NOU::boolean unload();

		NOU::boolean isLoaded();

		const NOU::NOU_CORE::Version& getVersion() const;

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
				FIRST_ELEMENT = 6000,

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
		NOU::NOU_DAT_ALG::Vector<EnginePlugin> m_plugins;

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