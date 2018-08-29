#ifndef NOE_MATSYS_PROGRAM_HPP
#define NOE_MATSYS_PROGRAM_HPP

#include "nostrautils/NostraUtils.hpp"

#include "nostraengine/NostraEngine.hpp"

/**
\author	 Dennis Franz
\version 1.0.0
\since   1.0.0
*/

namespace NOE::NOE_MATSYS
{
    class NOU_CLASS Program
    {
	protected:
		/**
		\brief A String for the vertex shader source.
		*/
		NOU::NOU_DAT_ALG::String8 m_vShaderSource;
		/**
		\brief A String for the fragment shader source.
		*/
		NOU::NOU_DAT_ALG::String8 m_fShaderSource;
		/**
		\brief A String for the geometry shader source.
		*/
		NOU::NOU_DAT_ALG::String8 m_gShaderSource;

		virtual NOU::boolean linkShader() = 0;
		virtual NOU::boolean createVertexShader() = 0;
		virtual NOU::boolean createFragmetShader() = 0;
		virtual NOU::boolean createGeometryShader() = 0;
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

    public:
		/**
		\brief A default destructor.
		*/
        virtual ~Program() = default;

		/**
		\brief A Method to create a Shader.
		*/
        virtual NOU::boolean createShader() = 0;
		/**
		\brief A Method to bind a Shader to the corresponding program.
		*/
        virtual NOU::boolean bind() = 0;
		virtual NOU::boolean unbind() = 0;
    };
}
#endif