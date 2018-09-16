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
%token<s> oph
%token<s> opm
%token<s> opl
%token<s> opc
%token<s> negation
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

S : EXPR_LOW { printf("%s\n", "ACCEPTED"); }
  ;


 /* FUNCTIONS */


PARAM_DEF : ntype identifier { PRINTLN("PARAM_DEF"); }
          ;

PARAM_LIST : PARAM_LIST seperator PARAM_DEF { PRINTLN("PARAM_LIST1"); }
           | PARAM_DEF { PRINTLN("PARAM_LIST2"); }

PARAM_BLOCK : paramb PARAM_LIST parame { PRINTLN("PARAM_BLOCK"); }
            | paramb parame { PRINTLN("PARAM_BLOCK"); }
            ;

FUNC_DEF : ntype identifier PARAM_BLOCK BLOCK { PRINTLN("FUNC_DEF"); }
         ;

FUNC_CALL : identifier EXPR_BLOCK {PRINTLN("FUNC_CALL"); }
          ;


/* Variables */


VAR_DEC : UNMOD_VAR_DEC semicolon { PRINTLN("VAR_DEC1"); }
        | CONST_VAR_DEC semicolon { PRINTLN("VAR_DEC2"); }
        | MOD_VAR_DEC   semicolon { PRINTLN("VAR_DEC3"); }
        ;

CONST_VAR_DEC : constkw ntype identifier{ PRINTLN("CONST_VAR_DEC"); }
              ;

CONST_VAR_INIT : CONST_VAR_DEC assign EXPRESSION { PRINTLN("CONST_VAR_INIT"); }
               ;

MOD_VAR_DEC : MODIFIER ntype identifier{ PRINTLN("MOD_VAR_DEC"); }
            ;

MOD_VAR_INIT : MOD_VAR_DEC assign EXPRESSION { PRINTLN("CONST_VAR_INIT"); }
             ;

UNMOD_VAR_DEC : ntype identifier{ PRINTLN("UNMOD_VAR_DEC"); }
              ;

UNMOD_VAR_INIT : UNMOD_VAR_DEC assign EXPRESSION { PRINTLN("UNMOD_VAR_INIT"); }
               ;

VAR_INIT : VAR_DEC assign EXPRESSION { PRINTLN("VAR_INIT"); }
         ;


MODIFIER : inkw { PRINTLN("MODIFIER1"); }
         | outkw { PRINTLN("MODIFIER2"); }
         | sharedkw { PRINTLN("MODIFIER3"); }
         | extkw { PRINTLN("MODIFIER4"); }
         ;

/* STATEMENTS */


STATEMENT : VAR_DEC { PRINTLN("STATEMENT1"); }
          | VAR_INIT semicolon { PRINTLN("STATEMENT2"); }
          | FUNC_CALL semicolon { PRINTLN("STATEMENT3"); }
          | ASSIGN semicolon { PRINTLN("STATEMENT4"); }
          | IF_ELSE { PRINTLN("STATEMENT5"); }
          | LOOP { PRINTLN("STATEMENT6"); }
          ;

STMNT_LIST : STMNT_LIST STATEMENT { PRINTLN("STMNT_LIST1"); }
           | STATEMENT { PRINTLN("STMNT_LIST2"); }
           ;

ASSIGN : identifier assign EXPRESSION { PRINTLN("ASSIGN"); }



/* CODE BLOCKS */


BLOCK : blockb STMNT_LIST blocke { PRINTLN("BLOCK1"); }
      | blockb blocke { PRINTLN("BLOCK2"); }
      ;


/* EXPRESSIONS */


EXPR_LIST : EXPR_LIST seperator EXPRESSION { PRINTLN("EXPR_LIST1"); }
          | EXPRESSION { PRINTLN("EXPR_LIST2"); }
          ;

EXPR_BLOCK : paramb EXPR_LIST parame { PRINTLN ("EXPR_BLOCK"); }
           ;

OPERAND : intl {  }
        | floatl { }
        | identifier { }
        | FUNC_CALL { }
        ;

EXPR_SPEC : paramb EXPR_LOW parame { PRINTLN("EXPR_SPEC"); }
          ;


EXPR_LOW : EXPR_MID { PRINTLN("EXPR_LOW1"); }
         | EXPR_LOW opl EXPR_MID { PRINTLN("EXPR_LOW2"); }
         | EXPR_LOW negation EXPR_MID { PRINTLN("EXPR_LOW3"); }
         | paramb EXPR_LOW parame { PRINTLN("EXPR_LOW4"); }
         ;

EXPR_MID : EXPR_HIGH { PRINTLN("EXPR_MID1"); }
         | EXPR_MID opm EXPR_HIGH { PRINTLN("EXPR_MID2"); }
         ;

EXPR_HIGH : EXPR_NEG { PRINTLN("EXPR_HIGH1"); }
          | EXPR_HIGH oph EXPR_NEG { PRINTLN("EXPR_HIGH2"); }
          | EXPR_SPEC { PRINTLN("EXPR_HIGH3"); }
          | EXPR_HIGH oph EXPR_SPEC{ PRINTLN("EXPR_HIGH"); }
          ;
  
EXPR_NEG : paramb negation OPERAND parame { PRINTLN("EXPR_NEG1"); }
         | OPERAND { PRINTLN("EXPR_NEG2") }
         ;


EXPRESSION : EXPR_LOW { PRINTLN("EXPRESSION1"); }
           ;



COND : EXPRESSION { PRINTLN("COND"); }
     ;


/* For loop */


FOR_UPDT : EXPRESSION { PRINTLN("FOR_UPDT"); }
         ;

FOR_INIT : UNMOD_VAR_DEC { PRINTLN("FOR_INIT"); }
         | UNMOD_VAR_INIT { PRINTLN("FOR_INIT"); }
         | ASSIGN semicolon { PRINTLN("FOR_INIT"); }
         ;

FOR_HEAD : paramb FOR_INIT COND semicolon FOR_UPDT parame { PRINTLN("FOR_HEAD1"); }
         | paramb semicolon COND semicolon FOR_UPDT parame { PRINTLN("FOR_HEAD1"); }
         | paramb FOR_INIT semicolon FOR_UPDT parame { PRINTLN("FOR_HEAD1"); }
         | paramb FOR_INIT COND semicolon parame { PRINTLN("FOR_HEAD1"); }
         | paramb FOR_INIT semicolon parame { PRINTLN("FOR_HEAD1"); }
         | paramb semicolon COND semicolon parame { PRINTLN("FOR_HEAD1"); } 
         | paramb semicolon semicolon FOR_UPDT parame { PRINTLN("FOR_HEAD1"); }
         | paramb semicolon semicolon parame { PRINTLN("FOR_HEAD1"); }
         ;

FOR_LOOP : forkw FOR_HEAD BLOCK { PRINTLN("FOR_LOOP"); }
    	 | forkw FOR_HEAD STATEMENT { PRINTLN("FOR_LOOP)"); }
         ;


/* While loop */


WHILE_HEAD : paramb COND parame { PRINTLN("WHILE_HEAD"); }
           ;

WHILE_LOOP : whilekw WHILE_HEAD BLOCK { PRINTLN("WHILE_LOOP1"); }
           | whilekw WHILE_HEAD STATEMENT { PRINTLN("WHILE_LOOP2"); }
           ;

/* If else */

IF_HEAD : paramb COND parame { PRINTLN("IF_HEAD"); }
        ;

IF : ifkw IF_HEAD BLOCK { PRINTLN("IF1"); }
   | ifkw IF_HEAD STATEMENT { PRINTLN("IF2"); }
   ;

ELSE : elsekw BLOCK { PRINTLN("ELSE1"); }
     | elsekw STATEMENT { PRINTLN("ELSE2"); }
     ;

IF_ELSE : IF ELSE { PRINTLN("IF_ELSE1"); }
        | IF { PRINTLN("IF_ELSE2"); }
        ;


/* Misc */

LOOP : FOR_LOOP { PRINTLN("LOOP1"); }
     | WHILE_LOOP { PRINTLN("LOOP2"); }
     ;

GLOB_STMNT : VAR_DEC { PRINTLN("GLOB_STMNT1"); }
           | FUNC_DEF { PRINTLN("GLOB_STMNT2"); }
           ; 

GLOB_LIST : GLOB_STMNT { PRINTLN("GLOB_LIST1"); }
          | GLOB_LIST GLOB_STMNT { PRINTLN("GLOB_LIST2"); }
          ;

GLOB : GLOB_LIST {  }
     ;
%%




int yyerror(char* msg){
    fprintf(stderr, "Error(%s) in line %i\n", msg, yylineno);
    return 1;
}
