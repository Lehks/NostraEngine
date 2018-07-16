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
	/**
	\brief					A pure virtual class that provides the basic functions for a RenderableImplFactory.
	*/
	class RenderableImplFactory
	{
	public:

		/**
		\brief				Default destructor.
		*/
		virtual ~RenderableImplFactory() = default;

		/**
		\return				A new instance of a RenderableImpl.

		\brief				Creates a new instance of a RenderableImpl.
		*/
		virtual RenderableImpl* construct() const = 0;

		/**
		\param identifier	The identifier of the factory.

		\brief				Sets the identifier of the factory to the passed value.
		*/
		virtual void setIdentifier(NOU::sizeType identifier) const = 0;

		/**
		\return				The identifier of the factory.

		\brief				Returns the identifier of the factory.
		*/
		virtual NOU::sizeType getIdentifier() const = 0;
	};
}

#endif