/*
* ========================================================================
* 
* Thais Minet
* 11/8/17
* CS 4223 Exam #2
* scanner.l 
* 
* ========================================================================
*/

%{
    #define DEBUG 0
    #include <stdio.h>
    #include "parser.h"
%}

%%

[mM][aA][iI][nN]                                          {
                                                              if (DEBUG) printf("MAIN ");
                                                              return(MAIN);
                                                          }

[dD][aA][tT][aA]                                          {
                                                              if (DEBUG) printf("DATA ");
                                                              return(DATA);
                                                          }

[aA][lL][gG][oO][rR][iI][tT][hH][mM]                      {
                                                              if (DEBUG) printf("ALGORITHM ");
                                                              return(ALGORITHM);
                                                          }

[eE][nN][dD]                                              {
                                                              if (DEBUG) printf("END ");
                                                              return(END);
                                                          }

[rR][eE][aA][lL]                                          {
                                                              if (DEBUG) printf("REAL ");
                                                              return(REAL);
                                                          }

[iI][nN][tT][eE][gG][eE][rR]                              {
                                                              if (DEBUG) printf("INTEGER ");
                                                              return(INTEGER);
                                                          }

[a-zA-Z][a-zA-Z0-9]*                                      {
                                                              if (DEBUG) printf("VARIABLE ");
                                                              return(VARIABLE);
                                                          }

[0-9]+                                                    {
                                                              if (DEBUG) printf("INT_CONST ");
                                                              return(INT_CONST);
                                                          }

":"                                                       {
                                                              if (DEBUG) printf("COLON ");
                                                              return(COLON);
                                                          }

"["                                                       {
                                                              if (DEBUG) printf("LBRACKET ");
                                                              return(LBRACKET);
                                                          }

"]"                                                       {
                                                              if (DEBUG) printf("RBRACKET ");
                                                              return(RBRACKET);
                                                          }

";"                                                       {
                                                              if (DEBUG) printf("END_STMT ");
                                                              return(END_STMT);
                                                          }

","                                                       {
                                                              if (DEBUG) printf("COMMA ");
                                                              return(COMMA);
                                                          }

\n                                                        {
                                                              if (DEBUG) printf("NEWLINE ");
                                                              /*NEWLINE*/
                                                          }

[\t ]+                                                    {
                                                              if (DEBUG) printf("WHITESPACE ");
                                                              /*WHITESPACE*/
                                                          }

#[^\n]*                                                   {
                                                              if (DEBUG) printf("COMMENT ");
                                                              /*COMMENT*/
                                                          }

.                                                         {
                                                              if (DEBUG) printf("TRASH ");
                                                              /*TRASH*/
                                                              return TRASH;
                                                          }

%%
