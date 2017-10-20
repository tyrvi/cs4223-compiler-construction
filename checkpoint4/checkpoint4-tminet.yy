/*
* ========================================================================
* 
* Thais Minet
* CS 4223 Checkpoint #4
* checkpoint4-tminet.yy
* 10/3/17
* 
* ========================================================================
*/

%{
    #include <stdio.h>
    #include <stdlib.h>
%}

%token    MAIN
%token    END_STMT
%token    END
%token    DATA
%token    COLON
%token    REAL
%token    INTEGER
%token    VARIABLE
%token    LBRACKET
%token    RBRACKET
%token    INT_CONST
%token    COMMA
%token    ALGORITHM
// tokens not used in data section
%token    IF
%token    ELSE
%token    WHILE
%token    COUNTING
%token    UPWARD
%token    DOWNWARD
%token    TO
%token    EXIT
%token    PRINT
%token    READ
%token    REAL_CONST
%token    CHAR_STRING_CONST
%token    ASSIGNMENT
%token    AND
%token    OR
%token    NOT
%token    LESS
%token    LESS_EQ
%token    GREATER
%token    GREATER_EQ
%token    EQUAL
%token    NOT_EQ
%token    ADD
%token    SUB
%token    MUL
%token    DIV
%token    MOD
%token    LPAREN
%token    RPAREN
%token    BANG
%token    TRASH

%%
prgm            : routine
                ;

routine         : MAIN END_STMT data algorithm END MAIN END_STMT
                ;
                
data            : DATA COLON declarationList
                | DATA COLON
                ;
                
declarationList : declaration END_STMT declarationList
                | declaration END_STMT
                ;

declaration     : dataType COLON variableList
                ;

dataType        : REAL
                | INTEGER
                ;

variableList    : VARIABLE COMMA variableList
                | VARIABLE LBRACKET INT_CONST RBRACKET COMMA variableList
                | VARIABLE
                | VARIABLE LBRACKET INT_CONST RBRACKET
                ;

algorithm       : ALGORITHM COLON
                ;

%%

int yyerror() {
    printf("Called yyerror()\n");
    return 0;
}
