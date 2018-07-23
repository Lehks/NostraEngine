#ifndef MATERIAL_SYSTEM_TOKENIZER_HPP
#define MATERIAL_SYSTEM_TOKENIZER_HPP

#include "nostraengine/core/StdIncludes.hpp"

namespace NOT
{
    class NOE_FUNC Tokenizer
    {
    public:

        enum class Types{
            EOC, // End of Code -> if the m_Code input is done flex will return this
            UNRECOGNIZED,
            SEMICOLON,
            IN,
            OUT,
            STRUCT,
            SHARED,
            CONST,
            IF,
            ELSE,
            WHILE,
            FOR,
            EXT,
            NTYPE,
            OPERATOR,
            ASSIGN,
            OPASSIGN,
            INTL,
            FLOATL,
            BOOLL,
            BLOCKB,
            BLOCKE,
            PARAMB,
            PARAME,
            ARRAY,
            IDENTIFIER
        };

        struct Token
        {
            Types m_type;
            NOU::NOU_DAT_ALG::String8 m_value;
            NOU::NOU_DAT_ALG::String8 m_raw;
            NOU::sizeType m_currLine;
            constexpr static NOU::sizeType NO_LINE_DISPLAY = -1;

            Token(Types type, NOU::NOU_DAT_ALG::String8 raw, NOU::NOU_DAT_ALG::String8 value = "", NOU::sizeType currLine = NO_LINE_DISPLAY);
        };

    private:

        NOU::NOU_DAT_ALG::Vector<Token> m_token;
        NOU::sizeType m_pos;
        NOU::NOU_DAT_ALG::String8 m_code;
        NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8> m_messages;

    public:

        Tokenizer(NOU::NOU_FILE_MNGT::File& inputFile);
        Tokenizer(const NOU::NOU_DAT_ALG::String8& inputCode);

        void start(const NOU ::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8>& args = NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8>());
        const NOU::NOU_DAT_ALG::Vector<Token>& getToken() const;
        const Token* const nextToken();
        void reset();
        const NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8>& getMessages() const;

    };
}

#endif