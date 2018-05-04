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
        File *m_source;
        File *m_target;
    
    public:
        /**
        \brief the constructor of the PreProcessor
        \param src the source File
        \param trg the target File
        */
        PreProcessor(const File *src = nullptr, const File *trg = nullptr);

        /**
        \brief starts the preprocessor
        */
        virtual void start() = 0;
        
        /**
        \brief sets the sourcefile. ("What will be processed?")
        \param src the sourcefile
        */
        void setSource(const File *src);

        /**
        \brief sets the targetfile ("Where will the procsessed file be stored?")
        \param trg the TargetFile
        */
        void setTarget(const File *trg);

        /**
        \brief returns the assigned sourceFile
        \return the assigned Targetfile
        */
        const File *getSource();

        /**
        \brief returns the assigned Targetfile
        \return the assigned Targetfile
        */
        const File *getTarget();
    }
}