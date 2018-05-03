//
// Created by Dennis Franz on 23.04.18.
//

#include "nostraengine/src/header/nostraengine/material_system/Shader.hpp"

namespace NOE::NOE_MATSYS
{
    Shader::Shader(NOU::int32 ID, const NOU::NOU_DAT_ALG::StringView8 *vertexShaderSource, const NOU::NOU_DAT_ALG::StringView8 *fragmentShaderSource, const NOU::NOU_DAT_ALG::StringView8 *geometryShaderSource) :
        vertexShaderSource(vertexShaderSource),
        fragmentShaderSource(fragmentShaderSource),
        geometryShaderSource(geometryShaderSource)
    {}

    void Shader::use()
    {
        glUseProgram(ID);
    }

    void Shader::link(NOU::uint32 vertex, NOU::uint32 fragment, NOU::uint32 geometry)
    {
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        if(geometryShaderSource != nullptr)
            glAttachShader(ID, geometry);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessery
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        if(geometryShaderSource != nullptr)
            glDeleteShader(geometry);
    }

    void Shader::compile()
    {
        NOU::uint32 vertex, fragment;
        NOU::int32 success;
        NOU::char8 infoLog[512];
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        const char * vShaderSource = vertexShaderSource->rawStr();
        glShaderSource(vertex, 1, &vShaderSource, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        const char * fShaderCode = fragmentShaderSource->rawStr();
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        // if geometry shader is given, compile geometry shader
        unsigned int geometry;
        if(geometryShaderSource != nullptr)
        {
            const char * gShaderCode = geometryShaderSource->rawStr();
            geometry = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(geometry, 1, &gShaderCode, NULL);
            glCompileShader(geometry);
            checkCompileErrors(geometry, "GEOMETRY");
        }

        link(vertex, fragment, geometry);
    }

    // utility uniform functions
    // ------------------------------------------------------------------------
    void Shader::setBool(NOU::NOU_DAT_ALG::StringView8 name, NOU::boolean value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.rawStr()), (int)value);
    }
    // ------------------------------------------------------------------------
    void Shader::setInt(NOU::NOU_DAT_ALG::StringView8 name, NOU::int32 value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.rawStr()), value);
    }
    // ------------------------------------------------------------------------
    void Shader::setFloat(NOU::NOU_DAT_ALG::StringView8 name, NOU::float32 value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.rawStr()), value);
    }
    // ------------------------------------------------------------------------
    void Shader::setVec2(NOU::NOU_DAT_ALG::StringView8 name, const glm::vec2 &value) const
    {
        glUniform2fv(glGetUniformLocation(ID, name.rawStr()), 1, &value[0]);
    }
    void Shader::setVec2(NOU::NOU_DAT_ALG::StringView8 name, NOU::float32 x, NOU::float32 y) const
    {
        glUniform2f(glGetUniformLocation(ID, name.rawStr()), x, y);
    }
    // ------------------------------------------------------------------------
    void Shader::setVec3(NOU::NOU_DAT_ALG::StringView8 name, const glm::vec3 &value) const
    {
        glUniform3fv(glGetUniformLocation(ID, name.rawStr()), 1, &value[0]);
    }
    void Shader::setVec3(NOU::NOU_DAT_ALG::StringView8 name, NOU::float32 x, NOU::float32 y, NOU::float32 z) const
    {
        glUniform3f(glGetUniformLocation(ID, name.rawStr()), x, y, z);
    }
    // ------------------------------------------------------------------------
    void Shader::setVec4(NOU::NOU_DAT_ALG::StringView8 name, const glm::vec4 &value) const
    {
        glUniform4fv(glGetUniformLocation(ID, name.rawStr()), 1, &value[0]);
    }
    void Shader::setVec4(NOU::NOU_DAT_ALG::StringView8 name, NOU::float32 x, NOU::float32 y, NOU::float32 z, NOU::float32 w) const
    {
        glUniform4f(glGetUniformLocation(ID, name.rawStr()), x, y, z, w);
    }
    // ------------------------------------------------------------------------
    void Shader::setMat2(NOU::NOU_DAT_ALG::StringView8 name, const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(ID, name.rawStr()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void Shader::setMat3(NOU::NOU_DAT_ALG::StringView8 name, const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(ID, name.rawStr()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void Shader::setMat4(NOU::NOU_DAT_ALG::StringView8 name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.rawStr()), 1, GL_FALSE, &mat[0][0]);
    }

    void Shader::checkCompileErrors(GLuint shader, std::string type)
    {
        GLint success;
        GLchar infoLog[1024];
        if(type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if(!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
}

