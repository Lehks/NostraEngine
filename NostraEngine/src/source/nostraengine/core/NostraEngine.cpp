#include "nostraengine/core/NostraEngine.hpp"

void NOE::NostraEngine::render()
{
	//------------------------------------------------------------
	//
	//PUT YOUR RENDER STUFF HERE !
	//
}

NOE::NostraEngine::NostraEngine(NOU::int32 ID) :
	ID(ID)
{}

NOU::int8 NOE::NostraEngine::init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//The two lines above mean OpenGL version 4.0.

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//------------------------------------------------------------
	//
	//DO YOUR STANDARD INIT METHOD'S HERE !
	//


	return 0;
}

NOU::int8 NOE::NostraEngine::start()
{

	init();
	if (init != 0)
	{
		std::cout << "An error occurred during initialization."  << std::endl;
		return 1;
	}

	while (true)			//DON'T RUN IT !!!!
	{
		render();
	}

	terminate();

	return 0;
}

NOU::int8 NOE::NostraEngine::terminate()
{
	glfwTerminate();

	//------------------------------------------------------------
	//
	//DO YOUR STANDARD TERMINATE METHOD'S HERE !
	//
	return 0;
}
