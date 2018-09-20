#include "GLRenderer.hpp"

namespace GLRenderablePlugin
{
	GLRenderer::GLRenderer()
	{
		if (!gladLoadGL())
		{
			NOU_PUSH_ERROR(NOU::NOU_CORE::getErrorHandler(), ErrorCodes::GLAD_INITIALIZATION_FAILED,
				"Could not load glad!");

			NOU_LOG_DEBUG("Could not initialize glad!");
		}
	}

	GLRenderer::~GLRenderer()
	{
	}

	void GLRenderer::renderOptimized() const
	{

	}

#ifndef NOU_RENDERER_MAKE_ERROR
#define NOU_RENDERER_MAKE_ERROR(code) NOU::NOU_CORE::Error(#code, ErrorCodes::code)
#endif

	ErrorPool::ErrorPool() :
		m_errors //must be in order
	{
		NOU_RENDERER_MAKE_ERROR(GLAD_INITIALIZATION_FAILED),
		NOU_RENDERER_MAKE_ERROR(RENDERER_INITIALIZATION_FAILED)
	}
	{}

#undef NOU_WINDOW_MAKE_ERROR

	const NOU::NOU_CORE::Error* ErrorPool::queryError(NOU::NOU_CORE::ErrorPool::ErrorType id) const
	{
		if (id > ErrorCodes::FIRST_ELEMENT && id < ErrorCodes::LAST_ELEMENT)
		{
			NOU::sizeType index = id - ErrorCodes::FIRST_ELEMENT + 1;

			return m_errors + index;
		}

		return nullptr;
	}
}