#ifndef NOE_MATSYS_SHADERCLASS_HPP
#define NOE_MATSYS_SHADERCLASS_HPP

#include "nostrautils/NostraUtils.hpp"
#include "nostraengine/core/StdIncludes.hpp"
#include "nostraengine/window/Monitor.hpp"

namespace NOE::NOE_MATSYS
{

    class ShaderClass
    {
    public:
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

    private:
        NOU::NOU_DAT_ALG::String8 m_vShaderSource;
        NOU::NOU_DAT_ALG::String8 m_fShaderSource;
        NOU::NOU_DAT_ALG::String8 m_gShaderSource;
        NOU::boolean m_allreadyCompiled;
        NOU::int32 ID;

    public:
        ShaderClass(NOU::int32 ID, const NOU::NOU_FILE_MNGT::Path& fShaderSourcePath, const NOU::NOU_FILE_MNGT::Path& vShaderSourcePath, const NOU::NOU_FILE_MNGT::Path& gShaderSourcePath = nullptr);
        NOU::boolean createShader();
        NOU::boolean bind();
        NOU::int32 getUniformLocation(NOU::int32 programID, const NOU::NOU_DAT_ALG::String8& uniformName);
        NOU::boolean setVariable(NOU::int32 programID, NOU::int32 uniformLocation, void* val);
    };
}


#endif //NOE_MATSYS_SHADERCLASS_HPP
