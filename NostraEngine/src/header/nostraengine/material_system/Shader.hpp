/**
\file material_system/Shader.hpp

\author	 Dennis Franz
\version 1.0.0
\since	 1.0.0
*/

#ifndef NOE_MATSYS_SHADER_HPP
#define NOE_MATSYS_SHADER_HPP

#include "nostraengine/core/StdIncludes.hpp"
#include "nostrautils/NostraUtils.hpp"

namespace NOE::NOE_MATSYS
{
    /**
    \brief		A class for compile / link and bind shaders.

    \details    This class is for Creating the actual Open-GL-Shader-Program.

                1. You have to create an instance of a Shader object by using the given constructor.
                   Note that the ID should be unique in the whole render pipeline and the vertex shader as well as the
                   fragment shader are a must, just the geometry shader is optional.

                2. You hae to compile the Shader via the compile method. In the compile message each shader gets compiled
                   and the checkCompileErrors method checks for compile errors. After the compiling is done without any errors
                   the shaders gets automatically attached and linked to the program.

                3. If you want to use the final shader you simply have to call the bind method.
*/
    class NOU_CLASS Shader
    {
    private:
        /**
        \brief The vertex shader sourcecode.
        */
        const NOU::NOU_DAT_ALG::StringView8 *vertexShaderSource;
        /**
        \brief The fragment shader sourcecode.
        */
        const NOU::NOU_DAT_ALG::StringView8 *fragmentShaderSource;
        /**
        \brief The vertex shader sourcecode (if used).
        */
        const NOU::NOU_DAT_ALG::StringView8 *geometryShaderSource;

        /**
        \param vertex the id of the vertex shader.
        \param fragment the id of the fragment shader.
        \param geometry the id of the geometry shader (nullptr if not used).

        \return void.

        \brief Attaches the shader to the shader program and links it. After that each shader get's deleted.
        */
        void link(NOU::uint32 vertex, NOU::uint32 fragment, NOU::uint32 geometry = nullptr);
    public:
        /**
        \brief The Id of the shader program.
        */
        NOU::uint32 ID;
        /**
        \param ID                   The id of the shader program.
        \param vertexShaderPath     The Path of the vertex shader source.
        \param fragmentShaderPath   The Path of the fragment shader source.
        \param geometryShaderSource The Path of the geometry shader source.

        \brief The constructor for the Shader. If no geometry shader is given or used this variable is set to nullptr by default.
        */
        Shader(NOU::uint32 ID, const NOU::NOU_DAT_ALG::StringView8 *vertexShaderPath, const NOU::NOU_DAT_ALG::StringView8 *fragmentShaderPath, const NOU::NOU_DAT_ALG::StringView8 *geometryShaderSource = nullptr);

        /**
        \retun void.

        \brief Binds the Shader with the given ID to a GL-Program.
        */
        void bind();
        /**
        \retun void.

        \brief Create's the shaders from the given source.
        */
        void compile();
        /**
        \retun void.
        \param name         the name of the uniform you want to modify.
        \param value        the value which should be given to the uniform.

        \brief Set's a boolean value in the given shader uniform.
        */
        void setBool(const NOU::NOU_DAT_ALG::StringView8 &name, NOU::boolean value) const;
        /**
        \retun void.
        \param name         the name of the uniform you want to modify.
        \param value        the value which should be given to the uniform.

        \brief Set's an integer value in the given shader uniform.
        */
        void setInt(const NOU::NOU_DAT_ALG::StringView8 &name, NOU::int32 value) const;
        /**
        \retun void.
        \param name         the name of the uniform you want to modify.
        \param value        the value which should be given to the uniform.

        \brief Set's a float value in the given shader uniform.
        */
        void setFloat(const NOU::NOU_DAT_ALG::StringView8 &name, NOU::float32 value) const;
        /**
        \retun void.
        \param name         the name of the uniform you want to modify.
        \param vec2         the 2-dimensional vector which should be given to the uniform.

        \brief Set's a 2-dimensional vector in the given shader uniform.

        \see nostrautils::math::vector.hpp
        */
        void setVec2(const NOU::NOU_DAT_ALG::StringView8 &name, const NOU::NOU_MATH::Vec2 &vec2) const;
        /**
        \retun void.
        \param name         the name of the uniform you want to modify.
        \param vec3         the 3-dimensional vector which should be given to the uniform.

        \brief Set's a 3-dimensional vector in the given shader uniform.

        \see nostrautils::math::vector.hpp
        */
        void setVec3(const NOU::NOU_DAT_ALG::StringView8 &name, const NOU::NOU_MATH::Vec3 &vec3) const;
        /**
        \retun void.
        \param name         the name of the uniform you want to modify.
        \param vec4         the 4-dimensional vector which should be given to the uniform.

        \brief Set's a 4-dimensional vector in the given shader uniform.

        \see nostrautils::math::vector.hpp
        */
        void setVec4(const NOU::NOU_DAT_ALG::StringView8 &name, const NOU::NOU_MATH::Vec4 &vec4) const;
        /**
        \retun void.
        \param name         the name of the uniform you want to modify.
        \param x            x value of the 2-dimensional vector.
        \param y            y value of the 2-dimensional vector.

        \brief Set's a 2-dimensional vector,  in form of "float x | float y ", in the given shader uniform.

        */
        void setVec2(const NOU::NOU_DAT_ALG::StringView8 &name, NOU::float32 x, NOU::float32 y) const;
        /**
        \retun void.
        \param name         the name of the uniform you want to modify.
        \param x            x value of the 3-dimensional vector.
        \param y            y value of the 3-dimensional vector.
        \param z            z value of the 3-dimensional vector.

        \brief Set's a 3-dimensional vector, in form of "float x | float y | float z", in the given shader uniform.
        */
        void setVec3(const NOU::NOU_DAT_ALG::StringView8 &name, NOU::float32 x, NOU::float32 y, NOU::float32 z) const;
        /**
        \retun void.
        \param name         the name of the uniform you want to modify.
        \param x            x value of the 4-dimensional vector.
        \param y            y value of the 4-dimensional vector.
        \param z            z value of the 4-dimensional vector.
        \param w            w value of the 4-dimensional vector.

        \brief Set's a 4-dimensional vector, in form of "float x | float y | float z | float w", in the given shader uniform.
        */
        void setVec4(const NOU::NOU_DAT_ALG::StringView8 &name, NOU::float32 x, NOU::float32 y, NOU::float32 z, NOU::float32 w) const;
        /**
        \retun void.
        \param name         the name of the uniform you want to modify.
        \param mat          the 2-dimensional matrix which should be given to the uniform.

        \brief Set's a 2-dimensional matrix in the given shader uniform.

        \see nostrautils::math::Matrix.hpp
        */
        void setMat2(const NOU::NOU_DAT_ALG::StringView8 &name, const NOU::NOU_MATH::Mat2 &mat2) const;
        /**
        \retun void.
        \param name         the name of the uniform you want to modify.
        \param mat          the 3-dimensional matrix which should be given to the uniform.

        \brief Set's a 3-dimensional matrix in the given shader uniform.

        \see nostrautils::math::Matrix.hpp
        */
        void setMat3(const NOU::NOU_DAT_ALG::StringView8 &name, const NOU::NOU_MATH::Mat3 &mat3) const;
        /**
        \retun void.
        \param name         the name of the uniform you want to modify.
        \param mat4         the 4-dimensional matrix which should be given to the uniform.

        \brief Set's a 4-dimensional matrix in the given shader uniform.

        \see nostrautils::math::Matrix.hpp
        */
        void setMat4(const NOU::NOU_DAT_ALG::StringView8 &name, const NOU::NOU_MATH::Mat4 &mat4) const;
        /**
        \retun void.
        \param shader        the id of the shader which had an error.
        \param type          the type of the error.

        \brief Checks if there where any compile errors. If so the errors will be written in a file called "logfile.txt" as well as
        printed to the console.
        */
        void checkCompileErrors(NOU::uint32 shader, const NOU::NOU_DAT_ALG::String8 &type);
    };
}


#endif //NOE_MATSYS_SHADER_HPP
