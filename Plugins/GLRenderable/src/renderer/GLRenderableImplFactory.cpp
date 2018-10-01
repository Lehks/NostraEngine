#include "GLRenderableImplFactory.hpp"


namespace GLRenderablePlugin
{
	const NOU::NOU_DAT_ALG::String8 GLRenderableImplFactory::IMPL_IDENTIFIER = "MESH";

	NOE::NOE_RENDERER::RenderableImpl* GLRenderableImplFactory::build()
	{
		m_renderableImplPtr = &GLRenderableImpl::GLRenderableImpl(IMPL_IDENTIFIER);

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