//
// Created by Dennis Franz on 23.04.18.
//

#ifndef NOSTRAENGINE_SHADER_HPP
#define NOSTRAENGINE_SHADER_HPP

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <nostraengine/core/StdIncludes.hpp>
#include <nostrautils/NostraUtils.hpp>

namespace NOE::NOE_MATSYS
{
    class NOU_CLASS Shader
    {
    private:

    public:
        NOU::uint32 ID;

        Shader(const GLchar* vertexShaderPath, const GLchar fragmentShaderPath);

        void use();
        void setBool();
        void setInt();
        void setFloat();
    };
}


#endif //NOSTRAENGINE_SHADER_HPP
