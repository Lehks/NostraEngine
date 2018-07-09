#ifndef NOE_SCENE_RENDERABLE_ACTOR_HPP
#define NOE_SCENE_RENDERABLE_ACTOR_HPP

#include "nostrautils/NostraUtils.hpp"

#include "nostraengine/NostraEngine.hpp"

#include "nostraengine/core/StdIncludes.hpp"

#include "nostraengine/renderer/RenderableImpl.hpp"
#include "nostraengine/renderer/RenderableImplFactory.hpp"

namespace NOE::NOE_SCENE
{
	class RenderableActor
	{
	private:

		NOU::boolean m_renderingEnabled;

		NOE::NOE_RENDERER::RenderableImpl* m_ptr;

		NOU::NOU_DAT_ALG::Vector<NOE::NOE_RENDERER::RenderableImplFactory*> m_factories;

	public:

		NOE_FUNC RenderableActor();

		NOE_FUNC ~RenderableActor();

		NOE_FUNC NOU::boolean getEnabled() const;

		NOE_FUNC void setEnabled(NOU::boolean enable);
		
		NOE_FUNC void bind(const RenderableActor renderable) const;

		NOE_FUNC void addFactory(NOE::NOE_RENDERER::RenderableImplFactory* factory, NOU::sizeType identifier);
	};
}

#endif