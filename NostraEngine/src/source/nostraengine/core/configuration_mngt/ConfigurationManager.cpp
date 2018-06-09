#include "nostraengine/core/configuration_mngt/ConfigurationManager.hpp"

namespace NOE::NOE_CORE
{
	const NOU::NOU_DAT_ALG::StringView8 ConfigurationManager::INITIALIZABLE_NAME = "Configuration Management";

	const ConfigurationManager::LoadMode ConfigurationManager::DEFAULT_LOAD_MODE 
		                                                                       = LoadMode::LOAD_ON_INITIALIZE;

	ConfigurationManager::ConfigurationManager() :
		m_loadMode(DEFAULT_LOAD_MODE),
		m_wasInitCalled(false)
	{}

	ConfigurationManager& ConfigurationManager::get()
	{
		static ConfigurationManager instance;
		return instance;
	}

	Initializable::ExitCode ConfigurationManager::initialize()
	{
		m_wasInitCalled = true;

		loadPluginList();

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
	}
}