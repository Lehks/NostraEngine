#include "nostraengine/core/StdIncludes.hpp"

#include "nostraengine/core/NostraEngine.hpp"
#include "nostraengine/core/Plugin.hpp"

namespace NOE::NOE_CORE
{
	class NOU_CLASS EnginePlugin
	{
	public:
		using FunctionGetVersion = NOU::uint32(*)();
		using FunctionGetName = const NOU::char8*(*)();
		using FunctionStart = NOU::uint32(*)(void*);

		static const NOU::NOU_DAT_ALG::StringView8 GET_NAME_FUNCNAME;
		static const NOU::NOU_DAT_ALG::StringView8 GET_VERSION_FUNCNAME;
		static const NOU::NOU_DAT_ALG::StringView8 START_FUNCNAME;

	private:
		void *m_library;

		NOU::NOU_FILE_MNGT::Path m_path;

		NOU::NOU_DAT_ALG::Uninitialized<NOU::NOU_CORE::Version> m_version;
		NOU::NOU_DAT_ALG::Uninitialized<NOU::NOU_DAT_ALG::String8> m_name;

		FunctionStart m_startFunc;

		NOU::boolean m_alreadyExecuted;

		void unload();

	public:
		explicit EnginePlugin(const NOU::NOU_FILE_MNGT::Path &path);
		EnginePlugin(EnginePlugin && other);

		EnginePlugin(const EnginePlugin &other) = delete;

		~EnginePlugin();

		NOU::boolean load();

		const NOU::NOU_CORE::Version& getVersion() const;
		const NOU::NOU_DAT_ALG::StringView8& getName() const;
		PluginStartResult start(NostraEngine &engineInstance);
	};

	class NOU_CLASS PluginManager
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

	private:
		NOU::NOU_FILE_MNGT::Path m_folder;
		NOU::NOU_DAT_ALG::Vector<EnginePlugin> m_plugins;

		NOU::boolean m_loadedPlugins;

		void loadPlugins();

	public:
		explicit PluginManager(const NOU::NOU_FILE_MNGT::Path &folder);

		PluginManager(const PluginManager &other) = delete;
		PluginManager(PluginManager &&) = delete;

		NOU::NOU_DAT_ALG::Vector<EnginePlugin>& getPlugins();
	};
}