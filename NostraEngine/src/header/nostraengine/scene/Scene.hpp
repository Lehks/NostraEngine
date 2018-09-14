#ifndef NOE_SCENE_SCENE_HPP
#define NOE_SCENE_SCENE_HPP

#include "nostrautils/core/Utils.hpp"

#include "nostraengine/scene/Actor.hpp"
#include "nostrautils/dat_alg/Vector.hpp"

namespace NOE::NOE_SCENE
{
	class Scene
	{
	public:
		using UID = Actor::UID;

	private:
		NOU::NOU_DAT_ALG::Vector<Actor*> m_actors;
		NOU::NOU_DAT_ALG::HashMap<UID, Actor*> m_actorMap;
		RootActor m_rootActor;

		UID m_nextUid;

		template<typename ACTOR, typename... ARGS>
		Actor* allocateActor(ARGS &&args);

		void deallocateActor(Actor *actor);

	public:
		UID generateUID();

		template<typename ACTOR, typename... ARGS>
		Actor* addActor(ARGS &&args);

		void removeActor(UID uid);

		Actor* getActor(UID uid);

		const NOU::NOU_DAT_ALG::Vector<Actor*>& getActors() const;

		Actor* getRoot();
	};

	template<typename ACTOR, typename... ARGS>
	Actor* Scene::allocateActor(ARGS &&args)
	{
		return new ACTOR(NOU_CORE::forward<ARGS>(args)...);
	}

	template<typename ACTOR, typename... ARGS>
	Actor* Scene::addActor(ARGS &&args)
	{
		Actor *actor = allocateActor(NOU_CORE::forward<ARGS>(args)...);

		actor->setUID(generateUID());

		m_actors.push(actor);
		m_actorMap.map(actor->getUID(), actor);

		return actor;
	}

}

#endif