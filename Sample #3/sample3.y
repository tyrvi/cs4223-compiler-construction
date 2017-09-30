%{

/*
 * ========================================================================
 * 
 * sample3.y ---- In-class example of yacc input file; parses arithmetic
 *                expressions and constructs a list of expression trees.
 * 
 * Programmer --- Bryan Crawley
 * 
 * ========================================================================
 */

#include "sample3.h"
#include <stdio.h>

struct listnode *list;

%}

%union {
   int ival;
   struct listnode *listpoint;
   struct expression *exppoint;
}

%token        PLUS
%token        MINUS
%token        MULTIPLY
%token        DIVIDE
%token <ival> NUMBER
%token        LPAREN
%token        RPAREN
%token        NEWLINE

%type  <listpoint> explist
%type  <exppoint>  exp
%type  <exppoint>  term
%type  <exppoint>  factor
%type  <exppoint>  unit

%%
prog    : explist
                  { 
                    list = $1;
                  }
        ;

explist : exp NEWLINE explist
                  { 
                    $$ = malloc(sizeof(struct listnode));
                    $$->link = $3;
                    $$->exp = $1;
                  }
        | exp NEWLINE
                  {
                    $$ = malloc(sizeof(struct listnode));
                    $$->link = NULL;
                    $$->exp = $1;
                  }
        ;

exp     : exp PLUS term
                  {
                    $$ = malloc(sizeof(struct expression));
                    $$->kind = EK_OP;
                    $$->operator = OP_ADD;
                    $$->l_operand = $1;
                    $$->r_operand = $3;
                  }
        | exp MINUS term
                  {
                    $$ = malloc(sizeof(struct expression));
                    $$->kind = EK_OP;
                    $$->operator = OP_SUB;
                    $$->l_operand = $1;
                    $$->r_operand = $3;
                  }
        | term
                  {
                    $$ = $1;
                  }
        ;

term    : term MULTIPLY factor
                  {
                    $$ = malloc(sizeof(struct expression));
                    $$->kind = EK_OP;
                    $$->operator = OP_MUL;
                    $$->l_operand = $1;
                    $$->r_operand = $3;
                  }

        | term DIVIDE factor
                  {
                    $$ = malloc(sizeof(struct expression));
                    $$->kind = EK_OP;
                    $$->operator = OP_DIV;
                    $$->l_operand = $1;
                    $$->r_operand = $3;
                  }
        | factor
                  {
                    $$ = $1;
                  }
        ;

factor  : MINUS unit
                  {
                    $$ = malloc(sizeof(struct expression));
                    $$->kind = EK_OP;
                    $$->operator = OP_UMIN;
                    $$->r_operand = $2;
                  }

        | unit
                  {
                    $$ = $1;
                  }
        ;

unit    : LPAREN exp RPAREN
                  {
                    $$ = $2;
                  }
        | NUMBER
                  {
                    $$ = malloc(sizeof(struct expression));
                    $$->kind = EK_INT;
                    $$->value = $1;
                  }
        ;
%%

int yyerror()
{
   printf("Called yyerror()\n");
   return;
}
