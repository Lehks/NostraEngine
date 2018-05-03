//
// Created by Dennis Franz on 23.04.18.
//

#ifndef NOSTRAENGINE_SHADER_HPP
#define NOSTRAENGINE_SHADER_HPP

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "nostraengine/core/StdIncludes.hpp"
#include "nostrautils/NostraUtils.hpp"

namespace NOE::NOE_MATSYS
{
    class NOU_CLASS Shader
    {
    private:
        NOU::NOU_DAT_ALG::String8 vertexShaderPath;
        NOU::NOU_DAT_ALG::String8 fragmentShaderPath;
    public:
        NOU::uint32 ID;

        Shader(NOU::NOU_DAT_ALG::String8 vertexShaderPath, NOU::NOU_DAT_ALG::String8 fragmentShaderPath);

        void use();
        void link();
        void compile();
        void setBool();
        void setInt();
        void setFloat();
    };
}


#endif //NOSTRAENGINE_SHADER_HPP
