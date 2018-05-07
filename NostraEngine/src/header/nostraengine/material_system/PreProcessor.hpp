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
        NOU::NOU_FILE_MNGT::File *m_source;
        NOU::NOU_FILE_MNGT::File *m_target;
    
    public:
        /**
        \brief the constructor of the PreProcessor
        \param src the source File
        \param trg the target File
        */
        PreProcessor(NOU::NOU_FILE_MNGT::File *src = nullptr, NOU::NOU_FILE_MNGT::File *trg = nullptr);

        /**
        \brief starts the preprocessor
        */
        virtual void start(NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8> args) = 0;
        
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
    };
}
#endif