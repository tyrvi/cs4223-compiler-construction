%{ 

/*
 * ========================================================================
 * 
 * sample.l ----- In-class example of lex input file; This project parses
 *                boolean expressions
 * 
 * Programmer --- Bryan Crawley
 * 
 * ========================================================================
 */

#define  DEBUG 0
#include "y.tab.h"
#include <stdio.h>
#include <string.h>

%}

%%
"&"                     {
                          if (DEBUG) printf("and ");
                          return(AND);
                        } 

"|"                     {
                          if (DEBUG) printf("or ");
                          return(OR);
                        }

"~"                     {
                          if (DEBUG) printf("not ");
                          return(NOT);
                        }

"("                     { 
                          if (DEBUG) printf("lparen ");
                          return(LPAREN);
                        }

")"                     {
                          if (DEBUG) printf("rparen ");
                          return(RPAREN);
                        }

[A-Za-z][A-Za-z0-9]*    {
                          if (DEBUG) printf("variable(%s) ", yytext);
                          yylval.sval = strdup(yytext);
                          return(VARIABLE);
                     	}

\n                   	{
                          if (DEBUG) printf("newline\n\n");
                          return(NEWLINE);
                        }

[\t ]+                  {
                          if (DEBUG) printf("whitespace ");
                        }
%%

