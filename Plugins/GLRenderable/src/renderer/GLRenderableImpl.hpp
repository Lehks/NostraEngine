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

		/**
		\brief				A void pointer to an object. Is not needed for the core functionality.
		*/
		void* m_ptr;

		/**
		\brief				The Identifier of the renderable. 
		*/
		NOU::NOU_DAT_ALG::String8 m_renderableIdentifier;

	public:

		/**
		\param str			The identifier of the GLRenderableImpl.
		\param ptr			A pointer to any object.

		\brief				The constructor.

		\details			ptr is default set to nullptr.
		*/
		NOE_PLUGIN_FUNC GLRenderableImpl(const NOU::NOU_DAT_ALG::String8& str, void* ptr = nullptr);

		/**
		\brief				Default destructor.
		*/
		NOE_PLUGIN_FUNC ~GLRenderableImpl() = default;
		
		///todo doc
		NOE_PLUGIN_FUNC virtual void bind() const override;

		///todo doc
		NOE_PLUGIN_FUNC virtual NOU::boolean setAttribute(const NOU::NOU_DAT_ALG::String8& str, void* ptr) override;

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

		/**
		\return			The identifier of the GLRenderableImpl.

		\brief			Returns a string that represents the identification of the GLRenderableImpl.
		*/
		NOE_PLUGIN_FUNC virtual NOU::NOU_DAT_ALG::String8 getRenderableIdentifier() const override;
	};
}

#endif