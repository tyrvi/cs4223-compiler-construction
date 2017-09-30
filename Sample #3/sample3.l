%{ 

/*
 * ========================================================================
 * 
 * sample3.l ---- In-class example of lex input file; scans for tokens in
 *                arithmetic expressions including +, -, *, /, and integer
 *                constants.
 * 
 * Programmer --- Bryan Crawley
 * 
 * ========================================================================
 */

#define  DEBUG 0
#include "y.tab.h"
#include <stdio.h>

%}

%%
"+"          {
               if (DEBUG) printf("PLUS ");
               return(PLUS);
             } 

"-"          {
               if (DEBUG) printf("MINUS ");
               return(MINUS);
             } 

"*"          {
               if (DEBUG) printf("MULTIPLY ");
               return(MULTIPLY);
             } 

"/"          {
               if (DEBUG) printf("DIVIDE ");
               return(DIVIDE);
             } 

"("          { 
               if (DEBUG) printf("lparen ");
               return(LPAREN);
             }

")"          {
               if (DEBUG) printf("rparen ");
               return(RPAREN);
             }

[0-9]+ 	     {
	       if (DEBUG) printf("NUMBER(%s) ", yytext);
               yylval.ival = atoi(yytext);
               return(NUMBER);
             }

\n           {
               if (DEBUG) printf("NEWLINE\n\n");
               return(NEWLINE);
             }

[\t ]+       {
               if (DEBUG) printf("WS ");
             }

.            {
               if (DEBUG) printf("IGNORE ");
             }
%%

