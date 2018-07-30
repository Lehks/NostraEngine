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

		/**
		\param str			The identificator of the GLRenderableImpl.
		\param ptr			The pointer to the renderable.

		\brief				The constructor.
		*/
		NOE_PLUGIN_FUNC GLRenderableImpl(NOU::NOU_DAT_ALG::String8 str, void* ptr);

		/**
		\brief				Default destructor.
		*/
		NOE_PLUGIN_FUNC ~GLRenderableImpl() = default;
		
		///todo doc
		NOE_PLUGIN_FUNC virtual void bind() const override;

		///todo doc
		NOE_PLUGIN_FUNC virtual NOU::boolean setAttribute(NOU::NOU_DAT_ALG::String8 str, void* ptr) override;

		/**
		\param other		The RenderableImpl you want to compare with.

		\return				Returns the result of the comparison.
		
		\brief				Compares the GLRenderableImpl with another.			
		*/
		NOE_PLUGIN_FUNC virtual NOU::NOU_DAT_ALG::CompareResult compare(const RenderableImpl& other) const override;
		
		/**
		\return			The void* of the GLRenderableImpl.

		\brief			Returns the void* of the GLRenderableImpl.
		*/
		NOE_PLUGIN_FUNC virtual void* getPtr() const override;
	};
}

#endif