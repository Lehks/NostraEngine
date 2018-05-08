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

    /*
    All the Following constants and structs are specific keywords used in the pre-processor directives
    */

    /**
    \brief Prefix for all preprocessor directives
    */
    const NOU::char8                PREPROCESSOR_PREFIX     = '#';

    /**
    \brief The keyword for including other source files
    */
    const NOU::NOU_DAT_ALG::String8 PREPROCESSOR_INCLUDE    = "include";

    /**
    \brief The keyword for defining macros
    */
    const NOU::NOU_DAT_ALG::String8 PREPROCESSOR_DEFINE     = "define";

    /**
    \brief The keyword for preprocessor if statements (if not defined do:)
    */
    const NOU::NOU_DAT_ALG::String8 PREPROCESSOR_IFNDEF     = "ifndef";

    /**
    \brief The keyword for preprocessor else statements after a ifndef
    */
    const NOU::NOU_DAT_ALG::String8 PREPROCESSOR_ELSE       = "else";

    /**
    \brief The keyword for preprocessor end of a if/else statement
    */
    const NOU::NOU_DAT_ALG::String8 PREPROCESSOR_ENDIF      = "endif";


    /**
    \brief The keyword for the indiviudal tokens that get processed
    */
    const NOU::char8 TOKEN_SEPERATOR[2] = {';', '{'};

    
    /**
    \brief Enum that contains all possible states of the internal statemachine
           DEFAULT = Statemachine waits for specific keywords
           PRE_PROCESSOR_DIRECTIVE = Statemachine found a '#' and waits for following keywords
           DEFINE = Statemachine enters the Define State where makros get defined
           INCLUDE = Statemachine enters the include State where it searches for Files to include
           IFNDEF = Statemachine enters the if/else State where it searches for specific if/else/endif keywords
    */
    enum class State
	{
		DEFAULT,
        PRE_PROCESSOR_DIRECTIVE,
        DEFINE,
        INCLUDE,
        IFNDEF
	};

    /**
    \brief The current State of the statemachine
    */
    State m_currentState;

    /**
    \brief the current Token where preprocessor commands are executed
    */
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

        /**
        \brief A class that contains an iterator for iterating trough specific tokens
        */
        class CodeIterator
        {
            private:

                /**
                \brief the whole source code where the iterator iterates trough
                */
                const NOU::NOU_DAT_ALG::String8 &m_code;

                /**
                \brief a pointer to the current position in the String#
                */
                NOU::uint64 m_pos;

                /**
                \brief the current token that gets returned
                */
                NOU::NOU_DAT_ALG::String8 m_currToken;

            public:

                /**
                \brief The constructor for this class
                \param code a string containing the whole sourcecode
                */
                CodeIterator(const NOU::NOU_DAT_ALG::String8 &code);
                
                /**
                \brief sets the Iterator to the initial state
                */
                void reset();

                /**
                \brief checks if there is another token left after the current token
                \return true if ther is a nother token left, false if not
                */
                NOU::boolean hasNext();

                /**
                \brief steps the iterator and returns the next token after the step
                \brief returns the next token
                */
                const NOU::NOU_DAT_ALG::String8 &next();

                /**
                \brief returns the token at the current position without stepping
                \return the current token
                */
                const NOU::NOU_DAT_ALG::String8 &getCurrToken();
        };
    };
}