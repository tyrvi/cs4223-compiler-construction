#include <stdlib.h>
#include <stdio.h>
#include "requires.h"
#include "ast.h"
#include "y.tab.h"

ast* new_ast(int nodetype) {
    ast *a = malloc(sizeof(ast));
    
    a->nodetype = nodetype;
    a->l = NULL;
    a->r = NULL;
    a->next = NULL;
    a->unary = NULL;
    a->n = 0;
    a->f = 0.0f;

    return a;
}

ast* new_int(int val) {
    ast *a = new_ast(INT_CONST);
    a->n = val;

    return a;
}

ast* new_float(float val) {
    ast *a = new_ast(REAL_CONST);
    a->f = val;

    return a;
}

ast* new_string(char *str) {

    ast *a = new_ast(STRING);
    a->str = str;

    return a;
}

ast* new_var(symbol *s) {
    ast *a = new_ast(VARIABLE);
    a->s = s;

    return a;
}

void free_ast(ast *a) {
    if (a) {

        free_ast(a->l);
        free_ast(a->r);
        free_ast(a->next);

        if (a->unary)
            free_ast(a->unary);
        
        free(a);        
    }
}
