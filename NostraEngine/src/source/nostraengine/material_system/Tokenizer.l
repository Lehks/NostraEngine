%option noyywrap nounistd never-interactive outfile="Tokenizer.cpp" yylineno

%{
    #include "nostraengine/material_system/Tokenizer.hpp"
    #define NOT_TYPE NOT::Tokenizer::Types
    #define NOT_TOKEN NOT::Tokenizer::Token

    NOT_TOKEN tmp(NOT_TYPE::EOC, "");
%} 

%%
"\n"    { tmp = NOT_TOKEN(NOT_TYPE::OPERATOR, yytext, yytext, yylineno); return 1;};
<<EOF>> { tmp = NOT_TOKEN(NOT_TYPE::EOC, yytext); return 0; }
%%


// THIS IS THE START METHOD OF THE TOKENIZER
void NOT::Tokenizer::start(const NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8>& args)
{
    while(yylex())
    {
        m_token.emplaceBack(tmp);
    }
    m_token.emplaceBack(tmp);
}










namespace NOT
{
    // 
    // Token
    // 
    constexpr NOU::sizeType Tokenizer::Token::NO_LINE_DISPLAY;

    Tokenizer::Token::Token(Types type, NOU::NOU_DAT_ALG::String8 raw, NOU::NOU_DAT_ALG::String8 value, NOU::sizeType currLine) :
    m_type(type),
    m_value(value),
    m_raw(raw),
    m_currLine(currLine) { }

    // 
    // Tokenizer
    // 
    const NOU::NOU_DAT_ALG::Vector<Tokenizer::Token>& Tokenizer::getToken() const
    {
        return m_token;
    }

    const Tokenizer::Token* const Tokenizer::nextToken()
    {
        if(m_pos < m_token.size())
        {
            return &m_token[m_pos];
            m_pos++;
        }
        return nullptr;
    }

    void Tokenizer::reset()
    {
        m_pos = 0;
    }

    const NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8>& Tokenizer::getMessages() const
    {
        return m_messages;
    }
}