#ifndef	INI_CONFIGURATION_PLUGIN_HPP
#define	INI_CONFIGURATION_PLUGIN_HPP

#include "nostraengine/NostraEngine.hpp"

namespace IniConfigurationPlugin
{
    class IniConfigurationPlugin final : public NOE::NOE_CORE::Plugin 
    {
    public:
        /**
         * Initializes the plugin.
         */
		NOE_PLUGIN_FUNC virtual NOE::NOE_CORE::Plugin::InitResult 
											initialize(NOE::NOE_CORE::NostraEngine &engineInstance) override;

        /**
         * Terminates the plugin.
         */
		NOE_PLUGIN_FUNC virtual NOE::NOE_CORE::Plugin::InitResult 
											terminate(NOE::NOE_CORE::NostraEngine &engineInstance) override;
        
        /**
         * Receives messages from other plugins or the engine itself.
         */
		NOE_PLUGIN_FUNC virtual void receive(NOE::NOE_CORE::Plugin::ID source, void *data, 
															NOU::sizeType size, NOU::uint32 flags) override;
	};
}

#endif

