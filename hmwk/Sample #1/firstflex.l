%{ 

/*
 * ========================================================================
 * 
 * firstflex.l -- In-class example of lex input file.
 * 
 * Programmer --- Bryan Crawley
 * 
 * ========================================================================
 */

#include <stdio.h>

%}

%%

[\t ]+                      { }

caught|threw|saw            { printf("Verb: %s\n", yytext); }

boy|house|ball              { printf("Noun: %s\n", yytext); }

[a-zA-Z]+                   { printf("????: %s\n", yytext); }

.|\n                        { }

%%

int main()
{
    yylex();
    return 0;
}
