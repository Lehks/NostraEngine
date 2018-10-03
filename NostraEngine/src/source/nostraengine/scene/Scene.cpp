#include "nostraengine/scene/Scene.hpp"

namespace NOE::NOE_SCENE
{

	void Scene::deallocateActor(Actor *actor)
	{
		delete actor;
	}

	Scene::UID Scene::generateUID()
	{
		return m_nextUid++;
	}

	void Scene::removeActor(UID uid)
	{
		if (Actor *actor = getActor(uid); actor != nullptr)
		{
			NOU::sizeType index = 0;

            //search for actor in vector
			for (NOU::sizeType i = 0; i < m_actors.size(); i++)
				if (actor == m_actors[i])
					index = i;

			deallocateActor(actor);

			m_actors.remove(index);
			m_actorMap.remove(uid);
		}
	}

	Actor* Scene::getActor(UID uid)
	{
		if (m_actorMap.containsKey(uid))
			return nullptr;
		else
			return m_actorMap.get(uid);
	}

	const NOU::NOU_DAT_ALG::Vector<Actor*>& Scene::getActors() const
	{
		return m_actors;
	}

	Actor* Scene::getRoot()
	{
		return &m_rootActor;
	}

    NOE_CORE::Initializable::ExitCode Scene::initialize()
    {
        return NOE_CORE::Initializable::ExitCode::SUCCESS;
    }

   void Scene::terminate()
    {
       for (auto &actor: m_actors)
           deallocateActor(actor);
    }

   void Scene::update(NOU::uint32 delta)
   {
       //update actor tree
   }
}