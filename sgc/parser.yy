/*
*  Thais Minet
*  CS 4223
*  parser.yy
*/

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "requires.h"
    #include "error.h"
    
    int yylex(void);
    int yyparse(void);
    void yyerror(char *errmsg);   
    
%}

%union {
    char *sval;
    int ival;
    float fval;
    ast *a;
}

// reserved
%token        MAIN
%token        END_STMT
%token        END
%token        DATA
%token        WHILE
%token        ALGORITHM
%token        REAL
%token        INTEGER
%token        COUNTING
%token        UPWARD
%token        DOWNWARD
%token        TO
%token        EXIT
%token        PRINT
%token        READ
%token        IF
%token        ELSE
%token        ASSIGNMENT

// arithmetic operators
%token        ADD
%token        SUB
%token        MUL
%token        DIV
%token        MOD

// boolean operators
%token        AND
%token        OR
%token        NOT

// comparison operators
%token        LT
%token        LTE
%token        GT
%token        GTE
%token        EQ
%token        NEQ

// literal
%token <sval> VARIABLE
%token <sval> STRING
%token <ival> INT_CONST
%token <fval> REAL_CONST

// other
%token        COMMA
%token        COLON
%token        LPAREN
%token        RPAREN
%token        LBRACKET
%token        RBRACKET
%token        BANG
%token        TRASH

 // type declarations
%type <a> algorithm
%type <a> stmtList
%type <a> stmt
%type <a> assignment
%type <a> print
%type <a> exit
%type <a> read
%type <a> loop
%type <a> range
%type <a> conditional
%type <a> printList
%type <a> printItem
%type <a> expr
%type <a> comp
%type <a> arithmetic
%type <a> term
%type <a> factor
%type <a> atom
%type <a> variable
%type <a> constant

%%
prgm            : MAIN END_STMT data algorithm END MAIN END_STMT { root = $4; }
                ;

// data section and symbol table                
data            : DATA COLON declarationList
                | DATA COLON
                ;
                
declarationList : declaration END_STMT declarationList
                | declaration END_STMT
                ;

declaration     : dataType COLON variableList
                ;

dataType        : INTEGER { datatype = INT_TYPE; }
                | REAL { datatype = REAL_TYPE; }
                ;

variableList    : VARIABLE COMMA variableList
                  {                      
                      if (insert($1, datatype, SCALAR, addr, 1) == -1) {
                          duplicate_variable($1);
                          YYERROR;
                      }
                      else
                          addr += 1;                      
                  }
                | VARIABLE LBRACKET INT_CONST RBRACKET COMMA variableList
                  {
                      if ($3 < 1) {
                          invalid_array_size($1);
                          YYERROR;
                      }
                      
                      if (insert($1, datatype, ARRAY, addr, $3) == -1) {
                          duplicate_variable($1);
                          YYERROR;
                      }
                      else
                          addr += $3;
                  }
                | VARIABLE
                  {
                      if (insert($1, datatype, SCALAR, addr, 1) == -1) {
                          duplicate_variable($1);
                          YYERROR;
                      }
                      else
                          addr += 1;
                  }
                | VARIABLE LBRACKET INT_CONST RBRACKET
                  {
                      if ($3 < 1) {
                          invalid_array_size($1);
                          YYERROR;
                      }
                      
                      if (insert($1, datatype, ARRAY, addr, $3) == -1) {
                          duplicate_variable($1);
                          YYERROR;
                      }
                      else
                          addr += $3;
                  }
                ;

// algorithm section
algorithm       : ALGORITHM COLON stmtList { $$ = $3;}
                | ALGORITHM COLON { $$ = NULL; }
                ;

stmtList        : stmt END_STMT stmtList
                  {
                      $1->next = $3;
                      $$ = $1;
                  }
                | stmt END_STMT { $$ = $1; }
                ;

stmt            : assignment { $$ = $1; }
                | print { $$ = $1; }
                | exit { $$ = $1; }
                | read { $$ = $1; }
                | conditional { $$ = $1; }
                | loop { $$ = $1; }
                ;

loop            : WHILE expr END_STMT stmtList END WHILE
                  {
                      ast *a = new_ast(WHILE);
                      a->unary = $2;
                      a->l = $4;
                      $$ = a;
                  }
                | COUNTING variable range END_STMT stmtList END COUNTING
                  {
                      if ($2->s->datatype == REAL_TYPE) {
                          // error counting variable must be an integer
                          invalid_var_type($2->s->name, INT_TYPE);
                          YYERROR;
                      }
                      
                      char loopname[100];
                      sprintf(loopname, "_loop%d", loopnum);
                      insert(loopname, INT_TYPE, SCALAR, addr, 1);
                      addr++;
                      loopnum++;
                                                                  
                      ast *a = new_ast(COUNTING);
                      a->unary = $2; // variable
                      a->l = $3; // range
                      a->r = $5; // stmtList
                      $$ = a;                                            
                  }
                ;

range           : UPWARD expr TO expr
                  {
                      ast *a = new_ast(UPWARD);
                      a->l = $2;
                      a->r = $4;
                      $$ = a;
                  }
                | DOWNWARD expr TO expr
                  {
                      ast *a = new_ast(DOWNWARD);
                      a->l = $2;
                      a->r = $4;
                      $$ = a;
                  }
                ;

conditional     : IF expr END_STMT stmtList END IF
                  {
                      ast *a = new_ast(IF);
                      a->unary = $2;
                      a->l = $4;
                      $$ = a;
                  }
                | IF expr END_STMT stmtList ELSE END_STMT stmtList END IF
                  {
                      ast *a = new_ast(ELSE);
                      a->unary = $2;
                      a->l = $4;
                      a->r = $7;
                      $$ = a;
                  }
                ;

print           : PRINT printList
                  {
                      ast *a = new_ast(PRINT);
                      a->r = $2;
                      $$ = a;
                  }
                ;

printList       : printItem COMMA printList
                  {
                      $1->next = $3;
                      $$ = $1;
                  }
                | printItem { $$ = $1; }
                ;

printItem       : expr { $$ = $1; }
                | STRING { $$ = new_string($1); }
                | BANG { $$ = new_ast(BANG); }
                ;

exit            : EXIT { $$ = new_ast(EXIT); }
                ;

read            : READ variable
                  {
                      ast *a = new_ast(READ);
                      a->unary = $2;
                      $$ = a;
                  }
                ;

assignment      : variable ASSIGNMENT expr
                  {
                      ast *a = new_ast(ASSIGNMENT);
                      a->l = $1;
                      a->r = $3;
                      $$ = a;
                  }
                ;

expr            : expr AND comp
                  {
                      ast *a = new_ast(AND);
                      a->l = $1;
                      a->r = $3;
                      $$ = a;
                  }
                | expr OR comp
                  {
                      ast *a = new_ast(OR);
                      a->l = $1;
                      a->r = $3;
                      $$ = a;
                  }
                | NOT expr
                {
                      ast *a = new_ast(NOT);
                      a->unary = $2;
                      $$ = a;
                }
                | comp { $$ = $1; }
                ;

comp            : comp LT arithmetic
                  {
                      ast *a = new_ast(LT);
                      a->l = $1;
                      a->r = $3;
                      $$ = a;
                  }
                | comp LTE arithmetic
                  {
                      ast *a = new_ast(LTE);
                      a->l = $1;
                      a->r = $3;
                      $$ = a;
                  }

                | comp GT arithmetic
                  {
                      ast *a = new_ast(GT);
                      a->l = $1;
                      a->r = $3;
                      $$ = a;
                  }
                | comp GTE arithmetic
                  {
                      ast *a = new_ast(GTE);
                      a->l = $1;
                      a->r = $3;
                      $$ = a;
                  }
                | comp EQ arithmetic
                  {
                      ast *a = new_ast(EQ);
                      a->l = $1;
                      a->r = $3;
                      $$ = a;
                  }
                | comp NEQ arithmetic
                  {
                      ast *a = new_ast(NEQ);
                      a->l = $1;
                      a->r = $3;
                      $$ = a;
                  }
                | arithmetic { $$ = $1; }
                ;

arithmetic      : arithmetic ADD term
                  {
                      ast *a = new_ast(ADD);
                      a->l = $1;
                      a->r = $3;
                      $$ = a;
                  }
                | arithmetic SUB term
                  {
                      ast *a = new_ast(SUB);
                      a->l = $1;
                      a->r = $3;
                      $$ = a;
                  }
                | term { $$ = $1; }
                ;

term            : term MUL factor
                  {
                      ast *a = new_ast(MUL);
                      a->l = $1;
                      a->r = $3;
                      $$ = a;
                  }
                | term DIV factor
                  {
                      ast *a = new_ast(DIV);
                      a->l = $1;
                      a->r = $3;
                      $$ = a;
                  }
                | term MOD factor
                  {
                      ast *a = new_ast(MOD);
                      a->l = $1;
                      a->r = $3;
                      $$ = a;
                  }
                | factor { $$ = $1; }
                ;

factor          : LPAREN expr RPAREN { $$ = $2; }
                | SUB factor
                  {
                      ast *a = new_ast(SUB);
                      a->unary = $2;
                      $$ = a;
                  }
                | ADD factor
                  {
                      ast *a = new_ast(ADD);
                      a->unary = $2;
                      $$ = a; 
                  }
                | atom { $$ = $1; }
                ;

atom            : variable { $$ = $1; }
                | constant { $$ = $1; }
                ;

variable        : VARIABLE
                  {
                      symbol *s;
                      s = (symbol *) malloc(sizeof(symbol));
                      s = search($1);
                      
                      if (!s) {
                          undeclared_variable($1);
                          YYERROR;
                      }
                      
                      if (s->type == ARRAY) {
                          invalid_var_ref($1, SCALAR);
                          YYERROR;
                      }

                      ast *a = new_var(s);
                      $$ = a;
                  }
                | VARIABLE LBRACKET expr RBRACKET
                  {
                      symbol *s;
                      s = (symbol *) malloc(sizeof(symbol));
                      s = search($1);
                      
                      if (!s) {
                          undeclared_variable($1);
                          YYERROR;
                      }
                      
                      if (s->type == SCALAR) {
                          invalid_var_ref($1, ARRAY);
                          YYERROR;
                      }

                      ast *a = new_var(s);
                      a->unary = $3;
                      $$ = a;
                  }
                ;

constant        : INT_CONST
                  {
                      $$ = new_int($1);
                  }
                | REAL_CONST
                  {
                      $$ = new_float($1);
                  }
                ;
%%

int datatype = UNKOWN_TYPE;
int addr = 0;
int loopnum = 0;
