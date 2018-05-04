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
        const NOU::NOU_DAT_ALG::StringView8 *vertexShaderSource;
        const NOU::NOU_DAT_ALG::StringView8 *fragmentShaderSource;
        const NOU::NOU_DAT_ALG::StringView8 *geometryShaderSource;

        void link(NOU::uint32 vertex, NOU::uint32 fragment, NOU::uint32 geometry = nullptr);
    public:
        NOU::uint32 ID;

        Shader(NOU::uint32 ID, const NOU::NOU_DAT_ALG::StringView8 *vertexShaderPath, const NOU::NOU_DAT_ALG::StringView8 *fragmentShaderPath, const NOU::NOU_DAT_ALG::StringView8 *geometryShaderSource = nullptr);

        void use();
        void compile();
        void setBool(const NOU::NOU_DAT_ALG::StringView8 &name, NOU::boolean value) const;
        void setInt(const NOU::NOU_DAT_ALG::StringView8 &name, NOU::int32 value) const;
        void setFloat(const NOU::NOU_DAT_ALG::StringView8 &name, NOU::float32 value) const;
        void setVec2(const NOU::NOU_DAT_ALG::StringView8 &name, const NOU::NOU_MATH::Vec2 &value) const;
        void setVec3(const NOU::NOU_DAT_ALG::StringView8 &name, const NOU::NOU_MATH::Vec3 &value) const;
        void setVec4(const NOU::NOU_DAT_ALG::StringView8 &name, const NOU::NOU_MATH::Vec4 &value) const;
        void setVec2(const NOU::NOU_DAT_ALG::StringView8 &name, NOU::float32 x, NOU::float32 y) const;
        void setVec3(const NOU::NOU_DAT_ALG::StringView8 &name, NOU::float32 x, NOU::float32 y, NOU::float32 z) const;
        void setVec4(const NOU::NOU_DAT_ALG::StringView8 &name, NOU::float32 x, NOU::float32 y, NOU::float32 z, NOU::float32 w) const;
        void setMat2(const NOU::NOU_DAT_ALG::StringView8 &name, const NOU::NOU_MATH::Mat2 &mat) const;
        void setMat3(const NOU::NOU_DAT_ALG::StringView8 &name, const NOU::NOU_MATH::Mat3 &mat) const;
        void setMat4(const NOU::NOU_DAT_ALG::StringView8 &name, const NOU::NOU_MATH::Mat4 &mat) const;
        void checkCompileErrors(NOU::uint32 shader, const NOU::NOU_DAT_ALG::String8 &type);
    };
}


#endif //NOSTRAENGINE_SHADER_HPP
