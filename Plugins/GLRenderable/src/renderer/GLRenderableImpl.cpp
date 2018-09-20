#include "GLRenderableImpl.hpp"

#include "nostraengine/scene/RenderableActor.hpp"
#include "GLRenderer.hpp"

namespace GLRenderablePlugin
{

	GLRenderableImpl::GLRenderableImpl(const NOU::NOU_DAT_ALG::String8& str, void* ptr) :
		m_ptr(ptr),
		m_renderableIdentifier(str),
		m_wireframeEnabled(false)
	{
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
	}

	GLRenderableImpl::~GLRenderableImpl()
	{
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
	}

	void GLRenderableImpl::bind() const
	{
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(NOU::float32), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

		if (m_wireframeEnabled)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
	}

	NOU::boolean GLRenderableImpl::setAttribute(const NOU::NOU_DAT_ALG::String8& str, void* ptr)
	{
		m_renderableIdentifier = str;
		m_ptr = ptr;
		///todo more?
		return true;
	}

	NOU::NOU_DAT_ALG::CompareResult GLRenderableImpl::compare(
		const NOE::NOE_RENDERER::RenderableImpl& other) const
	{
		if (m_ptr == other.getPtr())
			return 0;
		else if (m_ptr < other.getPtr())
			return -1;
		else
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

	NOU::boolean GLRenderableImpl::getWireframeStatus()
	{
		return m_wireframeEnabled;
	}

	void GLRenderableImpl::setWireframeStatus(NOU::boolean value)
	{
		m_wireframeEnabled = value;
	}
}