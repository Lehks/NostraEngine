#ifndef NOE_CORE_MATERIAL_SYSTEM_SHADER_COMPILER_HPP
#define NOE_CORE_MATERIAL_SYSTEM_SHADER_COMPILER_HPP

#include "nostraengine/core/StdIncludes.hpp"

/**
\file material_system/ShaderCompiler.hpp

\author  Leslie Marxen
\version 0.0.1
\since   0.0.1

\brief  A file that provides the base of any compiler class.
*/

/**
\brief  This is an interface. Every other Compiler implementation has to inherit from this interface.
        Usually a defaiult Shader provided by this Engine will be made fitting to the current context and compiled for later usage 
        on the GPU. The compiler should perform the tasks of Generating the source Shader (readable by the used GPU interface) and 
        compiling those for a later use on the GPU
*/
namespace NOE::NOE_MATSYS
{

    class ShaderCompiler
    {
    private:
        /**
        \brief the source File of the soon compiled shader 
        */
        File &m_source;
        /**
        \brief the target File of the soon compiled shader
        */
        File &m_target;

    public:
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

        /**
        \brief sets the source File that will be compiled later
        \param src a File object contianing the path to the sourcefile
        */
        void setSource(const File &src);

        /**
        \brief returns a File object containing the compiled shader for the corresponding ShaderLang
        \return a file object containgin the compiled shader 
        */
        const File& getTarget();
    };
}
#endif