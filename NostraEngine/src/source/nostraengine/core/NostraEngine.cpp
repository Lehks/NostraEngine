#include <thread>
#include <chrono>

#include "nostraengine/core/NostraEngine.hpp"

namespace NOE::NOE_CORE{
	NostraEngine* NostraEngine::s_instance = nullptr;
	NOU::uint8 NostraEngine::s_instanceCount = 0;

	void NostraEngine::render()
	{
		//------------------------------------------------------------
		//
		//PUT YOUR RENDER STUFF HERE !
		//
	}

	NostraEngine::NostraEngine() :
		m_runState(0) { }

	NOU::int32 NostraEngine::initialize()
	{
		//------------------------------------------------------------
		//
		//DO YOUR STANDARD INIT METHOD'S HERE !
		//
		setMaxFPS();		//disable the FPS limiter

		return 0;
	}

	NOU::int32 NostraEngine::start()
	{
		NOU::uint64 renderBeginTime, renderEndTime;

		if (initialize() != 0)
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

	NOU::int32 NostraEngine::terminate()
	{
		//------------------------------------------------------------
		//
		//DO YOUR STANDARD TERMINATE METHOD'S HERE !
		//
		return 0;
	}

	void NostraEngine::updateFrameInformations(const NOU::uint32 begin, const NOU::uint32 end)
	{
		m_frameTime = end - begin;
		m_currFPS   = 1000 / ((m_frameTime != 0) ? m_frameTime : 1);
	}

	void NostraEngine::setMaxFPS(const NOU::uint64 maxFPS)
	{
		m_maxFPS = maxFPS;
	}

	void NostraEngine::terminateEngine()
	{
		m_runState = -1;
	}

	const NOU::uint64& NostraEngine::getCurrFPS()
	{
		return m_currFPS;
	}

	const NOU::uint64& NostraEngine::getMaxFPS()
	{
		return m_maxFPS;
	}

	const NOU::uint32& NostraEngine::getFrameTime()
	{
		return m_frameTime;
	}

	void NostraEngine::fpsLimitStart()
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

	NOU::boolean NostraEngine::addInitializable(Initializable *init)
	{
		m_initializables.emplaceBack(init);
		return true;
	}

	NostraEngine &NostraEngine::get()
	{
		return *(s_instance);
	}

	void NostraEngine::setActiveInstance(NostraEngine &instance)
	{
		if(&instance == nullptr)
		{
			NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(), NOU::NOU_CORE::ErrorCodes::INVALID_STATE, "Cannot set the instance to a nullptr");
		} else
		{
			s_instance = &instance;
		}
	}

	NostraEngine *NostraEngine::createInstance()
	{
		if(s_instanceCount < 1)
		{
			static NostraEngine instance;
			s_instanceCount++;
			return &instance;
		}
		return nullptr;
	}
}

// 1000 / ms = fps | /fps
// 1000 / ms * fps = 1 | *ms
// 1000 / fps = ms