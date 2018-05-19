#include <thread>
#include <chrono>

#include "nostraengine/core/NostraEngine.hpp"

namespace NOE::NOE_CORE{

	//----------------------------------------------------- Start Private ------------------------------------------------------


	NostraEngine* NostraEngine::s_instance = nullptr;
	NOU::uint8 NostraEngine::s_instanceCount = 0;

	//CONSTRUCTOR
	NostraEngine::NostraEngine() :
		m_runState(0),
		m_version(0, 0, 1),
		m_logger(NOU::NOU_CORE::Logger::instance()),
		m_initializedObjects(0),
		m_preInitializedObjects(0)
	{
		m_logger->pushLogger<NOU::NOU_CORE::FileLogger>();
		m_logger->pushLogger<NOU::NOU_CORE::ConsoleLogger>();
	}

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
			// m_initializables[i]->preInitialize();
			m_preInitializedObjects++;
		}
		return ExitCode::SUCCESS;
	}

	ExitCode NostraEngine::initialize()
	{
		setMaxFPS();		//disable the FPS limiter

		NOU::sizeType initSize = m_initializables.size();

		for (NOU::sizeType i = 0; i < initSize; i++)
		{
			if(m_initializables[i]->initialize() == ExitCode::ERROR)
			{
				return ExitCode::ERROR;
			}
			m_initializedObjects++;
		}

		return ExitCode::SUCCESS;
	}

	ExitCode NostraEngine::postInitialize()
	{
		NOU::sizeType initSize = m_initializables.size();

		if(m_initializedObjects != initSize)
		{
			return ExitCode::ERROR;
		}

		for (NOU::sizeType i = 0; i < initSize; i++)
		{
			m_initializables[i]->postInitialize();
		}
		return ExitCode::SUCCESS;
	}

	ExitCode NostraEngine::terminate()
	{

		if (m_initializables.size() == 0)
		{
			return ExitCode::SUCCESS;
		}

		if(m_initializedObjects == 0)
		{
			return ExitCode::SUCCESS;
		}

		for (NOU::sizeType i = 0; i < m_initializedObjects; i++)
		{
			m_initializables[m_initializedObjects - i - 1]->terminate();
		}

		return ExitCode::SUCCESS;
	}

	ExitCode NostraEngine::postTerminate()
	{

		return ExitCode::SUCCESS;
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

	NOU::int32 NostraEngine::start()
	{
		
		m_logger->write(NOU::NOU_CORE::EventLevelCodes::INFO, getVersion().rawStr() ,"EngineLog.txt");



		m_initializables.sort();

		if(preInitialize() == ExitCode::ERROR)
		{
			m_runState = -1;
		}else{

			if(initialize() == ExitCode::ERROR)
			{
				m_runState = -1;
			}
			postInitialize();
		}

		mainLoop();

		terminate();
		postTerminate();

		return 0;
	}

	void NostraEngine::mainLoop()
	{
		NOU::uint64 renderBeginTime, renderEndTime;
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