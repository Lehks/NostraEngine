#include "nostraengine/core/configuration_mngt/ConfigrationSource.hpp"

namespace NOE::NOE_CORE
{
	void ConfigurationSource::addStorageBehavior(StorageBehavior storageBehavior)
	{
		m_storageBehavior = static_cast<StorageBehavior>(m_storageBehavior | storageBehavior);
	}

	void ConfigurationSource::removeStorageBehavior(StorageBehavior storageBehavior)
	{
		m_storageBehavior = static_cast<StorageBehavior>(m_storageBehavior & ~storageBehavior);
	}

	ConfigurationSource::ConfigurationSource(StorageBehavior storageBehavior) :
		m_storageBehavior(storageBehavior)
	{}
	
	ConfigurationSource::StorageBehavior ConfigurationSource::getStorageBehavior() const
	{
		return m_storageBehavior;
	}

	NOU::boolean ConfigurationSource::hasStorageBehavior(StorageBehavior storageBehavior) const
	{
		return static_cast<NOU::boolean>(m_storageBehavior & storageBehavior);
	}

}