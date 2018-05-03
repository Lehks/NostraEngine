#ifndef NOE_MATERIAL_SYSTEM_GLSL_COMPILER_HPP
#define NOE_MATERIAL_SYSTEM_GLSL_COMPILER_HPP

#include "nostrautils/NostraUtils.hpp"
#include "nostraengine/core/StdIncludes.hpp"
#include "nostraengine/material_system/ShaderCompiler.hpp"

/**
\file material_system/GLSLCompiler.hpp

\author  Leslie Marxen
\version 0.0.1
\since   0.0.1

\brief  A file that provides the implementation of the GLSL Shader compiler used by the Nostra Engine for rendering with OpenGL.
*/

namespace NOE
{
    namespace NOE_MATSYS{
        class NOU_CLASS GLSLCompiler : public ShaderCompiler
        {
        private:
            /*
            \brief some constants for the PreProcessor
            */
            const NOU::char8 PP_SYM = '#';
            const NOU::NOU_DAT_ALG::StringView8 PP_INCLUDE = "include";
            /**
            \brief executes the pre processor of the NOMat language
            */
            void preProcessor();
            /**
            \brief executes the lexical analysis of the code
            */
            void lex();
        public:
            /**
            \brief the constructor of the GLSLCompilerClass
            */
            GLSLCompiler();

            /**
            \brief a method that compiles the generated source shader.
            */
            virtual void compile()  = 0;
            /**
            \brief a method that generates the source shader based on the used material and the default shader
            */
            virtual void generate() = 0;
            /**
            \brief sets the internal Material attributes for later generation/compilation
            */
            virtual void setMaterial() = 0;
        };
    }
}
#endif