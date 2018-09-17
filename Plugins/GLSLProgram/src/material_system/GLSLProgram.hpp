#ifndef PLUGIN_GLSL_PROGRAM_HPP
#define PLUGIN_GLSL_PROGRAM_HPP

#include "nostraengine/NostraEngine.hpp"
#include "nostrautils/NostraUtils.hpp"

#include "../../../GLAD/include/glad/glad.h"

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
		NOU::sizeType m_ID;
		NOU::sizeType m_shaderID;
		NOU::sizeType m_vertexShaderId;
		NOU::sizeType m_fragmentShaderId;
		NOU::sizeType m_geometryShaderId;

		NOU::NOU_DAT_ALG::String8 m_vertexShader;
		NOU::NOU_DAT_ALG::String8 m_fragmentShader;
		NOU::NOU_DAT_ALG::String8 m_geometryShader;

		NOU::NOU_DAT_ALG::HashMap<NOU::NOU_DAT_ALG::String8, NOU::sizeType> m_uniforms;

		NOE_PLUGIN_FUNC virtual NOU::boolean linkShader() override;
		NOE_PLUGIN_FUNC virtual NOU::boolean createVertexShader() override;
		NOE_PLUGIN_FUNC virtual NOU::boolean createFragmetShader() override;
		NOE_PLUGIN_FUNC virtual NOU::boolean createGeometryShader() override;

	public:
		NOE_PLUGIN_FUNC GLSLProgram(NOU::sizeType mapSize = 100);
		NOE_PLUGIN_FUNC virtual ~GLSLProgram() = default;
		NOE_PLUGIN_FUNC NOU::boolean GLSLProgram::loadVertexShader(const NOU::NOU_DAT_ALG::String8 &shaderSource);
		NOE_PLUGIN_FUNC NOU::boolean GLSLProgram::loadFragmentShader(const NOU::NOU_DAT_ALG::String8 &shaderSource);
		NOE_PLUGIN_FUNC NOU::boolean GLSLProgram::loadGeometryShader(const NOU::NOU_DAT_ALG::String8 &shaderSource);
		NOE_PLUGIN_FUNC virtual NOU::boolean createShader(const NOU::NOU_DAT_ALG::String8 &vertexShaderSource, const NOU::NOU_DAT_ALG::String8 &fragmentShaderSource, const NOU::NOU_DAT_ALG::String8 &geometryShaderSource = nullptr) override;
		NOE_PLUGIN_FUNC virtual NOU::boolean bind() override;
		NOE_PLUGIN_FUNC virtual NOU::boolean unbind() override;
		NOE_PLUGIN_FUNC virtual NOU::boolean createUniform(const NOU::NOU_DAT_ALG::String8 &name) override;
		NOE_PLUGIN_FUNC virtual NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::boolean value)override;
		NOE_PLUGIN_FUNC virtual NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::sizeType value)override;
		NOE_PLUGIN_FUNC virtual NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::float32 value)override;
		NOE_PLUGIN_FUNC virtual NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::float32 xvalue, NOU::float32 yvalue)override;
		NOE_PLUGIN_FUNC virtual NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Vec2 &vec)override;
		NOE_PLUGIN_FUNC virtual NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::float32 xvalue, NOU::float32 yvalue, NOU::float32 zvalue)override;
		NOE_PLUGIN_FUNC virtual NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Vec3 &vec)override;
		NOE_PLUGIN_FUNC virtual NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::float32 xvalue, NOU::float32 yvalue, NOU::float32 zvalue, NOU::float32 wvalue)override;
		NOE_PLUGIN_FUNC virtual NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Vec4 &vec)override;
		NOE_PLUGIN_FUNC virtual NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Mat2 &mat)override;
	    NOE_PLUGIN_FUNC virtual NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Mat3 &mat)override;
		NOE_PLUGIN_FUNC virtual NOU::boolean setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Mat4 &mat)override;
		NOE_PLUGIN_FUNC virtual NOU::boolean enableLightning() override;
		NOE_PLUGIN_FUNC virtual NOU::boolean disableLightning() override;
	};
}
#endif
