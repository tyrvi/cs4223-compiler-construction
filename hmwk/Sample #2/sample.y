%{

/*
 * ========================================================================
 * 
 * sample.y ----- In-class example of yacc input file; This project parses
 *                boolean expressions
 * 
 * Programmer --- Bryan Crawley
 * 
 * ========================================================================
 */

#include <stdio.h>

%}

%union {
   char *sval;
}

%token        AND
%token        OR
%token        NOT
%token <sval> VARIABLE
%token        LPAREN
%token        RPAREN
%token        NEWLINE

%%
prog    : explist
        ;

explist : explist exp NEWLINE {printf("\n");}
	| exp NEWLINE {printf("\n");}
	;

exp     : exp AND term {printf("& ");}
	| exp OR term {printf("| ");}
	| term
	;

term    : NOT factor {printf("~ ");}
	| factor
	;

factor  : LPAREN exp RPAREN
        | VARIABLE {printf("%s ",$1);}
	;

%%

int yyerror() {
   printf("Called yyerror()\n");
   return;
}
