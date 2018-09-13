%option yylineno
%option nounistd
%option noyywrap
%option never-interactive

%{
    #include "MaterialParser.h" 
    #include <stdio.h>
    #include <stdlib.h>
%}

%%
"in"     { return inkw; } /* Keywords */
"out"    { return outkw; }
"struct" { return structkw; }
"shared" { return sharedkw; }
"const"  { return constkw; }
"if"     { return ifkw; }
"else"   { return elsekw; }
"while"  { return whilekw; }
"for"    { return forkw; }
"extern" { return extkw; }


"int"       { return ntype; } /* Native types */
"float"     { return ntype; }
"bool"      { return ntype; }
"vec"[2-4]  { return ntype; }
"mat"[2-4]  { return ntype; }


"+" { return op; } /* Arithmetic */
"-" { return op; }
"*" { return op; }
"/" { return op; }
"%" { return op; }

"+=" { return opassign; }
"-=" { return opassign; }
"*=" { return opassign; }
"/=" { return opassign; }
"%=" { return opassign; }

"&&" { return op; } /* AND */
"!"  { return op; } /* NOT */
"||" { return op; } /* OR  */
"^"  { return op; } /* XOR */
"==" { return op; } /* EQUALS  */
"<"  { return op; } /* LESS    */
">"  { return op; } /* GREATER */
"<=" { return op; } /* LEQ  */
">=" { return op; } /* GREQ */
"!=" { return op; } /* NEQ  */

"&=" { return opassign; }
"|=" { return opassign; }
"^=" { return opassign; }

"="  { return assign; }


-?[0-9]+                       { return intl; } /* Literals */ /* Integer */
[0-0]+(("."[0-9]*["f"]?)|"f") { return floatl; } /* Float */
("true"|"false")              { return booll; } /* boolean */


"{"             { return blockb; } /* Misc */
"}"             { return blocke; } 
"("             { return paramb; } 
")"             { return parame; } 
("["[0-9]*"]")  { return array; }  /* HOTFIX CURRENTLY, DON'T FORGET TO CHANGE BACK SO " " CAN BE BETWEEN NUMBERS AND BRACKETS*/ /*Array brackets with optional number inside*/

("_")*[a-zA-Z]([a-zA-Z]|[0-9]|"_")* { return identifier; } /* Identifier */

["//"].*\n          { }     /* Skip single line comment */
^"/*"[^*]*|[*]*"*/" { }     /* Skip multiline comments */
";"     { return semicolon; }
" "+    { }
.       { return unrecognized; }
%%

void setupLex(char* filename){

    FILE *f = fopen(filename, "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);  //same as rewind(f)

    char *string = malloc(fsize + 1);
    fread(string, fsize, 1, f);
    fclose(f);

    string[fsize] = 0;

    YY_BUFFER_STATE bp;
    bp = yy_scan_bytes(string, fsize - 1);
    yy_switch_to_buffer(bp);

}

/*

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

*/