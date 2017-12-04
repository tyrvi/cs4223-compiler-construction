/*
*  Thais Minet
*  CS 4223
*  scanner.l
*/

%{
    #define DEBUG 0
    #include "requires.h"
    #include "y.tab.h"
    #include <stdio.h>
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

[iI][fF]                                                  {
                                                              if (DEBUG) printf("IF ");
                                                              return(IF);
                                                          }

[eE][lL][sS][eE]                                          {
                                                              if (DEBUG) printf("ELSE ");
                                                              return(ELSE);
                                                          }

[wW][hH][iI][lL][eE]                                      {
                                                              if (DEBUG) printf("WHILE ");
                                                              return(WHILE);
                                                          }

[cC][oO][uU][nN][tT][iI][nN][gG]                          {
                                                              if (DEBUG) printf("COUNTING ");
                                                              return(COUNTING);
                                                          }

[uU][pP][wW][aA][rR][dD]                                  {
                                                              if (DEBUG) printf("UPWARD ");
                                                              return(UPWARD);
                                                          }

[dD][oO][wW][nN][wW][aA][rR][dD]                          {
                                                              if (DEBUG) printf("DOWNWARD ");
                                                              return(DOWNWARD);
                                                          }

[tT][oO]                                                  {
                                                              if (DEBUG) printf("TO ");
                                                              return(TO);
                                                          }

[eE][xX][iI][tT]                                          {
                                                              if (DEBUG) printf("EXIT ");
                                                              return(EXIT);
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

[pP][rR][iI][nN][tT]                                      {
                                                              if (DEBUG) printf("PRINT ");
                                                              return(PRINT);
                                                          }

[rR][eE][aA][dD]                                          {
                                                              if (DEBUG) printf("READ ");
                                                              return(READ);
                                                          }

[a-zA-Z][a-zA-Z0-9]*                                      {
                                                              if (DEBUG) printf("VARIABLE ");
                                                              yylval.sval = strdup(yytext);
                                                              return(VARIABLE);
                                                          }

[0-9]+                                                    {
                                                              if (DEBUG) printf("INT_CONST ");
                                                              yylval.ival = atoi(yytext);
                                                              return(INT_CONST);
                                                          }


[-+]?(([0-9]+\.[0-9]+)|([0-9]+(\.[0-9]+)?[eE][-+][0-9]+)) {
                                                              if (DEBUG) printf("REAL_CONST ");
                                                              yylval.fval = atof(yytext);
                                                              return(REAL_CONST);
                                                          }

\"([^"\n]|(\"\"))*["\n]                                   {
                                                              if (DEBUG) printf("STRING ");
                                                              char *yycpy = yytext;
                                                              yycpy++;
                                                              int len = strlen(yycpy);
                                                              yylval.sval = strdup(yytext);
                                                              strncpy(yylval.sval, yycpy, len-1);
                                                              yylval.sval[len-1] = '\0';
                                                              
                                                              return(STRING);
                                                          }

":"                                                       {
                                                              if (DEBUG) printf("COLON ");
                                                              return(COLON);
                                                          }

":="                                                      {
                                                              if (DEBUG) printf("ASSIGNMENT ");
                                                              return(ASSIGNMENT);
                                                          }

"&"                                                       {
                                                              if (DEBUG) printf("AND ");
                                                              return(AND);
                                                          }

"|"                                                       {
                                                              if (DEBUG) printf("OR ");
                                                              return(OR);
                                                          }

"~"                                                       {
                                                              if (DEBUG) printf("NOT ");
                                                              return(NOT);
                                                          }

"<"                                                       {
                                                              if (DEBUG) printf("LT ");
                                                              return(LT);
                                                          }

"<="                                                      {
                                                              if (DEBUG) printf("LTE ");
                                                              return(LTE);
                                                          }

">"                                                       {
                                                              if (DEBUG) printf("GT ");
                                                              return(GT);
                                                          }

">="                                                      {
                                                              if (DEBUG) printf("GTE ");
                                                              return(GTE);
                                                          }

"="                                                       {
                                                              if (DEBUG) printf("EQ ");
                                                              return(EQ);
                                                          }

"<>"                                                      {
                                                              if (DEBUG) printf("NEQ ");
                                                              return(NEQ);
                                                          }

"+"                                                       {
                                                              if (DEBUG) printf("ADD ");
                                                              return(ADD);
                                                          }

"-"                                                       {
                                                              if (DEBUG) printf("SUB ");
                                                              return(SUB);
                                                          }

"*"                                                       {
                                                              if (DEBUG) printf("MUL ");
                                                              return(MUL);
                                                          }

"/"                                                       {
                                                              if (DEBUG) printf("DIV ");
                                                              return(DIV);
                                                          }

"%"                                                       {
                                                              if (DEBUG) printf("MOD ");
                                                              return(MOD);
                                                          }

"("                                                       {
                                                              if (DEBUG) printf("LPAREN ");
                                                              return(LPAREN);
                                                          }

")"                                                       {
                                                              if (DEBUG) printf("RPAREN ");
                                                              return(RPAREN);
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

"!"                                                       {
                                                              if (DEBUG) printf("BANG ");
                                                              return(BANG);
                                                          }

","                                                       {
                                                              if (DEBUG) printf("COMMA ");
                                                              return(COMMA);
                                                          }

\n                                                        {
                                                              if (DEBUG) printf("NEWLINE ");
                                                              /*NEWLINE*/
                                                              yylineno++;
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
