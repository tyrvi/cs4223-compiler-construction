/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 23 "parser.yy" /* yacc.c:1909  */

    #include "symboltable.h"
    #include "ast.h"

    extern char* yytext;
    extern int yylineno;    

    int datatype;
    int addr;    

#line 55 "y.tab.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    MAIN = 258,
    END_STMT = 259,
    END = 260,
    DATA = 261,
    WHILE = 262,
    ALGORITHM = 263,
    REAL = 264,
    INTEGER = 265,
    COUNTING = 266,
    UPWARD = 267,
    DOWNWARD = 268,
    TO = 269,
    EXIT = 270,
    PRINT = 271,
    READ = 272,
    IF = 273,
    ELSE = 274,
    ASSIGNMENT = 275,
    ADD = 276,
    SUB = 277,
    MUL = 278,
    DIV = 279,
    MOD = 280,
    AND = 281,
    OR = 282,
    NOT = 283,
    LT = 284,
    LTE = 285,
    GT = 286,
    GTE = 287,
    EQ = 288,
    NEQ = 289,
    VARIABLE = 290,
    STRING = 291,
    INT_CONST = 292,
    REAL_CONST = 293,
    COMMA = 294,
    COLON = 295,
    LPAREN = 296,
    RPAREN = 297,
    LBRACKET = 298,
    RBRACKET = 299,
    BANG = 300,
    TRASH = 301
  };
#endif
/* Tokens.  */
#define MAIN 258
#define END_STMT 259
#define END 260
#define DATA 261
#define WHILE 262
#define ALGORITHM 263
#define REAL 264
#define INTEGER 265
#define COUNTING 266
#define UPWARD 267
#define DOWNWARD 268
#define TO 269
#define EXIT 270
#define PRINT 271
#define READ 272
#define IF 273
#define ELSE 274
#define ASSIGNMENT 275
#define ADD 276
#define SUB 277
#define MUL 278
#define DIV 279
#define MOD 280
#define AND 281
#define OR 282
#define NOT 283
#define LT 284
#define LTE 285
#define GT 286
#define GTE 287
#define EQ 288
#define NEQ 289
#define VARIABLE 290
#define STRING 291
#define INT_CONST 292
#define REAL_CONST 293
#define COMMA 294
#define COLON 295
#define LPAREN 296
#define RPAREN 297
#define LBRACKET 298
#define RBRACKET 299
#define BANG 300
#define TRASH 301

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 35 "parser.yy" /* yacc.c:1909  */

    char *sval;
    int ival;
    float fval;
    ast *a;

#line 166 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
