//
// Created by Dennis Franz on 23.04.18.
//

#include "nostraengine/src/header/nostraengine/material_system/Shader.hpp"

namespace NOE::NOE_MATSYS
{
    Shader::Shader(const GLchar *vertexShaderPath, const GLchar *fragmentShaderPath)
    {
        NOU::NOU_DAT_ALG::String8 vertexCode;
        NOU::NOU_DAT_ALG::String8 fragmentCode;

        NOU::NOU_FILE_MNGT::File vShader(vertexShaderPath);
        NOU::NOU_FILE_MNGT::File fShader(fragmentShaderPath);

        vShader.open();
        fShader.open();



    }

    Shader::use()
    {}

    Shader::setBool()
    {}

    Shader::seInt()
    {}

    setFloat()
    {}
}

