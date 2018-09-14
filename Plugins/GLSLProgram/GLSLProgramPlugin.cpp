#include "GLSLProgramPlugin.hpp"

namespace GLSLProgramPlugin
{
    NOE::NOE_CORE::Plugin::InitResult GLSLProgramPlugin::initialize(NOE::NOE_CORE::NostraEngine &engineInstance)
    {
			NOU_LOG_DEBUG("GLSL Program Plugin initialization successful!");
			return NOE::NOE_CORE::Plugin::InitResult::SUCCESS;
		}
    }

	NOE::NOE_CORE::Plugin::InitResult GLSLProgramPlugin::terminate(NOE::NOE_CORE::NostraEngine &engineInstance)
    {
		NOU_LOG_DEBUG("GLSL Program Plugin successfully terminated!");
		return NOE::NOE_CORE::Plugin::InitResult::SUCCESS;
    }

	void GLFWWindowPlugin::receive(NOE::NOE_CORE::Plugin::ID source, void *data, NOU::sizeType size, NOU::uint32 flags)
    {

    }
}

NOE_SET_AS_ACTIVE_PLUGIN_CLASS(GLMaterialPlugin::GLMaterialPlugin);
