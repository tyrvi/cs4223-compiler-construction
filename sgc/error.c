/*
*  Thais Minet
*  CS 4223
*  error.c
*/

#include <stdio.h>
#include <string.h>
#include "requires.h"
#include "y.tab.h"
#include "error.h"
#include "symboltable.h"

void duplicate_variable(char *var) {
    char errmsg[100];
    sprintf(errmsg, "duplicate variable '%s'", var);
    yyerror(errmsg);
}

void undeclared_variable(char *var) {
    char errmsg[100];
    sprintf(errmsg, "undeclared variable '%s'", var);
    yyerror(errmsg);    
}

void invalid_array_size(char *var) {
    char errmsg[100];
    sprintf(errmsg, "invalid array size '%s'", var);
    yyerror(errmsg);
}

void invalid_var_type(char *var, int exptype) {
    char errmsg[100];
    char *exp;
    char *ref;
    
    if (exptype == REAL_TYPE) {
        exp = "REAL";
        ref = "INTEGER";            
    }
    else {
        exp = "INTEGER";
        ref = "REAL";
    }
    sprintf(errmsg, "invalid variable type '%s' expected %s recieved %s", var, exp, ref);
    yyerror(errmsg);
}

void invalid_var_ref(char *var, int exptype) {
    char errmsg[100];
    char *exp;
    char *ref;
    
    if (exptype == ARRAY) {
        exp = "ARRAY";
        ref = "SCALAR";
    }
    else {
        exp = "SCALAR";
        ref = "ARRAY";
    }
    sprintf(errmsg, "invalid variable reference '%s' expected %s received %s", var, exp, ref);
    yyerror(errmsg);
}

void yyerror(char *errmsg) {
    fprintf(stderr, "%s: ERROR: %s on line %d\n", infile, errmsg, yylineno);
}
