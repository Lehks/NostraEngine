#include "nostraengine/core/PluginManager.hpp"

#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H
#include <Windows.h>
#elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX
#include <dlfcn.h>
#endif

#include <filesystem>

namespace NOE::NOE_CORE
{
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

	const NOU::NOU_DAT_ALG::StringView8 EnginePlugin::GET_VERSION_FUNCNAME = "noePluginGetVersion";

	const NOU::NOU_DAT_ALG::StringView8 EnginePlugin::PLUGIN_STARTUP_FUNCNAME = "noePluginStartup";
	const NOU::NOU_DAT_ALG::StringView8 EnginePlugin::PLUGIN_SHUTDOWN_FUNCNAME = "noePluginShutdown";
	const NOU::NOU_DAT_ALG::StringView8 EnginePlugin::PLUGIN_RECEIVE_FUNCNAME = "noePluginReceive";

	const NOU::NOU_DAT_ALG::StringView8 EnginePlugin::INITIALIZE_FUNCNAME = "noePluginInitialize"; 
	const NOU::NOU_DAT_ALG::StringView8 EnginePlugin::TERMINATE_FUNCNAME = "noePluginTerminate";

	EnginePlugin::EnginePlugin(Plugin::ID id) :
		m_library(nullptr),
		m_metadata(id),
		m_initializeFunc(nullptr),
		m_terminateFunc(nullptr),
		m_shutdownFunc(nullptr)
	{}

	EnginePlugin::EnginePlugin(EnginePlugin && other) :
		m_library(other.m_library),
		m_metadata(other.getMetadata().getId()),
		m_version(NOU::NOU_CORE::move(other.m_version)),
		m_initializeFunc(other.m_initializeFunc),
		m_terminateFunc(other.m_terminateFunc),
		m_shutdownFunc(other.m_shutdownFunc)
	{
		other.m_library = nullptr;
	}

	EnginePlugin::~EnginePlugin()
	{
		if (m_library != nullptr)
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
		void* lib = dlopen(path.cstr(), RTLD_NOW);
#endif

		//error loading the library
		if (lib == nullptr)
		{
			NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(), 
				PluginManager::ErrorCodes::COULD_NOT_LOAD_LIBRARY, "The plugin could not be loaded.");

			return false;
		}

		EnginePlugin::FunctionGetVersion getVersionFunc =
			getFuncAddress<EnginePlugin::FunctionGetVersion>(lib, EnginePlugin::GET_VERSION_FUNCNAME);

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

		if (getVersionFunc == nullptr)
		{
			NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(),
				PluginManager::ErrorCodes::COULD_NOT_LOAD_FUNCTION, 
				"The function \"noePluginGetVersion()\" could not be loaded.");

			success = false;
		}

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

		m_version = getVersionFunc();

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

	const NOU::NOU_CORE::Version& EnginePlugin::getVersion() const
	{
		return m_version;
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

	PluginMetadata getPluginMetdata(Plugin::ID id)
	{
		return PluginMetadata(id);
	}

	EnginePlugin& getPlugin(Plugin::ID id)
	{

	}

	Plugin::SendResult PluginManager::send(Plugin::ID recipient, Plugin::ID source, void *data,
		NOU::sizeType size, NOU::uint32 flags)
	{
		if (recipient == EnginePlugin::ENGINE_ID || recipient == source)
		{
			return Plugin::SendResult::INVALID_RECIPIENT;
		}

		PluginMetadata metadata = getPluginMetdata(recipient).isValid();

		if (!metadata.isValid())
		{
			return Plugin::SendResult::PLUGIN_NOT_FOUND;
		}

		getPlugin(recipient).receive(source, data, size, flags);
	}

	PluginManager::PluginManager()
	{}

	NOU::boolean PluginManager::loadPlugins()
	{

	}

	NOU::NOU_DAT_ALG::Vector<EnginePlugin>& PluginManager::getPlugins()
	{
		return m_plugins;
	}
}