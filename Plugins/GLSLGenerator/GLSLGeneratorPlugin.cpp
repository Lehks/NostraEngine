#include "GLSLGeneratorPlugin.hpp"

namespace GLSLGeneratorPlugin
{
    NOE::NOE_CORE::Plugin::InitResult GLSLGeneratorPlugin::initialize(NOE::NOE_CORE::NostraEngine &engineInstance)
    {
        NOU_LOG_DEBUG("GLFW initialization successful!");
        return NOE::NOE_CORE::Plugin::InitResult::SUCCESS;

    }

	NOE::NOE_CORE::Plugin::InitResult GLSLGeneratorPlugin::terminate(NOE::NOE_CORE::NostraEngine &engineInstance)
    {
		NOU_LOG_DEBUG("GLFW successfully terminated!");
		return NOE::NOE_CORE::Plugin::InitResult::SUCCESS;
    }
        
	void GLSLGeneratorPlugin::receive(NOE::NOE_CORE::Plugin::ID source, void *data, NOU::sizeType size, NOU::uint32 flags)
    {

    }
}

NOE_SET_AS_ACTIVE_PLUGIN_CLASS(GLSLGeneratorPlugin::GLSLGeneratorPlugin);

