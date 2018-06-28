#include "nostraengine/core/configuration_mngt/ConfigurationManager.hpp"

namespace NOE::NOE_CORE
{
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
		NOU::NOU_DAT_ALG::Vector<NOU::NOU_FILE_MNGT::File> files 
			                                        = createFileList(DEFAULT_CONFIGURATION_PATH);
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
					&m_data[m_data.size() - 1]);

				NOU_LOG_INFO(
					NOU::NOU_DAT_ALG::String8("Successfully constructed configuration source ") +
					m_data[m_data.size() - 1].m_sourcePtr->getName() + " .");
			}
		}

		NOU_LOG_INFO(NOU::NOU_DAT_ALG::String8("Successfully loaded ") + m_data.size() + " of " +
		  	files.size() + " configuration sources.");

		return ret;
	}

	void ConfigurationManager::destroyFactoryMap()
	{
		//for (auto &factory : m_factoryNameDataMap.entrySet())
		{
		//	delete factory;
		}
	}

	void ConfigurationManager::resolveFullyQualifiedPath(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified,
		NOU::NOU_DAT_ALG::StringView8 *sourceName, NOU::NOU_DAT_ALG::StringView8 *qualified)
	{
		NOU::sizeType separator = fullyQualified.find(PATH_SEPARATOR);

		if (separator == NOU::NOU_DAT_ALG::StringView8::NULL_INDEX)
		{
			//push error
		}

		*sourceName = fullyQualified.logicalSubstring(0, separator);
		*qualified = fullyQualified.logicalSubstring(separator + PATH_SEPARATOR.size());
	}

	ConfigurationSource* 
		ConfigurationManager::getConfigurationSource(const NOU::NOU_DAT_ALG::StringView8 &sourceName)
	{
		return m_nameDataMap.get(sourceName)->m_sourcePtr.rawPtr();
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

	void ConfigurationManager::setLoadMode(LoadMode loadMode)
	{
		if (!m_wasInitCalled)
		{
			m_loadMode = loadMode;
		}
#ifndef NOU_LOG_DEBUG_DISABLE
		else
		{
			NOU_LOG_DEBUG("It was attempted to change the load mode of the configuration manager after "
				"it was initialized. The changes were not made; the load mode is still the same.");
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
			NOU_LOG_DEBUG("It was attempted to get the type of an entry value in a configuration that does "
				"not exist.");
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
			NOU_LOG_DEBUG("It was attempted to check the availability of an entry in a configuration that "
				"does not exist.");
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
			NOU_LOG_DEBUG("It was attempted to get a value from an entry in a configuration that "
				"does not exist.");
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
			NOU_LOG_DEBUG("It was attempted to get a value from an entry in a configuration that "
				"does not exist.");
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
			NOU_LOG_DEBUG("It was attempted to get a value from an entry in a configuration that "
				"does not exist.");
			return 0;
		}
	}

	NOU::int64 ConfigurationManager::getInt64(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified) const
	{
		NOU::NOU_DAT_ALG::StringView8 sourceName;
		NOU::NOU_DAT_ALG::StringView8 qualified;

		resolveFullyQualifiedPath(fullyQualified, &sourceName, &qualified);

		return getInt32(sourceName, qualified);
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
			NOU_LOG_DEBUG("It was attempted to get a value from an entry in a configuration that "
				"does not exist.");
			return 0;
		}
	}

	NOU::float32 ConfigurationManager::getFloat32(const NOU::NOU_DAT_ALG::StringView8 &fullyQualified) const
	{
		NOU::NOU_DAT_ALG::StringView8 sourceName;
		NOU::NOU_DAT_ALG::StringView8 qualified;

		resolveFullyQualifiedPath(fullyQualified, &sourceName, &qualified);

		return getBoolean(sourceName, qualified);
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
			NOU_LOG_DEBUG("It was attempted to get a value from an entry in a configuration that "
				"does not exist.");
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
			NOU_LOG_DEBUG("It was attempted to get a value from an entry in a configuration that "
				"does not exist.");
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
			NOU_LOG_DEBUG("It was attempted to get a value from an entry in a configuration that "
				"does not exist.");
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
			NOU_LOG_DEBUG("It was attempted to set a value from an entry in a configuration that "
				"does not exist.");
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
			NOU_LOG_DEBUG("It was attempted to set a value from an entry in a configuration that "
				"does not exist.");
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
			NOU_LOG_DEBUG("It was attempted to set a value from an entry in a configuration that "
				"does not exist.");
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
			NOU_LOG_DEBUG("It was attempted to set a value from an entry in a configuration that "
				"does not exist.");
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
			NOU_LOG_DEBUG("It was attempted to set a value from an entry in a configuration that "
				"does not exist.");
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
			NOU_LOG_DEBUG("It was attempted to set a value from an entry in a configuration that "
				"does not exist.");
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
			NOU_LOG_DEBUG("It was attempted to set a value from an entry in a configuration that "
				"does not exist.");
			return false;
		}
	}
}