#ifndef MATERIAL_SYSTEM_TOKENIZER_HPP
#define MATERIAL_SYSTEM_TOKENIZER_HPP

#include "nostraengine/core/StdIncludes.hpp"

namespace NOT
{
    class NOE_FUNC Tokenizer
    {
    public:

        enum class Types{
            EOC = 130, // End of Code -> if the m_Code input is done flex will return this
            UNRECOGNIZED = 131,
            SEMICOLON = 132,
            IN = 133,
            OUT = 134,
            STRUCT = 135,
            SHARED = 136,
            CONST = 137,
            IF = 138,
            ELSE = 139,
            WHILE = 140,
            FOR = 141,
            EXT = 142,
            NTYPE = 143,
            OPERATOR = 144,
            ASSIGN = 145,
            OPASSIGN = 146,
            INTL = 147,
            FLOATL = 148,
            BOOLL = 149,
            BLOCKB = 150,
            BLOCKE = 151,
            PARAMB = 152,
            PARAME = 153,
            ARRAY = 154,
            IDENTIFIER = 155
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