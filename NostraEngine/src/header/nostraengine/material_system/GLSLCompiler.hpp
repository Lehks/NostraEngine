#ifndef NOE_MATERIAL_SYSTEM_GLSL_COMPILER_HPP
#define NOE_MATERIAL_SYSTEM_GLSL_COMPILER_HPP

#include "nostraengine/material_system/ShaderCompiler.hpp"
#include "nostrautils/NostraUtils.hpp.hpp"

/**
\file material_system/GLSLCompiler.hpp

\author  Leslie Marxen
\version 0.0.1
\since   0.0.1

\brief  A file that provides the implementation of the GLSL Shader compiler used by the Nostra Engine for rendering with OpenGL.
*/

namespace NOE::NOE_MATSYS
{
    class GLSLCompiler : public ShaderCompiler
    {
    private:
        /**
        \brief executes the pre processor of the NOMat language
        */
        void preProcessor()
        /**
        \brief executes the lexical analysis of the code
        */
        void lex();
    public:
        /**
        \brief the constructor of the GLSLCompilerClass
        */
        GLSLCompiler();
    };
}
#endif