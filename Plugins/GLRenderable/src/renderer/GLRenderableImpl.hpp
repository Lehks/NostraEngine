#ifndef PLUGIN_GL_RENDERABLE_IMPL_HPP
#define PLUGIN_GL_RENDERABLE_IMPL_HPP

#include "nostrautils/NostraUtils.hpp"

#include "nostraengine/NostraEngine.hpp"
#include "nostraengine/core/StdIncludes.hpp"

#include "nostraengine/renderer/RenderableImpl.hpp"

namespace GLRenderablePlugin
{
	class GLRenderableImpl final : public NOE::NOE_RENDERER::RenderableImpl
	{
	private:

		void* m_ptr;

		NOU::NOU_DAT_ALG::String8 m_identificator;

	public:

		NOE_PLUGIN_FUNC GLRenderableImpl(NOU::NOU_DAT_ALG::String8 str, void* ptr);

		NOE_PLUGIN_FUNC virtual ~GLRenderableImpl() override;

		///todo doc
		NOE_PLUGIN_FUNC virtual void bind() const override;

		///todo doc
		NOE_PLUGIN_FUNC virtual NOU::boolean setAttribute(NOU::NOU_DAT_ALG::String8 str, void* ptr) override;

		NOE_PLUGIN_FUNC virtual NOU::NOU_DAT_ALG::CompareResult compare(const RenderableImpl& other) const override;
	};
}

#endif