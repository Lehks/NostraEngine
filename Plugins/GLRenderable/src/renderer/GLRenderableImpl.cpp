	#include "GLRenderableImpl.hpp"

#include "nostraengine/scene/RenderableActor.hpp"

namespace GLRenderablePlugin
{

	GLRenderableImpl::GLRenderableImpl(const NOU::NOU_DAT_ALG::String8& str, void* ptr) :
		m_ptr(ptr),
		m_renderableIdentifier(str)
	{}

	void GLRenderableImpl::bind() const
	{
		//todo
	}

	NOU::boolean GLRenderableImpl::setAttribute(const NOU::NOU_DAT_ALG::String8& str, void* ptr)
	{
		//todo
	}

	NOU::NOU_DAT_ALG::CompareResult GLRenderableImpl::compare(
		const NOE::NOE_RENDERER::RenderableImpl& other) const
	{
		if (m_ptr == other.getPtr())
			return 0;
		else if (m_ptr < other.getPtr())
			return -1;
		else if (m_ptr > other.getPtr())
			return 1;
	}

	void* GLRenderableImpl::getPtr() const
	{
		return m_ptr;
	}

	NOU::NOU_DAT_ALG::String8 GLRenderableImpl::getRenderableIdentifier() const
	{
		return m_renderableIdentifier;
	}
}