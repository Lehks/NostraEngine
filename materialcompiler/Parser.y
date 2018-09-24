%defines
%error-verbose


%{
#include "MaterialParser.h"
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
int yyerror(char*);
extern int yylineno;
#ifdef NOE_DEBUG
    printf("Debug\n");
#endif

#ifdef NOE_DEBUG
#   define NOE_DBG_PRINT(ARG) printf(ARG);
#   define NOE_DBG_PRINTLN(ARG) printf("Reduced: %s\n", ARG);
#else
#   define NOE_DBG_PRINT(ARG) 
#   define NOE_DBG_PRINTLN(ARG) 
#endif

char* syntaxErrorMsg;
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
%token<i> vectype
%token<i> mattype
%token<s> oph
%token<s> opm
%token<s> opl
%token<s> opc
%token<s> opcb
%token<s> opnot
%token<s> negation
%token assign
%token<s> opassign
%token<i> intl
%token<f> floatl
%token<b> booll
%token sizeop
%token blockb
%token blocke
%token paramb
%token parame
%token arrayb
%token arraye
%token<s> identifier
%token voidt
%token seperator
%token accop
%token returnkw




%%
S : GLOB { printf("%s\n", "ACCEPTED"); }
  ;


 /* Function */


PARAM_DEF : TYPE identifier { NOE_DBG_PRINTLN("PARAM_DEF"); }
          ;

PARAM_LIST : PARAM_LIST seperator PARAM_DEF { NOE_DBG_PRINTLN("PARAM_LIST1"); }
           | PARAM_DEF { NOE_DBG_PRINTLN("PARAM_LIST2"); }
           ;

PARAM_BLOCK : paramb PARAM_LIST parame { NOE_DBG_PRINTLN("PARAM_BLOCK"); }
            | paramb parame { NOE_DBG_PRINTLN("PARAM_BLOCK"); }
            ;

FUNC_DEF : TYPE identifier PARAM_BLOCK BLOCK { NOE_DBG_PRINTLN("FUNC_DEF1"); }
         | voidt identifier PARAM_BLOCK BLOCK {NOE_DBG_PRINTLN("FUNC_DEF2"); }
         ;

FUNC_CALL : identifier EXPR_BLOCK {NOE_DBG_PRINTLN("FUNC_CALL"); }
          ;


/* Variable */


VAR_DEC : UNMOD_VAR_DEC semicolon { NOE_DBG_PRINTLN("VAR_DEC1"); }
        | CONST_VAR_DEC semicolon { NOE_DBG_PRINTLN("VAR_DEC2"); }
        | MOD_VAR_DEC   semicolon { NOE_DBG_PRINTLN("VAR_DEC3"); }
        ;

CONST_VAR_DEC : constkw TYPE identifier{ NOE_DBG_PRINTLN("CONST_VAR_DEC"); }
              ;

CONST_VAR_INIT : CONST_VAR_DEC assign EXPRESSION { NOE_DBG_PRINTLN("CONST_VAR_INIT"); }
               ;

MOD_VAR_DEC : MODIFIER TYPE identifier{ NOE_DBG_PRINTLN("MOD_VAR_DEC"); }
            ;

MOD_VAR_INIT : MOD_VAR_DEC assign EXPRESSION { NOE_DBG_PRINTLN("CONST_VAR_INIT"); }
             ;

UNMOD_VAR_DEC : TYPE identifier{ NOE_DBG_PRINTLN("UNMOD_VAR_DEC"); }
              ;

UNMOD_VAR_INIT : UNMOD_VAR_DEC assign EXPRESSION { NOE_DBG_PRINTLN("UNMOD_VAR_INIT"); }
               ;

VAR_INIT : VAR_DEC assign EXPRESSION { NOE_DBG_PRINTLN("VAR_INIT"); }
         ;

VAR_LIST : UNMOD_VAR_DEC semicolon { NOE_DBG_PRINTLN("VAR_LIST1"); }
         | VAR_LIST UNMOD_VAR_DEC semicolon { NOE_DBG_PRINTLN("VAR_LIST2"); }
         ;

MODIFIER : inkw { NOE_DBG_PRINTLN("MODIFIER1"); }
         | outkw { NOE_DBG_PRINTLN("MODIFIER2"); }
         | sharedkw { NOE_DBG_PRINTLN("MODIFIER3"); }
         | extkw { NOE_DBG_PRINTLN("MODIFIER4"); }
         ;


/* Array */


ARRAY_OP : arrayb EXPR_LOW arraye { NOE_DBG_PRINTLN("ARRAY_OP1"); }
         | ARRAY_OP arrayb EXPR_LOW arraye { NOE_DBG_PRINTLN("ARRAY_OP2"); }
         ;

SIZE_OP_LIST : arrayb arraye { NOE_DBG_PRINTLN("SIZE_OP_LIST1"); }
             | SIZE_OP_LIST arrayb arraye { NOE_DBG_PRINTLN("SIZE_OP_LIST2"); }
             ;

SIZE_OP : arrayb sizeop arraye { NOE_DBG_PRINTLN("SIZEOP1"); }
        | SIZE_OP_LIST arrayb sizeop arraye { NOE_DBG_PRINTLN("SIZEOP2"); }
        ;

ARR_SIZE : identifier SIZE_OP { NOE_DBG_PRINTLN("ARR_SIZE"); }

UNMOD_ARR_DEC : UNMOD_VAR_DEC ARRAY_OP { NOE_DBG_PRINTLN("UNMOD_ARR_DEC1"); }
              | UNMOD_VAR_DEC arrayb arraye { NOE_DBG_PRINTLN("UNMOD_ARR_DEC2"); }
              ;

UNMOD_ARR_INIT_I : UNMOD_VAR_DEC arrayb arraye assign TYPE ARRAY_OP{ NOE_DBG_PRINTLN("UNMOD_ARR_INIT_I"); }
                 ;

MOD_ARR_DEC : MOD_VAR_DEC ARRAY_OP{ NOE_DBG_PRINTLN("MOD_ARR_DEC"); }
            | MOD_VAR_DEC arrayb arraye{ NOE_DBG_PRINTLN("MOD_ARR_DEC"); }
            ;

MOD_ARR_INIT_I : MOD_VAR_DEC arrayb arraye assign TYPE ARRAY_OP{ NOE_DBG_PRINTLN("MOD_ARR_INIT_I"); }
               ;

ARR_INIT : identifier assign TYPE ARRAY_OP { NOE_DBG_PRINTLN("ARR_INIT"); }
         ;

ARR_DEC : UNMOD_ARR_DEC semicolon{ NOE_DBG_PRINTLN("ARR_DEC1"); }
        | MOD_ARR_DEC semicolon { NOE_DBG_PRINTLN("ARR_DEC2"); }
        ;

ARR_ACC : identifier ARRAY_OP{ NOE_DBG_PRINTLN("ARR_ACC"); }
        ;


/* Statement */


STATEMENT : CONST_VAR_DEC semicolon { NOE_DBG_PRINTLN("STATEMENT1"); }
          | UNMOD_VAR_DEC semicolon { NOE_DBG_PRINTLN("STATEMENT2"); }
          | CONST_VAR_INIT semicolon { NOE_DBG_PRINTLN("STATEMENT3"); }
          | UNMOD_VAR_INIT semicolon { NOE_DBG_PRINTLN("STATEMENT4"); }
          | FUNC_CALL semicolon { NOE_DBG_PRINTLN("STATEMENT5"); }
          | ASSIGN semicolon { NOE_DBG_PRINTLN("STATEMENT6"); }
          | IF_ELSE { NOE_DBG_PRINTLN("STATEMENT7"); }
          | LOOP { NOE_DBG_PRINTLN("STATEMENT8"); }
          | UNMOD_ARR_DEC semicolon{NOE_DBG_PRINTLN("STATEMENT9"); }
          | ARR_INIT semicolon {NOE_DBG_PRINTLN("STATEMENT10"); }
          | UNMOD_ARR_INIT_I semicolon {NOE_DBG_PRINTLN("STATEMENT11"); }
          | STRUCT_ASSIGN semicolon {NOE_DBG_PRINTLN("STATEMENT12"); }
          | RETURN semicolon {NOE_DBG_PRINTLN("STATEMENT13"); }
          | OP_ASSIGN semicolon {NOE_DBG_PRINTLN("STATEMENT14"); }
          ;

STMNT_LIST : STMNT_LIST STATEMENT { NOE_DBG_PRINTLN("STMNT_LIST1"); }
           | STATEMENT { NOE_DBG_PRINTLN("STMNT_LIST2"); }
           ;

ASSIGN : identifier assign EXPRESSION { NOE_DBG_PRINTLN("ASSIGN"); }
       ;



/* Code block */


BLOCK : blockb STMNT_LIST blocke { NOE_DBG_PRINTLN("BLOCK1"); }
      | blockb blocke { NOE_DBG_PRINTLN("BLOCK2"); }
      ;

BLOCK_DEC : blockb 
          ;


/* Expression */


EXPR_LIST : EXPR_LIST seperator EXPRESSION { NOE_DBG_PRINTLN("EXPR_LIST1"); }
          | EXPRESSION { NOE_DBG_PRINTLN("EXPR_LIST2"); }
          ;

EXPR_BLOCK : paramb EXPR_LIST parame { NOE_DBG_PRINTLN ("EXPR_BLOCK"); }
           ;

OPERAND : intl {  }
        | floatl { }
        | identifier { }
        | FUNC_CALL { }
        | ARR_ACC { }
        | STRUCT_ACC { }
        | ARR_SIZE { }
        ;

EXPR_COND : EXPR_COND_B { NOE_DBG_PRINTLN("EPXR_COND1"); } /* && ||  */
          | EXPR_NOT { NOE_DBG_PRINTLN("EXPR_COND2")}
          | EXPR_COND opc EXPR_COND_B { NOE_DBG_PRINTLN("EXPR_COND3"); }
          | EXPR_COND opc EXPR_NOT { NOE_DBG_PRINTLN("EXPR_COND4"); }
          ;



EXPR_SPECIAL_COND : paramb EXPR_COND parame
                  ;

EXPR_COND_B : EXPR_LOW opcb EXPR_LOW { NOE_DBG_PRINTLN("EXPR_COND_B1"); } /* == != < >  */
            | EXPR_LOW { NOE_DBG_PRINTLN("EXPR_COND_B2"); }
            | EXPR_SPECIAL_COND opcb EXPR_SPECIAL_COND { NOE_DBG_PRINTLN("EXPR_COND_B3"); }
            | EXPR_SPECIAL_COND opcb EXPR_LOW { NOE_DBG_PRINTLN("EXPR_COND_B3"); }
            | EXPR_LOW opcb EXPR_SPECIAL_COND { NOE_DBG_PRINTLN("EXPR_COND_B4"); }
            | EXPR_LOW opcb EXPR_NOT { NOE_DBG_PRINTLN("EXPR_COND_B5"); }
            | EXPR_SPECIAL_COND opcb EXPR_NOT {NOE_DBG_PRINTLN("EXPR_COND_B6"); }
            | EXPR_NOT opcb EXPR_LOW { NOE_DBG_PRINTLN("EXPR_COND_B7"); }
            | EXPR_NOT opcb EXPR_SPECIAL_COND { NOE_DBG_PRINTLN("EXPR_COND_B8")}
            ;

EXPR_NOT : EXPR_LOW { NOE_DBG_PRINTLN("EXPR_NEG2"); }
         | paramb opnot EXPR_SPEC parame {NOE_DBG_PRINTLN("EXPR_NEG3"); }
         ;

EXPR_NEG : paramb negation OPERAND parame { NOE_DBG_PRINTLN("EXPR_NEG1"); }
         | OPERAND { NOE_DBG_PRINTLN("EXPR_NEG2"); }
         | paramb negation EXPR_SPEC parame{NOE_DBG_PRINTLN("EXPR_NEG3"); }
         ;


EXPR_LOW : EXPR_MID { NOE_DBG_PRINTLN("EXPR_LOW1"); }
         | EXPR_LOW opl EXPR_MID { NOE_DBG_PRINTLN("EXPR_LOW2"); }
         | EXPR_LOW negation EXPR_MID { NOE_DBG_PRINTLN("EXPR_LOW3"); }
         | paramb EXPR_LOW parame { NOE_DBG_PRINTLN("EXPR_LOW4"); }
         ;

EXPR_MID : EXPR_HIGH { NOE_DBG_PRINTLN("EXPR_MID1"); }
         | EXPR_MID opm EXPR_HIGH { NOE_DBG_PRINTLN("EXPR_MID2"); }
         ;

EXPR_HIGH : EXPR_NEG { NOE_DBG_PRINTLN("EXPR_HIGH1"); }
          | EXPR_HIGH oph EXPR_NEG { NOE_DBG_PRINTLN("EXPR_HIGH2"); }
          | EXPR_SPEC { NOE_DBG_PRINTLN("EXPR_HIGH3"); }
          | EXPR_HIGH oph EXPR_SPEC{ NOE_DBG_PRINTLN("EXPR_HIGH"); }
          ;

EXPR_SPEC : paramb EXPR_COND parame { NOE_DBG_PRINTLN("EXPR_SPEC"); }
          ;
  

OP_ASSIGN : identifier opassign EXPRESSION { NOE_DBG_PRINTLN("OP_ASSIGN1"); }
          | STRUCT_ACC opassign EXPRESSION { NOE_DBG_PRINTLN("OP_ASSIGN2"); }
          ;

EXPRESSION : EXPR_COND { NOE_DBG_PRINTLN("EXPRESSION1"); }
           ;

COND : EXPRESSION { NOE_DBG_PRINTLN("COND"); }
     ;


/* For loop */


FOR_UPDT : EXPRESSION { NOE_DBG_PRINTLN("FOR_UPDT"); }
         ;

FOR_INIT : UNMOD_VAR_DEC { NOE_DBG_PRINTLN("FOR_INIT"); }
         | UNMOD_VAR_INIT { NOE_DBG_PRINTLN("FOR_INIT"); }
         | ASSIGN semicolon { NOE_DBG_PRINTLN("FOR_INIT"); }
         ;

FOR_HEAD : paramb FOR_INIT COND semicolon FOR_UPDT parame { NOE_DBG_PRINTLN("FOR_HEAD1"); }
         | paramb semicolon COND semicolon FOR_UPDT parame { NOE_DBG_PRINTLN("FOR_HEAD1"); }
         | paramb FOR_INIT semicolon FOR_UPDT parame { NOE_DBG_PRINTLN("FOR_HEAD1"); }
         | paramb FOR_INIT COND semicolon parame { NOE_DBG_PRINTLN("FOR_HEAD1"); }
         | paramb FOR_INIT semicolon parame { NOE_DBG_PRINTLN("FOR_HEAD1"); }
         | paramb semicolon COND semicolon parame { NOE_DBG_PRINTLN("FOR_HEAD1"); } 
         | paramb semicolon semicolon FOR_UPDT parame { NOE_DBG_PRINTLN("FOR_HEAD1"); }
         | paramb semicolon semicolon parame { NOE_DBG_PRINTLN("FOR_HEAD1"); }
         ;

FOR_LOOP : forkw FOR_HEAD BLOCK { NOE_DBG_PRINTLN("FOR_LOOP"); }
    	 | forkw FOR_HEAD STATEMENT { NOE_DBG_PRINTLN("FOR_LOOP)"); }
         ;


/* While loop */


WHILE_HEAD : paramb COND parame { NOE_DBG_PRINTLN("WHILE_HEAD"); }
           ;

WHILE_LOOP : whilekw WHILE_HEAD BLOCK { NOE_DBG_PRINTLN("WHILE_LOOP1"); }
           | whilekw WHILE_HEAD STATEMENT { NOE_DBG_PRINTLN("WHILE_LOOP2"); }
           ;


/* If else */


IF_HEAD : paramb COND parame { NOE_DBG_PRINTLN("IF_HEAD"); }
        ;

IF : ifkw IF_HEAD BLOCK { NOE_DBG_PRINTLN("IF1"); }
   | ifkw IF_HEAD STATEMENT { NOE_DBG_PRINTLN("IF2"); }
   ;

ELSE : elsekw BLOCK { NOE_DBG_PRINTLN("ELSE1"); }
     | elsekw STATEMENT { NOE_DBG_PRINTLN("ELSE2"); }
     ;

IF_ELSE : IF ELSE { NOE_DBG_PRINTLN("IF_ELSE1"); }
        | IF { NOE_DBG_PRINTLN("IF_ELSE2"); }
        ;


/* Structs */


STRUCT_DEF : structkw identifier blockb VAR_LIST blocke { NOE_DBG_PRINTLN("STRUCT_DEC"); }
           ;

STRUCT_ACC : identifier accop identifier{ NOE_DBG_PRINTLN("STRUCT_ACC1"); }
           | STRUCT_ACC accop identifier { NOE_DBG_PRINTLN("STRUCT_ACC2"); }
           ;

STRUCT_ASSIGN : STRUCT_ACC assign EXPRESSION{ NOE_DBG_PRINTLN("STRUCT_ASSIGN"); }
              ;


/* Misc */


RETURN : returnkw EXPRESSION{ NOE_DBG_PRINTLN("RETURN"); }
       ;

TYPE : ntype { NOE_DBG_PRINTLN("TYPE1"); }
     | mattype { NOE_DBG_PRINTLN("TYPE2"); }
     | vectype { NOE_DBG_PRINTLN("TYPE3"); }
     | USR_TYPE { NOE_DBG_PRINTLN("Type4"); }
     ;

USR_TYPE : identifier { NOE_DBG_PRINTLN("USR_TYPE"); }
         ;

LOOP : FOR_LOOP { NOE_DBG_PRINTLN("LOOP1"); }
     | WHILE_LOOP { NOE_DBG_PRINTLN("LOOP2"); }
     ;

GLOB_STMNT : VAR_DEC { NOE_DBG_PRINTLN("GLOB_STMNT1"); }
           | FUNC_DEF { NOE_DBG_PRINTLN("GLOB_STMNT2"); }
           | STRUCT_DEF { NOE_DBG_PRINTLN("GLOB_STMNT3"); }
           | ARR_DEC { NOE_DBG_PRINTLN("GLOB_STMNT4"); }
           ;

GLOB_LIST : GLOB_STMNT { NOE_DBG_PRINTLN("GLOB_LIST1"); }
          | GLOB_LIST GLOB_STMNT { NOE_DBG_PRINTLN("GLOB_LIST2"); }
          ;

GLOB : GLOB_LIST {  }
     ;


%%




int yyerror(char* incomingMsg){
    

    char* msg[1024];
    sprintf(msg, "(line %i): \0", yylineno);
    strcat(msg, incomingMsg);
    
    int lengthMsg = strlen(msg) + 2;

    if(syntaxErrorMsg == 0){
        syntaxErrorMsg = (char*) malloc(lengthMsg);
        strcpy(syntaxErrorMsg, msg);
        syntaxErrorMsg[lengthMsg - 2] = '|';
        syntaxErrorMsg[lengthMsg - 1] = 0;
    } else {
        int lengthNew = strlen(syntaxErrorMsg) + lengthMsg;
        char* newMsg = malloc(lengthNew * sizeof(char));
        strcpy(newMsg, syntaxErrorMsg);
        strcat(newMsg, msg);
        newMsg[lengthNew - 2] = '|';
        newMsg[lengthNew - 1] = 0;
        free(syntaxErrorMsg);
        syntaxErrorMsg = newMsg;
    }
    return 1;
}
