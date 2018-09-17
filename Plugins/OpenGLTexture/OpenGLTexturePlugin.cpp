#include "OpenGLTexturePlugin.hpp"

namespace OpenGLTexturePlugin
{
    NOE::NOE_CORE::Plugin::InitResult OpenGLTexturePlugin::initialize(NOE::NOE_CORE::NostraEngine &engineInstance)
    {
			NOU_LOG_DEBUG("OpenGL Texture Plugin initialization successful!");
			return NOE::NOE_CORE::Plugin::InitResult::SUCCESS;
    }

	NOE::NOE_CORE::Plugin::InitResult OpenGLTexturePlugin::terminate(NOE::NOE_CORE::NostraEngine &engineInstance)
    {
		NOU_LOG_DEBUG("OpenGL Texture successfully terminated!");
		return NOE::NOE_CORE::Plugin::InitResult::SUCCESS;
    }

	void OpenGLTexturePlugin::receive(NOE::NOE_CORE::Plugin::ID source, void *data, NOU::sizeType size, NOU::uint32 flags)
    {

    }
}

NOE_SET_AS_ACTIVE_PLUGIN_CLASS(OpenGLTexturePlugin::OpenGLTexturePlugin);
