/*
* ========================================================================
* 
* Thais Minet
* 11/8/17
* CS 4223 Exam #2
* parser.c
* 
* ========================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

#define DEBUG 0

int token;

int yylex();
int parse(void);

void match(int exptok);
void parse_error(char *errmsg);

void prgm(void);
void data(void);
void declarationlist(void);
void declaration(void);
void datatype(void);
void variablelist(void);
void algorithm(void);


int parse() {
    token = yylex();
    prgm();

    return 0;
}

void parse_error(char *errmsg) {
    printf("Error: %s\n", errmsg);

    exit(0);
}

void match(int exptok) {
    if (DEBUG) printf("*** match(%d, %d)\n", exptok, token);
    
    if (exptok == token)
        token = yylex();
    else
        parse_error("parsing failed with error #1 unexpected token");
}

void prgm() {
    if (DEBUG) printf("*** prgm()\n");
    
    match(MAIN);
    match(END_STMT);    
    data();
    algorithm();
    match(END);
    match(MAIN);
    match(END_STMT);    
    match(0); // ensure no tokens after end main;
}

void data() {
    if (DEBUG) printf("*** data()\n");
    
    match(DATA);
    match(COLON);
    declarationlist();
}

void declarationlist() {
    if (DEBUG) printf("*** declarationlist()\n");
    int i = 0;    
    while (token != ALGORITHM) {
        declaration();
        match(END_STMT);
    }
}

void declaration() {
    if (DEBUG) printf("*** declaration()\n");
    
    datatype();
    match(COLON);
    variablelist();
}

void datatype() {
    if (DEBUG) printf("*** datatype()\n");
    
    if (token == INTEGER)
        match(INTEGER);
    else if (token == REAL)
        match(REAL);
    else
        parse_error("parsing failed with error #2 invalid data type");        
}

void variablelist() {
    if (DEBUG) printf("*** variablelist()\n");

    do {
        match(VARIABLE);
        if (token == LBRACKET) {
            match(LBRACKET);
            match(INT_CONST);
            match(RBRACKET);
        }
        if (token == COMMA) {
            match(COMMA);
            if (token == END_STMT)
                parse_error("parsing failed with error #3");
        }
    } while (token != END_STMT);
}

void algorithm() {
    if (DEBUG) printf("*** algorithm()\n");
    match(ALGORITHM);
    match(COLON);
}
