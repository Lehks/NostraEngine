#include "nostraengine/core/configuration_mngt/ConfigurationManager.hpp"

namespace NOE::NOE_CORE
{
	ConfigurationManager::ErrorPool::ErrorPool() :
		m_errors
		{
			NOU::NOU_CORE::Error("INVALID_FULLY_QUALIFIED_PATH", ErrorCodes::INVALID_FULLY_QUALIFIED_PATH),
			NOU::NOU_CORE::Error("SOURCE_NOT_FOUND", ErrorCodes::SOURCE_NOT_FOUND),
			NOU::NOU_CORE::Error("ENTRY_NOT_FOUND", ErrorCodes::ENTRY_NOT_FOUND)
		}
	{}

	const NOU::NOU_CORE::Error* ConfigurationManager::ErrorPool::queryError
	(typename NOU::NOU_CORE::ErrorHandler::ErrorType id) const
	{
		if (id > ErrorCodes::FIRST_ELEMENT && id < ErrorCodes::LAST_ELEMENT)
			return m_errors + id;
		else
			return nullptr;
	}

	ConfigurationManager::ConfigurationSourceData::ConfigurationSourceData(ConfigurationSource *ptr,
		const NOU::NOU_FILE_MNGT::Path &path) :
		m_sourcePtr(ptr, NOU::NOU_MEM_MNGT::defaultDeleter),
		m_path(path)
	{}

	const NOU::NOU_DAT_ALG::StringView8 ConfigurationManager::INITIALIZABLE_NAME 
		                                                                  = "Configuration Management";

	const NOU::uint32 ConfigurationManager::INITIALIZABLE_PRIORITY = 250;

	const ConfigurationManager::LoadMode ConfigurationManager::DEFAULT_LOAD_MODE 
		                                                                = LoadMode::LOAD_ON_INITIALIZE;

	const NOU::sizeType ConfigurationManager::DEFAULT_FACTORY_MAP_CAPACITY = 100;

	const NOU::NOU_DAT_ALG::StringView8 ConfigurationManager::DEFAULT_CONFIGURATION_PATH = "./data/cfg";

	const NOU::NOU_DAT_ALG::StringView8 ConfigurationManager::PATH_SEPARATOR = "::";

	ConfigurationManager::ConfigurationManager() :
		Initializable(INITIALIZABLE_PRIORITY),
		m_loadPath(DEFAULT_CONFIGURATION_PATH),
		m_loadMode(DEFAULT_LOAD_MODE),
		m_wasInitCalled(false),
		m_factoryNameDataMap(DEFAULT_FACTORY_MAP_CAPACITY)
	{}

	NOU::NOU_DAT_ALG::Vector<NOU::NOU_FILE_MNGT::File> 
		ConfigurationManager::createFileList(const NOU::NOU_FILE_MNGT::Path &path) const
	{
		return NOU::NOU_FILE_MNGT::Folder(path).listFiles();
	}

	NOU::boolean ConfigurationManager::loadSourcesList()
	{
		NOU::NOU_DAT_ALG::Vector<NOU::NOU_FILE_MNGT::File> files = createFileList(m_loadPath);
		NOU::boolean ret = true;

		for (auto &file : files)
		{
			ConfigurationSourceFactory *fa = nullptr;

			if (m_factoryNameDataMap.containsKey(file.getPath().getFileExtension()))
			{
				fa = m_factoryNameDataMap.get(file.getPath().getFileExtension()).rawPtr();
			}
			else
			{
				NOU_LOG_WARNING(NOU::NOU_DAT_ALG::String8("The factory for the file extension .") +
					file.getPath().getFileExtension() + " could not be found.");
				ret = false;
			}

			//if factory could be found
			if (fa)
			{
				ConfigurationSourceData data(fa->build(file.getPath()), file.getPath());

				data.m_path = file.getPath();

				data.m_factory = fa;

				m_data.push(NOU::NOU_CORE::move(data));
				m_nameDataMap.map(m_data[m_data.size() - 1].m_sourcePtr->getName(),
					m_data.size() - 1);

				NOU_LOG_INFO(
					NOU::NOU_DAT_ALG::String8("Successfully constructed configuration source ") +
					m_data[m_data.size() - 1].m_sourcePtr->getName() + ".");
			}
		}

		NOU_LOG_INFO(NOU::NOU_DAT_ALG::String8("Successfully loaded ") + m_data.size() + " of " +
		  	files.size() + " configuration sources.");

		return ret;
	}

	void ConfigurationManager::destroyFactoryMap()
	{
		for (auto &key : m_factoryNameDataMap.keySet())
		{
			m_factoryNameDataMap.remove(*key);
		}
	}

	void ConfigurationManager::resolveFullyQualifiedPath(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified,
		NOU::NOU_DAT_ALG::StringView8 *sourceName, NOU::NOU_DAT_ALG::StringView8 *qualified)
	{
		NOU::sizeType separator = fullyQualified.find(PATH_SEPARATOR);

		if (separator == NOU::NOU_DAT_ALG::StringView8::NULL_INDEX)
		{
			NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(), ErrorCodes::INVALID_FULLY_QUALIFIED_PATH, 
				"A fully qualified path could not be resolved because the double colon (::) was missing.");
			NOU_LOG_DEBUG("It was attempted to resolve a path that did not have separator (::) in it.");
			*sourceName = "";
			*qualified = "";
			return;
		}

		*sourceName = fullyQualified.logicalSubstring(0, separator);
		*qualified = fullyQualified.logicalSubstring(separator + PATH_SEPARATOR.size());
	}

	ConfigurationSource* 
		ConfigurationManager::getConfigurationSource(const NOU::NOU_DAT_ALG::StringView8 &sourceName)
	{
		if (!m_nameDataMap.containsKey(sourceName))
		{
			NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(), ErrorCodes::SOURCE_NOT_FOUND, "A configuration "
				"source with that name does not exist.");
			NOU_LOG_DEBUG("It was attempted to get a value from an entry in a configuration that "
				"does not exist.");
			return nullptr;
		}

		return m_data[m_nameDataMap.get(sourceName)].m_sourcePtr.rawPtr();
	}

	ConfigurationManager& ConfigurationManager::get()
	{
		static ConfigurationManager instance;
		return instance;
	}

	Initializable::ExitCode ConfigurationManager::initialize()
	{
		Initializable::ExitCode ret = Initializable::ExitCode::SUCCESS;

		m_wasInitCalled = true;
		//from here on, m_loadMode will not change its value

		if (!loadSourcesList()) //initialize() does logging
		{
			ret = Initializable::ExitCode::WARNING;
		}

		//all configuration sources are constructed now and the factories are no longer needed
		destroyFactoryMap();

		//if mode is set, initialize all configuration sources
		if (m_loadMode == LoadMode::LOAD_ON_INITIALIZE)
		{
			for (NOU::sizeType i = 0; i < m_data.size(); i++)
			{
				if (m_data[i].m_isInitialized)
				{
					if (!m_data[i].m_sourcePtr->initialize()) //initialize() does logging
					{
						ret = Initializable::ExitCode::WARNING;
					}
				}
			}
		}

		return ret;
	}

	void ConfigurationManager::terminate()
	{
		for (NOU::sizeType i = 0; i < m_data.size(); i++)
		{
			if (m_data[i].m_isInitialized)
			{
				m_data[i].m_sourcePtr->terminate();
			}
		}

		/*
		 * Explicitly clear the vector to destroy all sources
		 * Otherwise, the sources would be destroyed during the destruction of static objects aka. after the
		 * plugins have been unloaded. This means, the destructors from the plugins can't be called anymore.
		 */
		m_data.clear();
	}

	const NOU::NOU_DAT_ALG::StringView8& ConfigurationManager::getName() const
	{
		return INITIALIZABLE_NAME;
	}

	void ConfigurationManager::flush()
	{
		for (NOU::sizeType i = 0; i < m_data.size(); i++)
		{
			if (m_data[i].m_isInitialized)
			{
				m_data[i].m_sourcePtr->flush();
			}
		}
	}

	ConfigurationManager::LoadMode ConfigurationManager::getLoadMode() const
	{
		return m_loadMode;
	}

	NOU::boolean ConfigurationManager::setLoadMode(LoadMode loadMode)
	{
		if (!m_wasInitCalled)
		{
			m_loadMode = loadMode;
			return true;
		}
#ifndef NOU_LOG_DEBUG_DISABLE
		else
		{
			NOU_LOG_DEBUG("It was attempted to change the load mode of the configuration manager after "
				"it was initialized. The changes were not made; the load mode is still the same.");
			return false;
		}
#endif
	}

	const NOU::NOU_FILE_MNGT::Path& ConfigurationManager::getPath() const
	{
		return m_loadPath;
	}

	NOU::boolean ConfigurationManager::setPath(const NOU::NOU_FILE_MNGT::Path &path)
	{
		if (!m_wasInitCalled)
		{
			m_loadPath = path;
			return true;
		}
#ifndef NOU_LOG_DEBUG_DISABLE
		else
		{
			NOU_LOG_DEBUG("It was attempted to change the load path of the configuration manager after "
				"it was initialized. The changes were not made; the path is still the same.");
			return false;
		}
#endif
	}

	ConfigurationSource::TypeID 
		ConfigurationManager::getTypeOf(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified)
	{
		NOU::NOU_DAT_ALG::StringView8 sourceName;
		NOU::NOU_DAT_ALG::StringView8 qualified;

		resolveFullyQualifiedPath(fullyQualified, &sourceName, &qualified);

		return getTypeOf(sourceName, qualified);
	}

	ConfigurationSource::TypeID 
		ConfigurationManager::getTypeOf(const NOU::NOU_DAT_ALG::StringView8 &sourceName, 
			const NOU::NOU_DAT_ALG::StringView8 &qualified)
	{
		ConfigurationSource *configSource = getConfigurationSource(sourceName);

		if (configSource)
		{
			return configSource->getTypeOf(qualified);
		}
		else
		{
			return ConfigurationSource::TypeID::INVALID;
		}
	}

	NOU::boolean ConfigurationManager::hasEntry(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified)
	{
		NOU::NOU_DAT_ALG::StringView8 sourceName;
		NOU::NOU_DAT_ALG::StringView8 qualified;

		resolveFullyQualifiedPath(fullyQualified, &sourceName, &qualified);

		return hasEntry(sourceName, qualified);
	}

	NOU::boolean ConfigurationManager::hasEntry(const NOU::NOU_DAT_ALG::StringView8 &sourceName,
		const NOU::NOU_DAT_ALG::StringView8 &qualified)
	{
		ConfigurationSource *configSource = getConfigurationSource(sourceName);

		if (configSource)
		{
			return configSource->hasEntry(qualified);
		}
		else
		{
			return false;
		}
	}

	NOU::boolean ConfigurationManager::getBoolean(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified) const
	{
		NOU::NOU_DAT_ALG::StringView8 sourceName;
		NOU::NOU_DAT_ALG::StringView8 qualified;

		resolveFullyQualifiedPath(fullyQualified, &sourceName, &qualified);

		return getBoolean(sourceName, qualified);
	}

	NOU::boolean ConfigurationManager::getBoolean(const NOU::NOU_DAT_ALG::StringView8 &sourceName,
		const NOU::NOU_DAT_ALG::StringView8 &qualified) const
	{
		ConfigurationSource *configSource = 
			                     const_cast<ConfigurationManager*>(this)->getConfigurationSource(sourceName);

		if (configSource)
		{
			return configSource->getBoolean(qualified);
		}
		else
		{
			return false;
		}
	}

	NOU::NOU_DAT_ALG::String8 
		ConfigurationManager::getString(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified) const
	{
		NOU::NOU_DAT_ALG::StringView8 sourceName;
		NOU::NOU_DAT_ALG::StringView8 qualified;

		resolveFullyQualifiedPath(fullyQualified, &sourceName, &qualified);

		return getString(sourceName, qualified);
	}

	NOU::NOU_DAT_ALG::String8 ConfigurationManager::getString(const NOU::NOU_DAT_ALG::StringView8 &sourceName,
		const NOU::NOU_DAT_ALG::StringView8 &qualified) const
	{
		ConfigurationSource *configSource =
			const_cast<ConfigurationManager*>(this)->getConfigurationSource(sourceName);

		if (configSource)
		{
			return configSource->getString(qualified);
		}
		else
		{
			return "";
		}
	}

	NOU::int32 ConfigurationManager::getInt32(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified) const
	{
		NOU::NOU_DAT_ALG::StringView8 sourceName;
		NOU::NOU_DAT_ALG::StringView8 qualified;

		resolveFullyQualifiedPath(fullyQualified, &sourceName, &qualified);

		return getInt32(sourceName, qualified);
	}

	NOU::int32 ConfigurationManager::getInt32(const NOU::NOU_DAT_ALG::StringView8 &sourceName,
		const NOU::NOU_DAT_ALG::StringView8 &qualified) const
	{
		ConfigurationSource *configSource =
			const_cast<ConfigurationManager*>(this)->getConfigurationSource(sourceName);

		if (configSource)
		{
			return configSource->getInt32(qualified);
		}
		else
		{
			return 0;
		}
	}

	NOU::int64 ConfigurationManager::getInt64(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified) const
	{
		NOU::NOU_DAT_ALG::StringView8 sourceName;
		NOU::NOU_DAT_ALG::StringView8 qualified;

		resolveFullyQualifiedPath(fullyQualified, &sourceName, &qualified);

		return getInt64(sourceName, qualified);
	}

	NOU::int64 ConfigurationManager::getInt64(const NOU::NOU_DAT_ALG::StringView8 &sourceName,
		const NOU::NOU_DAT_ALG::StringView8 &qualified) const
	{
		ConfigurationSource *configSource =
			const_cast<ConfigurationManager*>(this)->getConfigurationSource(sourceName);

		if (configSource)
		{
			return configSource->getInt64(qualified);
		}
		else
		{
			return 0;
		}
	}

	NOU::float32 ConfigurationManager::getFloat32(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified) const
	{
		NOU::NOU_DAT_ALG::StringView8 sourceName;
		NOU::NOU_DAT_ALG::StringView8 qualified;

		resolveFullyQualifiedPath(fullyQualified, &sourceName, &qualified);

		return getFloat32(sourceName, qualified);
	}

	NOU::float32 ConfigurationManager::getFloat32(const NOU::NOU_DAT_ALG::StringView8 &sourceName,
		const NOU::NOU_DAT_ALG::StringView8 &qualified) const
	{
		ConfigurationSource *configSource =
			const_cast<ConfigurationManager*>(this)->getConfigurationSource(sourceName);

		if (configSource)
		{
			return configSource->getFloat32(qualified);
		}
		else
		{
			return 0;
		}
	}

	NOU::float64 ConfigurationManager::getFloat64(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified) const
	{
		NOU::NOU_DAT_ALG::StringView8 sourceName;
		NOU::NOU_DAT_ALG::StringView8 qualified;

		resolveFullyQualifiedPath(fullyQualified, &sourceName, &qualified);

		return getFloat64(sourceName, qualified);
	}

	NOU::float64 ConfigurationManager::getFloat64(const NOU::NOU_DAT_ALG::StringView8 &sourceName,
		const NOU::NOU_DAT_ALG::StringView8 &qualified) const
	{
		ConfigurationSource *configSource =
			const_cast<ConfigurationManager*>(this)->getConfigurationSource(sourceName);

		if (configSource)
		{
			return configSource->getFloat64(qualified);
		}
		else
		{
			return 0;
		}
	}

	void* ConfigurationManager::getVoidPtr(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified) const
	{
		NOU::NOU_DAT_ALG::StringView8 sourceName;
		NOU::NOU_DAT_ALG::StringView8 qualified;

		resolveFullyQualifiedPath(fullyQualified, &sourceName, &qualified);

		return getVoidPtr(sourceName, qualified);
	}

	void* ConfigurationManager::getVoidPtr(const NOU::NOU_DAT_ALG::StringView8 &sourceName,
		const NOU::NOU_DAT_ALG::StringView8 &qualified) const
	{
		ConfigurationSource *configSource =
			const_cast<ConfigurationManager*>(this)->getConfigurationSource(sourceName);

		if (configSource)
		{
			return configSource->getVoidPtr(qualified);
		}
		else
		{
			return nullptr;
		}
	}

	NOU::boolean ConfigurationManager::setBoolean(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified, 
		NOU::boolean v)
	{
		NOU::NOU_DAT_ALG::StringView8 sourceName;
		NOU::NOU_DAT_ALG::StringView8 qualified;

		resolveFullyQualifiedPath(fullyQualified, &sourceName, &qualified);

		return setBoolean(sourceName, qualified, v);
	}

	NOU::boolean ConfigurationManager::setBoolean(const NOU::NOU_DAT_ALG::StringView8 &sourceName,
		const NOU::NOU_DAT_ALG::StringView8 &qualified, NOU::boolean v)
	{
		ConfigurationSource *configSource = getConfigurationSource(sourceName);

		if (configSource)
		{
			return configSource->setBoolean(qualified, v);
		}
		else
		{
			return false;
		}
	}

	NOU::boolean ConfigurationManager::setString(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified,
		NOU::NOU_DAT_ALG::String8 v)
	{
		NOU::NOU_DAT_ALG::StringView8 sourceName;
		NOU::NOU_DAT_ALG::StringView8 qualified;

		resolveFullyQualifiedPath(fullyQualified, &sourceName, &qualified);

		return setString(sourceName, qualified, v);
	}

	NOU::boolean ConfigurationManager::setString(const NOU::NOU_DAT_ALG::StringView8 &sourceName,
		const NOU::NOU_DAT_ALG::StringView8 &qualified, NOU::NOU_DAT_ALG::String8 v)
	{
		ConfigurationSource *configSource = getConfigurationSource(sourceName);

		if (configSource)
		{
			return configSource->setString(qualified, v);
		}
		else
		{
			return false;
		}
	}

	NOU::boolean ConfigurationManager::setInt32(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified, 
		NOU::int32 v)
	{
		NOU::NOU_DAT_ALG::StringView8 sourceName;
		NOU::NOU_DAT_ALG::StringView8 qualified;

		resolveFullyQualifiedPath(fullyQualified, &sourceName, &qualified);

		return setInt32(sourceName, qualified, v);
	}

	NOU::boolean ConfigurationManager::setInt32(const NOU::NOU_DAT_ALG::StringView8 &sourceName,
		const NOU::NOU_DAT_ALG::StringView8 &qualified, NOU::int32 v)
	{
		ConfigurationSource *configSource = getConfigurationSource(sourceName);

		if (configSource)
		{
			return configSource->setInt32(qualified, v);
		}
		else
		{
			return false;
		}
	}

	NOU::boolean ConfigurationManager::setInt64(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified, 
		NOU::int64 v)
	{
		NOU::NOU_DAT_ALG::StringView8 sourceName;
		NOU::NOU_DAT_ALG::StringView8 qualified;

		resolveFullyQualifiedPath(fullyQualified, &sourceName, &qualified);

		return setInt64(sourceName, qualified, v);
	}

	NOU::boolean ConfigurationManager::setInt64(const NOU::NOU_DAT_ALG::StringView8 &sourceName,
		const NOU::NOU_DAT_ALG::StringView8 &qualified, NOU::int64 v)
	{
		ConfigurationSource *configSource = getConfigurationSource(sourceName);

		if (configSource)
		{
			return configSource->setInt64(qualified, v);
		}
		else
		{
			return false;
		}
	}

	NOU::boolean ConfigurationManager::setFloat32(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified, 
		NOU::float32 v)
	{
		NOU::NOU_DAT_ALG::StringView8 sourceName;
		NOU::NOU_DAT_ALG::StringView8 qualified;

		resolveFullyQualifiedPath(fullyQualified, &sourceName, &qualified);

		return setFloat32(sourceName, qualified, v);
	}

	NOU::boolean ConfigurationManager::setFloat32(const NOU::NOU_DAT_ALG::StringView8 &sourceName,
		const NOU::NOU_DAT_ALG::StringView8 &qualified, NOU::float32 v)
	{
		ConfigurationSource *configSource = getConfigurationSource(sourceName);

		if (configSource)
		{
			return configSource->setFloat32(qualified, v);
		}
		else
		{
			return false;
		}
	}

	NOU::boolean ConfigurationManager::setFloat64(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified,
		NOU::float64 v)
	{
		NOU::NOU_DAT_ALG::StringView8 sourceName;
		NOU::NOU_DAT_ALG::StringView8 qualified;

		resolveFullyQualifiedPath(fullyQualified, &sourceName, &qualified);

		return setFloat64(sourceName, qualified, v);
	}

	NOU::boolean ConfigurationManager::setFloat64(const NOU::NOU_DAT_ALG::StringView8 &sourceName,
		const NOU::NOU_DAT_ALG::StringView8 &qualified, NOU::float64 v)
	{
		ConfigurationSource *configSource = getConfigurationSource(sourceName);

		if (configSource)
		{
			return configSource->setFloat64(qualified, v);
		}
		else
		{
			return false;
		}
	}

	NOU::boolean ConfigurationManager::setVoidPtr(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified, 
		void *v)
	{
		NOU::NOU_DAT_ALG::StringView8 sourceName;
		NOU::NOU_DAT_ALG::StringView8 qualified;

		resolveFullyQualifiedPath(fullyQualified, &sourceName, &qualified);

		return setVoidPtr(sourceName, qualified, v);
	}

	NOU::boolean ConfigurationManager::setVoidPtr(const NOU::NOU_DAT_ALG::StringView8 &sourceName,
		const NOU::NOU_DAT_ALG::StringView8 &qualified, void *v)
	{
		ConfigurationSource *configSource = getConfigurationSource(sourceName);

		if (configSource)
		{
			return configSource->setVoidPtr(qualified, v);
		}
		else
		{
			return false;
		}
	}
}