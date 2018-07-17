#include "nostraengine/renderer/Renderer.hpp"
#include "nostrautils/dat_alg/BinarySearch.hpp"

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
		NOU::int64 insertionIndex;
		
		NOU::NOU_DAT_ALG::binarySearch(m_renderables, renderable, 0, -1, &insertionIndex);

		m_renderables.insert(static_cast<NOU::sizeType>(insertionIndex), renderable);
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