%option noyywrap nounistd never-interactive outfile="Tokenizer.cpp" yylineno

%{
    #include "nostraengine/material_system/Tokenizer.hpp"
    #define NOT_TYPE NOT::Tokenizer::Types
    #define NOT_TOKEN NOT::Tokenizer::Token
    #define NOT_CRT_TOK2(TYPE,VALUE) NOT_TOKEN(TYPE,VALUE,yytext,yylineno)
    #define NOT_CRT_TOK1(TYPE) NOT_CRT_TOK2(TYPE,"")

    NOT_TOKEN tmp(NOT_TYPE::EOC, "");
%} 

LETTER ([a-ZA-Z])
WORD (LETTER+)
NUMBER ([0-9])
INTEGER ([NUMBER+])

%%
/* Keywords */
"in"    { }
"out"   { }
"struct"{ }
"shared"{ }
"const" { }
"if"    { }
"else"  { }
"while" { }
"for"   { }
"extern"{ }

/* Native types */
"int"   { }
"float" { }
"bool"  { }
"vec"[2-4]  { }
"mat"[2-4]  { }

/* Arithmetic */
"+" { }
"-" { }
"*" { }
"/" { }
"%" { }

/* Literals */
[0-9]+  { } /* Integer */
[0-0]+(("."[0-9]*["f"]?) | "f") { } /* Float */
"true" | "false"    { } /* boolean */


/* Misc */
"{" { } /* Block begin */
"}" { } /* Block end */
"(" { } /* Paramblock begin */
")" { } /* Paramblock end */
("["[" "]*([0-9]+)*[" "]"]") {  } /*Array brackets with optional number inside*/



[a-zA-Z]([a-zA-Z]* | [0-9]* | "_")* { } /* Identifier */
.      { tmp = NOT_CRT_TOK1(NOT_TYPE::UNRECOGNIZED); return 1; }
<<EOF>> { tmp = NOT_CRT_TOK1(NOT_TYPE::EOC); return 0; }
%%


// THIS IS THE START METHOD OF THE TOKENIZER
void NOT::Tokenizer::start(const NOU::NOU_DAT_ALG::Vector<NOU::NOU_DAT_ALG::String8>& args)
{
    // NOU::sizeType argc = args.size();


    YY_BUFFER_STATE bp;
    bp = yy_scan_bytes(m_code.rawStr(), m_code.size());
    yy_switch_to_buffer(bp);


    while(yylex())
    {
        m_token.emplaceBack(tmp);
    }
    m_token.emplaceBack(tmp);

    yy_delete_buffer(bp);
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

    Tokenizer::Tokenizer(NOU::NOU_FILE_MNGT::File& inputFile) :
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
        Tokenizer::Tokenizer(const NOU::NOU_DAT_ALG::String8& inputCode) :
        m_pos(0),
        m_code(inputCode){ }
}