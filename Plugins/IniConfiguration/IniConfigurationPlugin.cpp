#include "IniConfigurationPlugin.hpp"
#include "src/iniconf/IniConfigurationSourceFactory.hpp"

namespace IniConfigurationPlugin
{
    NOE::NOE_CORE::Plugin::InitResult IniConfigurationPlugin::initialize(NOE::NOE_CORE::NostraEngine &engineInstance)
    {
		NOE::NOE_CORE::ConfigurationManager::get().addSourceFactory<IniConfigurationSourceFactory>();

        return NOE::NOE_CORE::Plugin::InitResult::SUCCESS;
    }

	NOE::NOE_CORE::Plugin::InitResult IniConfigurationPlugin::terminate(NOE::NOE_CORE::NostraEngine &engineInstance)
    {
		return NOE::NOE_CORE::Plugin::InitResult::SUCCESS;
    }
        
	void IniConfigurationPlugin::receive(NOE::NOE_CORE::Plugin::ID source, void *data, NOU::sizeType size, NOU::uint32 flags)
    {

    }
}

NOE_SET_AS_ACTIVE_PLUGIN_CLASS(IniConfigurationPlugin::IniConfigurationPlugin);



