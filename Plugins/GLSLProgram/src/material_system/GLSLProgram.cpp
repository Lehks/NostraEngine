#include "GLSLProgram.hpp"

namespace GLSLProgramPlugin
{
    NOU::boolean GLSLProgram::linkShader()
    {
        glLinkProgram(m_ID);
    }

    NOU::boolean GLSLProgram::createVertexShader()
    {
        m_vertexShaderId = createShader(m_vertexShader, GL_VERTEX_SHADER);
        if(m_vertexShaderId == 0)
        {
            return false;
        }

        return true;
    }

    NOU::boolean GLSLProgram::createFragmetShader()
    {
        m_fragmentShaderId = createShader(m_fragmentShader, GL_FRAGMENT_SHADER);
        if(m_fragmentShaderId == 0)
        {
            return false;
        }

        return true;
    }

    NOU::boolean GLSLProgram::createGeometryShader()
    {
        m_geometryShaderId = createShader(m_geometryShader, GL_GEOMETRY_SHADER);
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

    NOU::boolean GLSLProgram::loadVertexShader(const NOU::NOU_DAT_ALG::String8 &shaderSource)
    {
        NOU::NOU_FILE_MNGT::File file(shaderSource);
        file.open(NOU::NOU_FILE_MNGT::File::AccessMode.READ);
        m_vertexShader = file.read();
        file.close();
        return true;
    }

    NOU::boolean GLSLProgram::loadFragmentShader(const NOU::NOU_DAT_ALG::String8 &shaderSource)
    {
        NOU::NOU_FILE_MNGT::File file(shaderSource);
        file.open(NOU::NOU_FILE_MNGT::File::AccessMode.READ);
        m_fragmentShader = file.read();
        file.close();
        return true;
    }

    NOU::boolean GLSLProgram::loadGeometryShader(const NOU::NOU_DAT_ALG::String8 &shaderSource)
    {
        NOU::NOU_FILE_MNGT::File file(shaderSource);
        file.open(NOU::NOU_FILE_MNGT::File::AccessMode.READ);
        m_geometryShader = file.read();
        file.close();
        return true;
    }

    NOU::boolean GLSLProgram::~Program() {}

    NOU::boolean GLSLProgram::createShader(const NOU::NOU_DAT_ALG::String8 &vertexShaderSource, const NOU::NOU_DAT_ALG::String8 &fragmentShaderSource, const NOU::NOU_DAT_ALG::String8 &geometryShaderSource)
    {
        loadVertexShader(vertexShaderSource);
        loadFragmentShader(fragmentShaderSource);
        if(geometryShaderSource != nullptr)
        {
            loadGeometryShader(geometryShaderSource);
        }

        createVertexShader();
        createFragmetShader();
        if(geometryShaderSource != nullptr)
        {
            createGeometryShader();
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

        linkShader();

        glDeleteShader(m_vertexShaderId);
        glDeleteShader(m_fragmentShaderId);
        if(m_geometryShader != nullptr)
        {
            glDeleteShader(m_geometryShaderId);
        }

        return true;
    }

    NOU::boolean GLSLProgram::bind()
    {
        glUseProgram(m_ID);
    }

    NOU::boolean GLSLProgram::unbind()
    {
        glUseProgram(0);
    }

    NOU::boolean GLSLProgram::createUniform(const NOU::NOU_DAT_ALG::String8 &name)
    {
        NOU::sizeType uniformLocation = glGetUniformLocation(m_ID, name);
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
        glUniform1i(m_uniforms.get(name), value);
        return true;
    }

    NOU::boolean GLSLProgram::setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::float32 xvlaue, NOU::float32 yvalue)
    {
        glUniform1i(m_uniforms.get(name), xvalue, yvalue);
        return true;
    }

    NOU::boolean GLSLProgram::setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Vec2 &vec)
    {
        glUniform1i(m_uniforms.get(name), vec.Value[0], vec.Value[1]);
        return true;
    }

    NOU::boolean GLSLProgram::setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::float32 xvalue, NOU::float32 yvalue, NOU::float32 zvalue)
    {
        glUniform1i(m_uniforms.get(name), xvalue, yvalue, zvalue);
        return true;
    }

    NOU::boolean GLSLProgram::setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Vec3 &vec)
    {
        glUniform1i(m_uniforms.get(name), vec.Value[0], vec.Value[1], vec.Value[2]);
        return true;
    }

    NOU::boolean GLSLProgram::setUniform(const NOU::NOU_DAT_ALG::String8 &name, NOU::float32 xvalue, NOU::float32 yvalue, NOU::float32 zvalue, NOU::float32 wvalue)
    {
        glUniform1i(m_uniforms.get(name), xvalue, yvalue, zvalue, wvalue);
        return true;
    }

    NOU::boolean GLSLProgram::setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Vec4 &vec)
    {
        glUniform1i(m_uniforms.get(), vec.Value[0], vec.Value[1], vec.Value[2], vec.Value[3]);
        return true;
    }

    NOU::boolean GLSLProgram::setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Mat2 &mat)
    {
        //glUniform1i(m_uniforms.get(), value, );
        return true;
    }

    NOU::boolean GLSLProgram::setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Mat3 &mat)
    {
        //glUniform1i(m_uniforms.get(),value);
        return true;
    }

    NOU::boolean GLSLProgram::setUniform(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_MATH::Mat4 &mat)
    {
        //glUniform1i(m_uniforms.get(),value);
        return true;
    }

	NOU::boolean GLSLProgram::enabnleLightning()
	{
		return true;
	}

	NOU::boolean GLSLProgram::disableLightning()
	{
		return true;
	}
}
