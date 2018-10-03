#include "GLSLProgram.hpp"

namespace GLSLProgramPlugin
{
    NOU::boolean GLSLProgram::LinkShader()
    {
        glLinkProgram(m_ID);
        return true;
    }

    NOU::boolean GLSLProgram::CreateVertexShader()
    {
        m_vertexShaderId = CreateShader(m_vertexShader, GL_VERTEX_SHADER);
        if(m_vertexShaderId == 0)
        {
            return false;
        }

        return true;
    }

    NOU::boolean GLSLProgram::CreateFragmetShader()
    {
        m_fragmentShaderId = CreateShader(m_fragmentShader, GL_FRAGMENT_SHADER);
        if(m_fragmentShaderId == 0)
        {
            return false;
        }

        return true;
    }

    NOU::boolean GLSLProgram::CreateGeometryShader()
    {
        m_geometryShaderId = CreateShader(m_geometryShader, GL_GEOMETRY_SHADER);
        if(m_geometryShaderId == 0)
        {
            return false;
        }

        return true;
    }

    //------------------------ PUBLIC -------------------------

    GLSLProgram::GLSLProgram(NOU::sizeType mapSize) :
        m_ID(glCreateProgram()),
        m_uniforms(mapSize),
        m_vertexShader(nullptr),
        m_fragmentShader(nullptr),
        m_geometryShader(nullptr)
    {}

    NOU::boolean GLSLProgram::LoadVertexShader(const NOU::NOU_DAT_ALG::String8 &shaderSource)
    {
        NOU::NOU_FILE_MNGT::File file(shaderSource);
        file.open(NOU::NOU_FILE_MNGT::AccessMode::READ);
        m_vertexShader = file.read();
        file.close();
        return true;
    }

    NOU::boolean GLSLProgram::LoadFragmentShader(const NOU::NOU_DAT_ALG::String8 &shaderSource)
    {
        NOU::NOU_FILE_MNGT::File file(shaderSource);
        file.open(NOU::NOU_FILE_MNGT::AccessMode::READ);
        m_fragmentShader = file.read();
        file.close();
        return true;
    }

    NOU::boolean GLSLProgram::LoadGeometryShader(const NOU::NOU_DAT_ALG::String8 &shaderSource)
    {
        NOU::NOU_FILE_MNGT::File file(shaderSource);
        file.open(NOU::NOU_FILE_MNGT::AccessMode::READ);
        m_geometryShader = file.read();
        file.close();
        return true;
    }

    NOU::boolean GLSLProgram::CreateShader(const NOU::NOU_DAT_ALG::String8 &vertexShaderSource, const NOU::NOU_DAT_ALG::String8 &fragmentShaderSource, const NOU::NOU_DAT_ALG::String8 &geometryShaderSource)
    {
        LoadVertexShader(vertexShaderSource);
        LoadFragmentShader(fragmentShaderSource);
        if(geometryShaderSource != nullptr)
        {
            LoadGeometryShader(geometryShaderSource);
        }

        CreateVertexShader();
        CreateFragmetShader();
        if(geometryShaderSource != nullptr)
        {
            CreateGeometryShader();
        }

        glCompileShader(m_vertexShaderId);
        glCompileShader(m_fragmentShaderId);
        if(m_geometryShader != nullptr)
        {
            glCompileShader(m_geometryShaderId);
        }

        glAttachShader(m_ID, m_vertexShaderId);
        glAttachShader(m_ID, m_fragmentShaderId);
        if(m_geometryShader != nullptr)
        {
            glAttachShader(m_ID, m_geometryShaderId);
        }

        LinkShader();

        glDeleteShader(m_vertexShaderId);
        glDeleteShader(m_fragmentShaderId);
        if(m_geometryShader != nullptr)
        {
            glDeleteShader(m_geometryShaderId);
        }

        return true;
    }

    NOU::boolean GLSLProgram::Bind()
    {
        glUseProgram(m_ID);
        return true;
    }

    NOU::boolean GLSLProgram::Unbind()
    {
        glUseProgram(0);
        return true;
    }

    NOU::boolean GLSLProgram::CreateUniform(const NOU::NOU_DAT_ALG::String8 &name)
    {
        NOU::sizeType uniformLocation = glGetUniformLocation(m_ID, name.rawStr());
        if(uniformLocation == 0)
        {
            return false;
        }
        m_uniforms.map(name,uniformLocation);
        return true;
    }

    NOU::boolean GLSLProgram::setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::boolean value)
    {
        glUniform1i(m_uniforms.get(name), value);
        return true;
    }

    NOU::boolean GLSLProgram::setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::sizeType value)
    {
        glUniform1i(m_uniforms.get(name), value);
        return true;
    }

    NOU::boolean GLSLProgram::setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::float32 value)
    {
        glUniform1f(m_uniforms.get(name), value);
        return true;
    }

    NOU::boolean GLSLProgram::setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::float32 xvalue, NOU::float32 yvalue)
    {
        glUniform2f(m_uniforms.get(name), xvalue, yvalue);
        return true;
    }

    NOU::boolean GLSLProgram::setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Vec2 &vec)
    {
        glUniform2f(m_uniforms.get(name), vec[0], vec[1]);
        return true;
    }

    NOU::boolean GLSLProgram::setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::float32 xvalue, NOU::float32 yvalue, NOU::float32 zvalue)
    {
        glUniform3f(m_uniforms.get(name), xvalue, yvalue, zvalue);
        return true;
    }

    NOU::boolean GLSLProgram::setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Vec3 &vec)
    {
        glUniform3f(m_uniforms.get(name), vec[0], vec[1], vec[2]);
        return true;
    }

    NOU::boolean GLSLProgram::setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::float32 xvalue, NOU::float32 yvalue, NOU::float32 zvalue, NOU::float32 wvalue)
    {
        glUniform4f(m_uniforms.get(name), xvalue, yvalue, zvalue, wvalue);
        return true;
    }

    NOU::boolean GLSLProgram::setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Vec4 &vec)
    {
        glUniform4f(m_uniforms.get(name), vec[0], vec[1], vec[2], vec[3]);
        return true;
    }

    NOU::boolean GLSLProgram::setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Mat2 &mat)
    {
        //TODO: glUniformMatrix2fv(m_uniforms.get(name), mat);
        return true;
    }

    NOU::boolean GLSLProgram::setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Mat3 &mat)
    {
        //TODO: glUniform1i(m_uniforms.get(),value);
        return true;
    }

    NOU::boolean GLSLProgram::setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Mat4 &mat)
    {
        //TODO: glUniform1i(m_uniforms.get(),value);
        return true;
    }

	NOU::boolean GLSLProgram::EnableLightning()
	{
		return true;
	}

	NOU::boolean GLSLProgram::DisableLightning()
	{
		return true;
	}
}