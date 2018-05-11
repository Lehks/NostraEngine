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
	const NOU::NOU_DAT_ALG::StringView8 EnginePlugin::GET_NAME_FUNCNAME = "noePluginGetName";
	const NOU::NOU_DAT_ALG::StringView8 EnginePlugin::START_FUNCNAME = "noePluginStart"; 

	void EnginePlugin::unload()
	{
#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H
		FreeLibrary(reinterpret_cast<HMODULE>(m_library));
#elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX
		dlclose(m_library);
#endif
	}

	EnginePlugin::EnginePlugin(const NOU::NOU_FILE_MNGT::Path &path) :
		m_library(nullptr),
		m_path(path),
		m_startFunc(nullptr),
		m_alreadyExecuted(false)
	{}

	EnginePlugin::EnginePlugin(EnginePlugin && other) :
		m_library(other.m_library),
		m_path(NOU::NOU_CORE::move(other.m_path)),
		m_version(NOU::NOU_CORE::move(other.m_version)),
		m_name(NOU::NOU_CORE::move(other.m_name)),
		m_startFunc(other.m_startFunc),
		m_alreadyExecuted(other.m_alreadyExecuted)
	{
		other.m_library = nullptr;
	}

	EnginePlugin::~EnginePlugin()
	{
		if (m_library == nullptr)
			return;

		unload();
	}

	NOU::boolean EnginePlugin::load()
	{

#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H
		HMODULE lib = LoadLibrary(m_path.getAbsolutePath().rawStr());
#elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX
		void* lib = dlopen(path.cstr(), RTLD_NOW);
#endif

		//error loading the library; it will be omitted
		if (lib == nullptr)
		{
			NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(), 
				PluginManager::ErrorCodes::COULD_NOT_LOAD_LIBRARY, "The plugin could not be loaded.");

			return false;
		}

		EnginePlugin::FunctionGetVersion getVersionFunc =
			getFuncAddress<EnginePlugin::FunctionGetVersion>(lib, EnginePlugin::GET_VERSION_FUNCNAME);

		EnginePlugin::FunctionGetName getNameFunc =
			getFuncAddress<EnginePlugin::FunctionGetName>(lib, EnginePlugin::GET_NAME_FUNCNAME);

		EnginePlugin::FunctionStart startFunc =
			getFuncAddress<EnginePlugin::FunctionStart>(lib, EnginePlugin::START_FUNCNAME);

		if (getVersionFunc == nullptr)
		{
			NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(),
				PluginManager::ErrorCodes::COULD_NOT_LOAD_FUNCTION, 
				"The function \"noePluginGetVersion()\" could not be loaded.");

			return false;
		}

		if (getNameFunc == nullptr)
		{
			NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(),
				PluginManager::ErrorCodes::COULD_NOT_LOAD_FUNCTION,
				"The function \"noePluginGetName()\" could not be loaded.");

			return false;
		}

		if (startFunc == nullptr)
		{
			NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(),
				PluginManager::ErrorCodes::COULD_NOT_LOAD_FUNCTION,
				"The function \"noePluginStart()\" could not be loaded.");

			return false;
		}

		m_version = getVersionFunc();
		m_name = getNameFunc();

		m_startFunc = startFunc;

		return true;
	}

	const NOU::NOU_CORE::Version& EnginePlugin::getVersion() const
	{
		return m_version;
	}

	const NOU::NOU_DAT_ALG::StringView8& EnginePlugin::getName() const
	{
		return m_name;
	}

	PluginStartResult EnginePlugin::start(NostraEngine &engineInstance)
	{
		if (!m_alreadyExecuted)
			return PluginStartResult(m_startFunc(&engineInstance));
		else
			return PluginStartResult::FAILED;
	}




	PluginManager::ErrorPool::ErrorPool() :
		m_errors
		{
			NOU::NOU_CORE::Error("COULD_NOT_LOAD_LIBRARY", ErrorCodes::COULD_NOT_LOAD_LIBRARY),
			NOU::NOU_CORE::Error("COULD_NOT_LOAD_FUNCTION", ErrorCodes::COULD_NOT_LOAD_FUNCTION)
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

	void PluginManager::loadPlugins()
	{
		std::filesystem::directory_iterator it(m_folder.getAbsolutePath().rawStr());

		for (auto &f : it)
		{
			std::string path = f.path().string();

			//Not a DLL, omit
			if (f.is_directory() || path.substr(path.size() - 4, path.size()) != ".dll")
				continue;

			m_plugins.push(EnginePlugin(f.path().string().c_str()));

			if (!m_plugins[m_plugins.size() - 1].load())
				std::cout << "Error" << std::endl;
		}

		m_loadedPlugins = true;
	}

	PluginManager::PluginManager(const NOU::NOU_FILE_MNGT::Path &folder) :
		m_folder(folder),
		m_loadedPlugins(false)
	{}

	NOU::NOU_DAT_ALG::Vector<EnginePlugin>& PluginManager::getPlugins()
	{
		if (!m_loadedPlugins)
			loadPlugins();

		return m_plugins;
	}
}