#include "GLMaterialPlugin.hpp"

namespace GLFMaterialPlugin
{
    NOE::NOE_CORE::Plugin::InitResult GLFMaterialPlugin::initialize(NOE::NOE_CORE::NostraEngine &engineInstance)
    {
			NOU_LOG_DEBUG("OpenGL Material Plugin initialization successful!");
			return NOE::NOE_CORE::Plugin::InitResult::SUCCESS;
		}
    }

	NOE::NOE_CORE::Plugin::InitResult GLMaterialPlugin::terminate(NOE::NOE_CORE::NostraEngine &engineInstance)
    {
		NOU_LOG_DEBUG("OpenGL Material Plugin successfully terminated!");
		return NOE::NOE_CORE::Plugin::InitResult::SUCCESS;
    }

	void GLFWWindowPlugin::receive(NOE::NOE_CORE::Plugin::ID source, void *data, NOU::sizeType size, NOU::uint32 flags)
    {

    }
}

NOE_SET_AS_ACTIVE_PLUGIN_CLASS(GLMaterialPlugin::GLMaterialPlugin);
