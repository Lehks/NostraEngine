#ifndef	INI_CONFIGURATION_SOURCE_FACTORY_HPP
#define INI_CONFIGURATION_SOURCE_FACTORY_HPP

#include "nostraengine/NostraEngine.hpp"

namespace IniConfigurationPlugin
{
	class NOU_CLASS IniConfigurationSourceFactory final : public NOE::NOE_CORE::ConfigurationSourceFactory
	{
	public:
		static const NOU::NOU_DAT_ALG::StringView8 EXTENSION;

		virtual const NOU::NOU_DAT_ALG::StringView8& getAssociatedExtension() const override;

		virtual NOE::NOE_CORE::ConfigurationSource* build(const NOU::NOU_FILE_MNGT::Path &path) override;
	};
}

#endif