#include "GLRenderableImplFactory.hpp"

namespace GLRenderablePlugin
{
	NOE::NOE_RENDERER::RenderableImpl* GLRenderableImplFactory::build() const
	{

	}

	void GLRenderableImplFactory::setIdentifier(NOU::sizeType identifier)
	{
		m_identifier = identifier;
	}
	
	NOU::sizeType GLRenderableImplFactory::getIdentifier() const
	{
		return m_identifier;
	}
} 