#ifndef NOE_RENDERER_RENDERER_HPP
#define NOE_RENDERER_RENDERER_HPP

#include "nostrautils/NostraUtils.hpp"

#include "nostraengine/NostraEngine.hpp"

#include "nostraengine/core/StdIncludes.hpp"

#include "nostraengine/scene/RenderableActor.hpp"

/**
\file renderer/Renderer.hpp

\author	 Lukas Gross
\version 0.0.1
\since   0.0.1

\brief A file that contains the rendering part of the engine.
*/
namespace NOE::NOE_RENDERER
{
	/**
	\brief					A pure virtual class that provides the basic functions of the Optimizer.
	*/
	class Optimizer
	{
	public:

		/**
		\brief				Default destructor of the Optimizer.
		*/
		virtual ~Optimizer() = default;

		/**
		\param renderable	The renderable that will be optimized.

		\brief				Optimizes the renderable to be rendered or not.
		*/
		virtual NOU::NOU_DAT_ALG::Vector<NOE::NOE_SCENE::RenderableActor>
			optimize(const NOE::NOE_SCENE::RenderableActor& renderable) const = 0;
	};

	/**
	\brief					A class that is used for storing and accessing renderables in a vector.

	\details				It provides only one function for adding renderables. This function adds all
							renderables in a sorted order.
	*/
	class RenderableList
	{
	private:

		/**
		\brief				The vector that stores all renderables.
		*/
		NOU::NOU_DAT_ALG::Vector<NOE::NOE_SCENE::RenderableActor*> m_renderables;

	public:
		/**
		\brief				Constructor of the RenderableList.
		*/
		NOE_FUNC RenderableList();

		/**
		\brief				Destructor of the RenderableList.
		*/
		NOE_FUNC ~RenderableList();

		/**
		\param index		The index value of the renderable.

		\return				Returns the renderable.

		\brief				Returns the renderable at the position of the index.
		*/
		NOE_FUNC NOE::NOE_SCENE::RenderableActor* at(NOU::int32 index) const;

		/**
		\param renderable	The renderable that will be inserted.

		\brief				Adds a new renderable into the RenderableList. This function ensures that all
							added renderables are always in a sorted order.
		*/
		NOE_FUNC void insertSorted(NOE::NOE_SCENE::RenderableActor* renderable);

		/**
		\brief				Removes all elements in the RenderableList.
		*/
		NOE_FUNC void clear();

	};

	/**
	\brief					The primary class of the renderer.

	\details				Provides the functionality for rendering Actors and transferring the renderables
							to the GPU.
	*/
	class Renderer : public NOE::NOE_CORE::Initializable
	{
	private:

		/**
		\brief				An object of the RenderableList that stores all renderables.
		*/
		RenderableList m_renderableList;

		/**
		\brief				The optimizer that is used.
		*/
		Optimizer* m_optimizer;

	public:

		/**
		\brief				Constructor of the Renderer.
		*/
		NOE_FUNC Renderer();

		/**
		\brief				Destructor of the Renderer.
		*/
		NOE_FUNC virtual ~Renderer();

		/**
		\return				All renderables.

		\brief				A function that retuns all renderables in the Renderer.
		*/
		NOE_FUNC RenderableList getRenderables() const;

		/**
		\brief				Transfers the enabled renderables to the GPU for rendering.
		*/
		NOE_FUNC void render() const;

		/**
		\brief				Sets the optimizer of the renderer.
		*/
		NOE_FUNC void setOptimizer(Optimizer* optimizer);

		///todo doc
		NOE_FUNC virtual void renderOptimized() const = 0;
	};
}

#endif