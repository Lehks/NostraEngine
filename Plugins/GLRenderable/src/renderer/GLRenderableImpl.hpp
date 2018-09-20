#ifndef PLUGIN_GL_RENDERABLE_IMPL_HPP
#define PLUGIN_GL_RENDERABLE_IMPL_HPP

#include "nostrautils/NostraUtils.hpp"

#include "nostraengine/NostraEngine.hpp"
#include "nostraengine/core/StdIncludes.hpp"

#include "nostraengine/renderer/RenderableImpl.hpp"

namespace GLRenderablePlugin
{
	/**
	@author					Lukas Gross

	\brief					A implementation of the Renderer class with glad.
	*/
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

		/**
		\brief				The Vertex Array Object is saved in this attribute.
		*/
		NOU::uint32 m_VAO;

		/**
		\brief				The Vertex Buffer Object is saved in this attribute.
		*/
		NOU::uint32 m_VBO;

		/**
		\brief				Pointer to an array of vertices.
		*/
		const NOU::float32* m_vertices;

		/**
		\brief				Status of the wireframe.
		*/
		NOU::boolean m_wireframeEnabled;

	public:

		/**
		\param str			The identifier of the GLRenderableImpl.
		\param ptr			A pointer to any object.

		\brief				The constructor.

		\details			ptr is default set to nullptr.
		*/
		NOE_PLUGIN_FUNC GLRenderableImpl(const NOU::NOU_DAT_ALG::String8& str, void* ptr = nullptr);

		/**
		\brief				The destructor.
		*/
		NOE_PLUGIN_FUNC ~GLRenderableImpl();
		
		/**
		\brief				Binds the vertices in the vertex array and vertex buffer.
		*/
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
		\return				The void* of the GLRenderableImpl.

		\brief				Returns the void* of the GLRenderableImpl.
		*/
		NOE_PLUGIN_FUNC virtual void* getPtr() const override;

		/**
		\return				The identifier of the GLRenderableImpl.

		\brief				Returns a string that represents the identification of the GLRenderableImpl.
		*/
		NOE_PLUGIN_FUNC virtual NOU::NOU_DAT_ALG::String8 getRenderableIdentifier() const override;

		/**
		\return				Status of the wireframe(enabled/disabled).

		\brief				Returns true if the wireframe is enabled and false if not.
		*/
		NOE_PLUGIN_FUNC NOU::boolean getWireframeStatus();

		/**
		\param value		The new status of the wireframe.

		\brief				Sets the status of the wireframe to enabled if the passed parameter is true and 
							disables the wireframe if the parameter is false.
		*/
		NOE_PLUGIN_FUNC void setWireframeStatus(NOU::boolean value);
	};
}

#endif