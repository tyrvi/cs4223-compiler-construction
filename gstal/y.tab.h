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

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    WHITE_SPACE = 258,
    END_LINE = 259,
    TRASH = 260,
    POSINT = 261,
    NEGINT = 262,
    POSFLOAT = 263,
    NEGFLOAT = 264,
    COMMENT = 265,
    ADD = 266,
    SUB = 267,
    MLT = 268,
    DIV = 269,
    EQL = 270,
    NEQ = 271,
    LTH = 272,
    LEQ = 273,
    GTH = 274,
    GEQ = 275,
    STO = 276,
    STM = 277,
    NEG = 278,
    LOD = 279,
    PTN = 280,
    PTC = 281,
    JPF = 282,
    PTL = 283,
    INP = 284,
    RET = 285,
    HLT = 286,
    ISP = 287,
    DSP = 288,
    LAA = 289,
    LRA = 290,
    JMP = 291,
    CAL = 292,
    PAR = 293,
    ADI = 294,
    ADF = 295,
    SBI = 296,
    SBF = 297,
    MLI = 298,
    MLF = 299,
    DVI = 300,
    DVF = 301,
    EQI = 302,
    EQF = 303,
    NEI = 304,
    NEF = 305,
    LTI = 306,
    LTF = 307,
    LEI = 308,
    LEF = 309,
    GTI = 310,
    GTF = 311,
    GEI = 312,
    GEF = 313,
    NGI = 314,
    NGF = 315,
    PTI = 316,
    PTF = 317,
    INI = 318,
    INF = 319,
    LLI = 320,
    LLF = 321,
    FTI = 322,
    ITF = 323,
    NOP = 324
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 32 "gst_parser.y" /* yacc.c:1909  */

   int opcode;
   int intval;
   float floatval;

#line 130 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
