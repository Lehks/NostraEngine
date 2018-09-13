%defines


%{
#include "MaterialParser.h"
#include <stdio.h>
#include <stdlib.h>



int yylex(void);
int yyerror(char*);
extern int yylineno;
%}

%union {
int i;
float f;
char* s;
char c;
double d;
long l;
int b;
}


%token unrecognized
%token semicolon
%token inkw
%token outkw
%token structkw
%token sharedkw
%token constkw
%token ifkw
%token elsekw
%token whilekw
%token forkw
%token extkw
%token<s> ntype
%token<s> op
%token assign
%token<s> opassign
%token<i> intl
%token<f> floatl
%token<b> booll
%token blockb
%token blocke
%token paramb
%token parame
%token<i> array
%token<s> identifier




%%


ARR_EXPR : intl op intl { printf("ARR_EXPR"); }
         | floatl op floatl { printf("ARR_EXPR"); }
         | intl op floatl { printf("ARR_EXPR"); }
         | floatl op intl { printf("ARR_EXPR"); }
         ; 


%%

int yyerror(char* msg){
    fprintf(stderr, msg);
    return 1;
}
