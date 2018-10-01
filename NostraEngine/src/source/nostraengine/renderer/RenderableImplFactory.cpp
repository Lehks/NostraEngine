#include "nostraengine/renderer/RenderableImplFactory.hpp"

namespace NOE::NOE_RENDERER
{
	void RenderableImplFactory::deallocate(RenderableImpl* ptr)
	{
		delete ptr;
	}
}