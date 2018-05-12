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
		using FunctionGetName = const NOU::char8*(*)();
		using FunctionStart = NOU::uint32(*)(void*);
		using FunctionStartup = void(*)();
		using FunctionShutdown = void(*)();

		static const NOU::NOU_DAT_ALG::StringView8 GET_NAME_FUNCNAME;
		static const NOU::NOU_DAT_ALG::StringView8 GET_VERSION_FUNCNAME;
		static const NOU::NOU_DAT_ALG::StringView8 START_FUNCNAME;

		static const NOU::NOU_DAT_ALG::StringView8 PLUGIN_STARTUP_FUNCNAME;
		static const NOU::NOU_DAT_ALG::StringView8 PLUGIN_SHUTDOWN_FUNCNAME;

	private:
		void *m_library;

		NOU::NOU_FILE_MNGT::Path m_path;

		NOU::NOU_DAT_ALG::Uninitialized<NOU::NOU_CORE::Version> m_version;
		NOU::NOU_DAT_ALG::Uninitialized<NOU::NOU_DAT_ALG::String8> m_name;

		FunctionStart m_startFunc;

		FunctionShutdown m_shutdownFunc;

		NOU::boolean m_alreadyExecuted;

		void unload();

	public:
		explicit EnginePlugin(const NOU::NOU_FILE_MNGT::Path &path);
		EnginePlugin(EnginePlugin && other);

		EnginePlugin(const EnginePlugin &other) = delete;

		~EnginePlugin();

		NOU::boolean load();

		const NOU::NOU_CORE::Version& getVersion() const;
		typename Plugin::InitResult initialize(NostraEngine &engineInstance);
		typename Plugin::InitResult terminate(NostraEngine &engineInstance);
		void receive(Plugin::ID source, void *data, NOU::sizeType size, NOU::uint32 flags);

		PluginMetadata getMetadata() const;
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

				COULD_NOT_LOAD_LIBRARY,
				COULD_NOT_LOAD_FUNCTION,

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

		constexpr static Plugin::ID ENGINE_ID = 0;

	private:
		NOU::NOU_FILE_MNGT::Path m_folder;
		NOU::NOU_DAT_ALG::Vector<EnginePlugin> m_plugins;

		NOU::boolean m_loadedPlugins;

		void loadPlugins();

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



		NOU::NOU_DAT_ALG::Vector<EnginePlugin>& getPlugins();
	};

	constexpr Plugin::ID PluginManager::ENGINE_ID;
}