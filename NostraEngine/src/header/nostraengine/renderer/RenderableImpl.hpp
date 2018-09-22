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
namespace NOE::NOE_SCENE
{
	class RenderableActor;
}

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
		virtual void bind(const NOE_SCENE::RenderableActor& renderable) const = 0;

		virtual void draw() const = 0;

		///todo doc
		virtual NOU::boolean setAttribute(const NOU::NOU_DAT_ALG::String8& str, void* ptr) = 0;

		/**
		\param other	The renderable that will be compared.	

		\return			The result of the comparison.

		\brief			Compares the renderables.

		\details		Returns 0 if the renderables are equal, -1 if the passed renderable is bigger and 1 
						if the passed renderable is smaller.
		*/
		virtual NOU::NOU_DAT_ALG::CompareResult compare(const RenderableImpl& other) const = 0;

		/**
		\return			Returns a void pointer.

		\brief			Returns a pointer to the object.
		*/
		virtual void* getPtr() const = 0;

		/**
		\return			The identifier of the renderable.

		\brief			Returns the identifier of the renderable.
		*/
		virtual NOU::NOU_DAT_ALG::String8 getRenderableIdentifier() const = 0;
	};
}

#endif