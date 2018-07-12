#include "nostraengine/renderer/Renderer.hpp"

namespace NOE::NOE_RENDERER
{
	RenderableList::RenderableList()
	{}

	RenderableList::~RenderableList()
	{
		clear();
	}

	NOE::NOE_SCENE::RenderableActor RenderableList::at(NOU::int32 index) const
	{
		return m_renderables.at(index);
	}

	void RenderableList::insertSorted(NOE::NOE_SCENE::RenderableActor renderable)
	{
		NOU::int32 compareResult = 0;

		NOU::boolean inserted = false;

		for (NOU::sizeType i = 0; i < m_renderables.size(); i++)
		{
			compareResult = Renderer::comparable(m_renderables.at(i), renderable);

			if (compareResult < NOU::int32(0))
			{
				m_renderables.insert(NOU::int32(0), renderable);
				inserted = true;
			}
			else if (compareResult == NOU::int32(0))
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

	Renderer::Renderer() :
		m_optimizer(nullptr)
	{}

	Renderer::~Renderer()
	{
		m_renderableList.clear();
	}

	RenderableList Renderer::getRenderables() const
	{
		return m_renderableList;
	}

	void Renderer::render() const
	{
		//todo
	}

	void Renderer::setOptimizer(Optimizer* optimizer)
	{
		m_optimizer = optimizer;
	}

	NOU::int32 Renderer::comparable(NOE::NOE_SCENE::RenderableActor firstActor,
		NOE::NOE_SCENE::RenderableActor secondActor)
	{
		//todo Implement comparison: compare the meshes and textures
		
		return 0;
	}
}