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
	class Optimizer
	{
	private:

	public:

		virtual ~Optimizer() = default;

		virtual NOU::NOU_DAT_ALG::Vector<NOE::NOE_SCENE::RenderableActor> 
			optimize(NOE::NOE_SCENE::RenderableActor renderable) const = 0;
	};

	class RenderableList
	{
	private:

		NOU::NOU_DAT_ALG::Vector<NOE::NOE_SCENE::RenderableActor> m_renderables;

	public:

		NOE_FUNC RenderableList();

		NOE_FUNC ~RenderableList();

		NOE_FUNC NOE::NOE_SCENE::RenderableActor at(NOU::int32 index) const;

		NOE_FUNC void insertSorted(NOE::NOE_SCENE::RenderableActor renderable);

		NOE_FUNC void clear();

	};

	class Renderer
	{
	private:

		RenderableList m_renderableList;

		Optimizer* m_optimizer;

	public:

		NOE_FUNC Renderer();

		NOE_FUNC ~Renderer();

		NOE_FUNC RenderableList getRenderables() const;

		NOE_FUNC void render() const;

		NOE_FUNC void setOptimizer(Optimizer* optimizer);

		NOE_FUNC virtual void renderOptimized() const = 0;

		NOE_FUNC static NOU::int32 comparable(NOE::NOE_SCENE::RenderableActor firstActor,
			NOE::NOE_SCENE::RenderableActor secondActor);
	};
}

#endif