%option yylineno
%option nounistd
%option noyywrap
%option never-interactive

%{
    #include "MaterialParser.h" 
    #include <stdio.h>
    #include <stdlib.h>
    #define CONV_STR(ARG) (#ARG)
    #define RET(ARG) printf("Matched: %s\n",CONV_STR(ARG));return ARG
%}

%%

"in"     { RET(inkw); } /* Keywords */
"out"    { RET(outkw); }
"shared" { RET(sharedkw); }
"const"  { RET(constkw); }
"if"     { RET(ifkw); }
"while"  { RET(whilekw); }
"for"    { RET(forkw); }
"extern" { RET(extkw); }

"void" { RET(voidt); }
"int" { RET(ntype); }


"+" { RET(op); } /* Arithmetic */

"="  { RET(assign); }



-?[0-9]+                       { RET(intl); } /* Literals */ /* Integer */

"{"             { RET(blockb); }
"}"             { RET(blocke); }
"("             { RET(paramb); } 
")"             { RET(parame); } 

([a-z]|[A-Z]|"_")(([a-z]|[A-Z]|"_"|[0-9])+)? { RET(identifier); }

["//"].*\n          { }     /* Skip single line comment */
^"/*"[^*]*|[*]*"*/" { }     /* Skip multiline comments */
";"     { RET(semicolon); }
","     { RET(seperator); }
" "+    {  }
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