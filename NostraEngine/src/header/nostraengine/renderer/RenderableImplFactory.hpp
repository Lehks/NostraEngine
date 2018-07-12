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
	protected:

		template<typename T, typename... ARGS>
		static RenderableImpl* allocate(ARGS&&... args);

	public:

		virtual ~RenderableImplFactory() = default;

		virtual RenderableImpl* build() const = 0;

		NOE_FUNC static void deallocate(RenderableImpl* ptr)
	};
}

#endif