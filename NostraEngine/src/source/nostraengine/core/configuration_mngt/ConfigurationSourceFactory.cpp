#include "nostraengine/core/configuration_mngt/ConfigurationSourceFactory.hpp"

namespace NOE::NOE_CORE
{
	void ConfigurationSourceFactory::deallocateSource(ConfigurationSource *source)
	{
		delete source;
	}
}