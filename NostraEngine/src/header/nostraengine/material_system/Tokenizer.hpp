#ifndef MATERIAL_SYSTEM_TOKENIZER_HPP
#define MATERIAL_SYSTEM_TOKENIZER_HPP

#include "nostraengine/core/StdIncludes.hpp"

namespace NOT
{
    class NOE_FUNC Tokenizer
    {
    public:

        class Types
        {
        private:
            Types() = default;

        public:
            enum Types_ : NOU::uint8
            {
                EOC, // End of Code
                IDENTIFIER
            };
            private:
        };

        struct Token
        {
            Types::Types_ m_type;
            NOU::NOU_DAT_ALG::String8 m_value;
            NOU::NOU_DAT_ALG::String8 m_raw;

            Token(Types type, NOU::NOU_DAT_ALG::String8 value = "", NOU::NOU_DAT_ALG::String8 raw = "");
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