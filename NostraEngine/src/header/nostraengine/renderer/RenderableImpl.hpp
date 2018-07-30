#ifndef NOE_RENDERER_RENDERABLE_IMPL_HPP
#define NOE_RENDERER_RENDERABLE_IMPL_HPP

#include "nostrautils/NostraUtils.hpp"

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
	public:

		/**
		\brief			Default constructor.
		*/
		RenderableImpl() = default;

		/**
		\brief			Default destructor.
		*/
		virtual ~RenderableImpl() = default;

		///todo doc
		virtual void bind() const = 0;

		///todo doc
		virtual NOU::boolean setAttribute(NOU::NOU_DAT_ALG::String8 str, void* ptr) = 0;

		virtual NOU::NOU_DAT_ALG::CompareResult compare(const RenderableImpl& other) const = 0;

		virtual void* getPtr() const = 0;
	};
}

#endif