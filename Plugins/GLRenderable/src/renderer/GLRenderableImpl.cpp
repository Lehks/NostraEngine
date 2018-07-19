#include "GLRenderableImpl.hpp"

namespace GLRenderablePlugin
{

	GLRenderableImpl::GLRenderableImpl(NOU::NOU_DAT_ALG::String8 str, void* ptr) :
		m_ptr(ptr),
		m_identificator(str)
	{

	}

	GLRenderableImpl::~GLRenderableImpl()
	{

	}

	void GLRenderableImpl::bind() const
	{

	}

	NOU::boolean GLRenderableImpl::setAttribute(NOU::NOU_DAT_ALG::String8 str, void* ptr)
	{

	}

	NOU::NOU_DAT_ALG::CompareResult GLRenderableImpl::compare(const NOE::NOE_RENDERER::RenderableImpl& other) const
	{

	}
}