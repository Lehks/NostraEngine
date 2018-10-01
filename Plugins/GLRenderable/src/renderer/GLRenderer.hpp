#ifndef PLUGIN_GL_RENDERER_HPP
#define PLUGIN_GL_RENDERER_HPP

#include "nostrautils/NostraUtils.hpp"

#include "nostraengine/NostraEngine.hpp"
#include "nostraengine/core/StdIncludes.hpp"

#include "nostraengine/renderer/Renderer.hpp"

#include "glad/glad.h"

/**
\author Lukas Gross

\version 0.0.1
\since   0.0.1
*/
namespace GLRenderablePlugin
{
	/**
	\brief			A implementation of the Renderer class with glad.
	*/
	class GLRenderer : public NOE::NOE_RENDERER::Renderer
	{
	private:

	public:

		NOE_PLUGIN_FUNC GLRenderer();

		NOE_PLUGIN_FUNC virtual ~GLRenderer();

		NOE_PLUGIN_FUNC virtual void renderOptimized() const override;
	};

	/**
\brief				The error codes that are used by the GLFWWindow class.
*/
	class ErrorCodes
	{
	public:

		enum
		{
			/**
			\brief		Always the first element in the enum. This has only technical purposes and is not an
						actual error code.
			*/
			FIRST_ELEMENT = 5200,

			/**
			\brief		The initialization of the GLFW failed.
			*/
			GLAD_INITIALIZATION_FAILED,

			/**
			\brief		The initialization of the window failed.
			*/
			RENDERER_INITIALIZATION_FAILED,

			/**
			\brief		Always the last element in the enum. This has only technical purposes and is not an
						actual error code.
			*/
			LAST_ELEMENT
		};
	};

	/**
	\brief				The error pool that is used to provide the errors for the SQLite interfaces.
						This is barely documented because it behaves according to the rules that are set
						up by nostra::utils::core::ErrorPool.
	*/
	class ErrorPool : public NOU::NOU_CORE::ErrorPool
	{
		NOU::NOU_CORE::Error m_errors[ErrorCodes::LAST_ELEMENT - ErrorCodes::FIRST_ELEMENT - 1];

	public:

		ErrorPool();

		virtual const NOU::NOU_CORE::Error* queryError(NOU::NOU_CORE::ErrorPool::ErrorType id) const;
	};
}

#endif