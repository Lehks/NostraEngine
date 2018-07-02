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
    class PreProcessor
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

        class Message
        {
        private:
            const NOU::NOU_DAT_ALG::String8 m_message;
            const NOU::uint64 m_line;
        protected:
            const NOU::NOU_DAT_ALG::String8 m_constructedMessage;
        public:
            constexpr static NOU::uint64 NO_LINE_DISPLAY = -1; // If m_line is set to this the line won't be shown in getMessage
        public:
            NOU_FUNC Message(const NOU::NOU_DAT_ALG::String8 &message, const NOU::uint64 line = NO_LINE_DISPLAY);

            NOU_FUNC const NOU::NOU_DAT_ALG::String8& getMessage() const;
            NOU_FUNC NOU::uint64 getLine() const;
            NOU_FUNC virtual const NOU::NOU_DAT_ALG::String8& getConstructedMessage() const;     

            NOU_FUNC NOU::boolean operator==(const Message &other) const;

            virtual ~Message() = default;
        };

        class Warning final : public Message
        {
        private:
            const WarningCode m_id;
        public:
            // -1 meaning the warning has no specific line
            NOU_FUNC Warning(WarningCode id,const NOU::NOU_DAT_ALG::String8 &message = "", NOU::uint64 line = Message::NO_LINE_DISPLAY);
            NOU_FUNC WarningCode getID() const;
            NOU_FUNC const NOU::NOU_DAT_ALG::String8& getWarningMessage() const;
            NOU_FUNC const NOU::NOU_DAT_ALG::String8& getConstructedMessage() const override;

            NOU_FUNC NOU::boolean operator== (const Message &other) const;
        };

        class Error final : public Message
        {
        private:
            const ErrorCode   m_id;
        public:
            NOU_FUNC Error(ErrorCode id,const NOU::NOU_DAT_ALG::String8 &message = "", NOU::uint64 line = Message::NO_LINE_DISPLAY);
            NOU_FUNC ErrorCode getID() const;
            NOU_FUNC const NOU::NOU_DAT_ALG::String8& getErrorMessage() const;
            NOU_FUNC const NOU::NOU_DAT_ALG::String8& getConstructedMessage() const override;

            NOU_FUNC NOU::boolean operator==(const Error &other) const;
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
            GROUP,
            ERROR,
            WARNING
        };

        static const NOU::NOU_DAT_ALG::StringView8 PRE_PROCESSOR_DIRECTIVE_PREFIX;

        static const NOU::NOU_DAT_ALG::StringView8 PRE_PROCESSOR_INCLUDE;

        static const NOU::NOU_DAT_ALG::StringView8 PRE_PROCESSOR_DEFINE;

        static const NOU::NOU_DAT_ALG::StringView8 PRE_PROCESSOR_ERROR;

        static const NOU::NOU_DAT_ALG::StringView8 PRE_PROCESSOR_WARNING;

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
            NOU_FUNC Iterator(const NOU::NOU_DAT_ALG::String8 &s, const NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8> &tokenSeperators, NOU::sizeType pos = 0);

            NOU_FUNC NOU::boolean hasNext() const;
            NOU_FUNC NOU::NOU_DAT_ALG::String8 &next();
            NOU_FUNC const NOU::NOU_DAT_ALG::String8 &getCurrentToken() const;
            NOU_FUNC NOU::NOU_DAT_ALG::String8 &getCurrentToken();
            NOU_FUNC NOU::sizeType getCurrentPosition() const;

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
        NOU_FUNC PreProcessor(NOU::NOU_FILE_MNGT::File &f, const NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8> &args = NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8>());

        /**
        \brief Starts the preprocessor on the given Files.7
        */
        NOU_FUNC void start();

        /**
        \brief A Hashmap that maps ErrorCodes to Human Readable ErrorMessages
        */
        NOU_FUNC static const NOU::NOU_DAT_ALG::HashMap<ErrorCode, NOU::NOU_DAT_ALG::String8> ERRORS;

        /**
        \brief A Hashmap that maps WarningCodes to Human Readable WarningMessages
        */
        NOU_FUNC static const NOU::NOU_DAT_ALG::HashMap<WarningCode, NOU::NOU_DAT_ALG::String8> WARNINGS;

    public:
        /**
        \brief initializes StaticMembers if they are not allready initialized
        \details Mostly used for adding IDs and Messages to the error/warning system
        */
        NOU_FUNC static void initializeStaticMembers();

        NOU_FUNC void convertLineendings();

        NOU_FUNC void directive(Iterator &it);

        NOU_FUNC void includeDirective(Iterator &it);

        NOU_FUNC void defineDirective(Iterator &it);

        NOU_FUNC void errorDirective(Iterator &it);

        NOU_FUNC void warningDirective(Iterator &it);

        NOU_FUNC void defaultDirective(Iterator &it);

        // Helper functions

        NOU_FUNC NOU::boolean addDefineVar(const NOU::NOU_DAT_ALG::String8 &name, const NOU::NOU_DAT_ALG::String8 &value);

        // Error Handling

        NOU_FUNC void emitMessage(const Message &m);

        NOU_FUNC void emitError(const Error &e);

        NOU_FUNC void emitWarning(const Warning &w);

        NOU_FUNC void errorHandler(const Error &e, Iterator &it);

    public:

        NOU_FUNC const NOU::NOU_DAT_ALG::Vector<Warning>& getThrownWarnings();

        NOU_FUNC const NOU::NOU_DAT_ALG::Vector<Error>& getThrownErrors();

        NOU_FUNC const NOU::NOU_DAT_ALG::Vector<Message>& getThrownMessages();

        NOU_FUNC const NOU::NOU_DAT_ALG::Vector<const Message*> getAllThrownMessages();
        
    };
    constexpr  NOU::uint64 PreProcessor::Message::NO_LINE_DISPLAY;
}

#endif