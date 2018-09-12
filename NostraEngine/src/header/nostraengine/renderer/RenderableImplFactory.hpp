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
	protected:

		/**
		\tparam T			The type of the allocated pointer.
		\tparam ARGS		The arguments types.

		\param args			The passed arguments.

		\return				A pointer to a RenderableImpl.

		\brief				Allocates a pointer to a new RenderableImpl.
		*/
		template<typename T, typename... ARGS>
		static RenderableImpl* allocate(ARGS&&... args);

	public:

		/**
		\brief				Default destructor.
		*/
		virtual ~RenderableImplFactory() = default;

		/**
		\param ptr			The pointer that will be deallocated.

		\brief				Deallocates the passed pointer.
		*/
		NOE_FUNC static void deallocate(RenderableImpl* ptr);

		/**
		\return				A new instance of a RenderableImpl.

		\brief				Creates a new instance of a RenderableImpl.
		*/
		virtual RenderableImpl* build() = 0;

		/**
		\param identifier	The identifier of the factory.

		\brief				Sets the identifier of the factory to the passed value.
		*/
		virtual void setFactoryIdentifier(NOU::sizeType factoryIdentifier) = 0;

		/**
		\return				The identifier of the factory.

		\brief				Returns the identifier of the factory.
		*/
		virtual NOU::sizeType getFactoryIdentifier() const = 0;
	};

	template<typename T, typename... ARGS>
	RenderableImpl* RenderableImplFactory::allocate(ARGS&&... args)
	{
		return new T(NOU::NOU_CORE::forward<ARGS>(args)...);
	}
}
#endif