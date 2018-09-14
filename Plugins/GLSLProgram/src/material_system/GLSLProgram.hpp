#ifndef PLUGIN_GLSL_PROGRAM_HPP
#define PLUGIN_GLSL_PROGRAM_HPP

#include "nostraengine/NostraEngine.hpp"

/**
\file material_system/GLSLProgram.hpp

\author  Dennis Franz
\version 0.0.1
\since   0.0.1

\brief A file that provides the functionality for the shader accsessability.
*/
namespace GLSLProgramPlugin
{
	class GLSLProgram : public NOE::NOE_MATSYS::Program
	{
    private:
		NOE_PLUGIN_FUNC virtual NOU::boolean linkShader() override;
		NOE_PLUGIN_FUNC virtual NOU::boolean createVertexShader() override;
		NOE_PLUGIN_FUNC virtual NOU::boolean createFragmetShader() override;
		NOE_PLUGIN_FUNC virtual NOU::boolean createGeometryShader() override;

	public:
		NOE_PLUGIN_FUNC virtual ~Program() override;
		NOE_PLUGIN_FUNC virtual NOU::boolean createShader() override;
		NOE_PLUGIN_FUNC virtual NOU::boolean bind() override;
		NOE_PLUGIN_FUNC virtual NOU::boolean unbind() override;
	};
}
#endif
