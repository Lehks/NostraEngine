%defines


%{
#include "MaterialParser.h"
#include <stdio.h>
#include <stdlib.h>



int yylex(void);
int yyerror(char*);
extern int yylineno;
#define PRINT(ARG) printf(ARG);
#define PRINTLN(ARG) printf("Reduced: %s\n", ARG);
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
%token voidt
%token seperator




%%

S : FUNC_DEF { printf("%s\n", "ACCEPTED"); }
  ;

ARRITH_EXPR : intl {  }
         | floatl {  }
         | ARRITH_EXPR op ARRITH_EXPR { PRINTLN("ARR_EXPR"); }
         ;

BLOCK : blockb blocke { PRINTLN("BLOCK"); }
      ;

VAR_DEC : ntype identifier semicolon{ PRINTLN("VAR_DEC"); }
        ;

PARAM_DEF : ntype identifier { PRINTLN("PARAM_DEF"); }
          ;

PARAM_LIST : PARAM_LIST seperator PARAM_DEF { PRINTLN("PARAM_LIST1"); }
           | PARAM_DEF { PRINTLN("PARAM_LIST2"); }

PARAM_BLOCK : paramb PARAM_LIST parame { PRINTLN("PARAM_BLOCK"); }
            ;

FUNC_DEF : ntype identifier PARAM_BLOCK BLOCK { PRINTLN("FUNC_DEF"); }
         ;

STATEMENT : VAR_DEC { PRINTLN("STATEMENT"); }

STMNT_LIST : STMNT_LIST STATEMENT

 

%%




int yyerror(char* msg){
    fprintf(stderr, "%s\n", msg);
    return 1;
}
