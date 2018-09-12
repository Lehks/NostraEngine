#include "GLRenderableImplFactory.hpp"

namespace GLRenderablePlugin
{
	NOE::NOE_RENDERER::RenderableImpl* GLRenderableImplFactory::build()
	{
		m_renderableImplPtr = &GLRenderableImpl::GLRenderableImpl("");///todo what renderable identificator?

		return m_renderableImplPtr;
	}

	void GLRenderableImplFactory::setFactoryIdentifier(NOU::sizeType factoryIdentifier)
	{
		m_factoryIdentifier = factoryIdentifier;
	}
	
	NOU::sizeType GLRenderableImplFactory::getFactoryIdentifier() const
	{
		return m_factoryIdentifier;
	}
} 