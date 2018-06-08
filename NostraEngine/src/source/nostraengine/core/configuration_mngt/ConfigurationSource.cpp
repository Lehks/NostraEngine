#include "nostraengine/core/configuration_mngt/ConfigrationSource.hpp"

namespace NOE::NOE_CORE
{
	void ConfigurationSource::addStorageBehavior(StorageBehavior::Value storageBehavior)
	{
		m_storageBehavior = static_cast<StorageBehavior::Value>(m_storageBehavior | storageBehavior);
	}

	void ConfigurationSource::removeStorageBehavior(StorageBehavior::Value storageBehavior)
	{
		m_storageBehavior = static_cast<StorageBehavior::Value>(m_storageBehavior & ~storageBehavior);
	}

	ConfigurationSource::ConfigurationSource(StorageBehavior::Value storageBehavior) :
		m_storageBehavior(storageBehavior)
	{}
	
	ConfigurationSource::StorageBehavior::Value ConfigurationSource::getStorageBehavior() const
	{
		return m_storageBehavior;
	}

	NOU::boolean ConfigurationSource::hasStorageBehavior(StorageBehavior::Value storageBehavior) const
	{
		return m_storageBehavior & storageBehavior;
	}

}