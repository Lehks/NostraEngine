#include "nostraengine/material_system/Tokenizer.hpp"

namespace NOT
{
    //
    // TOKENIZER CLASS
    //

    Tokenizer::Tokenizer(NOU::NOU_FILE_MNGT::File& inputFile): 
    m_pos(0)
    {
        if(inputFile.isCurrentlyOpen())
        {
            inputFile.close();
        }

        inputFile.open();
        inputFile.read(m_code);
        inputFile.close();
    }

    Tokenizer::Tokenizer(const NOU::NOU_DAT_ALG::String8& code) : 
    m_code(code),
    m_pos(0) { }

    const NOU::NOU_DAT_ALG::Vector<Tokenizer::Token>& Tokenizer::getToken() const
    {
        return m_token;
    }

    void Tokenizer::reset()
    {
        m_pos = 0;
    }

    const Tokenizer::Token* const Tokenizer::nextToken()
    {
        if(m_pos <= m_token.size())
        {
            return &m_token[m_pos];
        }
        return nullptr;
    }

    const NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8>& Tokenizer::getMessages() const
    {
        return m_messages;
    }

    //
    // Token
    //

    Tokenizer::Token::Token(Types type, NOU::NOU_DAT_ALG::String8 value, NOU::NOU_DAT_ALG::String8 raw):
    m_value(value),
    m_type(type),
    m_raw(raw) { }

}