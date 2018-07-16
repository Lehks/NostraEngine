%option noyywrap nounistd c++

%%
    #include "nostraengine/material_system/Tokenizer.hpp"
    NOU::DAT_ALG::String8 rawValue;
    NOU::DAT_ALF::String8 value;
%% 

%{
"\n" {return NOT::Tokenizer::Type::EOC;}
%}

NOT::Tokenizer::start(const NOU::NOU_DAT_ALG::String8& args)
{
    Token tmp;
    while((tmp = yylex())
}