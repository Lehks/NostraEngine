#include <thread>
#include <chrono>

#include "nostraengine/core/NostraEngine.hpp"

namespace NOE::NOE_CORE{

	//----------------------------------------------------- Start Private ------------------------------------------------------

	NostraEngine* NostraEngine::s_instance = nullptr;
	NOU::uint8 NostraEngine::s_instanceCount = 0;

	void NostraEngine::updateFrameInformations(const NOU::uint32 begin, const NOU::uint32 end)
	{
		m_frameTime = end - begin;
		m_currFPS = 1000 / ((m_frameTime != 0) ? m_frameTime : 1);
	}

	void NostraEngine::fpsLimitStart()
	{
		if (getMaxFPS() > 0)
		{
			NOU::uint64 minFrameTime, timeDiff;
			NOU::uint64 currFPS = getCurrFPS();
			minFrameTime = 1000 / ((currFPS != 0) ? currFPS : 1);
			if (getFrameTime() < minFrameTime)
			{
				timeDiff = minFrameTime - getFrameTime();
				std::chrono::milliseconds msDuration(timeDiff);
				std::this_thread::sleep_for<>(msDuration);
			}
		}
	}

	ExitCode NostraEngine::preInitialize()
	{



		NOU::sizeType s = m_initializables.size();
		for (NOU::sizeType i = 0; i < s; i++)
		{
			m_initializables[i]->preInitialize();
		}
		return 0;
	}

	ExitCode NostraEngine::initialize()
	{
		setMaxFPS();		//disable the FPS limiter

		NOU::sizeType initSize = m_initializables.size();

		for (NOU::sizeType i = 0; i < initSize; i++)
		{
			m_initializables[i]->initialize();
		}

		return 0;
	}

	ExitCode NostraEngine::postInitialize()
	{
		NOU::sizeType initSize = m_initializables.size();

		for (NOU::sizeType i = 0; i < initSize; i++)
		{
			m_initializables[i]->postInitialize();
		}
		return 0;
	}

	ExitCode NostraEngine::terminate()
	{
		NOU::sizeType initVecSize = m_initializables.size();

		if (initVecSize == 0)
		{
			return 0;
		}

		for (NOU::sizeType i = 0; i < initVecSize; i++)
		{
			m_initializables[initVecSize - i - 1]->terminate();
		}

		return 0;
	}

	ExitCode NostraEngine::postTerminate()
	{
		NOU::sizeType initVecSize = m_initializables.size();

		if (initVecSize == 0)
		{
			return 0;
		}

		for (NOU::sizeType i = 0; i < initVecSize; i++)
		{
			m_initializables[initVecSize - i - 1]->postTerminate();
		}

		return 0;
	}

	//CONSTRUCTOR
	NostraEngine::NostraEngine() :
		m_runState(0),
		m_version(0, 0, 1),
		m_logger(NOU::NOU_CORE::Logger::instance())
	{
		m_logger->pushLogger<NOU::NOU_CORE::FileLogger>();
		m_logger->pushLogger<NOU::NOU_CORE::ConsoleLogger>();
	}

	void NostraEngine::logicMain()
	{
		updateUpdatables();
	}

	void NostraEngine::renderMain()
	{

	}

	NOU::boolean NostraEngine::addUpdatable(Updatable *updt)
	{
		m_updatables.emplaceBack(updt);
		return true;
	}

	NOU::boolean NostraEngine::addInitializable(Initializable *init)
	{
		m_initializables.emplaceBack(init);
		return true;
	}

	NOU::boolean NostraEngine::removeUpdatable(Updatable *updt)
	{
		NOU::sizeType s = m_updatables.size();
		for(NOU::sizeType i = 0; i < s; i++)
		{
			if(m_updatables[i] == updt)
			{
				m_updatables.remove(i);
				return true;
			}
		}
		return false;
	}

	NOU::boolean NostraEngine::removeInitializable(Initializable *init)
	{
		NOU::sizeType s = m_initializables.size();
		for(NOU::sizeType i = 0; i < s; i++)
		{
			if(m_initializables[i] == init)
			{
				m_initializables.remove(i);
				return true;
			}
		}
		return false;
	}

	//----------------------------------------------------- End Private ------------------------------------------------------

	//----------------------------------------------------- Start public -----------------------------------------------------

	ExitCode NostraEngine::start()
	{
		
		m_logger->write(NOU::NOU_CORE::EventLevelCodes::INFO, getVersion().rawStr() ,"EngineLog.txt");

        NOU::uint64 renderBeginTime, renderEndTime;

		m_initializables.sort();

		preInitialize();
		initialize();
		postInitialize();

		//@Lukas Groß: please add || (statement of window) so that the engine can be terminated with the x button of the window.
		while(m_runState != -1)
        {
            renderBeginTime = NOU::NOU_CORE::currentTimeNanos();
            logicMain();
            renderMain();
            renderEndTime   = NOU::NOU_CORE::currentTimeNanos();
            updateFrameInformations(renderBeginTime, renderEndTime);

            //Engine Runs just 1 time.
            terminateEngine();
        }

		terminate();
		postTerminate();

		return 0;
	}

	NostraEngine *NostraEngine::createInstance()
	{
		if (s_instanceCount < 1)
		{
			static NostraEngine instance;
			s_instanceCount++;
			return &instance;
		}
		return nullptr;
	}

	NostraEngine &NostraEngine::get()
	{
		return *(s_instance);
	}

	void NostraEngine::setActiveInstance(NostraEngine &instance)
	{
		if (&instance == nullptr)
		{
			NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(), NOU::NOU_CORE::ErrorCodes::INVALID_STATE, "Cannot set the instance to a nullptr");
		}
		else
		{
			s_instance = &instance;
		}
	}

	void NostraEngine::terminateEngine()
	{
		m_runState = -1;
	}


	void NostraEngine::updateUpdatables()
	{
		NOU::sizeType s = m_updatables.size();
		for (NOU::sizeType i = 0; i < s; i++)
		{
			m_updatables[i]->update();
		}
	}

	void NostraEngine::setMaxFPS(const NOU::uint64 maxFPS)
	{
		m_maxFPS = maxFPS;
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

    const NOU::NOU_DAT_ALG::String8 & NostraEngine::getVersion()
    {

		NOU::NOU_DAT_ALG::String8 ver;

		ver.append(m_version.getMajor());
		ver.append('.');
		ver.append(m_version.getMinor());
		ver.append('.');
		ver.append(m_version.getPatch());

        return ver;
    }

	//----------------------------------------------------- End public -----------------------------------------------------
}