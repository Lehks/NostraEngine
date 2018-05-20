#include "nostraengine/core/PluginManager.hpp"

#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H
#include <Windows.h>
#elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX
#include <dlfcn.h>
#endif

#include <filesystem>

namespace NOE::NOE_CORE
{
	const NOU::NOU_DAT_ALG::StringView8 PluginMetadata::PLUGIN_FILE_EXTENSION = ".np";
	const PluginMetadata::Priority LOWEST_PRIORITY = 0;
	const PluginMetadata::Priority HIGHEST_PRIORITY = -1;


	void PluginMetadata::load(const NOU::NOU_FILE_MNGT::Path &config)
	{
		m_id = 1;
		m_name = "MyPlugin";
		m_description = "MyPlugin. Duh.";
		m_version = NOU::NOU_CORE::Version(1, 0, 0);
		m_requiredVersion = NOU::NOU_CORE::Version(0, 0, 1);

		// the filename is the name of the plugin plus the plugin name extension
		m_path = m_name + PLUGIN_FILE_EXTENSION;

		m_priority = 0;
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
			NOU::NOU_CORE::Error("COULD_NOT_FREE_LIBRARY", ErrorCodes::COULD_NOT_FREE_LIBRARY)
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

	EnginePlugin& PluginManager::getPlugin(Plugin::ID id)
	{
	//	if (m_idIndexMap.containsKey(id))
	//		return m_idIndexMap.get(id);
	//	else
	//		return m_idIndexMap.get(EnginePlugin::INVALID_ID);

		return EnginePlugin();
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

	PluginManager::PluginManager()
	{
		//map invalid plugin
	//	m_idIndexMap.map(EnginePlugin::INVALID_ID, EnginePlugin());
	}

	PluginManager& PluginManager::get()
	{
		static PluginManager instance;
		return instance;
	}

	NOU::boolean PluginManager::createPluginList()
	{
		return false;
	}

	NOU::NOU_DAT_ALG::Vector<EnginePlugin*>& PluginManager::getPlugins()
	{
		return m_sortedPlugins;
	}
}