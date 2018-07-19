#include "GLRenderablePlugin.hpp"

#include "glad/glad.h"

namespace GLRenderablePlugin
{
	NOE::NOE_CORE::Plugin::InitResult GLRenderablePlugin::initialize(NOE::NOE_CORE::NostraEngine &engineInstance)
	{
		gladLoadGL();
		return NOE::NOE_CORE::Plugin::InitResult::SUCCESS;
	}

	NOE::NOE_CORE::Plugin::InitResult GLRenderablePlugin::terminate(NOE::NOE_CORE::NostraEngine &engineInstance)
	{
		return NOE::NOE_CORE::Plugin::InitResult::SUCCESS;
	}

	void GLRenderablePlugin::receive(NOE::NOE_CORE::Plugin::ID source, void *data, NOU::sizeType size, NOU::uint32 flags)
	{

	}
}