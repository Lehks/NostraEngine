#include <thread>
#include <chrono>

#include "nostraengine/core/NostraEngine.hpp"

void NOE::NOE_CORE::NostraEngine::render()
{
	//------------------------------------------------------------
	//
	//PUT YOUR RENDER STUFF HERE !
	//
}

NOE::NOE_CORE::NostraEngine::NostraEngine(NOU::int32 ID) :
	ID(ID),
	m_runState(0)
{

}

NOU::int32 NOE::NOE_CORE::NostraEngine::load()
{
	//------------------------------------------------------------
	//
	//DO YOUR STANDARD INIT METHOD'S HERE !
	//
	setMaxFPS();		//disable the FPS limiter

	return 0;
}

NOU::int32 NOE::NOE_CORE::NostraEngine::start()
{
	NOU::uint64 renderBeginTime, renderEndTime;

	if (load() != 0)
	{
		std::cout << "An error occurred during initialization."  << std::endl;
		return 1;
	}


	while (m_runState != -1)			//DON'T RUN IT !!!!
	{
		renderBeginTime = NOU::NOU_CORE::currentTimeNanos();
		render();
		renderEndTime   = NOU::NOU_CORE::currentTimeNanos();
		updateFrameInformations(renderBeginTime, renderEndTime);
        
		//this loop runs 1 time because of this methode.
		terminateEngine();
	}

	terminate();

	return 0;
}

NOU::int32 NOE::NOE_CORE::NostraEngine::terminate()
{
	//------------------------------------------------------------
	//
	//DO YOUR STANDARD TERMINATE METHOD'S HERE !
	//
	return 0;
}

void NOE::NOE_CORE::NostraEngine::updateFrameInformations(const NOU::uint32 begin, const NOU::uint32 end)
{
	m_frameTime = end - begin;
	m_currFPS   = 1000 / ((m_frameTime != 0) ? m_frameTime : 1);
}

void NOE::NOE_CORE::NostraEngine::setMaxFPS(const NOU::uint64 maxFPS)
{
	m_maxFPS = maxFPS;
}

void NOE::NOE_CORE::NostraEngine::terminateEngine()
{
	m_runState = -1;
}

const NOU::uint64& NOE::NOE_CORE::NostraEngine::getCurrFPS()
{
	return m_currFPS;
}

const NOU::uint64& NOE::NOE_CORE::NostraEngine::getMaxFPS()
{
	return m_maxFPS;
}

const NOU::uint32& NOE::NOE_CORE::NostraEngine::getFrameTime()
{
	return m_frameTime;
}

void NOE::NOE_CORE::NostraEngine::fpsLimitStart()
{
	if(getMaxFPS() > 0)
	{
		NOU::uint64 minFrameTime, timeDiff;
		NOU::uint64 currFPS = getCurrFPS();
		minFrameTime = 1000/((currFPS != 0) ? currFPS : 1);
		if(getFrameTime() < minFrameTime)
		{	
			timeDiff = minFrameTime - getFrameTime();
			std::chrono::milliseconds msDuration(timeDiff);
			std::this_thread::sleep_for<>(msDuration);
		}
	}
}

NOU::boolean NOE::NOE_CORE::NostraEngine::addInitializable(NOE::NOE_CORE::Initializable *init)
{
	m_initializables.emplaceBack(init);
	return true;
}

// 1000 / ms = fps | /fps
// 1000 / ms * fps = 1 | *ms
// 1000 / fps = ms