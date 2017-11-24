/*
* ========================================================================
* 
* Thais Minet
* CS 4223 Checkpoint #5
* parser.yy
* 10/3/17
* 
* ========================================================================
*/

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "hashtable.h"
    int datatype;
    int addr;
%}

%union {
    char *sval;
    int ival;
}

%token        MAIN
%token        END_STMT
%token        END
%token        DATA
%token        COLON
%token        REAL
%token        INTEGER
%token <sval> VARIABLE
%token        LBRACKET
%token        RBRACKET
%token <ival> INT_CONST
%token        COMMA
%token        ALGORITHM
%token        IF
%token        ELSE
%token        WHILE
%token        COUNTING
%token        UPWARD
%token        DOWNWARD
%token        TO
%token        EXIT
%token        PRINT
%token        READ
%token        REAL_CONST
%token        CHAR_STRING_CONST
%token        ASSIGNMENT
%token        AND
%token        OR
%token        NOT
%token        LESS
%token        LESS_EQ
%token        GREATER
%token        GREATER_EQ
%token        EQUAL
%token        NOT_EQ
%token        ADD
%token        SUB
%token        MUL
%token        DIV
%token        MOD
%token        LPAREN
%token        RPAREN
%token        BANG
%token        TRASH

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

dataType        : INTEGER { datatype = 0; }
                | REAL { datatype = 1; }
                ;

variableList    : VARIABLE COMMA variableList
                                        {
                                            if (insert($1, datatype, 0, addr, 1) == -1)
                                                printf("Error: duplicate variable '%s' not inserted\n", $1);
                                            addr += 1;    
                                        }
                | VARIABLE LBRACKET INT_CONST RBRACKET COMMA variableList
                                        {
                                            if (insert($1, datatype, 1, addr, $3) == -1)
                                                printf("Error: duplicate variable '%s' not inserted\n", $1);
    
                                            addr += $3;
                                        }
                | VARIABLE
                                        {
                                            if (insert($1, datatype, 0, addr, 1) == -1)
                                                printf("Error: duplicate variable '%s' not inserted\n", $1);
                                            addr += 1;
                                        }
                | VARIABLE LBRACKET INT_CONST RBRACKET
                                        {
                                            if (insert($1, datatype, 1, addr, $3) == -1)
                                                printf("Error: duplicate variable '%s' not inserted\n", $1);
                                            addr += $3;
                                        }
                ;

algorithm       : ALGORITHM COLON
                ;

%%

int yyerror() {
    printf("Called yyerror()\n");
    return 0;
}
