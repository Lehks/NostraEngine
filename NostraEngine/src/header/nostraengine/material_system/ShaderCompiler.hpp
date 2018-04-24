#ifndef NOE_CORE_MATERIAL_SYSTEM_SHADER_COMPILER_HPP
#define NOE_CORE_MATERIAL_SYSTEM_SHADER_COMPILER_HPP

/**
\file material_system/ShaderCompiler.hpp

\author  Leslie Marxen
\version 0.0.1
\since   0.0.1

\brief  A file that provides the base of any compiler class, every other Compiler implementation has to inherit from this interface.
        Usually a defaiult Shader provided by this Engine will be made fitting to the current context and compiled for later usage 
        on the GPU.
*/

class ShaderCompiler
{
public:
    /**
    \brief a method that compiles the generated source shader.
    */
    virtual void compile()  = 0;
    /**
    \brief a method that generates the source shader based on the used material and the default shader
    */
    virtual void generate() = 0;
};

#endif