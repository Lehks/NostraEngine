#ifndef NOE_CORE_MATERIAL_SYSTEM_SHADER_COMPILER_HPP
#define NOE_CORE_MATERIAL_SYSTEM_SHADER_COMPILER_HPP

#include "nostraengine/core/StdIncludes.hpp"
#include "nostrautils/NostraUtils.hpp"
#include "nostraengine/material_system/PreProcessor.hpp"

/**
\file material_system/ShaderCompiler.hpp

\author  Leslie Marxen
\version 0.0.1
\since   0.0.1

\brief  A file that provides the base of any compiler class.
*/

/**
\brief  This is an interface. Every other Compiler implementation has to inherit from this interface.
        Usually a default Shader provided by this Engine will be made fitting to the current context and compiled for later usage 
        on the GPU. The compiler should perform the tasks of Generating the source Shader (readable by the used GPU interface) and 
        compiling those for a later use on the GPU
*/
namespace NOE::NOE_MATSYS
{
    /**
    \brief this class provides the base of any compiler
    */
    class NOU_CLASS ShaderCompiler
    {
    protected:
        /**
        \brief the source File of the soon compiled shader 
        */
        NOU::NOU_FILE_MNGT::File *m_source;  

        /**
        \brief the temporary file where the preprocessed code is stored
        */
        NOU::NOU_FILE_MNGT::File *m_processed;
        
        /**
        \brief the target File of the soon compiled shader
        */
        NOU::NOU_FILE_MNGT::File *m_target;

        /**
        \brief the used Preprocessor
        */
        NOE::NOE_MATSYS::PreProcessor *m_preprocessor;

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
        \brief a method that calls the corresponding preprocessor
        */
        void process();

        /**
        \brief sets the internal Material attributes for later generation/compilation
        */
        virtual void setMaterial() = 0;

        /**
        \brief sets the source File that will be compiled later
        \param src a File object contianing the path to the sourcefile
        */
        void setSource(NOU::NOU_FILE_MNGT::File *src);

        /**
        \brief returns a File object containing the compiled shader for the corresponding ShaderLang
        \return a file object containgin the compiled shader 
        */
        NOU::NOU_FILE_MNGT::File& getTarget();

        /**
        \brief sets the target destination File that will be compiled to later
        \param trg a File object contianing the path to the target file
        */
        void setTarget(NOU::NOU_FILE_MNGT::File *trg);

        /**
        \brief returns a File object containing the Source file
        \return a file object containing the source file 
        */
        const NOU::NOU_FILE_MNGT::File& getSource();

        /**
        \brief sets the destination of the preprocessed file
        \param pp the File object containing the preprocessed file
        */
        void setPreProcessedTarget(NOU::NOU_FILE_MNGT::File *pp);

        /**
        \brief gets the destination of the preprocessed file
        \return the File object containing the preprocessed file
        */
       NOU::NOU_FILE_MNGT::File *getPreProcessedTarget();
        /**
        \brief sets the PreProcessor that will be used in the compile process
        \param pp an object that implements a preprocessor
        */
       void setPreProcessor(PreProcessor *pp);
    };
}
#endif