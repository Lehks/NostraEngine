#ifndef NOE_SCENE_ACTOR_HPP
#define NOE_SCENE_ACTOR_HPP

#include "nostraengine/core/StdIncludes.hpp"

namespace NOE::NOE_SCENE
{
	class Actor
	{
		friend class Scene;

	public:
		using UID = NOU::uint32;

	private:
		void setUID(UID uid);

	public:
		UID getUID() const;
	};

	class RootActor : public Actor
	{

	};
}

#endif