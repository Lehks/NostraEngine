#include "IniConfigurationSourceFactory.hpp"
#include "IniConfigurationSource.hpp"

namespace IniConfigurationPlugin
{
	const NOU::NOU_DAT_ALG::StringView8 IniConfigurationSourceFactory::EXTENSION = "ini";

	const NOU::NOU_DAT_ALG::StringView8& IniConfigurationSourceFactory::getAssociatedExtension() const
	{
		return EXTENSION;
	}

	NOE::NOE_CORE::ConfigurationSource* 
		IniConfigurationSourceFactory::build(const NOU::NOU_FILE_MNGT::Path &path)
	{
		return NOE::NOE_CORE::ConfigurationSourceFactory::allocateSource<IniConfigurationSource>(path);
	}
}