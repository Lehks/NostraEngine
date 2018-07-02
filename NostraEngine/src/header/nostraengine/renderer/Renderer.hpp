#ifndef NOE_RENDERER_RENDERER_HPP
#define NOE_RENDERER_RENDERER_HPP

#include "nostrautils/NostraUtils.hpp"

#include "nostraengine/NostraEngine.hpp"
#include "nostraengine/core/StdIncludes.hpp"

/**
\file renderer/Renderer.hpp

\author	 Lukas Gross
\version 0.0.1
\since   0.0.1

\brief A file that contains the rendering part of the engine.
*/
namespace NOE::NOE_RENDERER
{
	class Renderer
	{
	private:

	public:

		RenderableList getRenderables();

		void render();

		void setOptimizer(Optimizer optimizer);

		void renderOptimized();

		NOU::int32 comparable(RenderableActor firstActor, RenderableActor secondActor);
	};

	class Optimizer
	{
	private:

	public:

		virtual ~Optimizer() = default;

		virtual void optimize(RenderableActor renderable) const = 0;
	};

	class RenderableList
	{
	private:

		NOU::NOU_DAT_ALG::Vector<RenderableActor> m_renderables;

	public:

		RenderableActor at(NOU::int32 index);

		void insertSorted();

	};
}

#endif