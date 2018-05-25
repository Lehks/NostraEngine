#include "nostraengine/core/PluginManager.hpp"
#include "nostrautils/file_mngt/Folder.hpp"

#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H
#include <Windows.h>
#elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX
#include <dlfcn.h>
#endif

#include <filesystem>

//w/o, logging functions do not work
#undef ERROR

namespace NOE::NOE_CORE
{
	const NOU::NOU_DAT_ALG::StringView8 PluginMetadata::PLUGIN_FILE_EXTENSION = ".np";
	const PluginMetadata::Priority PluginMetadata::LOWEST_PRIORITY = 0;
	const PluginMetadata::Priority PluginMetadata::HIGHEST_PRIORITY = -1;

	const NOU::NOU_DAT_ALG::StringView8 PluginMetadata::PCONF_SECTION_CORE = "core";
	const NOU::NOU_DAT_ALG::StringView8 PluginMetadata::PCONF_SECTION_META = "meta";

	const NOU::NOU_DAT_ALG::StringView8 PluginMetadata::PCONF_ATTRIB_ID               = "id";
	const NOU::NOU_DAT_ALG::StringView8 PluginMetadata::PCONF_ATTRIB_PRIORITY         = "priority";
	const NOU::NOU_DAT_ALG::StringView8 PluginMetadata::PCONF_ATTRIB_MINVERSION_MAJOR = "minversion.major";
	const NOU::NOU_DAT_ALG::StringView8 PluginMetadata::PCONF_ATTRIB_MINVERSION_MINOR = "minversion.minor";
	const NOU::NOU_DAT_ALG::StringView8 PluginMetadata::PCONF_ATTRIB_MINVERSION_PATCH = "minversion.patch";
	const NOU::NOU_DAT_ALG::StringView8 PluginMetadata::PCONF_ATTRIB_NAME             = "name";
	const NOU::NOU_DAT_ALG::StringView8 PluginMetadata::PCONF_ATTRIB_DESCRIPTION      = "description";
	const NOU::NOU_DAT_ALG::StringView8 PluginMetadata::PCONF_ATTRIB_VERSION_MAJOR    = "version.major";
	const NOU::NOU_DAT_ALG::StringView8 PluginMetadata::PCONF_ATTRIB_VERSION_MINOR    = "version.minor";
	const NOU::NOU_DAT_ALG::StringView8 PluginMetadata::PCONF_ATTRIB_VERSION_PATCH    = "version.patch";


	void PluginMetadata::load(const NOU::NOU_FILE_MNGT::Path &config)
	{
		NOU::NOU_FILE_MNGT::INIFile pluginConfig(config.getAbsolutePath());

		if (!pluginConfig.read())
		{
			NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(), 
				PluginManager::ErrorCodes::PLUGIN_CONFIGURATION_PARSE_ERROR, 
				"The plugin configuration of a plugin could not be loaded.");

			m_id = EnginePlugin::INVALID_ID;

			return;
		}

		m_id = pluginConfig.getInt(PCONF_ATTRIB_ID, PCONF_SECTION_CORE);
		m_priority = pluginConfig.getInt(PCONF_ATTRIB_PRIORITY, PCONF_SECTION_CORE);

		NOU::uint32 minversionMajor = pluginConfig.getInt(PCONF_ATTRIB_MINVERSION_MAJOR, PCONF_SECTION_CORE);
		NOU::uint32 minversionMinor = pluginConfig.getInt(PCONF_ATTRIB_MINVERSION_MINOR, PCONF_SECTION_CORE);
		NOU::uint32 minversionPatch = pluginConfig.getInt(PCONF_ATTRIB_MINVERSION_PATCH, PCONF_SECTION_CORE);

		m_requiredVersion = NOU::NOU_CORE::Version(minversionMajor, minversionMinor, minversionPatch);



		m_name = pluginConfig.getString(PCONF_ATTRIB_NAME, PCONF_SECTION_META);
		m_description = pluginConfig.getString(PCONF_ATTRIB_DESCRIPTION, PCONF_SECTION_META);

		NOU::uint32 versionMajor = pluginConfig.getInt(PCONF_ATTRIB_VERSION_MAJOR, PCONF_SECTION_META);
		NOU::uint32 versionMinor = pluginConfig.getInt(PCONF_ATTRIB_VERSION_MINOR, PCONF_SECTION_META);
		NOU::uint32 versionPatch = pluginConfig.getInt(PCONF_ATTRIB_VERSION_PATCH, PCONF_SECTION_META);
		
		m_version = NOU::NOU_CORE::Version(versionMajor, versionMinor, versionPatch);

		// the filename is the name of the plugin plus the plugin name extension
		m_path = m_name + PLUGIN_FILE_EXTENSION;
	}

	PluginMetadata::PluginMetadata(const NOU::NOU_FILE_MNGT::Path &config) : 
		m_id(EnginePlugin::INVALID_ID),
		m_version(0, 0, 0),
		m_requiredVersion(0, 0, 0),
		m_path("./")
	{
		load(config);
	}

	PluginMetadata::PluginMetadata() :
		m_id(EnginePlugin::INVALID_ID),
		m_version(0, 0, 0),
		m_requiredVersion(0, 0, 0),
		m_path("./")
	{}

	Plugin::ID PluginMetadata::getID() const
	{
		return m_id;
	}

	const NOU::NOU_DAT_ALG::String8& PluginMetadata::getName() const
	{
		return m_name;
	}

	const NOU::NOU_DAT_ALG::String8& PluginMetadata::getDescription() const
	{
		return m_description;
	}

	const NOU::NOU_CORE::Version& PluginMetadata::getPluginVersion() const
	{
		return m_version;
	}

	const NOU::NOU_CORE::Version& PluginMetadata::getRequiredVersion() const
	{
		return m_requiredVersion;
	}

	NOU::NOU_FILE_MNGT::Path PluginMetadata::getPath() const
	{
		return m_path;
	}

	PluginMetadata::Priority PluginMetadata::getPriority() const
	{
		return m_priority;
	}

	NOU::boolean PluginMetadata::isValid() const
	{
		return getID() == EnginePlugin::INVALID_ID;
	}

	PluginMetadata::operator NOU::boolean() const
	{
		return isValid();
	}

	//helper function
	template<typename T>
	T getFuncAddress(void *lib, const NOU::NOU_DAT_ALG::StringView8 &name)
	{
#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H
		HMODULE libPtr = reinterpret_cast<HMODULE>(lib);

		return reinterpret_cast<T>(GetProcAddress(libPtr, name.rawStr()));
#elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX
		return reinterpret_cast<T>(dlsym(lib, name.rawStr()));
#endif
	}

	const NOU::NOU_DAT_ALG::StringView8 EnginePlugin::PLUGIN_STARTUP_FUNCNAME = "noePluginStartup";
	const NOU::NOU_DAT_ALG::StringView8 EnginePlugin::PLUGIN_SHUTDOWN_FUNCNAME = "noePluginShutdown";
	const NOU::NOU_DAT_ALG::StringView8 EnginePlugin::PLUGIN_RECEIVE_FUNCNAME = "noePluginReceive";

	const NOU::NOU_DAT_ALG::StringView8 EnginePlugin::INITIALIZE_FUNCNAME = "noePluginInitialize"; 
	const NOU::NOU_DAT_ALG::StringView8 EnginePlugin::TERMINATE_FUNCNAME = "noePluginTerminate";

	NOU::NOU_DAT_ALG::CompareResult EnginePlugin::comparator(EnginePlugin *const&a, EnginePlugin *const&b)
	{
		return NOU::NOU_DAT_ALG::genericComparator(a->getMetadata().getPriority(), 
			b->getMetadata().getPriority());
	}

	EnginePlugin::EnginePlugin(const NOU::NOU_FILE_MNGT::Path &config) :
		m_library(nullptr),
		m_metadata(config),
		m_initializeFunc(nullptr),
		m_terminateFunc(nullptr),
		m_shutdownFunc(nullptr)
	{}

	EnginePlugin::EnginePlugin() :
		m_library(nullptr),
		m_metadata(),
		m_initializeFunc(nullptr),
		m_terminateFunc(nullptr),
		m_shutdownFunc(nullptr)
	{}

	EnginePlugin::EnginePlugin(EnginePlugin && other) :
		m_library(other.m_library),
		m_metadata(NOU::NOU_CORE::move(other.m_metadata)),
		m_initializeFunc(other.m_initializeFunc),
		m_terminateFunc(other.m_terminateFunc),
		m_shutdownFunc(other.m_shutdownFunc)
	{
		other.m_library = nullptr;
	}

	EnginePlugin::~EnginePlugin()
	{
		if (isLoaded())
			unload();
	}

	NOU::boolean EnginePlugin::load()
	{
		if (isLoaded())
		{
			NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(),
				PluginManager::ErrorCodes::PLUGIN_ALREADY_LOADED, "The plugin is already loaded.");

			return false;
		}

		if (getMetadata().isValid())
		{
			NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(),
				PluginManager::ErrorCodes::PLUGIN_NOT_EXISTING, "A plugin with that ID does not exist.");

			return false;
		}

		NOU::NOU_FILE_MNGT::Path path = getMetadata().getPath();

#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H
		HMODULE lib = LoadLibrary(path.getAbsolutePath().rawStr());
#elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX
		void *lib = dlopen(path.cstr(), RTLD_NOW);
#endif

		//error loading the library
		if (lib == nullptr)
		{
			NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(), 
				PluginManager::ErrorCodes::COULD_NOT_LOAD_LIBRARY, "The plugin could not be loaded.");

			return false;
		}

		EnginePlugin::FunctionStartup startupFunc =
			getFuncAddress<EnginePlugin::FunctionStartup>(lib, EnginePlugin::PLUGIN_STARTUP_FUNCNAME);

		EnginePlugin::FunctionShutdown shutdownFunc =
			getFuncAddress<EnginePlugin::FunctionShutdown>(lib, EnginePlugin::PLUGIN_SHUTDOWN_FUNCNAME);

		EnginePlugin::FunctionReceive receiveFunc =
			getFuncAddress<EnginePlugin::FunctionReceive>(lib, EnginePlugin::PLUGIN_RECEIVE_FUNCNAME);

		EnginePlugin::FunctionInitialize initializeFunc =
			getFuncAddress<EnginePlugin::FunctionInitialize>(lib, EnginePlugin::INITIALIZE_FUNCNAME);

		EnginePlugin::FunctionTerminate terminateFunc =
			getFuncAddress<EnginePlugin::FunctionTerminate>(lib, EnginePlugin::TERMINATE_FUNCNAME);

		NOU::boolean success = true;

		if (startupFunc == nullptr)
		{
			NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(),
				PluginManager::ErrorCodes::COULD_NOT_LOAD_FUNCTION,
				"The function \"noePluginStartup()\" could not be loaded.");

			success = false;
		}

		if (shutdownFunc == nullptr)
		{
			NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(),
				PluginManager::ErrorCodes::COULD_NOT_LOAD_FUNCTION,
				"The function \"noePluginShutdown()\" could not be loaded.");

			success = false;
		}

		if (receiveFunc == nullptr)
		{
			NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(),
				PluginManager::ErrorCodes::COULD_NOT_LOAD_FUNCTION,
				"The function \"noePluginReceive()\" could not be loaded.");

			success = false;
		}

		if (initializeFunc == nullptr)
		{
			NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(),
				PluginManager::ErrorCodes::COULD_NOT_LOAD_FUNCTION,
				"The function \"noePluginInitialize()\" could not be loaded.");

			success = false;
		}

		if (terminateFunc == nullptr)
		{
			NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(),
				PluginManager::ErrorCodes::COULD_NOT_LOAD_FUNCTION,
				"The function \"noePluginTerminate()\" could not be loaded.");

			success = false;
		}

		if (!success)
			return false;

		//start the plugin
		startupFunc();

		m_library = lib;

		m_initializeFunc = initializeFunc;
		m_terminateFunc = terminateFunc;;
		m_receiveFunc = receiveFunc;

		m_shutdownFunc = shutdownFunc;

		return true;
	}

	NOU::boolean EnginePlugin::unload()
	{
		if (isLoaded())
		{
#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H
			//FreeLibrary was successful if return value is != 0
			NOU::boolean success = (FreeLibrary(reinterpret_cast<HMODULE>(m_library)) != 0);
#elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX
			//dlclose was successful if return value is == 0
			NOU::boolean success = dlclose(m_library) == 0;
#endif

			if (!success)
			{
				NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(),
					PluginManager::ErrorCodes::COULD_NOT_FREE_LIBRARY,
					"The system call to free the library failed.");
			}
		}
		else
		{
			NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(),
				PluginManager::ErrorCodes::PLUGIN_NOT_LOADED,
				"The plugin is not loaded.");

			return false;
		}
	}

	NOU::boolean EnginePlugin::isLoaded() const
	{
		return m_library != nullptr;
	}

	Plugin::InitResult EnginePlugin::initialize(NostraEngine &engineInstance)
	{
		return Plugin::InitResult(m_initializeFunc(&engineInstance));
	}

	Plugin::InitResult EnginePlugin::terminate(NostraEngine &engineInstance)
	{
		return Plugin::InitResult(m_terminateFunc(&engineInstance));
	}

	void EnginePlugin::receive(Plugin::ID source, void *data, NOU::sizeType size, NOU::uint32 flags)
	{
		m_receiveFunc(source, data, size, flags);
	}

	const PluginMetadata& EnginePlugin::getMetadata() const
	{
		return m_metadata;
	}




	PluginManager::ErrorPool::ErrorPool() :
		m_errors
		{
			NOU::NOU_CORE::Error("PLUGIN_NOT_EXISTING", ErrorCodes::PLUGIN_NOT_EXISTING),
			NOU::NOU_CORE::Error("PLUGIN_ALREADY_LOADED", ErrorCodes::PLUGIN_ALREADY_LOADED),
			NOU::NOU_CORE::Error("COULD_NOT_LOAD_LIBRARY", ErrorCodes::COULD_NOT_LOAD_LIBRARY),
			NOU::NOU_CORE::Error("COULD_NOT_LOAD_FUNCTION", ErrorCodes::COULD_NOT_LOAD_FUNCTION),
			NOU::NOU_CORE::Error("PLUGIN_NOT_LOADED", ErrorCodes::PLUGIN_NOT_LOADED),
			NOU::NOU_CORE::Error("COULD_NOT_FREE_LIBRARY", ErrorCodes::COULD_NOT_FREE_LIBRARY),
			NOU::NOU_CORE::Error("PLUGIN_CONFIGURATION_PARSE_ERROR", 
				ErrorCodes::PLUGIN_CONFIGURATION_PARSE_ERROR)
		}
	{}

	const NOU::NOU_CORE::Error* PluginManager::ErrorPool::queryError
												(typename NOU::NOU_CORE::ErrorHandler::ErrorType id) const
	{
		if (id > ErrorCodes::FIRST_ELEMENT && id < ErrorCodes::LAST_ELEMENT)
			return m_errors + id;
		else
			return nullptr;
	}

	const NOU::NOU_FILE_MNGT::Path PluginManager::DEFAULT_LOAD_PATH = "./Plugins/";

	EnginePlugin& PluginManager::getPlugin(Plugin::ID id)
	{
		if (m_idIndexMap.containsKey(id))
			return *m_idIndexMap.get(id);
		else
			return *m_idIndexMap.get(EnginePlugin::INVALID_ID);
	}

	NOU::NOU_DAT_ALG::Vector<NOU::NOU_FILE_MNGT::Path> PluginManager::listPluginFiles()
	{
		NOU::NOU_DAT_ALG::Vector<NOU::NOU_FILE_MNGT::Path> paths;

		NOU::NOU_FILE_MNGT::Folder folder(m_loadPath);

		auto list = folder.listFiles();

		for (auto file : list)
		{
			if (file.getPath().getFileExtension() == PluginMetadata::PLUGIN_FILE_EXTENSION)
				paths.push(file.getPath());
		}

		return paths;
	}

	void PluginManager::setPluginLoadPath(const NOU::NOU_FILE_MNGT::Path &path)
	{
		if (!isPluginListCreated())
			m_loadPath = path;
	}

	const NOU::NOU_FILE_MNGT::Path& PluginManager::getPluginLoadPath() const
	{
		return m_loadPath;
	}

	void PluginManager::initialize()
	{
		NOU::NOU_CORE::ErrorHandler::pushPool<PluginManager::ErrorPool>();
	}

	void PluginManager::terminate()
	{
		//does nothing yet
	}

	Plugin::SendResult PluginManager::send(Plugin::ID recipient, void *data, NOU::sizeType size, 
		NOU::uint32 flags)
	{
		return sendImpl(recipient, EnginePlugin::ENGINE_ID, data, size, flags);
	}

	Plugin::SendResult PluginManager::sendImpl(Plugin::ID recipient, Plugin::ID source, void *data,
		NOU::sizeType size, NOU::uint32 flags)
	{
		if (recipient == EnginePlugin::ENGINE_ID || recipient == source)
		{
			return Plugin::SendResult::INVALID_RECIPIENT;
		}

		EnginePlugin &plugin = getPlugin(recipient);

		if (!plugin.getMetadata().isValid())
		{
			return Plugin::SendResult::PLUGIN_NOT_FOUND;
		}

		plugin.receive(source, data, size, flags);
	}

	PluginManager::PluginManager() : 
		m_createdPluginList(false),
		m_loadPath(DEFAULT_LOAD_PATH)
	{}

	PluginManager& PluginManager::get()
	{
		static PluginManager instance;
		return instance;
	}

	NOU::boolean PluginManager::createPluginList()
	{
		NOU::NOU_DAT_ALG::Vector<NOU::NOU_FILE_MNGT::Path> paths = listPluginFiles();

		//+1 b/c of invalid plugin
		m_idIndexMap = NOU::NOU_DAT_ALG::HashMap<NOU::uint32, 
			NOU::NOU_MEM_MNGT::UniquePtr<EnginePlugin>>(paths.size() + 1);

		m_idIndexMap.map(EnginePlugin::INVALID_ID, NOU::NOU_MEM_MNGT::UniquePtr<EnginePlugin>(
			new EnginePlugin(), NOU::NOU_MEM_MNGT::defaultDeleter));

		for (auto path : paths)
		{
			NOU::NOU_MEM_MNGT::UniquePtr<EnginePlugin> plugin(new EnginePlugin(path), 
				NOU::NOU_MEM_MNGT::defaultDeleter);

			if (plugin->getMetadata().isValid())
			{
				NOU::uint32 id = plugin->getMetadata().getID();

				m_sortedPlugins.push(plugin.rawPtr());
				m_idIndexMap.map(id, NOU::NOU_CORE::move(plugin));
			}
			else
			{
				m_createdPluginList = false;
				return false;
			}
		}

		if(m_sortedPlugins.size() > 0)
			m_sortedPlugins.sortComp(EnginePlugin::comparator);

		m_createdPluginList = true;
		return true;
	}

	NOU::boolean PluginManager::isPluginListCreated() const
	{
		return m_createdPluginList;
	}

	NOU::NOU_DAT_ALG::Vector<EnginePlugin*>& PluginManager::getPlugins()
	{
		return m_sortedPlugins;
	}
}