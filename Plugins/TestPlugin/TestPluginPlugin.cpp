#include "TestPluginPlugin.hpp"

namespace TestPluginPlugin
{
    NOE::NOE_CORE::Plugin::InitResult TestPluginPlugin::initialize(NOE::NOE_CORE::NostraEngine &engineInstance)
    {
		//std::cout << "TestPlugin::initialize()" << std::endl;

        return NOE::NOE_CORE::Plugin::InitResult::SUCCESS;
    }

	NOE::NOE_CORE::Plugin::InitResult TestPluginPlugin::terminate(NOE::NOE_CORE::NostraEngine &engineInstance)
    {
		//std::cout << "TestPlugin::terminate()" << std::endl;

		return NOE::NOE_CORE::Plugin::InitResult::SUCCESS;
    }
        
	void TestPluginPlugin::receive(NOE::NOE_CORE::Plugin::ID source, void *data, NOU::sizeType size, NOU::uint32 flags)
    {
		std::cout << "Received from: " << source << "; Data: " << reinterpret_cast<NOU::char8*>(data) << std::endl;
    }
}

NOE_SET_AS_ACTIVE_PLUGIN_CLASS(TestPluginPlugin::TestPluginPlugin);



