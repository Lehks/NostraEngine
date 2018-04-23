//
// Created by Dennis Franz on 23.04.18.
//

#include <nostraengine/src/header/nostraengine/material_system/Shader.hpp>

namespace NOE::NOE_MATSYS
{
    Shader::Shader(const GLchar *vertexShaderPath, const GLchar fragmentShaderPath)
    {
        NOU::dat_alg::String8 vertexCode;
        NOU::dat_alg::String8 fragmentCode;

        NOU::file_mngt::File vShader (vertexShaderPath);
        NOU::file_mngt::File fShader (fragmentShaderPath);

        vShader.open();
        fShader.open();
        


    }
}

