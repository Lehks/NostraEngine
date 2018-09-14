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

S : STATEMENT { printf("%s\n", "ACCEPTED"); }
  ;


 /* FUNCTIONS */


PARAM_DEF : ntype identifier { PRINTLN("PARAM_DEF"); }
          ;

PARAM_LIST : PARAM_LIST seperator PARAM_DEF { PRINTLN("PARAM_LIST1"); }
           | PARAM_DEF { PRINTLN("PARAM_LIST2"); }

PARAM_BLOCK : paramb PARAM_LIST parame { PRINTLN("PARAM_BLOCK"); }
            ;

FUNC_DEF : ntype identifier PARAM_BLOCK BLOCK { PRINTLN("FUNC_DEF"); }
         ;

FUNC_CALL : identifier EXPR_BLOCK {PRINTLN("FUNC_CALL"); }
          ;


/* Variables */


VAR_DEC : ntype identifier{ PRINTLN("VAR_DEC"); }
        ;

VAR_INIT : VAR_DEC assign EXPRESSION { PRINTLN("VAR_INIT"); }
         ;

/* STATEMENTS */


STATEMENT : VAR_DEC semicolon { PRINTLN("STATEMENT1"); }
          | VAR_INIT semicolon { PRINTLN("STATEMENT2"); }
          | FUNC_CALL semicolon { PRINTLN("STATEMENT3"); }
          ;

STMNT_LIST : STMNT_LIST STATEMENT { PRINTLN("STMNT_LIST")}
           ;



/* CODE BLOCKS */


BLOCK : blockb blocke { PRINTLN("BLOCK"); }
      ;

/* EXPRESSIONS */
EXPRESSION : ARRITH_EXPR { PRINTLN("EXPRESSION1"); }
           | identifier { PRINTLN("EXPRESSION2"); }
           | FUNC_CALL { PRINTLN("EXPRESSION 3");}
           ;

EXPR_LIST : EXPR_LIST seperator EXPRESSION { PRINTLN("EXPR_LIST1"); }
          | EXPRESSION { PRINTLN("EXPR_LIST2"); }
          ;

EXPR_BLOCK : paramb EXPR_LIST parame { PRINTLN ("EXPR_BLOCK"); }
           ;

ARRITH_EXPR : intl {  }
         | floatl {  }
         | identifier {  }
         | FUNC_CALL { }
         | ARRITH_EXPR op ARRITH_EXPR { PRINTLN("ARR_EXPR"); }
         ;

%%




int yyerror(char* msg){
    fprintf(stderr, "%s\n", msg);
    return 1;
}
