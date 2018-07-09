#include "nostraengine/scene/RenderableActor.hpp"

namespace NOE::NOE_SCENE
{
	RenderableActor::RenderableActor() :
		m_renderingEnabled(false)
	{}
	
	RenderableActor::~RenderableActor()
	{
		m_factories.clear();
	}

	NOU::boolean RenderableActor::getEnabled()
	{
		return m_renderingEnabled;
	}
		
	void RenderableActor::setEnabled(NOU::boolean enable)
	{
		m_renderingEnabled = enable;
	}
		
	void RenderableActor::bind(const RenderableActor renderable)
	{
		//todo
	}
		
	void RenderableActor::addFactory(NOE::NOE_RENDERER::RenderableImplFactory* factory,
		NOU::sizeType identifier)
	{
		//todo
	}
}