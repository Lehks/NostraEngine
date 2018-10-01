#include "nostraengine/scene/RenderableActor.hpp"

namespace NOE::NOE_SCENE
{
	NOU::NOU_DAT_ALG::Vector<NOE::NOE_RENDERER::RenderableImplFactory*> RenderableActor::m_factories;

	RenderableActor::RenderableActor(NOU::sizeType identifier) :
		m_renderingEnabled(false),
		m_ptr(nullptr)
	{
		for (NOE::NOE_RENDERER::RenderableImplFactory* elem : m_factories)
		{
			if (elem->getFactoryIdentifier() == identifier)
			{
				m_ptr = elem->build();
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
		
	void RenderableActor::bind(const RenderableActor& renderable) const
	{
		m_ptr->bind(renderable);
	}

	void RenderableActor::draw() const
	{
		m_ptr->draw();
	}

	NOU::boolean RenderableActor::addFactory(NOE::NOE_RENDERER::RenderableImplFactory* factory,
		NOU::sizeType identifier)
	{
		NOU::boolean found = false;
		for (NOE::NOE_RENDERER::RenderableImplFactory* elem : m_factories)
		{
			if (elem->getFactoryIdentifier() == identifier)
			{
				found = true;
			}
		}

		if (!found)
		{
			factory->setFactoryIdentifier(identifier);
			m_factories.pushBack(factory);

			return true;
		}
		return false;
	}

	NOU::boolean RenderableActor::operator == (const RenderableActor& other) const
	{
		return m_ptr->compare(*other.m_ptr) == 0;
	}

	NOU::boolean RenderableActor::operator > (const RenderableActor& other) const
	{
		return m_ptr->compare(*other.m_ptr) > 0;
	}

	NOU::boolean RenderableActor::operator < (const RenderableActor& other) const
	{
		return m_ptr->compare(*other.m_ptr) < 0;
	}

	NOU::int32 RenderableActor::compare(const RenderableActor& firstActor,
		const RenderableActor& secondActor)
	{
		if (firstActor == secondActor)
			return 0;
		else if (firstActor < secondActor)
			return -1;
		else
			return 1;
	}
}