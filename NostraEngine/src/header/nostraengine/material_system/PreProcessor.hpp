#ifndef NOE_MATERIAL_SYSTEM_PREPROCESSOR_HPP
#define NOE_MATERIAL_SYSTEM_PREPROCESSOR_HPP

#include "nostraengine/core/StdIncludes.hpp"
#include "nostrautils/NostraUtils.hpp"

/**
\file material_system/ShaderCompiler.hpp

\author  Leslie Marxen
\version 0.0.1
\since   0.0.1

\brief  A file that provides the base of any preprocessor class.
*/

/**
\brief This is an interface. Every other PreProcessor implementation has to inherit from this interface.
       This preprocessor has to fulfill any duty and to adjust the sourcecode fitting for the compiler.
*/
namespace NOE::NOE_MATSYS
{
    /**
    \brief this class provides the base of any preprocessor
    */
    class NOU_CLASS PreProcessor
    {
    private:
        /**
        \brief the outputfile
        */
        NOU::NOU_FILE_MNGT::File  *m_target;

        /**
        \brief the sourcecode
        */
        NOU::NOU_DAT_ALG::String8 m_code;
        /**
        \brief the sourcefile (nullptr if code was never read from a file)
        */
        NOU::NOU_FILE_MNGT::File *m_source;
    
    public:
        /**
        \brief the constructor of the PreProcessor
        \param src the source File
        \param trg the target File
        */
        PreProcessor(NOU::NOU_FILE_MNGT::File *src, NOU::NOU_FILE_MNGT::File *trg = nullptr);

        /** a constructor of the PreProcessor
        \param src A string containing the whole sourcecode
        \param trg the target file
        */
        PreProcessor(const NOU::NOU_DAT_ALG::String8 &code, NOU::NOU_FILE_MNGT::File *trg = nullptr);

        /**
        \brief starts the preprocessor
        */
        virtual void start(NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8> args = NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8>()) = 0;
        
        /**
        \brief sets the sourcefile. ("What will be processed?")
        \param src the sourcefile
        */
        void setSource(const NOU::NOU_FILE_MNGT::File *src);

        /**
        \brief sets the targetfile ("Where will the procsessed file be stored?")
        \param trg the TargetFile
        */
        void setTarget(NOU::NOU_FILE_MNGT::File *trg);

        /**
        \brief returns the assigned sourceFile
        \return the assigned Targetfile
        */
        NOU::NOU_FILE_MNGT::File *getSource();

        /**
        \brief returns the assigned Targetfile
        \return the assigned Targetfile
        */
        NOU::NOU_FILE_MNGT::File *getTarget();

        /**
        \brief setter for the code
        \param code the sourcecode
        */
        void setCode(const NOU::NOU_DAT_ALG::String8 &code);

        /**
        \brief getter for the code
        \return A string containing the whole source code
        */
        const NOU::NOU_DAT_ALG::String8 &getCode();
        
    };
}
#endif