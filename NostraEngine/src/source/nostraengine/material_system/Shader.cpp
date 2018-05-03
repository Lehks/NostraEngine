//
// Created by Dennis Franz on 23.04.18.
//

#include "NostraEngine/material_system/Shader.hpp"

namespace NOE::NOE_MATSYS
{
    Shader::Shader(NOU::NOU_DAT_ALG::String8 vertexShaderPath, NOU::NOU_DAT_ALG::String8 fragmentShaderPath) :
        vertexShaderPath(vertexShaderPath),
        fragmentShaderPath(fragmentShaderPath)
    {}

    void Shader::use()
    {}

    void Shader::link()
    {}

    void Shader::compile()
    {}

    void Shader::setBool()
    {}

    void Shader::setInt()
    {}

    void Shader::setFloat()
    {}
}

