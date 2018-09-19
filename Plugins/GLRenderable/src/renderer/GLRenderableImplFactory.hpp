#ifndef PLUGIN_GL_RENDERABLE_IMPL_FACTORY_HPP
#define PLUGIN_GL_RENDERABLE_IMPL_FACTORY_HPP

#include "nostrautils/NostraUtils.hpp"

#include "nostraengine/NostraEngine.hpp"
#include "nostraengine/core/StdIncludes.hpp"

#include "nostraengine/renderer/RenderableImplFactory.hpp"

#include "GLRenderableImpl.hpp"

namespace GLRenderablePlugin
{
	class GLRenderableImplFactory final : public NOE::NOE_RENDERER::RenderableImplFactory
	{
	private:

		/**
		\brief				A pointer to the renderable.
		*/
		NOE::NOE_RENDERER::RenderableImpl* m_renderableImplPtr;

		/**
		\brief				The identifier of the factory.
		*/
		NOU::sizeType m_factoryIdentifier;

		static const NOU::NOU_DAT_ALG::String8 IMPL_IDENTIFIER;

	public:

		/**
		\brief				Default constructor.
		*/
		GLRenderableImplFactory() = default;

		/**
		\brief				Default destructor.
		*/
		virtual ~GLRenderableImplFactory() = default;

		/**
		\return				A new instance of a RenderableImpl.

		\brief				Creates a new instance of a RenderableImpl.
		*/
		virtual NOE::NOE_RENDERER::RenderableImpl* build() override;

		/**
		\param identifier	The identifier of the factory.

		\brief				Sets the identifier of the factory to the passed value.
		*/
		virtual void setFactoryIdentifier(NOU::sizeType factoryIdentifier) override;

		/**
		\return				The identifier of the factory.

		\brief				Returns the identifier of the factory.
		*/
		virtual NOU::sizeType getFactoryIdentifier() const override;
	};
}

#endif