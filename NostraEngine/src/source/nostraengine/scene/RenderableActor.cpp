#include "nostraengine/scene/RenderableActor.hpp"

namespace NOE::NOE_SCENE
{
	RenderableActor::RenderableActor(NOU::sizeType identifier) :
		m_renderingEnabled(false),
		m_ptr(nullptr)
	{
		for (NOE::NOE_RENDERER::RenderableImplFactory* elem : m_factories)
		{
			if (elem->getIdentifier() == identifier)
			{
				m_ptr = elem->construct();
				break;
			}
		}
	}
	
	RenderableActor::~RenderableActor()
	{
		m_factories.clear();
	}

	NOU::boolean RenderableActor::getEnabled() const
	{
		return m_renderingEnabled;
	}
		
	void RenderableActor::setEnabled(NOU::boolean enable)
	{
		m_renderingEnabled = enable;
	}
		
	void RenderableActor::bind(const RenderableActor renderable) const
	{
		//todo
	}
		
	NOU::int8 RenderableActor::addFactory(NOE::NOE_RENDERER::RenderableImplFactory* factory,
		NOU::sizeType identifier)
	{
		NOU::boolean found = false;
		for (NOE::NOE_RENDERER::RenderableImplFactory* elem : m_factories)
		{
			if (elem->getIdentifier() == identifier)
			{
				found = true;
			}
		}

		if (!found)
		{
			factory->setIdentifier(identifier);
			m_factories.pushBack(factory);

			return 1;
		}
		return -1;
	}
}