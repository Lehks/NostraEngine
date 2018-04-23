#include <thread>
#include <chrono>

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
{
	m_runState = 0;
}

NOU::int32 NOE::NostraEngine::init()
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
	setMaxFPS();		//disable the FPS limiter

	return 0;
}

NOU::int32 NOE::NostraEngine::start()
{
	NOU::uint32 renderBeginTime, renderEndTime;

	if (init() != 0)
	{
		std::cout << "An error occurred during initialization."  << std::endl;
		return 1;
	}


	while (!m_runState == -1)			//DON'T RUN IT !!!!
	{
		renderBeginTime = NOU::NOU_CORE::currentTimeMillis();
		render();
		renderEndTime   = NOU::NOU_CORE::currentTimeMillis();
		updateFrameInformations(renderBeginTime, renderEndTime);

		std::cout << "HAllo" << std::endl;
		//this loop runs 1 time because of this methode.
		terminateEngine();
	}

	terminate();

	return 0;
}

NOU::int32 NOE::NostraEngine::terminate()
{
	glfwTerminate();

	//------------------------------------------------------------
	//
	//DO YOUR STANDARD TERMINATE METHOD'S HERE !
	//
	return 0;
}

void NOE::NostraEngine::updateFrameInformations(const NOU::uint32 begin, const NOU::uint32 end)
{
	m_frameTime = end - begin;
	m_currFPS   = 1000 / m_frameTime;
}

void NOE::NostraEngine::setMaxFPS(const NOU::uint64 maxFPS)
{
	m_maxFPS = maxFPS;
}

void NOE::NostraEngine::terminateEngine()
{
	m_runState = -1;
}

const NOU::uint64& NOE::NostraEngine::getCurrFPS()
{
	return m_currFPS;
}

const NOU::uint64& NOE::NostraEngine::getMaxFPS()
{
	return m_maxFPS;
}

const NOU::uint32& NOE::NostraEngine::getFrameTime()
{
	return m_frameTime;
}

void NOE::NostraEngine::fpsLimitStart()
{
	if(getMaxFPS() > 0)
	{
		NOU::uint64 minFrameTime, timeDiff;

		minFrameTime = 1000/getCurrFPS();
		if(getFrameTime() < minFrameTime)
		{	
			timeDiff = minFrameTime - getFrameTime();
			std::chrono::milliseconds msDuration(timeDiff);
			std::this_thread::sleep_for<>(msDuration);
		}
	}
}

// 1000 / ms = fps | /fps
// 1000 / ms * fps = 1 | *ms
// 1000 / fps = ms