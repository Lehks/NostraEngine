#include "TestPluginPlugin2.hpp"

namespace TestPluginPlugin2
{
    NOE::NOE_CORE::Plugin::InitResult TestPluginPlugin2::initialize(NOE::NOE_CORE::NostraEngine &engineInstance)
    {
		std::cout << "TestPlugin2::initialize()" << std::endl;

		send(666941819, "Hello Plugin!", sizeof("Hello Plugin!"), 0);

        return NOE::NOE_CORE::Plugin::InitResult::SUCCESS;
    }

	NOE::NOE_CORE::Plugin::InitResult TestPluginPlugin2::terminate(NOE::NOE_CORE::NostraEngine &engineInstance)
    {
		std::cout << "TestPlugin2::terminate()" << std::endl;

		return NOE::NOE_CORE::Plugin::InitResult::SUCCESS;
    }
        
	void TestPluginPlugin2::receive(NOE::NOE_CORE::Plugin::ID source, void *data, NOU::sizeType size, NOU::uint32 flags)
    {

    }
}

#define NOU_FUNC __declspec(dllexport)

NOE_SET_AS_ACTIVE_PLUGIN_CLASS(TestPluginPlugin2::TestPluginPlugin2);



