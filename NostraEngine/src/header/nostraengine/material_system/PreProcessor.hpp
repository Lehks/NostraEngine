#ifndef NOE_MATERIAL_SYSTEM_PREPROCESSOR_HPP
#define NOE_MATERIAL_SYSTEM_PREPROCESSOR_HPP

#include "nostraengine/core/StdIncludes.hpp"

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

        class NOU_CLASS Message
        {
        private:
            const NOU::NOU_DAT_ALG::String8 m_message;
            const NOU::uint64 m_line;
        public:
            constexpr static NOU::uint64 NO_LINE_DISPLAY = -1; // If m_line is set to this the line won't be shown in getMessage
        public:
            Message(const NOU::NOU_DAT_ALG::String8 &message, const NOU::uint64 line = NO_LINE_DISPLAY);

            const NOU::NOU_DAT_ALG::String8& getMessage() const;
            NOU::uint64 getLine() const;

            virtual ~Message() = default;
        };

        class NOU_CLASS Warning final : public Message
        {
        private:
            const WarningCode m_id;
        public:
            // -1 meaning the warning has no specific line
            Warning(WarningCode id, NOU::NOU_DAT_ALG::String8 message = "", NOU::uint64 line = Message::NO_LINE_DISPLAY);
            WarningCode getID() const;
            const NOU::NOU_DAT_ALG::String8& getWarningMessage() const;
        };

        class NOU_CLASS Error final : public Message
        {
        private:
            const ErrorCode   m_id;
        public:
            Error(ErrorCode id, NOU::NOU_DAT_ALG::String8 message = "", NOU::uint64 line = Message::NO_LINE_DISPLAY);
            ErrorCode getID() const;
            const NOU::NOU_DAT_ALG::String8& getErrorMessage() const;
        };

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
            DEFINE,
            UNDEFINE,
            INCLUDE,
            IFDEF,
            IFNDEF,
            GROUP
        };

        static const NOU::NOU_DAT_ALG::StringView8 PRE_PROCESSOR_DIRECTIVE_PREFIX;

        static const NOU::NOU_DAT_ALG::StringView8 PRE_PROCESSOR_INCLUDE;

        static const NOU::NOU_DAT_ALG::StringView8 PRE_PROCESSOR_DEFINE;

        static const NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8> s_tokenSeperators;

        /**
        \brief Class used for iterating through the tokens of the sourceCode
        */
        class Iterator
        {  
        private:
            /**
            \brief The string the iterator is currently iterating through.
            */
            const NOU::NOU_DAT_ALG::String8 &m_currString;

            /**
            \brief The current substring containing the found token.
            */
            NOU::NOU_DAT_ALG::String8 m_currToken;

            /**
            \brief A vector containing all of the seperators seperating tokens
            */
            const NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8> &m_tokenSeperators;

            /**
            \brief The current position of the iterator in the String
            */
            NOU::sizeType m_currPos;
        public:
            /**
            \brief The constructor for the Iterator Class
            \param s The strin which will be iterated
            \param tokenSeperators specific Strings seperating the unique tokens
            */
            Iterator(const NOU::NOU_DAT_ALG::String8 &s, const NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8> &tokenSeperators, NOU::sizeType pos = 0);

            NOU::boolean hasNext() const;
            NOU::NOU_DAT_ALG::String8 &next();
            const NOU::NOU_DAT_ALG::String8 &getCurrentToken() const;
            NOU::NOU_DAT_ALG::String8 &getCurrentToken();
            NOU::sizeType getCurrentPosition() const;

        };

        NOU_DEFINE_PAIR(DefineVariable, name, value)

        /**
        \brief The current state of the machine.
        */
        States m_currState;

        /**
        \brief a String containing the whole source code.
        */
        NOU::NOU_DAT_ALG::String8 m_sourceCode;

        NOU::NOU_FILE_MNGT::Path m_sourcePath;

        /**
        \brief a String containing the processed source code.
        */
        NOU::NOU_DAT_ALG::String8 m_targetCode;

        /**
        \brief a Vector containing all defined variables and their corresponding values
        */
        NOU::NOU_DAT_ALG::Vector<DefineVariable<NOU::NOU_DAT_ALG::String8, NOU::NOU_DAT_ALG::String8>> m_defineVars;

        /**
        \brief a Vector containing all thrown messages during the preprocessing process
        */
        NOU::NOU_DAT_ALG::Vector<Message> m_messages;

        /**
        \brief a Vector containing all thrown warnings during the preprocessing process
        */
        NOU::NOU_DAT_ALG::Vector<Warning> m_warnings;
        
        /**
        \brief a Vector containing all thrown errors during the preprocessing process
        */
        NOU::NOU_DAT_ALG::Vector<Error>   m_errors;

    public:
        /**
        \brief The constructor for this class
        */
        PreProcessor(NOU::NOU_FILE_MNGT::File &f, const NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8> &args = NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8>());

        /**
        \brief Starts the preprocessor on the given Files.7
        */
        void start();

        /**
        \brief A Hashmap that maps ErrorCodes to Human Readable ErrorMessages
        */
        static const NOU::NOU_DAT_ALG::HashMap<ErrorCode, NOU::NOU_DAT_ALG::String8> s_errors;

        /**
        \brief A Hashmap that maps WarningCodes to Human Readable WarningMessages
        */
        static const NOU::NOU_DAT_ALG::HashMap<ErrorCode, NOU::NOU_DAT_ALG::String8> s_warnings;

    private:
        /**
        \brief initializes StaticMembers if they are not allready initialized
        \details Mostly used for adding IDs and Messages to the error/warning system
        */
        static void initializeStaticMembers();

        void convertLineendings();

        void directive(Iterator &it);

        void include(Iterator &it);

        void define(Iterator &it);

        void defaultDirective(Iterator &it);

        // Helper functions

        NOU::boolean addDefineVar(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_DAT_ALG::String8 &value);

        void throwMessage(const Message &m);

        void throwError(const Error &e);

        void throwWarning(const Warning &w);
        
    };
    constexpr  NOU::uint64 PreProcessor::Message::NO_LINE_DISPLAY;
}
#endif