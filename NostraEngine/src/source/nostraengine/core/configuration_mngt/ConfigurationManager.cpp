#include "nostraengine/core/configuration_mngt/ConfigurationManager.hpp"

namespace NOE::NOE_CORE
{
	const NOU::NOU_DAT_ALG::StringView8 ConfigurationManager::INITIALIZABLE_NAME = "Configuration Management";

	const ConfigurationManager::LoadMode ConfigurationManager::DEFAULT_LOAD_MODE 
		                                                                       = LoadMode::LOAD_ON_INITIALIZE;

	const NOU::sizeType ConfigurationManager::DEFAULT_FACTORY_MAP_CAPACITY = 100;

	ConfigurationManager::ConfigurationManager() :
		m_loadMode(DEFAULT_LOAD_MODE),
		m_wasInitCalled(false),
		m_factoryNameDataMap(DEFAULT_FACTORY_MAP_CAPACITY)
	{}

	void ConfigurationManager::loadPluginList()
	{

	}

	void ConfigurationManager::destroyFactoryMap()
	{
		for (auto &factory : m_factoryNameDataMap.entrySet())
		{
			delete factory;
		}
	}

	ConfigurationManager& ConfigurationManager::get()
	{
		static ConfigurationManager instance;
		return instance;
	}

	Initializable::ExitCode ConfigurationManager::initialize()
	{
		m_wasInitCalled = true;
		//from here on, m_loadMode will not change its value

		loadPluginList();

		//all configuration sources are constructed now and the factories are no longer needed
		destroyFactoryMap();

		//if mode is set, initialize all configuration sources
		if (m_loadMode == LoadMode::LOAD_ON_INITIALIZE)
		{
			for (NOU::sizeType i = 0; i < m_data.size(); i++)
			{
				if (m_data[i].m_isInitialized)
				{
					m_data[i].m_sourcePtr->initialize();
				}
			}
		}
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
			configSource->getTypeOf(qualified);
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
			configSource->hasEntry(qualified);
		}
		else
		{
			NOU_LOG_DEBUG("It was attempted to check the availability of an entry in a configuration that "
				"does not exist.");
			return false;
		}
	}
}