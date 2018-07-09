#include "nostraengine/renderer/Renderer.hpp"

namespace NOE::NOE_RENDERER
{
	Renderer::Renderer() :
		m_renderableList(RenderableList())
	{}

	Renderer::~Renderer()
	{
		m_renderableList.clear();
	}

	RenderableList Renderer::getRenderables()
	{
		return m_renderableList;
	}

	void Renderer::render()
	{
		//todo
	}

	void Renderer::setOptimizer()
	{
		//todo
	}

	void Renderer::renderOptimized()
	{
		//todo
	}

	NOU::int32 Renderer::comparable(NOE::NOE_SCENE::RenderableActor firstActor,
		NOE::NOE_SCENE::RenderableActor secondActor)
	{
		//todo Implement comparison: compare the meshes and textures

		return 0;
	}

	RenderableList::RenderableList()
	{}

	RenderableList::~RenderableList()
	{
		m_renderables.clear();
	}

	NOE::NOE_SCENE::RenderableActor RenderableList::at(NOU::int32 index)
	{
		return m_renderables.at(index);
	}

	void RenderableList::insertSorted(NOE::NOE_SCENE::RenderableActor renderable)
	{
		NOU::int32 compareResult = 0;

		NOU::boolean inserted = false;

		for (NOU::int32 i = 0; i < m_renderables.size(); i++)
		{
			compareResult = Renderer::comparable(m_renderables.at(i), renderable);

			if (compareResult < 0)
			{
				m_renderables.insert(0, renderable);
				inserted = true;
			}
			else if (compareResult == 0)
			{
				m_renderables.insert(compareResult, renderable);
				inserted = true;
			}
		}

		if (!inserted)
		{
			m_renderables.pushBack(renderable);
		}
	}

	void RenderableList::clear()
	{
		m_renderables.clear();
	}
}