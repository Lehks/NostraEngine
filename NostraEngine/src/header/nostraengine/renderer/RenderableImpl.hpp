#ifndef NOE_RENDERER_RENDERABLE_IMPL_HPP
#define NOE_RENDERER_RENDERABLE_IMPL_HPP

#include "nostraengine/core/StdIncludes.hpp"
#include "nostraengine/core/NostraEngine.hpp"

/**
\file renderer/RenderableImpl.hpp

\author	 Lukas Gross
\version 0.0.1
\since   0.0.1

\brief A interface for the renderables.
*/
namespace NOE::NOE_RENDERER
{
	class RenderableImpl
	{
		virtual ~RenderableImpl() = default;

		virtual void bind() const = 0;
	};
}

#endif