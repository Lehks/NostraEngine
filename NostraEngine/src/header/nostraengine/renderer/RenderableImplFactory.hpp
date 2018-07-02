#ifndef NOE_RENDERER_RENDERABLE_IMPL_FACTORY_HPP
#define NOE_RENDERER_RENDERABLE_IMPL_FACTORY_HPP

#include "nostraengine/core/StdIncludes.hpp"
#include "nostraengine/core/NostraEngine.hpp"

#include "RenderableImpl.hpp"

/**
\file renderer/RenderableImplFactory.hpp

\author	 Lukas Gross
\version 0.0.1
\since   0.0.1

\brief A interface for the factory that provides a instance of a renderable.
*/
namespace NOE::NOE_RENDERER
{
	class RenderableImplFactory
	{
		virtual ~RenderableImplFactory() = default;

		virtual RenderableImpl* construct() = 0;
	};
}

#endif