#include "GLFWWindowPlugin.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace GLFWWindowPlugin
{
    NOE::NOE_CORE::Plugin::InitResult GLFWWindowPlugin::initialize(NOE::NOE_CORE::NostraEngine &engineInstance)
    {
		if (glfwInit())
		{
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

#if NOU_OS == NOU_OS_MAC
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

			return NOE::NOE_CORE::Plugin::InitResult::SUCCESS;
		}
		else
			return NOE::NOE_CORE::Plugin::InitResult::FAILED;

		m_window = GLFWWindow();

		//set window in main
    }

	NOE::NOE_CORE::Plugin::InitResult GLFWWindowPlugin::terminate(NOE::NOE_CORE::NostraEngine &engineInstance)
    {
		glfwTerminate();

		return NOE::NOE_CORE::Plugin::InitResult::SUCCESS;
    }
        
	void GLFWWindowPlugin::receive(NOE::NOE_CORE::Plugin::ID source, void *data, NOU::sizeType size, NOU::uint32 flags)
    {

    }
}

NOE_SET_AS_ACTIVE_PLUGIN_CLASS(GLFWWindowPlugin::GLFWWindowPlugin);

