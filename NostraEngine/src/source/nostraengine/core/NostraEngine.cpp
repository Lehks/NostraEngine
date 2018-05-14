#include <thread>
#include <chrono>

#include "nostraengine/core/NostraEngine.hpp"

namespace NOE::NOE_CORE{
	NostraEngine* NostraEngine::s_instance = nullptr;
	NOU::uint8 NostraEngine::s_instanceCount = 0;

	void NostraEngine::renderMain()
	{
		//------------------------------------------------------------
		//
		//PUT YOUR RENDER STUFF HERE !
		//
	}

	NostraEngine::NostraEngine() :
		m_runState(0) { }

	NOU::int32 NostraEngine::start()
	{


		preInitialize();
		initialize();
		postInitialize();

		logicMain();


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

	NOU::boolean NostraEngine::addUpdatable(Updatable *updt)
	{
		m_updatables.emplaceBack(updt);
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

	void NostraEngine::updateUpdatables()
	{
		NOU::sizeType s = m_updatables.size();
		for(NOU::sizeType i = 0; i < s; i++)
		{
			m_updatables[i]->update();
		}
	}

	NOU::int32 NostraEngine::preInitialize()
	{
		m_initializables.sort();


		NOU::sizeType s = m_initializables.size();
		for(NOU::sizeType i = 0; i < s; i++)
		{
			m_initializables[i]->preInitialize();
		}
		return 0;
	}

	NOU::int32 NostraEngine::initialize()
	{
		setMaxFPS();		//disable the FPS limiter

		NOU::sizeType initSize = m_initializables.size();

		for(NOU::sizeType i = 0; i < initSize; i++)
		{
			m_initializables[i]->initialize();
		}

		return 0;
	}

	NOU::int32 NostraEngine::postInitialize()
	{
		NOU::sizeType initSize = m_initializables.size();

		for(NOU::sizeType i = 0; i < initSize; i++)
		{
			m_initializables[i]->postInitialize();
		}
		return 0;
	}

	void NostraEngine::logicMain()
	{
		NOU::uint64 renderBeginTime, renderEndTime;
		while (m_runState != -1)
			{
				renderBeginTime = NOU::NOU_CORE::currentTimeNanos();
				updateUpdatables();
				renderEndTime   = NOU::NOU_CORE::currentTimeNanos();
				updateFrameInformations(renderBeginTime, renderEndTime);
				
				//this loop runs 1 time because of this methode.
				terminateEngine();
			}
		}
}