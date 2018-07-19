%option noyywrap nounistd never-interactive outfile="Tokenizer.cpp" yylineno

%{
    #include "nostraengine/material_system/Tokenizer.hpp"
    #define NOT_TYPE NOT::Tokenizer::Types
    #define NOT_TOKEN NOT::Tokenizer::Token
    #define NOT_CRT_TOK2(TYPE,VALUE) NOT_TOKEN(TYPE,VALUE,yytext,yylineno)
    #define NOT_CRT_TOK1(TYPE) NOT_CRT_TOK2(TYPE,"")

    NOU::int16 setToken(NOT_TYPE type, NOU::NOU_DAT_ALG::String8 value = "");

    NOT_TOKEN currToken(NOT_TYPE::EOC, "");
%}

%%
"in"     { return setToken(NOT_TYPE::IN); } /* Keywords */
"out"    { return setToken(NOT_TYPE::OUT); }
"struct" { return setToken(NOT_TYPE::STRUCT); }
"shared" { return setToken(NOT_TYPE::SHARED); }
"const"  { return setToken(NOT_TYPE::CONST); }
"if"     { return setToken(NOT_TYPE::IF); }
"else"   { return setToken(NOT_TYPE::ELSE); }
"while"  { return setToken(NOT_TYPE::WHILE); }
"for"    { return setToken(NOT_TYPE::WHILE); }
"extern" { return setToken(NOT_TYPE::EXT); }


"int"       { return setToken(NOT_TYPE::NTYPE, yytext); } /* Native types */
"float"     { return setToken(NOT_TYPE::NTYPE, yytext); }
"bool"      { return setToken(NOT_TYPE::NTYPE, yytext); }
"vec"[2-4]  { return setToken(NOT_TYPE::NTYPE, yytext); }
"mat"[2-4]  { return setToken(NOT_TYPE::NTYPE, yytext); }


"+" { return setToken(NOT_TYPE::OPERATOR, yytext); } /* Arithmetic */
"-" { return setToken(NOT_TYPE::OPERATOR, yytext); }
"*" { return setToken(NOT_TYPE::OPERATOR, yytext); }
"/" { return setToken(NOT_TYPE::OPERATOR, yytext); }
"%" { return setToken(NOT_TYPE::OPERATOR, yytext); }

"+=" { return setToken(NOT_TYPE::OPASSIGN, yytext); }
"-=" { return setToken(NOT_TYPE::OPASSIGN, yytext); }
"*=" { return setToken(NOT_TYPE::OPASSIGN, yytext); }
"/=" { return setToken(NOT_TYPE::OPASSIGN, yytext); }
"%=" { return setToken(NOT_TYPE::OPASSIGN, yytext); }

"&&" { return setToken(NOT_TYPE::OPERATOR, yytext); } /* AND */
"!"  { return setToken(NOT_TYPE::OPERATOR, yytext); } /* NOT */
"||" { return setToken(NOT_TYPE::OPERATOR, yytext); } /* OR */
"^"  { return setToken(NOT_TYPE::OPERATOR, yytext); } /* XOR */
"==" { return setToken(NOT_TYPE::OPERATOR, yytext); } /* EQUALS */
"<"  { return setToken(NOT_TYPE::OPERATOR, yytext); } /* LESS */
">"  { return setToken(NOT_TYPE::OPERATOR, yytext); } /* GREATER */
"<=" { return setToken(NOT_TYPE::OPERATOR, yytext); } /* LEQ */
">=" { return setToken(NOT_TYPE::OPERATOR, yytext); } /* GREQ */
"!=" { return setToken(NOT_TYPE::OPERATOR, yytext); } /* NEQ */

"&=" { return setToken(NOT_TYPE::OPASSIGN, yytext); }
"|=" { return setToken(NOT_TYPE::OPASSIGN, yytext); }
"^=" { return setToken(NOT_TYPE::OPASSIGN, yytext); }

"="  { return setToken(NOT_TYPE::ASSIGN, yytext); }


[0-9]+                        { return setToken(NOT_TYPE::INTL, yytext); } /* Literals */ /* Integer */
[0-0]+(("."[0-9]*["f"]?)|"f") { return setToken(NOT_TYPE::FLOATL, yytext); } /* Float */
("true"|"false")              { return setToken(NOT_TYPE::BOOLL, yytext); } /* boolean */


"{"             { return setToken(NOT_TYPE::BLOCKB); } /* Misc */
"}"             { return setToken(NOT_TYPE::BLOCKE); } 
"("             { return setToken(NOT_TYPE::PARAMB); } 
")"             { return setToken(NOT_TYPE::PARAME); } 
("["[0-9]*"]")  { return setToken(NOT_TYPE::ARRAY, yytext); }  /* HOTFIX CURRENTLY, DON'T FORGET TO CHANGE BACK SO " " CAN BE BETWEEN NUMBERS AND BRACKETS*/ /*Array brackets with optional number inside*/

("_")*[a-zA-Z]([a-zA-Z]|[0-9]|"_")* { return setToken(NOT_TYPE::IDENTIFIER, yytext); } /* Identifier */

";"     {return setToken(NOT_TYPE::SEMICOLON);}
" "+    { }
.       { return setToken(NOT_TYPE::UNRECOGNIZED, yytext); }
<<EOF>> { return setToken(NOT_TYPE::EOC); }
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
        m_token.emplaceBack(currToken);
    }
    m_token.emplaceBack(currToken);

    yy_delete_buffer(bp);
}


NOU::int16 setToken(NOT_TYPE type, NOU::NOU_DAT_ALG::String8 value)
{
    currToken = NOT_CRT_TOK2(type, value);
    NOU::NOU_DAT_ALG::String8 tmp;

    switch(type)
    {
        case(NOT_TYPE::EOC):
            return 0;    
        break;
        case(NOT_TYPE::ARRAY):
            currToken.m_value.preserve(1, currToken.m_value.size()-2);
        default:
            return 1;
        break;
    }

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