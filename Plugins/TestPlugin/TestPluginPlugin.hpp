#include "nostraengine/NostraEngine.hpp"

namespace TestPluginPlugin
{
    class NOU_CLASS TestPluginPlugin final : public NOE::NOE_CORE::Plugin 
    {
    public:
        /**
         * Initializes the plugin.
         */
        virtual NOE::NOE_CORE::Plugin::InitResult initialize(NOE::NOE_CORE::NostraEngine &engineInstance) override;

        /**
         * Terminates the plugin.
         */
		virtual NOE::NOE_CORE::Plugin::InitResult terminate(NOE::NOE_CORE::NostraEngine &engineInstance) override;
        
        /**
         * Receives messages from other plugins or the engine itself.
         */
		virtual void receive(NOE::NOE_CORE::Plugin::ID source, void *data, NOU::sizeType size, NOU::uint32 flags) override;
	};
}



