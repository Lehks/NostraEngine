#include "GLRenderableImplFactory.hpp"

namespace GLRenderablePlugin
{
	NOE::NOE_RENDERER::RenderableImpl* GLRenderableImplFactory::build() const
	{
	}

	void GLRenderableImplFactory::setIdentifier(NOU::sizeType factoryIdentifier)
	{
		m_factoryIdentifier = factoryIdentifier;
	}
	
	NOU::sizeType GLRenderableImplFactory::getFactoryIdentifier() const
	{
		return m_factoryIdentifier;
	}
} 