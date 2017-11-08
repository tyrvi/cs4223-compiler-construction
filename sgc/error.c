#include <stdio.h>
#include <string.h>
#include "y.tab.h"
#include "error.h"

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

void yyerror(char *errmsg) {
    fprintf(stderr, "%s: ERROR: %s on line %d\n", infile, errmsg, yylineno);
}
