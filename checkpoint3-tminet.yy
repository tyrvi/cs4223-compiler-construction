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

algorithm       : ALGORITHM COLON body
                | ALGORITHM COLON
                ;

body            : stmtList
                ;

stmtList        : stmt END_STMT stmtList
                | stmt END_STMT
                ;

stmt            : assignment
                | loop
                | conditional
                | print
                | read
                | exit
                ;

assignment      : variable ASSIGNMENT expression
                ;

loop            : whileLoop END_STMT body END WHILE
                | countingLoop END_STMT body END COUNTING
                ;

whileLoop       : WHILE expr

countingLoop    : COUNTING variable UPWARD expr TO expr
                | COUNTING variable DOWNWARD expr TO expr
                ;

conditional     : IF expr END_STMT body END IF
                | IF expr END_STMT body ELSE END_STMT body END IF
                ;

print           : PRINT printList
                ;

printList       : printItem COMMA printList
                | printItem
                ;

printItem       : expr
                | CHAR_STRING_CONST
                | CARRIAGE_RETURN
                ;

read            : READ variable
                ;

exit            : EXIT

expr            : expr AND comp
                | expr OR comp
                | NOT expr
                | comp
                ;

comp            : comp LESS arithmetic
                | comp LESS_EQ arithmetic
                | comp GREATER arithmetic
                | comp GREATER_EQ arithmetic
                | comp EQUAL arithmetic
                | comp NOT_EQ arithmetic
                | arithmetic
                ;

arithmetic      : arithmetic ADD term
                | arithmetic SUB term
                | term
                ;

term            : term MUL factor
                | term DIV factor
                | term MOD factor
                | factor
                ;

factor          : LPAREN expr RPAREN
                | SUB factor
                | ADD factor
                | atom
                ;

atom            : variable
                | constant
                ;

variable        : arrayVariable
                | VARIABLE
                ;

arrayVariable   : VARIABLE LBRACKET expr RBRACKET
                ;

constant        : INT_CONST
                | REAL_CONST
                ;
