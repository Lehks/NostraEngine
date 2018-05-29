#ifndef NOE_MATSYS_SHADERCLASS_HPP
#define NOE_MATSYS_SHADERCLASS_HPP

#include "nostrautils/NostraUtils.hpp"
#include "nostraengine/core/StdIncludes.hpp"
#include "nostraengine/window/Monitor.hpp"

namespace NOE::NOE_MATSYS
{

    class ShaderClass
    {
        enum class Variables
        {
            INT,
            FLOAT,
            BOOLEAN,
            VEC1,
            VEC2,
            VEC3,
            VEC4,
            MAT1,
            MAT2,
            MAT3,
            MAT4
        };

        NOU::NOU_DAT_ALG::String8 m_vShaderSource;
        NOU::NOU_DAT_ALG::String8 m_fShaderSource;
        NOU::NOU_DAT_ALG::String8 m_gShaderSource;


    };
}


#endif //NOE_MATSYS_SHADERCLASS_HPP
