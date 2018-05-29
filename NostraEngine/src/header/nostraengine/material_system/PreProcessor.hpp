#ifndef NOE_MATERIAL_SYSTEM_PREPROCESSOR_HPP
#define NOE_MATERIAL_SYSTEM_PREPROCESSOR_HPP

#include "nostraengine/core/StdIncludes.hpp"
#include "nostrautils/NostraUtils.hpp"

/**
\file material_system/ShaderCompiler.hpp

\author  Leslie Marxen
\version 0.0.1
\since   0.0.1

\brief  A file that provides the preprocessor of the material language.
*/


namespace NOT
{
    /**
    \brief This class handles every preprocess steps before the actual compiling process.
    */
    class NOU_CLASS PreProcessor
    {
    public:
        /**
        \brief An integer describing some error case.
        */
        using ErrorCode = NOU::uint32;

        /**
        \brief An integer describing some warning case.
        */
        using WarningCode = NOU::uint32;

    private:
        /**
        \brief an enum describing all the states that the statemachine can be in.
        \details
            DEFAULT = The default state when no directive has been found.
            PRE_PROCESSOR_DIRECTIVE = The state as soon as a \p # has been found.
            DEFINE = The state as soon as a \p define directive has been found.
            UNDEFINE = The state as soon as a \p undefine directive has been found.
            INCLUDE = The state as soon as a \p include directive has been found.
            IFDEF = The state as soon as a \p ifdef directive has been found.
            IFNDEF = The state as soon as a \p ifndef directive has been found.
        */
        enum class States
        {
            DEFAULT,
            PRE_PROCESSOR_DIRECTIVE,
            DEFINE,
            UNDEFINE,
            INCLUDE,
            IFDEF,
            IFNDEF,
            GROUP
        };

        /**
        \brief The current state of the machine.
        */
        States m_currState;

        /**
        \brief A Hashmap that maps ErrorCodes to Human Readable ErrorMessages
        */
        static NOU::NOU_DAT_ALG::HashMap<ErrorCode, NOU::NOU_DAT_ALG::String8> s_errors;

        /**
        \brief A Hashmap that maps WarningCodes to Human Readable WarningMessages
        */
        static NOU::NOU_DAT_ALG::HashMap<ErrorCode, NOU::NOU_DAT_ALG::String8> s_warnings;

    public:
        /**
        \brief The constructor for this class
        */
        PreProcessor(const NOU::NOU_FILE_MNGT::File &f, const NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8> &args = NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8>());

        /**
        \brief Starts the preprocessor on the given Files.7
        */
        void start();

    private:

        void initializeStaticMembers();
    };
}
#endif