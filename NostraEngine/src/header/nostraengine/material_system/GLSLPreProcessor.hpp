#include "nostraengine/material_system/PreProcessor.hpp"


/**
\file material_system/ShaderCompiler.hpp

\author  Leslie Marxen
\version 0.0.1
\since   0.0.1

\brief  A file that implements the preprocessor for GLSL.
*/
namespace NOE::NOE_MATSYS
{
    /**
    \brief This is an interface. Every other PreProcessor implementation has to inherit from this interface.
           This preprocessor has to fulfill any duty and to adjust the sourcecode fitting for the compiler.
    */
    class NOU_CLASS GLSLPreProcessor : public PreProcessor
    {
    private:

    /**
    All the Following constants and structs are specific keywords used in the pre-processor directives
    */

    const NOU::char8                PREPROCESSOR_PREFIX     = '#';
    
    const NOU::NOU_DAT_ALG::String8 PREPROCESSOR_INCLUDE    = "include";
    const NOU::NOU_DAT_ALG::String8 PREPROCESSOR_DEFINE     = "define";
    const NOU::NOU_DAT_ALG::String8 PREPROCESSOR_IFNDEF     = "ifndef";
    const NOU::NOU_DAT_ALG::String8 PREPROCESSOR_ELSE       = "else";
    const NOU::NOU_DAT_ALG::String8 PREPROCESSOR_ENDIF      = "endif";

    const NOU::char8 TOKEN_SEPERATOR[2] = {';', '{'};

    

    enum class State
	{
		DEFAULT,
        PRE_PROCESSOR_DIRECTIVE,
        DEFINE,
        INCLUDE,
        IFNDEF
	};

    State m_currentState;
    NOU::NOU_DAT_ALG::String8 m_currentToken;

    public:
        /**
        \brief This is the constructor of the GLSL Preprocessor
        \param src a pointer to the source File
        \param trg a pointer to the target File (Where the output will be)
        */
        GLSLPreProcessor(NOU::NOU_FILE_MNGT::File *src, NOU::NOU_FILE_MNGT::File *trg = nullptr);

        /**
        \brief starts the preprocessor
        \param args if any Arguments have to be passed they will be written in this Vector
        */
        virtual void start(NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8> args = NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8>()) override;

    private:
        class CodeIterator
        {
            private:
                const NOU::NOU_DAT_ALG::String8 &m_code;
                NOU::uint64 m_pos;
                NOU::NOU_DAT_ALG::String8 m_currToken;

            public:
                CodeIterator(const NOU::NOU_DAT_ALG::String8 &code);
                
                void reset();
                NOU::boolean hasNext();
                const NOU::NOU_DAT_ALG::String8 &next();
                const NOU::NOU_DAT_ALG::String8 &getCurrToken();
        };
    };
}