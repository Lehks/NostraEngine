//
// Created by Dennis Franz on 23.04.18.
//
#include "glad/glad.h"
#include "nostraengine/src/header/nostraengine/material_system/Shader.hpp"

namespace NOE::NOE_MATSYS
{
    void Shader::link(NOU::uint32 vertex, NOU::uint32 fragment, NOU::uint32 geometry)
    {
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        if(geometryShaderSource != nullptr)
            glAttachShader(ID, geometry);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        if(geometryShaderSource != nullptr)
            glDeleteShader(geometry);
    }

    Shader::Shader(NOU::uint32 ID, const NOU::NOU_DAT_ALG::StringView8 *vertexShaderSource, const NOU::NOU_DAT_ALG::StringView8 *fragmentShaderSource, const NOU::NOU_DAT_ALG::StringView8 *geometryShaderSource) :
        ID(ID),
        vertexShaderSource(vertexShaderSource),
        fragmentShaderSource(fragmentShaderSource),
        geometryShaderSource(geometryShaderSource)
    {}

    void Shader::bind()
    {
        glUseProgram(ID);
    }

    void Shader::compile()
    {
        NOU::uint32 vertex, fragment;
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        const char * vShaderSource = vertexShaderSource->rawStr();
        glShaderSource(vertex, 1, &vShaderSource, nullptr);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        const char * fShaderCode = fragmentShaderSource->rawStr();
        glShaderSource(fragment, 1, &fShaderCode, nullptr);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        // if geometry shader is given, compile geometry shader
        unsigned int geometry = nullptr;
        if(geometryShaderSource != nullptr)
        {
            const char * gShaderCode = geometryShaderSource->rawStr();
            geometry = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(geometry, 1, &gShaderCode, nullptr);
            glCompileShader(geometry);
            checkCompileErrors(geometry, "GEOMETRY");
        }

        link(vertex, fragment, geometry);
    }

    // utility uniform functions
    // ------------------------------------------------------------------------
    void Shader::setBool(const NOU::NOU_DAT_ALG::StringView8 &name, NOU::boolean value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.rawStr()), (int)value);
    }
    // ------------------------------------------------------------------------
    void Shader::setInt(const NOU::NOU_DAT_ALG::StringView8 &name, NOU::int32 value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.rawStr()), value);
    }
    // ------------------------------------------------------------------------
    void Shader::setFloat(const NOU::NOU_DAT_ALG::StringView8 &name, NOU::float32 value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.rawStr()), value);
    }
    // ------------------------------------------------------------------------
    void Shader::setVec2(const NOU::NOU_DAT_ALG::StringView8 &name, const NOU::NOU_MATH::Vec2 &vec2) const
    {
        glUniform2fv(glGetUniformLocation(ID, name.rawStr()), 1, &vec2.value(0));
    }
    void Shader::setVec2(const NOU::NOU_DAT_ALG::StringView8 &name, NOU::float32 x, NOU::float32 y) const
    {
        glUniform2f(glGetUniformLocation(ID, name.rawStr()), x, y);
    }
    // ------------------------------------------------------------------------
    void Shader::setVec3(const NOU::NOU_DAT_ALG::StringView8 &name, const NOU::NOU_MATH::Vec3 &vec3) const
    {
        glUniform3fv(glGetUniformLocation(ID, name.rawStr()), 1, &vec3.value(0));
    }
    void Shader::setVec3(const NOU::NOU_DAT_ALG::StringView8 &name, NOU::float32 x, NOU::float32 y, NOU::float32 z) const
    {
        glUniform3f(glGetUniformLocation(ID, name.rawStr()), x, y, z);
    }
    // ------------------------------------------------------------------------
    void Shader::setVec4(const NOU::NOU_DAT_ALG::StringView8 &name, const NOU::NOU_MATH::Vec4 &vec4) const
    {
        glUniform4fv(glGetUniformLocation(ID, name.rawStr()), 1, &vec4.value(0));
    }
    void Shader::setVec4(const NOU::NOU_DAT_ALG::StringView8 &name, NOU::float32 x, NOU::float32 y, NOU::float32 z, NOU::float32 w) const
    {
        glUniform4f(glGetUniformLocation(ID, name.rawStr()), x, y, z, w);
    }
    // ------------------------------------------------------------------------
    void Shader::setMat2(const NOU::NOU_DAT_ALG::StringView8 &name, const NOU::NOU_MATH::Mat2 &mat2) const
    {
        glUniformMatrix2fv(glGetUniformLocation(ID, name.rawStr()), 1, GL_FALSE, &mat2.value(0,0));
    }
    // ------------------------------------------------------------------------
    void Shader::setMat3(const NOU::NOU_DAT_ALG::StringView8 &name, const NOU::NOU_MATH::Mat3 &mat3) const
    {
        glUniformMatrix3fv(glGetUniformLocation(ID, name.rawStr()), 1, GL_FALSE, &mat3.value(0,0));
    }
    // ------------------------------------------------------------------------
    void Shader::setMat4(const NOU::NOU_DAT_ALG::StringView8 &name, const NOU::NOU_MATH::Mat4 &mat3) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.rawStr()), 1, GL_FALSE, &mat3.value(0,0));
    }

    void Shader::checkCompileErrors(NOU::uint32 shader, const NOU::NOU_DAT_ALG::String8 &type)
    {
        NOU::int32 success;
        NOU::char8 infoLog[1024];

        NOU::NOU_CORE::Logger *Logger = NOU::NOU_CORE::Logger::instance();
        Logger->pushLogger<NOU::NOU_CORE::FileLogger>();
        Logger->pushLogger<NOU::NOU_CORE::ConsoleLogger>();

        NOU::NOU_DAT_ALG::String8 shaderCompileErrorMsg("ERROR::SHADER_COMPILATION_ERROR of type: ");
        NOU::NOU_DAT_ALG::String8 shaderLinkErrorMsg("ERROR::PROGRAM_LINKING_ERROR of type: ");

        if(type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
                NOU_WRITE_LOG(Logger, NOU::NOU_CORE::EventLevelCodes::ERROR, shaderCompileErrorMsg + " " + type.rawStr() + " " + infoLog, "logfile.txt");
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if(!success)
            {
                glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
                NOU_WRITE_LOG(Logger, NOU::NOU_CORE::EventLevelCodes::ERROR, shaderLinkErrorMsg + " " + type.rawStr() + " " + infoLog, "logfile.txt");
            }
        }
    }
}

